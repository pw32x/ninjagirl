using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildMaster
{
    class Utils
    {
        public static void RunCommandLine(string command, string commandParameters)
        {
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = command,
                Arguments = commandParameters,
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true,
            };

            Process process = new Process
            {
                StartInfo = psi
            };

            process.Start();

            using (StreamWriter sw = process.StandardInput)
            {
                if (sw.BaseStream.CanWrite)
                {
                    sw.WriteLine("blah");
                }
            }

            string output = process.StandardOutput.ReadToEnd();
            string errors = process.StandardError.ReadToEnd();

            process.WaitForExit();

            //Console.WriteLine("Command Output:");
            Console.WriteLine(output);

            if (!string.IsNullOrEmpty(errors))
            {
                Console.WriteLine("Command Errors:");
                Console.WriteLine(errors);
            }

            if (process.ExitCode != 0)
                throw new Exception("RunCommandLine failed. Command: " + command + " parameters: " + commandParameters + "\n" + 
                                    errors);
        }

        public static string EnsureTrailingSlash(string path)
        {
            if (!path.EndsWith("\\") && !path.EndsWith("/"))
            {
                // Add a trailing slash
                path = path + "\\";
            }

            return path;
        }

        public static void CreateFolders(IEnumerable<string> sourceDestinationFolders)
        {
            foreach (var sourceDestinationFolder in sourceDestinationFolders)
            {
                if (!Directory.Exists(sourceDestinationFolder))
                    Directory.CreateDirectory(sourceDestinationFolder);
            }
        }

        public static void DeleteAllFiles(string folder)
        {
            // Delete files in the current folder
            foreach (string file in Directory.GetFiles(folder))
            {
                File.Delete(file);
            }
            // Recursively delete files in subdirectories
            foreach (string subfolder in Directory.GetDirectories(folder))
            {
                DeleteAllFiles(subfolder);
            }
        }

        public static void BenchmarkStep(Action<Config> step, Config config, string stepDescription)
        {
            var startTime = DateTime.Now;

            step(config);

            var elapsedTime = DateTime.Now - startTime;

            Console.WriteLine("Step: " + stepDescription + " complete.");
            Console.WriteLine("Elapsed time: " + elapsedTime.Duration());
        }
    }
}
