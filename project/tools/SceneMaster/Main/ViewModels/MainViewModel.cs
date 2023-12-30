using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using SceneMaster.Documents.ViewModels;
using System;
using System.IO;
using System.Windows;
using System.Windows.Input;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Export;
using System.Windows.Forms;

namespace SceneMaster.Main.ViewModels
{
    public class AppConfig
    {
        public string GameObjectTemplatesDirectory { get => "..\\..\\..\\..\\..\\gamedata\\gameobjecttemplates"; }
    }

    public class MainViewModel : ObservableObject
    {
        public string Title => "Scene Master";

        private AppConfig AppConfig { get; } = new();
        private GameObjectTemplateLibraryViewModel GameObjectTemplateLibraryViewModel { get; } = new();

        private SceneMasterDocument m_currentDocument;

        public SceneMasterDocument CurrentDocument
        {
            get => m_currentDocument;
            private set => SetProperty(ref m_currentDocument, value);
        }

        public MainViewModel()
        {
            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var dllDirectory = baseDirectory + @"thirdparty\GraphicsGale"; // ensures galefile.dll gets loaded.
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllDirectory);

            GameObjectTemplateLibraryViewModel.GameObjectTemplateLibrary.Load(AppConfig.GameObjectTemplatesDirectory);

            CurrentDocument = new SceneMasterDocument(GameObjectTemplateLibraryViewModel);

            NewCommand = new RelayCommand(New);
            OpenCommand = new RelayCommand(Open);
            SaveCommand = new RelayCommand(SaveNoReturn);
            SaveAsCommand = new RelayCommand(SaveAs);
            ExitCommand = new RelayCommand(Exit);
            ImportTiledMapCommand = new RelayCommand(ImportGalFile);
            ExportCFilesCommand = new RelayCommand(ExportCFiles);
        }

        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public ICommand SaveCommand { get; }
        public ICommand SaveAsCommand { get; }
        public ICommand ExitCommand { get; }
        public ICommand ImportTiledMapCommand { get; }
        public ICommand ExportCFilesCommand { get; }



        private void New()
        {
            if (!CheckForSave())
                return;

            CurrentDocument?.Dispose();
            CurrentDocument = new SceneMasterDocument(GameObjectTemplateLibraryViewModel);
            // Add logic to clear/reset your UI or perform other actions for a new document
        }

        private void Open()
        {
            if (!CheckForSave())
                return;

            var openFileDialog = new Microsoft.Win32.OpenFileDialog();

            SetSceneMasterFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            CurrentDocument?.Dispose();
            CurrentDocument = new SceneMasterDocument(GameObjectTemplateLibraryViewModel);

            if (!CurrentDocument.Load(openFileDialog.FileName))
            {
                System.Windows.MessageBox.Show($"Loading {openFileDialog.FileName} failed.");
                CurrentDocument?.Dispose();
                CurrentDocument = new SceneMasterDocument(GameObjectTemplateLibraryViewModel);
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
                var saveFileDialog = new Microsoft.Win32.SaveFileDialog();

                SetSceneMasterFileExtensions(saveFileDialog);

                saveFileDialog.FileName = Path.GetFileName(filePath);

                if (saveFileDialog.ShowDialog() == false)
                    return false;

                filePath = saveFileDialog.FileName;
            }

            if (!CurrentDocument.Save(filePath))
            {
                System.Windows.MessageBox.Show($"Saving {filePath} failed.");
                return false;
            }

            return true;
        }

        private void SetSceneMasterFileExtensions(Microsoft.Win32.FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = SceneMasterDocument.SceneMasterDocumentFileExtension;
            string documentType = SceneMasterDocument.DocumentTypeName;
            fileDialog.DefaultExt = extension;
            fileDialog.Filter = $"{documentType} Files (*{extension})|*{extension}|All Files (*.*)|*.*";
        }

        private void SetTiledMapFileExtensions(Microsoft.Win32.FileDialog fileDialog)
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
                var result = System.Windows.MessageBox.Show($"Do you want to save changes to {CurrentDocument.FilePath}?", "Confirmation", MessageBoxButton.YesNoCancel);

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
                if (System.Windows.MessageBox.Show(message, "Overwrite", MessageBoxButton.YesNoCancel) != MessageBoxResult.Yes)
                    return;
            }

            var openFileDialog = new Microsoft.Win32.OpenFileDialog();

            SetTiledMapFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            CurrentDocument.ImportTiledMap(openFileDialog.FileName);
        }

        private void ExportCFiles()
        {
            // use current contents of map
            // export to folder

            if (CurrentDocument.SceneViewModel.IsModified ||
                !CurrentDocument.IsFilePathSet)
            {
                System.Windows.MessageBox.Show("The map needs to be saved before export.", "Saving Before Exporting");
                if (!Save(true))
                    return;
            }

            using var dialog = new FolderBrowserDialog();

            if (dialog.ShowDialog() != DialogResult.OK) 
                return;

            string sceneName = Path.GetFileNameWithoutExtension(CurrentDocument.Filename).Replace(" ", "_");

            SceneExporter.ExportScene(CurrentDocument.SceneViewModel.Scene, 
                                      sceneName,
                                      dialog.SelectedPath);
        }
    }
}