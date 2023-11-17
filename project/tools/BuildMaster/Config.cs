using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace BuildMaster
{
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

        public string BuildLinkCommand(IEnumerable<uint> usedBankNumbers)
        {
            var sb = new StringBuilder();

            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag(CompilationSettings.Compiler);
            addFlag("-o");
            addFlag(CompilationSettings.OutFolder + ProjectName + ".ihx");
            addFlag(CompilationSettings.GetLinkerFlags(usedBankNumbers));

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
            var sourceDestinationFolders = new HashSet<string>();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourcePath in sourceSet.SourceFolders)
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

        public IEnumerable<string> GetToolExportFolders()
        {
            var toolExportFolders = new HashSet<string>();

            foreach (var toolDestinationFolder in m_toolDestinationFolders)
            {
                toolExportFolders.Add(toolDestinationFolder);
            }

            return toolExportFolders;
        }

        public class SourceToBuild
        {
            public SourceToBuild(string filename,
                                 string destination,
                                 string flags,
                                 string bank = "")
            {
                Filename = Path.Combine(filename.Split('/'));
                Destination = Path.Combine(destination.Split('/'));
                Bank = bank;

                m_bankNumber = 0;
                uint.TryParse(bank, out m_bankNumber);

                Flags = flags;

                if (m_bankNumber != 0)
                    Flags += " --constseg BANK" + Bank;
            }

            public string Filename { get; }
            public string Destination { get; }
            public string Bank { get; }

            private uint m_bankNumber;
            public uint BankNumber => m_bankNumber;

            public string Flags { get; }

            public override int GetHashCode()
            {
                return Filename.GetHashCode();
            }

            public override bool Equals(object obj)
            {
                return obj is SourceToBuild other && Filename == other.Filename;
            }
        }

        public IEnumerable<SourceToBuild> BuildListOfSourceFilesToCompile()
        {
            var sourceFilesToBuild = new HashSet<SourceToBuild>();

            string[] sourceFileExtensions = { ".c", ".s" };

            var baseCompilerFlags = CompilationSettings.BuildCompilerFlags(IncludePaths);

            var currentDirectory = Directory.GetCurrentDirectory();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourcePath in sourceSet.SourcePaths)
                {
                    if (Utils.IsFile(sourcePath))
                    {
                        string relativePath = Path.GetRelativePath(currentDirectory, sourcePath);

                        sourceFilesToBuild.Add(new SourceToBuild(relativePath,
                                               CompilationSettings.OutFolder + Path.GetDirectoryName(relativePath) + "/" + Path.GetFileNameWithoutExtension(relativePath) + ".rel",
                                               baseCompilerFlags,
                                               sourceSet.Bank));

                    }
                    else if (Utils.IsFileOrFileSpec(sourcePath))
                    {
                        var filenames = Utils.GetFilesFromWildcardPath(sourcePath);

                        foreach (var filename in filenames)
                        {
                            string relativePath = Path.GetRelativePath(currentDirectory, filename);

                            sourceFilesToBuild.Add(new SourceToBuild(relativePath,
                                                                     CompilationSettings.OutFolder + Path.GetDirectoryName(relativePath) + "/" + Path.GetFileNameWithoutExtension(relativePath) + ".rel",
                                                                     baseCompilerFlags,
                                                                     sourceSet.Bank));
                        }
                    }
                    else if (Directory.Exists(sourcePath))
                    {
                        DirectoryInfo directoryInfo = new DirectoryInfo(sourcePath);
                        FileInfo[] files = directoryInfo.GetFiles();

                        var filteredFiles = files.Where(file => sourceFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                        foreach (var filteredFile in filteredFiles)
                        {
                            string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                            sourceFilesToBuild.Add(new SourceToBuild(relativePath,
                                                                     CompilationSettings.OutFolder + Path.GetDirectoryName(relativePath) + "/" + Path.GetFileNameWithoutExtension(relativePath) + ".rel",
                                                                     baseCompilerFlags,
                                                                     sourceSet.Bank));
                        }
                    }
                }
            }

            return sourceFilesToBuild;
        }


        public IEnumerable<string> BuildListOfHeaderFiles()
        {
            var headerFiles = new HashSet<string>();

            string[] headerFileExtensions = { ".h" };

            var compilerFlags = CompilationSettings.BuildCompilerFlags(IncludePaths);

            var currentDirectory = Directory.GetCurrentDirectory();

            foreach (var sourceSet in m_sourceSets)
            {
                foreach (var sourceFolder in sourceSet.SourceFolders)
                {
                    if (Directory.Exists(sourceFolder))
                    {
                        DirectoryInfo directoryInfo = new DirectoryInfo(sourceFolder);
                        FileInfo[] files = directoryInfo.GetFiles();

                        var filteredFiles = files.Where(file => headerFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                        foreach (var filteredFile in filteredFiles)
                        {
                            string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                            headerFiles.Add(relativePath);
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

                    var filteredFiles = files.Where(file => headerFileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

                    foreach (var filteredFile in filteredFiles)
                    {
                        string relativePath = Path.GetRelativePath(currentDirectory, filteredFile.FullName);

                        headerFiles.Add(relativePath);
                    }
                }
            }

            return headerFiles;
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
                    string bank = toolJob.Attributes["bank"]?.Value;
                    uint.TryParse(bank, out uint bankNumber);

                    m_toolJobs.Add(new ToolJobInfo(toolName,
                                                   Utils.NormalizePath(source),
                                                   Utils.NormalizePath(destination),
                                                   bankNumber));

                    // create a source set for the tool job.
                    // the source set's source is the destination of the tool job.

                    var sourceSet = new SourceSet(bank);

                    if (Utils.IsFileOrFileSpec(destination))
                    {
                        sourceSet.SourceFolders.Add(Utils.GetPathFromFileOrFileSpec(destination));
                    }
                    else
                    {
                        source = Utils.NormalizePath(destination);
                        sourceSet.SourceFolders.Add(destination);
                    }

                    sourceSet.SourcePaths.Add(destination);

                    m_sourceSets.Add(sourceSet);
                }
            }
        }

        // Include paths
        public HashSet<string> IncludePaths { get; } = new HashSet<string>();
        private void LoadIncludes(XmlDocument xmlDocument)
        {
            XmlNodeList includeNodes = xmlDocument.SelectNodes("/BuildMaster/Include");

            if (includeNodes != null)
            {
                foreach (XmlNode includeNode in includeNodes)
                {
                    string includePath = includeNode.Attributes["path"].Value;

                    IncludePaths.Add(Utils.NormalizePath(includePath));
                }
            }
        }

        // Source Sets

        class SourceSet
        {
            public SourceSet(string bank = "")
            {
                Bank = bank;
            }

            public HashSet<string> SourcePaths { get; } = new HashSet<string>();
            public HashSet<string> SourceFolders { get; } = new HashSet<string>();
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

                        if (Utils.IsFileOrFileSpec(sourcePath))
                        {
                            sourceSet.SourceFolders.Add(Utils.GetPathFromFileOrFileSpec(sourcePath));
                        }
                        else
                        {
                            sourcePath = Utils.NormalizePath(sourcePath);
                            sourceSet.SourceFolders.Add(sourcePath);
                        }


                        sourceSet.SourcePaths.Add(sourcePath);
                    }

                    m_sourceSets.Add(sourceSet);
                }
            }
        }

        

        // Settings
        Dictionary<string, string> m_settings = new Dictionary<string, string>();

        public string GetSetting(string name)
        {
            if (!m_settings.ContainsKey(name.ToLower()))
                return "Not found";

            return m_settings[name.ToLower()];
        }

        public string ProjectName { get { return GetSetting("ProjectName"); } }
        public string WorkingDirectory { get { return GetSetting("WorkingDirectory"); } }
        public string ResourceInfoExportFolder { get { return GetSetting("resourceInfoExportFolder"); } }

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
