using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace BuildMaster
{
    class NewSteps
    {
        public static void BuildCode(Config config)
        {
            Console.WriteLine("Step: Build code (New Method):");

            var sourceFilesToBuild = config.BuildListOfSourceFilesToCompile();
            var sourceDestinationFolders = config.BuildSourceDestinationFolders();

            Utils.CreateFolders(sourceDestinationFolders);

            BuildProject(sourceFilesToBuild, config);
        }

        internal static void GenerateResourceInfos(Config config)
        {
            var headerFiles = config.BuildListOfHeaderFiles();

            // scan headerFiles for types marked RESOURCE

            var foundResources = new List<(string, string)>();
            var foundIncludes = new List<string>();

            foreach (var headerFile in headerFiles)
            {
                var lines = File.ReadAllLines(headerFile);

                var taggedLines = lines.Where(l => l.StartsWith("RESOURCE"));

                bool found = false;

                foreach (var taggedLine in taggedLines)
                {
                    var tokens = taggedLine.Split(' ');

                    string bank = "0";
                    if (tokens[0] != "RESOURCE()")
                    {
                        bank = tokens[0].Trim(')');
                        bank = bank.Substring("RESOURCE(BANK".Length);
                    }

                    foundResources.Add((tokens[tokens.Length - 1].Trim(';'), bank));
                    found = true;
                }

                if (found)
                    foundIncludes.Add(headerFile);
            }

            string filename = "resource_infos";
            string headerFilename = config.ResourceInfoExportFolder + "\\" + filename + ".h";
            string sourceFilename = config.ResourceInfoExportFolder + "\\" + filename + ".c";

            var sb = new StringBuilder();
            sb.AppendLine("#ifndef RESOURCE_INFOS_INCLUDE_H");
            sb.AppendLine("#define RESOURCE_INFOS_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("#include \"resource_types.h\"");
            sb.AppendLine();

            foreach (var foundResource in foundResources)
            {
                sb.AppendLine("extern const ResourceInfo " + foundResource.Item1 + "ResourceInfo;");
            }

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(headerFilename, sb.ToString());

            sb.Clear();

            sb.AppendLine("#include \"" + filename + ".h\"");
            sb.AppendLine();

            var includePaths = config.IncludePaths;

            foreach (var headerFile in foundIncludes)
            {
                string includeFile = headerFile;

                foreach (var includePath in includePaths)
                {
                    if (includeFile.StartsWith(includePath))
                    {
                        includeFile = includeFile.Substring(includePath.Length);
                        break;
                    }
                }

                sb.AppendLine("#include \"" + includeFile + "\"");
            }
            sb.AppendLine();

            foreach (var foundResource in foundResources)
            {
                sb.AppendLine("const ResourceInfo " + foundResource.Item1 + "ResourceInfo = ");
                sb.AppendLine("{");
                sb.AppendLine("    RESOURCE_INFO_RESOURCE_TYPE,");
                sb.AppendLine("    " + foundResource.Item2 + ",");
                sb.AppendLine("    (const Resource*)&" + foundResource.Item1);
                sb.AppendLine("};");
                sb.AppendLine();
            }

            File.WriteAllText(sourceFilename, sb.ToString());
        }

        public static void CleanOutputFolder(Config config)
        {
            Utils.DeleteAllFilesRecursive(config.CompilationSettings.OutFolder);
        }

        public static void CleanExportFolder(Config config)
        {
            var toolExportFolders = config.GetToolExportFolders();

            foreach (var toolExportFolder in toolExportFolders)
            {
                Utils.DeleteAllFiles(toolExportFolder);
            }
        }

        private static void BuildProject(IEnumerable<Config.SourceToBuild> sourceFilesToBuild, Config config)
        {
            Action<StreamWriter> buildProject = (StreamWriter sw) =>
            {
                // Build files
                foreach (var sourceFile in sourceFilesToBuild)
                {
                    DateTime sourceLastWriteTime = File.GetLastWriteTime(sourceFile.Filename);
                    DateTime destinationLastWriteTime = File.GetLastWriteTime(sourceFile.Destination);

                    // only build if the source file is newer.
                    if (sourceLastWriteTime > destinationLastWriteTime)
                    {
                        sw.WriteLine(sourceFile.Flags + " -c " + sourceFile.Filename + " -o " + sourceFile.Destination);
                    }
                }
            };

            if (!Utils.RunProcess(buildProject))
                return;

            Action<StreamWriter> linkProject = (StreamWriter sw) =>
            {
                // Run the linker and ihx converter
                var sb = new StringBuilder();
                void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

                var destinationSourceObjects = sourceFilesToBuild.OrderBy(s => s.BankNumber).Select(s => s.Destination);

                foreach (var destinationSourceObject in destinationSourceObjects)
                {
                    addFlag(destinationSourceObject);
                }

                var usedBankNumbers = sourceFilesToBuild.Where(s => s.BankNumber > 1).Select(s => s.BankNumber).Distinct();

                sw.WriteLine(config.BuildLinkCommand(usedBankNumbers) + " " + sb.ToString());
                sw.WriteLine(config.BuildIHXToSMSCommand());
            };

            if (!Utils.RunProcess(linkProject))
                return;
        }
    }
}
