﻿using CommunityToolkit.Mvvm.ComponentModel;
using MotionMaster.EditorObjectLibrary.ViewModels;
using MotionMaster.Main;
using MotionMaster.Scenes.ViewModels;
using System;
using System.IO;
using System.Windows;

namespace MotionMaster.Documents.ViewModels
{
    public class MotionMasterDocument : ObservableObject, IDisposable
    {
        public static string MotionMasterDocumentFileExtension => ".mm";
        public static string DocumentTypeName => "Motion Master Document";

        public static string GraphicsGaleFileExtension => ".gal";
        public static string GraphicsGaleFileTypeName => "Graphics Gale animation file";

        public string DefaultFilename => "Untitled " + DocumentTypeName + MotionMasterDocumentFileExtension;

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

        //List<BitmapImage> m_tileTypeImages;

        public MotionMasterDocument(Settings settings,
                                   EditorObjectLibraryViewModel editorObjectLibraryViewModel,
                                   string graphicsGaleFilename)
        {
            m_settings = settings;
            EditorObjectLibraryViewModel = editorObjectLibraryViewModel;
            SceneViewModel = new SceneViewModel(m_settings, 
                                                EditorObjectLibraryViewModel,
                                                graphicsGaleFilename);

            FilePath = DefaultFilename;
        }

        public MotionMasterDocument(Settings settings,
                                    EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            m_settings = settings;
            EditorObjectLibraryViewModel = editorObjectLibraryViewModel;

            FilePath = DefaultFilename;
        }

        public void Dispose()
        {
            SceneViewModel.Dispose();
            SceneViewModel = null;
        }

        public bool Load(string filePath)
        {
            SceneViewModel = new SceneViewModel(filePath, 
                                                m_settings, 
                                                EditorObjectLibraryViewModel);

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