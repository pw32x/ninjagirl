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

            string makefilePath = config.GetSetting("makefile.Path");

            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "-nologo /c C:\\Windows\\System32\\wsl.exe make -f " + makefilePath;
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }

        public static void CleanOutputFolder(Config config)
        {
            Console.WriteLine("Step: Clean Output Folder:");

            string makefilePath = config.GetSetting("makefile.Path");

            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "/c C:\\Windows\\System32\\wsl.exe make clean -f " + makefilePath;
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }

        public static void ExportGameData(Config config)
        {
            Console.WriteLine("Step: Export Game Data:");
            ExportBackgrounds(config);
            ExportAnimations(config);
        }

        public static void ExportBackgrounds(Config config)
        {
            Console.WriteLine("Step: Export Backgrounds:");
            string exePath = config.GetSetting("tmx2c.ExePath");
            string sourceFolder = config.GetSetting("tmx2c.SourceFolder");
            string destinationFolder = config.GetSetting("tmx2c.DestinationFolder");

            Utils.RunCommandLine(exePath, sourceFolder + " " + destinationFolder);
        }

        public static void ExportAnimations(Config config)
        {
            Console.WriteLine("Step: Export Animations:");
            string exePath = config.GetSetting("gg2c.ExePath");
            string sourceFolder = config.GetSetting("gg2c.SourceFolder");
            string destinationFolder = config.GetSetting("gg2c.DestinationFolder");

            Utils.RunCommandLine(exePath, sourceFolder + " " + destinationFolder + " -sms -updateonly");
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
