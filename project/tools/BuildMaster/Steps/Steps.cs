using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildMaster
{
    class Steps
    {
        public static void BuildCode(Config config)
        {
            Console.WriteLine("Step: Build code:");

            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "-nologo /c C:\\Windows\\System32\\wsl.exe make -f " + config.MakefilePath;
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }

        public static void CleanOutputFolder(Config config)
        {
            Console.WriteLine("Step: Clean Output Folder:");

            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "/c C:\\Windows\\System32\\wsl.exe make clean -f " + config.MakefilePath;
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }

        public static void RunAllTools(Config config)
        {
            Console.WriteLine("Step: Running Tools:");

            var entries = config.Entries;

            foreach (var toolInfo in config.ToolInfos)
            {
                Console.WriteLine("Step: " + toolInfo.Info);

                var applicableEntries = entries.Where(e => e.ToolName == toolInfo.Name);

                string toolPath = toolInfo.Path;

                foreach (var entry in applicableEntries)
                {
                    Console.WriteLine("Tool: " + toolInfo.Name);
                    Console.WriteLine("Source Path: " + entry.SourcePath);
                    Console.WriteLine("Destination Path: " + entry.DestinationPath);
                    Console.WriteLine("Flags: " + toolInfo.Flags);

                    Utils.RunCommandLine(toolPath, entry.SourcePath + " " + entry.DestinationPath + " " + toolInfo.Flags);
                }
            }
        }

        public static void UpdateMakefileConfig(Config config)
        {
            var makefileConfigPath = config.GetSetting("buildFolder") + "\\Makefile.config";

            var sb = new StringBuilder();

            foreach (var directory in config.DestinationFolders)
            {
                sb.AppendLine(directory);
            }

            File.WriteAllText(makefileConfigPath, sb.ToString());
        }

        public static void RenameRom(Config config)
        {
            string romPath = config.GetSetting("romPath");


            string oldRomName = "untitled_project.sms";

            string projectName = config.ProjectName;
            string newRomName = projectName + ".sms";

            string sourceName = Path.Combine(romPath, oldRomName);


            string destinationName = Path.Combine(romPath, newRomName);

            File.Move(sourceName, destinationName, true);

            Console.WriteLine("Step: Rename ROM to " + newRomName);
        }

        public static void CopyRom(Config config)
        {
            string romPath = config.GetSetting("romPath");


            string oldRomName = "untitled_project.sms";

            string projectName = config.ProjectName;
            string newRomName = projectName + ".sms";

            string sourceName = Path.Combine(romPath, oldRomName);


            string destinationName = Path.Combine(romPath, newRomName);

            File.Copy(sourceName, destinationName, true);

            Console.WriteLine("Step: Rename ROM to " + newRomName);
        }

        public static void CopyToDailyFolder(Config config)
        {
            Console.WriteLine("Step: Copy output ROM to daily folder:");
            string dailyFolder = config.GetSetting("dailyVersionsFolder");

            string romPath = config.GetSetting("romPath");
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
