using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;

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

        public static string RunProcess(Action<StreamWriter> workerFunction)
        {
            // Create a new process start info
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "cmd.exe", // Use the command prompt
                RedirectStandardInput = true,
                RedirectStandardError = true,
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = !Debugger.IsAttached
            };

            // Start the process
            Process process = new Process { StartInfo = psi };
            process.Start();

            // Get the process's input stream
            StreamWriter sw = process.StandardInput;
            StreamReader errorReader = process.StandardError;
            var stdOutput = process.StandardOutput;

            workerFunction(sw);

            // Close the input stream to indicate the end of input
            sw.Close();

            string output = stdOutput.ReadToEnd();

            var errorString = errorReader.ReadToEnd();


            // Wait for the process to complete
            process.WaitForExit();

            // Display the exit code
            //Console.WriteLine("Exit Code: " + process.ExitCode);

            // Close the process
            process.Close();

            return errorString;
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

        public static string NormalizeSlashes(string path)
        {
            string result = path.Replace('/', '\\');

            result = Path.Combine(result.Split('\\'));

            return result;
        }

        public static string NormalizePath(string path)
        {
            return EnsureTrailingSlash(NormalizeSlashes(path));
        }

        public static void CreateFolders(IEnumerable<string> sourceDestinationFolders)
        {
            foreach (var sourceDestinationFolder in sourceDestinationFolders)
            {
                if (!Directory.Exists(sourceDestinationFolder))
                    Directory.CreateDirectory(sourceDestinationFolder);
            }
        }

        public static void DeleteAllFilesRecursive(string folder)
        {
            // Delete files in the current folder
            foreach (string file in Directory.GetFiles(folder))
            {
                File.Delete(file);
            }
            // Recursively delete files in subdirectories
            foreach (string subfolder in Directory.GetDirectories(folder))
            {
                DeleteAllFilesRecursive(subfolder);
            }
        }

        public static void DeleteAllFiles(string folder)
        {
            // Delete files in the current folder
            foreach (string file in Directory.GetFiles(folder))
            {
                File.Delete(file);
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

        public static IEnumerable<string> GetFilesFromWildcardPath(string path)
        {
            List<string> filenames = new List<string>();

            path = Path.Combine(path.Split('/'));
            int lastSlashIndex = path.LastIndexOf(System.IO.Path.DirectorySeparatorChar);

            string directoryPath = "";

            if (lastSlashIndex > 0)
                directoryPath = path.Substring(0, lastSlashIndex + 1);

            string searchPattern = Path.GetFileName(path);

            string[] matchingFiles = Directory.GetFiles(directoryPath, 
                                                        searchPattern, 
                                                        SearchOption.TopDirectoryOnly);

            foreach (string matchingFile in matchingFiles)
            {
                filenames.Add(matchingFile);
            }

            return filenames;
        }

        internal static bool IsFile(string path)
        {
            return File.Exists(path);
        }

        internal static bool IsFileOrFileSpec(string path)
        {
            return path.Contains('*') || path.Contains('.');
        }

        internal static string GetPathFromFileOrFileSpec(string path)
        {
            string result = NormalizeSlashes(path);

            result = Path.Combine(result.Split('\\'));
            int lastSlashIndex = result.LastIndexOf(System.IO.Path.DirectorySeparatorChar);

            string directoryPath = "";

            if (lastSlashIndex > 0)
                directoryPath = result.Substring(0, lastSlashIndex + 1);

            return directoryPath;
        }
    }
}
