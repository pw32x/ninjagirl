using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace BuildMasterSystem
{
    class Config
    {
        public void Load(string path)
        {
            if (!File.Exists(path))
                throw new Exception("Path for config file not found");

            XmlDocument xmlDocument = new XmlDocument();
                
            xmlDocument.Load(path);

            XmlNodeList settingsNodes = xmlDocument.SelectNodes("/BuildMasterSystem/Settings/Setting");

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

        public string ProjectName { get { return GetSetting("ProjectName"); }}
        public string WorkingDirectory { get { return GetSetting("WorkingDirectory"); }}
    }
}
