using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Scenes.ViewModels;
using System;
using System.IO;

namespace SceneMaster.Documents.ViewModels
{
    public class SceneMasterDocument : ObservableObject, IDisposable
    {
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

        private SceneViewModel m_sceneViewModel;
        public SceneViewModel SceneViewModel
        {
            get => m_sceneViewModel;
            set => SetProperty(ref m_sceneViewModel, value);
        }


        public bool IsFilePathSet { get; private set; } = false;

        public GameObjectTemplateLibraryViewModel GameObjectTemplateLibraryViewModel { get; private set; }

        public SceneMasterDocument(GameObjectTemplateLibraryViewModel gameObjectTemplateLibraryViewModel)
        {
            GameObjectTemplateLibraryViewModel = gameObjectTemplateLibraryViewModel;

            SceneViewModel = new SceneViewModel(GameObjectTemplateLibraryViewModel);

            FilePath = DefaultFilename;
        }

        public void Dispose()
        {
            SceneViewModel.Dispose();
            SceneViewModel = null;
        }

        public bool Load(string filePath)
        {
            SceneViewModel.Dispose();
            SceneViewModel = new SceneViewModel(GameObjectTemplateLibraryViewModel);
            SceneViewModel.Load(filePath);

            FilePath = filePath;
            IsFilePathSet = true;

            return true;
        }

        public bool Save(string filePath)
        {
            SceneViewModel.Save(filePath);

            FilePath = filePath;
            IsFilePathSet = true;

            return true;
        }

        internal void ImportTiledMap(string tiledMapFilePath)
        {
            SceneViewModel.Scene.ImportTiledMap(tiledMapFilePath);
        }
    }
}