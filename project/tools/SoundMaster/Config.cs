using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace SoundMaster
{
    class Config
    {
        public void Load(string path)
        {
            if (!File.Exists(path))
                throw new Exception("Path for config file not found");

            XmlDocument xmlDocument = new XmlDocument();
                
            xmlDocument.Load(path);

            XmlNodeList settingsNodes = xmlDocument.SelectNodes("/SoundMaster/Settings/Setting");

            if (settingsNodes != null)
            {
                foreach (XmlNode settingNode in settingsNodes)
                {
                    string name = settingNode.Attributes["name"].Value;
                    string value = settingNode.Attributes["value"].Value;

                    m_settings[name.ToLower()] = value;
                }
            }
        }

        Dictionary<string, string> m_settings = new Dictionary<string, string>();

        public string GetSetting(string name) 
        { 
            if (!m_settings.ContainsKey(name.ToLower()))
                throw new Exception("There is no value in the config file for " + name);

            return m_settings[name.ToLower()]; 
        }

        public string MusicDirectory { get { return GetSetting("MusicDirectory"); }}

        public string Channel2SFXDirectory { get { return GetSetting("Channel2SFXDirectory"); }}
        public string Channel3SFXDirectory { get { return GetSetting("Channel3SFXDirectory"); }}
        public string Channel23SFXDirectory { get { return GetSetting("Channel23SFXDirectory"); }}

        public string ExportDirectory { get { return GetSetting("ExportDirectory"); }}

        public string TempDirectory { get { return GetSetting("TempDirectory"); }}

        public string PSGToolPath { get { return GetSetting("PSGToolPath"); }}
        public string Assets2BanksPath { get { return GetSetting("assets2banksPath"); }}
    }
}
