using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildMasterSystem
{
    class Utils
    {
        public static void RunCommandLine(string powerShellCommand, string workingDirectory)
        {
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = "powershell",
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true,
                WorkingDirectory = workingDirectory
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
                    sw.WriteLine(powerShellCommand);
                }
            }

            string output = process.StandardOutput.ReadToEnd();
            string errors = process.StandardError.ReadToEnd();

            process.WaitForExit();

            Console.WriteLine("PowerShell Output:");
            Console.WriteLine(output);

            if (!string.IsNullOrEmpty(errors))
            {
                Console.WriteLine("PowerShell Errors:");
                Console.WriteLine(errors);
            }
        }
    }
}
