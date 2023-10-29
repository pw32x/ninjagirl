using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace BuildMaster
{
    class CompilationSettings
    {
        public CompilationSettings(string devkitSmsPath, string outFolder)
        {
            DevkitSmsPath = Utils.EnsureTrailingSlash(devkitSmsPath);
            OutFolder = Utils.EnsureTrailingSlash(outFolder);

            //IHX2SMS_Path = DevkitSmsPath + "/ihx2sms/Windows/ihx2sms.exe";
            IHX2SMS_Path = "ihx2sms.exe";

            SmsLib_BasePath = DevkitSmsPath + "/SMSlib";
            SmsLib_IncludePath = SmsLib_BasePath + "/src";
            SmsLib_LibraryPath = SmsLib_BasePath + "/SMSlib.lib";

            PeepRules_Path = SmsLib_BasePath + "/src/peep-rules.txt";
            CRT0_Path = DevkitSmsPath + "/crt0/crt0_sms.rel";

            PsgLib_BasePath = DevkitSmsPath + "/PSGlib/";
            PsgLib_IncludePath = PsgLib_BasePath + "/src";
            PsgLib_LibraryPath = PsgLib_BasePath + "/PSGlib.rel";
        }

        public string DevkitSmsPath { get; }
        public string OutFolder { get; }

        public string IHX2SMS_Path { get; }
        public string SmsLib_BasePath { get; }
        public string SmsLib_IncludePath { get; }
        public string SmsLib_LibraryPath { get; }

        public string PeepRules_Path { get; }
        public string CRT0_Path { get; }

        public string PsgLib_BasePath { get; }
        public string PsgLib_IncludePath { get; }
        public string PsgLib_LibraryPath { get; }

        public string Compiler => "sdcc";
        public string BuildCompilerFlags(IEnumerable<string> includeFolders)
        {
            var sb = new StringBuilder();

            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag(Compiler);
            addFlag("-mz80");
            addFlag("--peep-file " + PeepRules_Path);

            addFlag("-I" + SmsLib_IncludePath);
            addFlag("-I" + PsgLib_IncludePath);

            foreach (var includeFolder in includeFolders)
            {
                addFlag("-I" + includeFolder);
            }

            return sb.ToString();
        }

        public string GetLinkerFlags()
        {
            var sb = new StringBuilder();
            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag("-mz80");
            addFlag("--no-std-crt0");
            addFlag("--data-loc 0xC000");

            addFlag(SmsLib_LibraryPath);
            addFlag(CRT0_Path);
            addFlag(PsgLib_LibraryPath);

            return sb.ToString();
        }
    }

    class Config
    {
        public CompilationSettings CompilationSettings;

        public void Load(string path)
        {
            if (!File.Exists(path))
                throw new Exception("Path for config file not found");

            XmlDocument xmlDocument = new XmlDocument();

            xmlDocument.Load(path);

            LoadSettings(xmlDocument);
            LoadTools(xmlDocument);
            LoadToolJobs(xmlDocument);

            LoadIncludes(xmlDocument);
            LoadSourceSets(xmlDocument);

            BuildToolDestinationFoldersList();


            CompilationSettings = new CompilationSettings(GetSetting("devkitSmsPath"),
                                                            GetSetting("outFolder"));
        }

        public string BuildLinkCommand()
        {
            var sb = new StringBuilder();

            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag(CompilationSettings.Compiler);
            addFlag("-o");
            addFlag(CompilationSettings.OutFolder + ProjectName + ".ihx");
            addFlag(CompilationSettings.GetLinkerFlags());

            return sb.ToString();
        }

        public string BuildIHXToSMSCommand()
        {
            var sb = new StringBuilder();

            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag(CompilationSettings.IHX2SMS_Path);
            addFlag(CompilationSettings.OutFolder + ProjectName + ".ihx");
            addFlag(CompilationSettings.OutFolder + ProjectName + ".sms");

            return sb.ToString();
        }

        public IEnumerable<string> BuildSourceDestinationFolders()
        {
            var sourceDestinationFolders = new List<string>();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourcePath in sourceSet.SourcePaths)
                {
                    sourceDestinationFolders.Add(CompilationSettings.OutFolder + sourcePath);
                }
            }

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                sourceDestinationFolders.Add(CompilationSettings.OutFolder + toolDestinationFolder);
            }

            return sourceDestinationFolders;
        }

        public class SourceToBuild
        {
            public SourceToBuild(string path,
                                 string destination,
                                 string flags,
                                 string bank = "")
            {
                Path = path;
                Destination = destination;
                Bank = bank;
                Flags = flags;
            }

            public string Path { get; }
            public string Destination { get; }
            public string Bank { get; }
            public string Flags { get; }
        }

        public IEnumerable<SourceToBuild> BuildListOfSourceFilesToCompile()
        {
            List<SourceToBuild> sourceFilesToBuild = new List<SourceToBuild>();

            string[] sourceFileExtensions = { ".c", ".s" };

            var compilerFlags = CompilationSettings.BuildCompilerFlags(m_includePaths);

            var currentDirectory = Directory.GetCurrentDirectory();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourcePath in sourceSet.SourcePaths)
                {
                    if (Directory.Exists(sourcePath))
                    {
                        DirectoryInfo directoryInfo = new DirectoryInfo(sourcePath);
                        FileInfo[] files = directoryInfo.GetFiles();

                        var filteredFiles = files.Where(file => sourceFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                        foreach (var filteredFile in filteredFiles)
                        {
                            string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                            sourceFilesToBuild.Add(new SourceToBuild(relativePath,
                                                                     CompilationSettings.OutFolder + Path.GetDirectoryName(relativePath) + "/" + Path.GetFileNameWithoutExtension(relativePath) + ".rel",
                                                                     compilerFlags,
                                                                     sourceSet.Bank));
                        }
                    }
                }
            }

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                if (Directory.Exists(toolDestinationFolder))
                {
                    DirectoryInfo directoryInfo = new DirectoryInfo(toolDestinationFolder);
                    FileInfo[] files = directoryInfo.GetFiles();

                    var filteredFiles = files.Where(file => sourceFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                    foreach (var filteredFile in filteredFiles)
                    {
                        string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                        sourceFilesToBuild.Add(new SourceToBuild(filteredFile.FullName,
                                                                 CompilationSettings.OutFolder + Path.GetDirectoryName(relativePath) + "/" + Path.GetFileNameWithoutExtension(relativePath) + ".rel",
                                                                 compilerFlags
                                                                 /*, sourceSet.Bank)*/
                                                                 ));
                    }
                }
            }

            return sourceFilesToBuild;
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

        // Tools
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

                    m_toolInfos[name.ToLower()] = new ToolInfo(name,
                                                               path,
                                                               flags,
                                                               info);
                }
            }
        }

        private void LoadToolJobs(XmlDocument xmlDocument)
        {
            XmlNodeList toolJobNodes = xmlDocument.SelectNodes("/BuildMaster/ToolJobs/ToolJob");

            if (toolJobNodes != null)
            {
                foreach (XmlNode toolJob in toolJobNodes)
                {
                    string toolName = toolJob.Attributes["tool"].Value;
                    string source = toolJob.Attributes["source"].Value;
                    string destination = toolJob.Attributes["destination"].Value;
                    uint.TryParse(toolJob.Attributes["bank"]?.Value, out uint bankNumber);

                    m_toolJobs.Add(new ToolJobInfo(toolName,
                                                   Utils.EnsureTrailingSlash(source),
                                                   Utils.EnsureTrailingSlash(destination),
                                                   bankNumber));
                }
            }
        }

        // Include paths
        HashSet<string> m_includePaths = new HashSet<string>();
        private void LoadIncludes(XmlDocument xmlDocument)
        {
            XmlNodeList includeNodes = xmlDocument.SelectNodes("/BuildMaster/Include");

            if (includeNodes != null)
            {
                foreach (XmlNode includeNode in includeNodes)
                {
                    string includePath = includeNode.Attributes["path"].Value;

                    m_includePaths.Add(Utils.EnsureTrailingSlash(includePath));
                }
            }
        }

        class SourceSet
        {
            public SourceSet(string bank = "")
            {
                Bank = bank;
            }

            public HashSet<string> SourcePaths { get; } = new HashSet<string>();
            public string Bank { get; }
        }

        HashSet<SourceSet> m_sourceSets = new HashSet<SourceSet>();
        private void LoadSourceSets(XmlDocument xmlDocument)
        {
            XmlNodeList sourceSetNodes = xmlDocument.SelectNodes("/BuildMaster/SourceSet");

            if (sourceSetNodes != null)
            {
                foreach (XmlNode sourceSetNode in sourceSetNodes)
                {
                    string bank = sourceSetNode.Attributes["bank"]?.Value ?? "";

                    var sourceSet = new SourceSet(bank);

                    foreach (XmlNode sourceNode in sourceSetNode)
                    {
                        string sourcePath = sourceNode.Attributes["path"].Value;
                        sourceSet.SourcePaths.Add(Utils.EnsureTrailingSlash(sourcePath));
                    }

                    m_sourceSets.Add(sourceSet);
                }
            }
        }

        // Source Sets

        // Settings
        Dictionary<string, string> m_settings = new Dictionary<string, string>();

        public string GetSetting(string name)
        {
            if (!m_settings.ContainsKey(name.ToLower()))
                throw new Exception("There is no value in the config file for " + name);

            return m_settings[name.ToLower()];
        }

        public string ProjectName { get { return GetSetting("ProjectName"); } }
        public string WorkingDirectory { get { return GetSetting("WorkingDirectory"); } }

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


        // Tool Jobs 
        public class ToolJobInfo
        {
            public ToolJobInfo(string toolName,
                             string source,
                             string destination,
                             uint bankNumber)
            {
                ToolName = toolName.ToLower();
                SourcePath = source.ToLower();
                DestinationPath = destination.ToLower();
                BankNumber = bankNumber;
            }

            public string ToolName { get; }
            public string SourcePath { get; }
            public string DestinationPath { get; }
            public uint BankNumber { get; }
        }

        private List<ToolJobInfo> m_toolJobs = new List<ToolJobInfo>();
        public IEnumerable<ToolJobInfo> ToolJobs => m_toolJobs;

        // Destinations List

        private List<string> m_toolDestinationFolders;
        public IEnumerable<string> ToolDestinationFolders => m_toolDestinationFolders;

        private void BuildToolDestinationFoldersList()
        {
            var uniqueDirectories = new HashSet<string>();

            foreach (var entry in m_toolJobs)
            {
                string directory = entry.DestinationPath;

                if (Path.HasExtension(directory))
                    directory = Path.GetDirectoryName(directory);

                uniqueDirectories.Add(directory);
            }

            m_toolDestinationFolders = uniqueDirectories.ToList();
        }


    }

}
