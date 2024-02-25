using CommunityToolkit.Mvvm.ComponentModel;
using MotionMaster.Utils;
using System;
using System.IO;
using System.Xml.Serialization;

namespace MotionMaster.Main
{
    public class Settings : ObservableObject
    {
        private string m_settingsFilename = "settings.xml";

        private bool m_reloadLastScene = false;
        public bool ReloadLastScene { get => m_reloadLastScene; set => SetProperty(ref m_reloadLastScene, value); }

        private string m_lastLoadedSceneFilename = "";
        public string LastLoadedSceneFilename { get => m_lastLoadedSceneFilename; set => SetProperty(ref m_lastLoadedSceneFilename, value); }

        private string m_gameObjectTemplatesDirectory = "gamedata\\gameobjecttemplates";
        public string GameObjectTemplatesDirectory { get => m_gameObjectTemplatesDirectory; set => SetProperty(ref m_gameObjectTemplatesDirectory, value); }

        private string m_commandsSourceDirectory = "source";
        public string CommandsSourceDirectory { get => m_commandsSourceDirectory; set => SetProperty(ref m_commandsSourceDirectory, value); }

        private string m_sourceExportDirectory = "source\\client\\exported";
        public string SourceExportDirectory { get => m_sourceExportDirectory; set => SetProperty(ref m_sourceExportDirectory, value); }

        private string m_lastSceneSaveLocation = "";
        public string LastSceneLocation { get => m_lastSceneSaveLocation; set => SetProperty(ref m_lastSceneSaveLocation, value); }

        private string m_lastGraphicsGaleImportLocation = "";
        public string LastGraphicsGaleImportLocation { get => m_lastGraphicsGaleImportLocation; set => SetProperty(ref m_lastGraphicsGaleImportLocation, value); }

        private string m_lastTiledMapLocation = "";
        public string LastImportLocation { get => m_lastTiledMapLocation; set => SetProperty(ref m_lastTiledMapLocation, value); }

        private string m_lastExportLocation = "";
        public string LastExportLocation { get => m_lastExportLocation; set => SetProperty(ref m_lastExportLocation, value); }

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
