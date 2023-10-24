using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;

namespace BuildMaster
{
    class Config
    {
        public void Load(string path)
        {
            if (!File.Exists(path))
                throw new Exception("Path for config file not found");

            XmlDocument xmlDocument = new XmlDocument();

            xmlDocument.Load(path);

            LoadSettings(xmlDocument);
            LoadTools(xmlDocument);
            LoadEntries(xmlDocument);

            BuildDestinationFoldersList();
        }



        private void LoadSettings(XmlDocument xmlDocument)
        {
            XmlNodeList settingsNodes = xmlDocument.SelectNodes("/BuildMaster/Settings/Setting");

            if (settingsNodes != null)
            {
                foreach (XmlNode settingNode in settingsNodes)
                {
                    string name = settingNode.Attributes["name"].Value;
                    string value = settingNode.Attributes["value"].Value;

                    m_settings[name.ToLower()] = value;
                }
            }
        }

        private void LoadTools(XmlDocument xmlDocument)
        {
            XmlNodeList toolsNodes = xmlDocument.SelectNodes("/BuildMaster/Tools/Tool");

            if (toolsNodes != null)
            {
                foreach (XmlNode toolNode in toolsNodes)
                {
                    string name = toolNode.Attributes["name"].Value;
                    string path = toolNode.Attributes["path"].Value;
                    string flags = toolNode.Attributes["flags"]?.Value ?? "";
                    string info = toolNode.Attributes["info"]?.Value ?? "";

                    m_toolInfos[name.ToLower()] = new ToolInfo(name, path, flags, info);
                }
            }
        }

        private void LoadEntries(XmlDocument xmlDocument)
        {
            XmlNodeList entriesNodes = xmlDocument.SelectNodes("/BuildMaster/Entries/Entry");

            if (entriesNodes != null)
            {
                foreach (XmlNode entryNode in entriesNodes)
                {
                    string toolName = entryNode.Attributes["tool"].Value;
                    string source = entryNode.Attributes["source"].Value;
                    string destination = entryNode.Attributes["destination"].Value;

                    m_entries.Add(new EntryInfo(toolName, source, destination));
                }
            }
        }

        // Settings
        Dictionary<string, string> m_settings = new Dictionary<string, string>();

        public string GetSetting(string name) 
        { 
            if (!m_settings.ContainsKey(name.ToLower()))
                throw new Exception("There is no value in the config file for " + name);

            return m_settings[name.ToLower()]; 
        }

        public string ProjectName { get { return GetSetting("ProjectName"); }}
        public string WorkingDirectory { get { return GetSetting("WorkingDirectory"); }}
        public string MakefilePath { get { return GetSetting("makefile.Path"); }}

        // Tools
        public class ToolInfo
        {
            public ToolInfo(string name, 
                            string path,
                            string flags,
                            string info)
            {
                Name = name.ToLower();
                Path = path.ToLower();
                Flags = flags;
                Info = info;
            }

            public string Name { get; }
            public string Path { get; }
            public string Flags { get; }
            public string Info { get; }
        }

        private Dictionary<string, ToolInfo> m_toolInfos = new Dictionary<string, ToolInfo>();
        public IEnumerable<ToolInfo> ToolInfos => m_toolInfos.Values;

        public ToolInfo GetTool(string toolName) => m_toolInfos[toolName.ToLower()];


        // Entries
        public class EntryInfo
        {
            public EntryInfo(string toolName, 
                             string source, 
                             string destination)
            {
                ToolName = toolName.ToLower();
                SourcePath = source.ToLower();
                DestinationPath = destination.ToLower();
            }

            public string ToolName { get; }
            public string SourcePath { get; }
            public string DestinationPath { get; }
        }

        private List<EntryInfo> m_entries = new List<EntryInfo>();
        public IEnumerable<EntryInfo> Entries => m_entries;

        // Destinations List

        private List<string> m_destinationFolders;
        public IEnumerable<string> DestinationFolders => m_destinationFolders;

        private void BuildDestinationFoldersList()
        {
            var uniqueDirectories = new HashSet<string>();

            foreach (var entry in m_entries)
            {
                string directory = entry.DestinationPath;

                if (Path.HasExtension(directory))
                    directory = Path.GetDirectoryName(directory);

                uniqueDirectories.Add(directory);
            }

            m_destinationFolders = uniqueDirectories.ToList();
        }
    }

}
