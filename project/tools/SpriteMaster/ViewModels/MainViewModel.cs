using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using System;
using System.Windows;
using System.Windows.Input;

namespace SpriteMaster.ViewModels
{
    public class MainViewModel : ObservableObject
    {
        public string Title => "Sprite Master";

        public string MyProperty { get => CurrentDocument.SpriteMasterData.FilePath; }

        private SpriteMasterDocument m_currentDocument;
        public SpriteMasterDocument CurrentDocument
        {
            get => m_currentDocument;
            private set => SetProperty(ref m_currentDocument, value);
        }

        public MainViewModel()
        {
            CurrentDocument = new SpriteMasterDocument();

            NewCommand = new RelayCommand(New);
            OpenCommand = new RelayCommand(Open);
            SaveCommand = new RelayCommand(SaveNoReturn);
            ExitCommand = new RelayCommand(Exit);
            ImportGalFileCommand = new RelayCommand(ImportGalFile);
        }

        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public ICommand SaveCommand { get; }
        public ICommand ExitCommand { get; }
        public ICommand ImportGalFileCommand { get; }


        private void New()
        {
            if (!CheckForSave())
                return;

            CurrentDocument = new SpriteMasterDocument();
            // Add logic to clear/reset your UI or perform other actions for a new document
        }

        private void Open()
        {
            if (!CheckForSave())
                return;

            var openFileDialog = new OpenFileDialog();

            SetFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            CurrentDocument = new SpriteMasterDocument();
            
            if (!CurrentDocument.Load(openFileDialog.FileName))
            { 
                MessageBox.Show($"Loading {openFileDialog.FileName} failed.");
                CurrentDocument = new SpriteMasterDocument();
            }
        }

        private void SaveNoReturn()
        {
            Save();
        }

        private bool Save()
        {
            string filePath = "";

            if (!CurrentDocument.IsFilePathSet)
            {
                var saveFileDialog = new SaveFileDialog();

                SetFileExtensions(saveFileDialog);

                if (saveFileDialog.ShowDialog() == false)
                    return false;

                filePath = saveFileDialog.FileName;
            }

            if (!CurrentDocument.Save(filePath))
            {
                MessageBox.Show($"Saving {filePath} failed.");
                return false;
            }

            return true;
        }

        private void SetFileExtensions(FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = CurrentDocument.SpriteMasterDocumentFileExtension;
            string documentType = CurrentDocument.DocumentTypeName;
            fileDialog.DefaultExt = extension;
            fileDialog.Filter = $"{documentType} Files (*{extension})|*{extension}|All Files (*.*)|*.*";
        }

        private void Exit()
        {
            if (!CheckForSave())
                return;

            Environment.Exit(0);
        }

        private bool CheckForSave()
        {
            if (CurrentDocument.IsModified)
            {
                var result = MessageBox.Show($"Do you want to save changes to {CurrentDocument.SpriteMasterData.FilePath}?", "Confirmation", MessageBoxButton.YesNoCancel);

                switch (result)
                {
                    case MessageBoxResult.Yes:
                        return Save();
                    case MessageBoxResult.No:
                        return true;
                    case MessageBoxResult.Cancel:
                        return false;
                    default:
                        return false;
                }
            }

            return true;
        }


        private void ImportGalFile()
        {
        }
    }
}