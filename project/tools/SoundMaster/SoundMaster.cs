using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SoundMaster
{
    class SoundMaster
    {
        Config m_config = new Config();

        List<string> m_songFilenames;
        List<string> m_sfxChannel2Filenames;
        List<string> m_sfxChannel3Filenames;
        List<string> m_sfxChannel23Filenames;

        private void ProcessArgs(string[] args)
        {
            if (args.Length < 1)
                throw new Exception("SoundMaster config file not specified.");

            m_config.Load(args[0]);
        }

        internal void Run(string[] args)
        {
            ProcessArgs(args);

            var startTime = DateTime.Now;

            CollectFiles();

            ConvertAllToPSG();

            ConvertPsgToBanks();

            //m_songFilenames.ForEach(s => Console.WriteLine(s));
            //m_sfxChannel2Filenames.ForEach(s => Console.WriteLine(s));
            //m_sfxChannel3Filenames.ForEach(s => Console.WriteLine(s));
            //m_sfxChannel23Filenames.ForEach(s => Console.WriteLine(s));

            var elapsedTime = DateTime.Now - startTime;
            Console.WriteLine("Sound Export complete.");
            Console.WriteLine("Elapsed time: " + elapsedTime.Duration());
        }

        private List<string> GetVGMFilenames(string directory)
        {
            return Directory.GetFiles(directory, "*.vgm").ToList();
        }

        private void CollectFiles()
        {
            m_songFilenames = GetVGMFilenames(m_config.MusicDirectory);
            m_sfxChannel2Filenames = GetVGMFilenames(m_config.Channel2SFXDirectory);
            m_sfxChannel3Filenames = GetVGMFilenames(m_config.Channel3SFXDirectory);
            m_sfxChannel23Filenames = GetVGMFilenames(m_config.Channel23SFXDirectory);
        }

        private void ConvertToPSG(string path, string flags = "")
        {
            string outputFilename = Path.GetFileNameWithoutExtension(path) + ".psg";

            Console.Write("converting " + path + " to " + m_config.TempDirectory + "\\" + outputFilename);

            Utils.RunCommandLine("java", "-jar " + m_config.PSGToolPath + " " + path + " " + m_config.TempDirectory + "\\" + outputFilename + " " + flags);
        }

        private void ConvertAllToPSG()
        {
            if (!Directory.Exists(m_config.TempDirectory))
                Directory.CreateDirectory(m_config.TempDirectory);

            m_songFilenames.ForEach(s => ConvertToPSG(s));
            m_sfxChannel2Filenames.ForEach(s => ConvertToPSG(s, "2"));
            m_sfxChannel3Filenames.ForEach(s => ConvertToPSG(s, "3"));
            m_sfxChannel23Filenames.ForEach(s => ConvertToPSG(s, "23"));
        }

        private void ConvertPsgToBanks()
        {
            string fullTempDirectory = Path.GetFullPath(m_config.TempDirectory);
            string fullAssets2BanksPath = Path.GetFullPath(m_config.Assets2BanksPath);

            Directory.SetCurrentDirectory(m_config.ExportDirectory);

            Utils.RunCommandLine(fullAssets2BanksPath, fullTempDirectory + " --allowsplitting");
        }

    }
}
