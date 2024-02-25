using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using MotionMaster.Documents.ViewModels;
using MotionMaster.EditorObjectLibrary.ViewModels;
using MotionMaster.Export;
using MotionMaster.Scenes.Models;
using MotionMaster.Scenes.ViewModels;
using MotionMaster.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace MotionMaster.Main.ViewModels
{
    public class MainViewModel : ObservableObject
    {
        public string ApplicationName => "Motion Master";
        public string WindowTitle => ApplicationName + " - " + 
                                     (CurrentDocument != null && CurrentDocument.SceneViewModel.IsModified ? "*" : "") + 
                                     CurrentDocument?.FilePath;

        public Settings Settings { get; } = new();
        private EditorObjectLibraryViewModel EditorObjectLibraryViewModel { get; } = new();



        private MotionMasterDocument m_currentDocument;

        public bool HasCurrentDocument => CurrentDocument != null;
        public bool HasValidCurrentDocument() { return HasCurrentDocument; }

        public MotionMasterDocument CurrentDocument
        {
            get => m_currentDocument;
            private set
            {
                SetProperty(ref m_currentDocument, value);
                CommandManager.InvalidateRequerySuggested();
                OnPropertyChanged(nameof(HasCurrentDocument));
                OnPropertyChanged(nameof(WindowTitle));

                SaveCommand.NotifyCanExecuteChanged();
                SaveAsCommand.NotifyCanExecuteChanged();
                ExportCFilesCommand.NotifyCanExecuteChanged();
            }
        }

        public MainViewModel()
        {
            Settings.Load();
            Settings.PropertyChanged += Settings_PropertyChanged;

            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var dllDirectory = baseDirectory + @"thirdparty\GraphicsGale"; // ensures galefile.dll gets loaded.
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllDirectory);

            EditorObjectLibraryViewModel.LoadLibraries(Settings);

            //LoadTileTypes();

            bool openedScene = false;
            if (Settings.ReloadLastScene && 
                !string.IsNullOrEmpty(Settings.LastLoadedSceneFilename) &&
                File.Exists(Settings.LastLoadedSceneFilename))
            {
                openedScene = OpenHelper(Settings.LastLoadedSceneFilename);
            }
            
            //if (!openedScene)
            //    NewHelper();

            NewCommand = new RelayCommand(New);
            OpenCommand = new RelayCommand(Open);
            SaveCommand = new RelayCommand(SaveNoReturn, HasValidCurrentDocument);
            SaveAsCommand = new RelayCommand(SaveAs, HasValidCurrentDocument);
            ExitCommand = new RelayCommand(Exit);
            //ImportTiledMapCommand = new RelayCommand(ImportTiledMap);
            ExportCFilesCommand = new RelayCommand(ExportCFiles, HasValidCurrentDocument);
        }

        private void Settings_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            Settings.Save();
        }

        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public RelayCommand SaveCommand { get; }
        public RelayCommand SaveAsCommand { get; }
        public ICommand ExitCommand { get; }
        //public ICommand ImportTiledMapCommand { get; }
        public RelayCommand ExportCFilesCommand { get; }

        private void InitDocument()
        {
            CurrentDocument.PropertyChanging += Document_PropertyChanging;
            CurrentDocument.PropertyChanged += Document_PropertyChanged;
        }

        private void Document_PropertyChanging(object sender, System.ComponentModel.PropertyChangingEventArgs e)
        {
            if (e.PropertyName == nameof(MotionMasterDocument.SceneViewModel))
            {
                CurrentDocument.SceneViewModel.PropertyChanged -= SceneViewModel_PropertyChanged;
            }
        }

        private void Document_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(MotionMasterDocument.SceneViewModel))
            {
                CurrentDocument.SceneViewModel.PropertyChanged += SceneViewModel_PropertyChanged;
            }
        }

        private void SceneViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(SceneViewModel.IsModified))
                OnPropertyChanged(nameof(WindowTitle));
        }

        private void ShutdownDocument()
        {
            if (CurrentDocument != null && CurrentDocument.SceneViewModel != null)
            {
                CurrentDocument.PropertyChanged -= Document_PropertyChanged;
                CurrentDocument.PropertyChanging -= Document_PropertyChanging;
            }

            CurrentDocument?.Dispose();
            CurrentDocument = null;
        }

        private void NewHelper()
        {
            ShutdownDocument();

            // load a graphics gale file
            string graphicsGaleFilename = PromptForGraphicsGaleFilename();

            if (string.IsNullOrEmpty(graphicsGaleFilename))
                return;

            CurrentDocument = new MotionMasterDocument(Settings, EditorObjectLibraryViewModel, graphicsGaleFilename);

            if (CurrentDocument != null) 
            {
                InitDocument();
                Settings.LastLoadedSceneFilename = "";
            }
        }

        private void New()
        {
            if (!CheckForSave())
                return;

            NewHelper();
        }

        private bool OpenHelper(string filePath)
        {
            ShutdownDocument();

            var newDocument = new MotionMasterDocument(Settings, EditorObjectLibraryViewModel);

            if (newDocument.Load(filePath))
            {
                CurrentDocument = newDocument;
                InitDocument();
            }
            else
            {
                System.Windows.MessageBox.Show($"Loading {filePath} failed.");
                ShutdownDocument();
                Settings.LastLoadedSceneFilename = "";
                return false;
            }

            Settings.LastLoadedSceneFilename = CurrentDocument.FilePath;
            return true;
        }


        private void Open()
        {
            if (!CheckForSave())
                return;

            var openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.InitialDirectory = Settings.LastSceneLocation;

            SetMotionMasterFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            OpenHelper(openFileDialog.FileName);

            Settings.LastSceneLocation = Path.GetDirectoryName(openFileDialog.FileName);

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
                saveFileDialog.InitialDirectory = Settings.LastSceneLocation;

                SetMotionMasterFileExtensions(saveFileDialog);

                saveFileDialog.FileName = Path.GetFileName(filePath);

                if (saveFileDialog.ShowDialog() == false)
                    return false;

                filePath = saveFileDialog.FileName;

                Settings.LastSceneLocation = Path.GetDirectoryName(filePath);
            }

            if (!CurrentDocument.Save(filePath))
            {
                System.Windows.MessageBox.Show($"Saving {filePath} failed.");
                return false;
            }

            Settings.LastLoadedSceneFilename = CurrentDocument.FilePath;

            OnPropertyChanged(nameof(WindowTitle));

            return true;
        }

        private void SetMotionMasterFileExtensions(Microsoft.Win32.FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = MotionMasterDocument.MotionMasterDocumentFileExtension;
            string documentType = MotionMasterDocument.DocumentTypeName;
            fileDialog.DefaultExt = extension;
            fileDialog.Filter = $"{documentType} Files (*{extension})|*{extension}|All Files (*.*)|*.*";
        }

        private void SetTiledMapFileExtensions(Microsoft.Win32.FileDialog fileDialog)
        {
            // Filter files by extension
            string extension = MotionMasterDocument.GraphicsGaleFileExtension;
            string documentType = MotionMasterDocument.GraphicsGaleFileTypeName;
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
            if (CurrentDocument == null) return true;

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

        private string PromptForGraphicsGaleFilename()
        {
            var openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.InitialDirectory = Settings.LastGraphicsGaleImportLocation;

            SetTiledMapFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return "";

            Settings.LastGraphicsGaleImportLocation = Path.GetDirectoryName(openFileDialog.FileName);

            return openFileDialog.FileName;
        }

        /*
        private void ImportTiledMap()
        {
            if (!string.IsNullOrEmpty(CurrentDocument.SceneViewModel.Scene.TiledMapFilePath))
            {
                string message = "Replace existing " + MotionMasterDocument.TiledMapFileTypeName + " with new " + MotionMasterDocument.TiledMapFileTypeName + " file?";
                if (System.Windows.MessageBox.Show(message, "Overwrite", MessageBoxButton.YesNoCancel) != MessageBoxResult.Yes)
                    return;
            }

            var openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.InitialDirectory = Settings.LastImportLocation;

            SetTiledMapFileExtensions(openFileDialog);

            if (openFileDialog.ShowDialog() == false)
                return;

            Settings.LastImportLocation = Path.GetDirectoryName(openFileDialog.FileName);

            CurrentDocument.ImportTiledMap(openFileDialog.FileName);
        }
        */

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
            dialog.InitialDirectory = Settings.LastExportLocation;

            if (dialog.ShowDialog() != DialogResult.OK) 
                return;

            string sceneName = Path.GetFileNameWithoutExtension(CurrentDocument.Filename).Replace(" ", "_");

            string destinationHeaderFilename = StringUtils.EnsureTrailingSlash(dialog.SelectedPath) + sceneName + ".h";
            string destinationSourceFilename = StringUtils.EnsureTrailingSlash(dialog.SelectedPath) + sceneName + ".c";

            if (File.Exists(destinationHeaderFilename) || File.Exists(destinationSourceFilename))
            {
                if (System.Windows.MessageBox.Show("Overwrite existing files?", "Confirmation", MessageBoxButton.YesNoCancel) != MessageBoxResult.Yes)
                    return;
            }

            Settings.LastExportLocation = dialog.SelectedPath;

            SceneExporter.ExportScene(CurrentDocument.SceneViewModel.Scene, 
                                      sceneName,
                                      dialog.SelectedPath,
                                      EditorObjectLibraryViewModel.CommandLibrary);
        }
    }
}