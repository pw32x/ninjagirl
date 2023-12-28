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

            DirectoryInfo directoryInfo = new DirectoryInfo(gameObjectTemplatesDirectory);
            FileInfo[] fileInfos = directoryInfo.GetFiles();

            string[] fileExtensions = { ".xml" };
            var foundFileInfos = fileInfos.Where(file => fileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

            foreach (var fileInfo in foundFileInfos)
            {
                var gameObjectTemplate = new GameObjectTemplate();
                gameObjectTemplate.Load(fileInfo.FullName);
                GameObjectTemplates.Add(gameObjectTemplate);
            }
        }

        private List<GameObjectTemplate> m_gameObjectTemplates = new(); 
        public List<GameObjectTemplate> GameObjectTemplates { get => m_gameObjectTemplates; }

        private string m_gameObjectTemplatesDirectory;
    }
}
