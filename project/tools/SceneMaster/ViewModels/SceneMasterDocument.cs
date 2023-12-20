using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;
using System.IO;
using System.Windows;
using System.Windows.Input;
using System.Xml.Serialization;

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

        public static string SceneMasterDocumentFileExtension => ".scenem";
        public static string DocumentTypeName => "Scene Master";

        public static string GraphicsGaleFileExtension => ".gal";
        public static string GraphicsGaleFileTypeName => "Graphics Gale";

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

        private SceneMasterData m_sceneMasterData;
        public SceneMasterData SceneMasterData
        {
            get => m_sceneMasterData;
            private set
            {
                if (m_sceneMasterData != null) 
                { 
                    m_sceneMasterData.PropertyChanged -= SceneMasterData_PropertyChanged;
                }

                SetProperty(ref m_sceneMasterData, value);

                if (m_sceneMasterData != null) 
                {
                    m_sceneMasterData.PropertyChanged += SceneMasterData_PropertyChanged;
                }
            }
        }

        private void SceneMasterData_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        public bool IsFilePathSet { get; private set; } = false;

        public SceneMasterDocument()
        {
            SceneMasterData = new SceneMasterData();

            FilePath = DefaultFilename;

            ModifyDocumentCommand = new RelayCommand(ModifyDocument);
        }

        public ICommand ModifyDocumentCommand { get; }

        public bool Load(string filePath)
        {
            SceneMasterData = new SceneMasterData();
            SceneMasterData.Load(filePath);

            FilePath = filePath;
            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public bool Save(string filePath)
        {
            SceneMasterData.Save(filePath);

            FilePath = filePath;
            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public void ModifyDocument()
        {
            IsModified = true;
        }

        internal void ImportGalFile(string galFilePath)
        {
            SceneMasterData.ImportGraphicsGaleFile(galFilePath);
        }
    }
}