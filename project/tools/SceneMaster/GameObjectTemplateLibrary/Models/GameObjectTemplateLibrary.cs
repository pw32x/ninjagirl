using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SceneMaster.GameObjectTemplates.Models
{
    public class GameObjectTemplateLibrary
    {
        public GameObjectTemplateLibrary() { }

        public void Load(string gameObjectTemplatesDirectory)
        {
            m_gameObjectTemplatesDirectory = gameObjectTemplatesDirectory;

            DefaultGameObjectTemplate = new GameObjectTemplate();
            DefaultGameObjectTemplate.Name = "DefaultOrMissing";
            
            //DefaultGameObjectTemplate.Visual.Load("default.png");

            DirectoryInfo directoryInfo = new DirectoryInfo(gameObjectTemplatesDirectory);
            FileInfo[] fileInfos = directoryInfo.GetFiles();

            string[] fileExtensions = { ".xml" };
            var foundFileInfos = fileInfos.Where(file => fileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

            foreach (var fileInfo in foundFileInfos)
            {
                var gameObjectTemplate = new GameObjectTemplate();
                gameObjectTemplate.Load(fileInfo.FullName);
                GameObjectTemplates.Add(gameObjectTemplate.Name, gameObjectTemplate);
            }
        }

        private Dictionary<string, GameObjectTemplate> m_gameObjectTemplates = new(); 
        public Dictionary<string, GameObjectTemplate> GameObjectTemplates { get => m_gameObjectTemplates; }

        public GameObjectTemplate DefaultGameObjectTemplate { get; private set; }

        private string m_gameObjectTemplatesDirectory;
    }
}
