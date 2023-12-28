using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using SceneMaster.Documents.ViewModels;
using System;
using System.IO;
using System.Windows;
using System.Windows.Input;

namespace SceneMaster.Main.ViewModels
{
    public class MainViewModel : ObservableObject
    {
        public string Title => "Scene Master";

        private SceneMasterDocument m_currentDocument;
        public SceneMasterDocument CurrentDocument
        {
            get => m_currentDocument;
            private set => SetProperty(ref m_currentDocument, value);
        }

        public MainViewModel()
        {
            CurrentDocument = new SceneMasterDocument();

            NewCommand = new RelayCommand(New);
            OpenCommand = new RelayCommand(Open);
            SaveCommand = new RelayCommand(SaveNoReturn);
            SaveAsCommand = new RelayCommand(SaveAs);
            ExitCommand = new RelayCommand(Exit);
            ImportTiledMapCommand = new RelayCommand(ImportGalFile);
        }

        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public ICommand SaveCommand { get; }
        public ICommand SaveAsCommand { get; }
        public ICommand ExitCommand { get; }
        public ICommand ImportTiledMapCommand { get; }


        private void New()
        {
            if (!CheckForSave())
                return;

            CurrentDocument?.Dispose();
            CurrentDocument = new SceneMasterDocument();
            // Add logic to clear/reset your UI or perform other actions for a new document
        }

        private void Open()
        {
            if (!CheckForSave())
                return;

            var openFileDialog = new OpenFileDialog();

            SetSceneMasterFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            CurrentDocument?.Dispose();
            CurrentDocument = new SceneMasterDocument();

            if (!CurrentDocument.Load(openFileDialog.FileName))
            {
                MessageBox.Show($"Loading {openFileDialog.FileName} failed.");
                CurrentDocument?.Dispose();
                CurrentDocument = new SceneMasterDocument();
            }
        }

        private void SaveAs()
        {
            Save(forcePrompt: true);
        }

        private void SaveNoReturn()
        {
            Save();
        }

        private bool Save(bool forcePrompt = false)
        {
            string filePath = CurrentDocument.FilePath;

            if (!CurrentDocument.IsFilePathSet || forcePrompt)
            {
                var saveFileDialog = new SaveFileDialog();

                SetSceneMasterFileExtensions(saveFileDialog);

                saveFileDialog.FileName = Path.GetFileName(filePath);

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

        private void SetSceneMasterFileExtensions(FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = SceneMasterDocument.SceneMasterDocumentFileExtension;
            string documentType = SceneMasterDocument.DocumentTypeName;
            fileDialog.DefaultExt = extension;
            fileDialog.Filter = $"{documentType} Files (*{extension})|*{extension}|All Files (*.*)|*.*";
        }

        private void SetTiledMapFileExtensions(FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = SceneMasterDocument.TiledMapFileExtension;
            string documentType = SceneMasterDocument.TiledMapFileTypeName;
            fileDialog.DefaultExt = extension;
            fileDialog.Filter = $"{documentType} Files (*{extension})|*{extension}|All Files (*.*)|*.*";
        }


        private void Exit()
        {
            if (!CheckForSave())
                return;

            Environment.Exit(0);
        }

        public bool CheckForSave()
        {
            if (CurrentDocument.SceneViewModel.IsModified)
            {
                var result = MessageBox.Show($"Do you want to save changes to {CurrentDocument.FilePath}?", "Confirmation", MessageBoxButton.YesNoCancel);

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
            if (!string.IsNullOrEmpty(CurrentDocument.SceneViewModel.Scene.TiledMapFilePath))
            {
                string message = "Replace existing " + SceneMasterDocument.TiledMapFileTypeName + " with new " + SceneMasterDocument.TiledMapFileTypeName + " file?";
                if (MessageBox.Show(message, "Overwrite", MessageBoxButton.YesNoCancel) != MessageBoxResult.Yes)
                    return;
            }

            var openFileDialog = new OpenFileDialog();

            SetTiledMapFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            CurrentDocument.ImportTiledMap(openFileDialog.FileName);
        }
    }
}