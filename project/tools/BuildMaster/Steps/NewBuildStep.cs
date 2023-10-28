using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildMaster
{
    class NewBuildStep
    {
        public static void BuildCode(Config config)
        {
            Console.WriteLine("Step: Build code (New Method):");

            var sourceFilesToBuild = config.BuildListOfSourceFilesToCompile();
            var sourceDestinationFolders = config.BuildSourceDestinationFolders();

            CreateSourceDestinationFolders(sourceDestinationFolders);

            BuildSourceFiles(sourceFilesToBuild, config);

            var destinationSourceObjects = sourceFilesToBuild.Select(s => s.Destination);
            Link(config, destinationSourceObjects);
        }

        private static void Link(Config config, IEnumerable<string> destinationSourceObjects)
        {
            // Create a new process start info
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "cmd.exe", // Use the command prompt
                RedirectStandardInput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            // Start the process
            Process process = new Process { StartInfo = psi };
            process.Start();

            // Get the process's input stream
            StreamWriter sw = process.StandardInput;

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

        private static void BuildSourceFiles(IEnumerable<Config.SourceToBuild> sourceFilesToBuild, Config config)
        {
            // Create a new process start info
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "cmd.exe", // Use the command prompt
                RedirectStandardInput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            // Start the process
            Process process = new Process { StartInfo = psi };
            process.Start();

            // Get the process's input stream
            StreamWriter sw = process.StandardInput;

            foreach (var sourceFile in sourceFilesToBuild)
            {
                DateTime sourceLastWriteTime = File.GetLastWriteTime(sourceFile.Path);
                DateTime destinationLastWriteTime = File.GetLastWriteTime(sourceFile.Destination);

                // only build if the source file is newer.
                if (sourceLastWriteTime > destinationLastWriteTime)
                {
                    sw.WriteLine(sourceFile.Flags + " -c " + sourceFile.Path + " -o " + sourceFile.Destination);
                }
            }

            // Close the input stream to indicate the end of input
            sw.Close();

            // Wait for the process to complete
            process.WaitForExit();

            // Display the exit code
            Console.WriteLine("Exit Code: " + process.ExitCode);

            // Close the process
            process.Close();


        }

        private static void CreateSourceDestinationFolders(IEnumerable<string> sourceDestinationFolders)
        {
            foreach (var sourceDestinationFolder in sourceDestinationFolders)
            {
                Directory.CreateDirectory(sourceDestinationFolder);
            }
        }
    }
}
