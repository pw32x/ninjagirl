using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System.IO;
using System.Windows.Input;

namespace SceneMaster.ViewModels
{
    public class SceneMasterDocument : ObservableObject
    {
        private bool m_isModified = false;
        public bool IsModified
        {
            get => m_isModified;
            private set => SetProperty(ref m_isModified, value);
        }

        public static string SceneMasterDocumentFileExtension => ".scm";
        public static string DocumentTypeName => "Scene Master";

        public static string TiledMapFileExtension => ".tmx";
        public static string TiledMapFileTypeName => "Tiled map";

        public string DefaultFilename => "Untitled Scene Master Document" + SceneMasterDocumentFileExtension;
        
        private string m_filePath;
        public string FilePath
        {
            get => m_filePath;
            set
            {
                SetProperty(ref m_filePath, value);
                Filename = Path.GetFileName(m_filePath);
            }
        }

        private string m_filename;
        public string Filename
        {
            get => m_filename;
            private set => SetProperty(ref m_filename, value);
        }

        private Scene m_scene;
        public Scene Scene
        {
            get => m_scene;
            private set
            {
                if (m_scene != null) 
                { 
                    m_scene.PropertyChanged -= Scene_PropertyChanged;
                }

                SetProperty(ref m_scene, value);

                if (m_scene != null) 
                {
                    m_scene.PropertyChanged += Scene_PropertyChanged;
                }
            }
        }

        private void Scene_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        public bool IsFilePathSet { get; private set; } = false;

        public SceneMasterDocument()
        {
            Scene = new Scene();

            FilePath = DefaultFilename;

            ModifyDocumentCommand = new RelayCommand(ModifyDocument);
        }

        public ICommand ModifyDocumentCommand { get; }

        public bool Load(string filePath)
        {
            Scene = new Scene();
            Scene.Load(filePath);

            FilePath = filePath;
            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public bool Save(string filePath)
        {
            Scene.Save(filePath);

            FilePath = filePath;
            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public void ModifyDocument()
        {
            IsModified = true;
        }

        internal void ImportTiledMap(string tiledMapFilePath)
        {
            Scene.ImportTiledMap(tiledMapFilePath);
        }
    }
}