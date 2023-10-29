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
            // Create a new process start info
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "cmd.exe", // Use the command prompt
                RedirectStandardInput = true,
                UseShellExecute = false,
                CreateNoWindow = !Debugger.IsAttached
            };

            var destinationSourceObjects = sourceFilesToBuild.Select(s => s.Destination);

            // Start the process
            Process process = new Process { StartInfo = psi };
            process.Start();

            // Get the process's input stream
            StreamWriter sw = process.StandardInput;

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

            // Run the linker and ihx converter
            var sb = new StringBuilder();
            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            foreach (var destinationSourceObject in destinationSourceObjects)
            {
                addFlag(destinationSourceObject);
            }

            sw.WriteLine(config.BuildLinkCommand() + " " + sb.ToString());
            sw.WriteLine(config.BuildIHXToSMSCommand());

            // Close the input stream to indicate the end of input
            sw.Close();

            // Wait for the process to complete
            process.WaitForExit();

            // Display the exit code
            Console.WriteLine("Exit Code: " + process.ExitCode);

            // Close the process
            process.Close();


        }
    }
}
