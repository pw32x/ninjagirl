using System;
using System.IO;
using System.Linq;

namespace BuildMaster
{
    class Steps
    {
        public static void RunAllTools(Config config)
        {
            Console.WriteLine("Step: Running Tools:");

            foreach (var toolJob in config.ToolJobs)
            {
                var toolInfo = config.GetTool(toolJob.ToolName);

                Console.WriteLine("Tool: " + toolJob.ToolName);
                Console.WriteLine("Source Path: " + toolJob.SourcePath);
                Console.WriteLine("Destination Path: " + toolJob.DestinationPath);
                Console.WriteLine("Bank Number: " + toolJob.BankNumber);
                Console.WriteLine("Flags: " + toolInfo.Flags);
                Console.WriteLine("ExtraFlags: " + toolJob.ExtraFlags);

                string bankFlag = toolJob.BankNumber >= 2 ? "-bank" + toolJob.BankNumber : "";

                Utils.RunCommandLine(toolInfo.Path, toolJob.SourcePath + " " + toolJob.DestinationPath + " " + toolJob.ExtraFlags + " " + toolInfo.Flags + " " + bankFlag);
            }
        }

        public static void RenameRom(Config config)
        {
            string romPath = config.CompilationSettings.OutFolder;


            string oldRomName = "untitled_project.sms";

            string projectName = config.ProjectName;
            string newRomName = projectName + ".sms";

            string sourceName = Path.Combine(romPath, oldRomName);


            string destinationName = Path.Combine(romPath, newRomName);

            File.Move(sourceName, destinationName, true);

            Console.WriteLine("Step: Rename ROM to " + newRomName);
        }

        public static void CopyToDailyFolder(Config config)
        {
            Console.WriteLine("Step: Copy output ROM to daily folder:");
            string dailyFolder = config.GetSetting("dailyVersionsFolder");

            string romPath = config.CompilationSettings.OutFolder;
            string projectName = config.ProjectName;
            string romName = projectName + ".sms";

            string sourceName = Path.Combine(romPath, romName);

            DateTime time = DateTime.Now;

            string destinationRomName = projectName + "-" + time.Year + "-" + time.Month + "-" + time.Day + ".sms";

            string destinationName = Path.Combine(dailyFolder, destinationRomName);

            if (!Directory.Exists(dailyFolder))
                Directory.CreateDirectory(dailyFolder);

            File.Copy(sourceName, destinationName, true);
        }

    }
}
