using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuildMasterSystem
{
    class Steps
    {
        public static void BuildCode(Config config)
        {
            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "/c C:\\Windows\\System32\\wsl.exe make -f build/Makefile";
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }

        public static void ExportGameData(Config config)
        {
            ExportBackgrounds(config);
            ExportAnimations(config);
        }

        public static void ExportBackgrounds(Config config)
        {
            string exePath = config.GetSetting("tmx2c.ExePath");
            string sourceFolder = config.GetSetting("tmx2c.SourceFolder");
            string destinationFolder = config.GetSetting("tmx2c.DestinationFolder");

            Utils.RunCommandLine(exePath, sourceFolder + " " + destinationFolder);
        }

        public static void ExportAnimations(Config config)
        {
            string exePath = config.GetSetting("gg2c.ExePath");
            string sourceFolder = config.GetSetting("gg2c.SourceFolder");
            string destinationFolder = config.GetSetting("gg2c.DestinationFolder");

            Utils.RunCommandLine(exePath, sourceFolder + " " + destinationFolder + " -sms");
        }

        public static void CleanOutputFolder(Config config)
        {
            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string commandArguments = "/c C:\\Windows\\System32\\wsl.exe make clean -f build/Makefile ";
            Utils.RunCommandLine("powershell.exe", commandArguments);
        }
    }
}
