using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Forms;

namespace SceneMaster.GameObjectTemplates.Models
{
    public class DefaultGameObjectTemplate : GameObjectTemplate
    {
        public DefaultGameObjectTemplate() { IsEditorVisible = true; }
    }

    public class Group<T> : ObservableCollection<T>
    {
        public string Name { get; }

        public Group(string name)
        {
            Name = name;
        }
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

            GameObjectTemplatesCollectionView = CollectionViewSource.GetDefaultView(GameObjectTemplates.Values);
            GameObjectTemplatesCollectionView.GroupDescriptions.Add(new PropertyGroupDescription(nameof(GameObjectTemplate.EditorObjectType)));
            GameObjectTemplatesCollectionView.SortDescriptions.Add(new SortDescription(nameof(GameObjectTemplate.EditorObjectType), ListSortDirection.Ascending));

            EditorObjectType[] allEditorObjectTypes = (EditorObjectType[])Enum.GetValues(typeof(EditorObjectType));
            foreach (var editorObjectType in allEditorObjectTypes)
            {
                var group = new Group<GameObjectTemplate>(editorObjectType.ToString());

                var editorObjectsOfType = GameObjectTemplates.Values.Where(g => g.EditorObjectType == editorObjectType);

                foreach (var editorObject in editorObjectsOfType)
                    group.Add(editorObject);

                m_groupedGameObjectTemplates.Add(group);
            }
        }

        private Dictionary<string, GameObjectTemplate> m_invisibleGameObjectTemplates = new(); 
        private Dictionary<string, GameObjectTemplate> m_failedGameObjectTemplates = new(); 

        private Dictionary<string, GameObjectTemplate> m_gameObjectTemplates = new(); 
        public Dictionary<string, GameObjectTemplate> GameObjectTemplates { get => m_gameObjectTemplates; }

        public ICollectionView  GameObjectTemplatesCollectionView { get; private set; }

        private List<Group<GameObjectTemplate>> m_groupedGameObjectTemplates = new();
        public  List<Group<GameObjectTemplate>> GroupedGameObjectTemplates { get => m_groupedGameObjectTemplates; }

        public GameObjectTemplate DefaultGameObjectTemplate { get; private set; }

        private string m_gameObjectTemplatesDirectory;
    }
}
