using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;
using System.IO;
using System.Windows;
using System.Windows.Input;

namespace SpriteMaster.ViewModels
{
    public class SpriteMasterDocument : ObservableObject
    {
        private bool m_isModified = false;
        public bool IsModified
        {
            get => m_isModified;
            private set => SetProperty(ref m_isModified, value);
        }

        public static string SpriteMasterDocumentFileExtension => ".sm";
        public static string DocumentTypeName => "Sprite Master";

        public static string GraphicsGaleFileExtension => ".gal";
        public static string GraphicsGaleFileTypeName => "Graphics Gale";

        public string DefaultFilename => "Untitled Sprite Master Document" + SpriteMasterDocumentFileExtension;
        
        private bool IgnorePropertyChanged { get; set; }

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

        private SpriteMasterData m_spriteMasterData;
        public SpriteMasterData SpriteMasterData
        {
            get => m_spriteMasterData;
            private set
            {
                if (m_spriteMasterData != null) 
                { 
                    m_spriteMasterData.PropertyChanged -= SpriteMasterData_PropertyChanged;
                }

                SetProperty(ref m_spriteMasterData, value);

                if (m_spriteMasterData != null) 
                {
                    m_spriteMasterData.PropertyChanged += SpriteMasterData_PropertyChanged;
                }
            }
        }

        private void SpriteMasterData_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        public bool IsFilePathSet { get; private set; } = false;

        public SpriteMasterDocument()
        {
            IgnorePropertyChanged = true;
            SpriteMasterData = new SpriteMasterData();
            IgnorePropertyChanged = false;

            FilePath = DefaultFilename;

            ModifyDocumentCommand = new RelayCommand(ModifyDocument);
        }

        public ICommand ModifyDocumentCommand { get; }

        public bool Load(string filePath)
        {
            IgnorePropertyChanged = true;
            SpriteMasterData = new SpriteMasterData();
            IgnorePropertyChanged = false;

            /*
            if (!SpriteMasterData.Load(filePath))
            { 
                return false;
            }
            */

            FilePath = filePath;
            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public bool Save(string filePath)
        {
            /*
            if (!SpriteMasterData.Save(filePath))
                return false;
            */

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
            SpriteMasterData.GalFilePath = galFilePath;
        }
    }
}