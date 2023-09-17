using System;
using System.Diagnostics;
using System.IO;

namespace SoundMaster
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

             Console.WriteLine(commandParameters);

            Process process = new Process
            {
                StartInfo = psi
            };

            process.Start();

            /*
            using (StreamWriter sw = process.StandardInput)
            {
                if (sw.BaseStream.CanWrite)
                {
                    sw.WriteLine("blah");
                }
            }
            */

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
    }
}
