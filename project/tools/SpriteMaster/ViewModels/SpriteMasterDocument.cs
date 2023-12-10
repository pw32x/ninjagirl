using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
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

        public string SpriteMasterDocumentFileExtension => ".sm";
        public string DefaultFilename => "Untitled Sprite Master Document" + SpriteMasterDocumentFileExtension;
        public string DocumentTypeName => "Sprite Master";

        private SpriteMasterData m_spriteMasterData;
        public SpriteMasterData SpriteMasterData
        {
            get => m_spriteMasterData;
            private set => SetProperty(ref m_spriteMasterData, value);
        }


        public bool IsFilePathSet { get; private set; } = false;

        public SpriteMasterDocument()
        {
            SpriteMasterData = new SpriteMasterData();
            SpriteMasterData.FilePath = DefaultFilename;

            ModifyDocumentCommand = new RelayCommand(ModifyDocument);
        }

        public ICommand ModifyDocumentCommand { get; }

        public bool Load(string filePath)
        {
            SpriteMasterData = new SpriteMasterData();

            if (!SpriteMasterData.Load(filePath))
            { 
                return false;
            }

            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public bool Save(string filePath)
        {
            if (!SpriteMasterData.Save(filePath))
                return false;

            IsFilePathSet = true;
            IsModified = false;

            return true;
        }

        public void ModifyDocument()
        {
            IsModified = true;
        }
    }
}