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
            Console.WriteLine("CommandParameters: " + commandParameters);

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

        public static int RunSingleCommand(string commandLine, Action<string> onOutputLine, string additionalPathDirectory = null)
        {
            string executablePath;
            string args;

            if (commandLine.StartsWith("\""))
            {
                int closingQuoteIndex = commandLine.IndexOf('"', 1);
                executablePath = commandLine.Substring(1, closingQuoteIndex - 1);
                args = commandLine.Substring(closingQuoteIndex + 1).TrimStart();
            }
            else
            {
                int splitIndex = commandLine.IndexOf(' ');
                executablePath = splitIndex < 0 ? commandLine : commandLine.Substring(0, splitIndex);
                args = splitIndex < 0 ? "" : commandLine.Substring(splitIndex + 1);
            }

            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = executablePath,
                Arguments = args,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true,
            };

            if (!string.IsNullOrEmpty(additionalPathDirectory))
            {
                string existingPath = psi.EnvironmentVariables.ContainsKey("PATH") ? psi.EnvironmentVariables["PATH"] : "";
                psi.EnvironmentVariables["PATH"] = additionalPathDirectory + ";" + existingPath;
            }

            Process process = new Process { StartInfo = psi };

            void handleLine(object sender, DataReceivedEventArgs e)
            {
                if (e.Data != null)
                {
                    onOutputLine(e.Data);
                }
            }

            process.OutputDataReceived += handleLine;
            process.ErrorDataReceived += handleLine;

            process.Start();
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();
            process.WaitForExit();

            int exitCode = process.ExitCode;
            process.Close();

            return exitCode;
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
            string normalized = NormalizeSlashes(path);

            // don't add a slash if it's a filename
            if (!string.IsNullOrEmpty(Path.GetExtension(normalized)))
                return normalized;

            return EnsureTrailingSlash(normalized);
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

        public static bool BenchmarkStep(Func<Config, bool> step, Config config, string stepDescription)
        {
            var startTime = DateTime.Now;

            bool result = step(config);

            var elapsedTime = DateTime.Now - startTime;

            Console.WriteLine("Step: " + stepDescription + " complete.");
            Console.WriteLine("Elapsed time: " + elapsedTime.Duration());

            return result;
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
