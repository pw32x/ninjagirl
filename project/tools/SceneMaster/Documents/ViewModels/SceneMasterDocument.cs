using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.Main;
using SceneMaster.Scenes.ViewModels;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

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
        private Settings m_settings;

        public SceneViewModel SceneViewModel
        {
            get => m_sceneViewModel;
            set => SetProperty(ref m_sceneViewModel, value);
        }


        public bool IsFilePathSet { get; private set; } = false;

        public EditorObjectLibraryViewModel EditorObjectLibraryViewModel { get; private set; }

        List<BitmapImage> m_tileTypeImages;

        public SceneMasterDocument(Settings settings,
                                   EditorObjectLibraryViewModel editorObjectLibraryViewModel,
                                   List<BitmapImage> tileTypeImages)
        {
            m_settings = settings;
            EditorObjectLibraryViewModel = editorObjectLibraryViewModel;
            m_tileTypeImages = tileTypeImages;
            SceneViewModel = new SceneViewModel(m_settings, 
                                                EditorObjectLibraryViewModel,
                                                m_tileTypeImages);

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
            SceneViewModel = new SceneViewModel(m_settings, 
                                                EditorObjectLibraryViewModel, 
                                                m_tileTypeImages);
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
            try 
            {
                SceneViewModel.Scene.ImportTiledMap(tiledMapFilePath);
            }
            catch (Exception e) 
            {
                MessageBox.Show("Failed loading " + tiledMapFilePath + ". Error: " + e.Message);
            }
        }
    }
}