using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Utils;
using System;
using System.IO;
using System.Xml.Serialization;

namespace SceneMaster.Main
{
    public class Settings : ObservableObject
    {
        private string m_settingsFilename = "settings.xml";

        private bool m_reloadLastScene = false;
        public bool ReloadLastScene { get => m_reloadLastScene; set => SetProperty(ref m_reloadLastScene, value); }

        private string m_lastLoadedSceneFilename = "";
        public string LastLoadedSceneFilename { get => m_lastLoadedSceneFilename; set => SetProperty(ref m_lastLoadedSceneFilename, value); }

        private string m_gameObjectTemplatesDirectory = "..\\..\\..\\..\\..\\gamedata\\gameobjecttemplates";
        public string GameObjectTemplatesDirectory { get => m_gameObjectTemplatesDirectory; set => SetProperty(ref m_gameObjectTemplatesDirectory, value); }

        private string m_commandsSourceDirectory = "..\\..\\..\\..\\..\\source\\engine";
        public string CommandsSourceDirectory { get => m_commandsSourceDirectory; set => SetProperty(ref m_commandsSourceDirectory, value); }

        public void Load()
        {
            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);
            string fullPath = appFolder + m_settingsFilename;

            if (!File.Exists(fullPath))
                return;

            XmlSerializer serializer = new XmlSerializer(typeof(Settings));

            // Deserialize the object from XML
            using (TextReader reader = new StreamReader(fullPath))
            {
                var temp = serializer.Deserialize(reader);

                // Update the properties of the existing object with the deserialized data
                // This assumes that the properties have public setters
                foreach (var property in typeof(Settings).GetProperties())
                {
                    var deserializedValue = property.GetValue(temp);
                    property.SetValue(this, deserializedValue);
                }
            }
        }

        public void Save()
        {
            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);

            // Create an XmlSerializer for the type of the object
            XmlSerializer serializer = new XmlSerializer(typeof(Settings));

            // Serialize the object to XML
            using (TextWriter writer = new StreamWriter(appFolder + m_settingsFilename))
            {
                serializer.Serialize(writer, this);
            }
        }
    }
}
