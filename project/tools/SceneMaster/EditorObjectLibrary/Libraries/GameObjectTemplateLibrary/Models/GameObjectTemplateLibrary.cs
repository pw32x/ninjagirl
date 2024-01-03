using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace SceneMaster.GameObjectTemplates.Models
{
    public class DefaultGameObjectTemplate : GameObjectTemplate
    {
        public DefaultGameObjectTemplate() { IsEditorVisible = true; }
    }

    public class GameObjectTemplateLibrary
    {
        public GameObjectTemplateLibrary() { }

        public void Load(string gameObjectTemplatesDirectory)
        {
            m_gameObjectTemplatesDirectory = gameObjectTemplatesDirectory;

            DefaultGameObjectTemplate = new DefaultGameObjectTemplate();
            DefaultGameObjectTemplate.Name = "DefaultOrMissing";
            
            //DefaultGameObjectTemplate.Visual.Load("default.png");

            DirectoryInfo directoryInfo = new DirectoryInfo(gameObjectTemplatesDirectory);
            FileInfo[] fileInfos = directoryInfo.GetFiles();

            string[] fileExtensions = { ".xml" };
            var foundFileInfos = fileInfos.Where(file => fileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

            foreach (var fileInfo in foundFileInfos)
            {
                var gameObjectTemplate = new GameObjectTemplate();

                try
                {
                    gameObjectTemplate.Load(fileInfo.FullName);

                    if (gameObjectTemplate.IsEditorVisible)
                        GameObjectTemplates.Add(gameObjectTemplate.Name, gameObjectTemplate);
                    else
                        m_invisibleGameObjectTemplates.Add(gameObjectTemplate.Name, gameObjectTemplate);
                }
                catch (Exception) 
                {
                    m_failedGameObjectTemplates.Add(gameObjectTemplate.Name, gameObjectTemplate);
                }
            }
        }

        private Dictionary<string, GameObjectTemplate> m_invisibleGameObjectTemplates = new(); 
        private Dictionary<string, GameObjectTemplate> m_failedGameObjectTemplates = new(); 

        private Dictionary<string, GameObjectTemplate> m_gameObjectTemplates = new(); 
        public Dictionary<string, GameObjectTemplate> GameObjectTemplates { get => m_gameObjectTemplates; }

                public GameObjectTemplate DefaultGameObjectTemplate { get; private set; }

        private string m_gameObjectTemplatesDirectory;
    }
}
