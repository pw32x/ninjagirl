using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using SceneMaster.Documents.ViewModels;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.Export;
using SceneMaster.Scenes.Models;
using SceneMaster.Scenes.ViewModels;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace SceneMaster.Main.ViewModels
{
    public class MainViewModel : ObservableObject
    {
        public string ApplicationName => "Scene Master";
        public string WindowTitle => ApplicationName + " - " + 
                                     (CurrentDocument.SceneViewModel.IsModified ? "*" : "") + 
                                     CurrentDocument.FilePath;

        public Settings Settings { get; } = new();
        private EditorObjectLibraryViewModel EditorObjectLibraryViewModel { get; } = new();



        private SceneMasterDocument m_currentDocument;

        public SceneMasterDocument CurrentDocument
        {
            get => m_currentDocument;
            private set => SetProperty(ref m_currentDocument, value);
        }

        public MainViewModel()
        {
            Settings.Load();
            Settings.PropertyChanged += Settings_PropertyChanged;

            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var dllDirectory = baseDirectory + @"thirdparty\GraphicsGale"; // ensures galefile.dll gets loaded.
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllDirectory);

            EditorObjectLibraryViewModel.LoadLibraries(Settings);

            LoadTileTypes();

            bool openedScene = false;
            if (Settings.ReloadLastScene && 
                !string.IsNullOrEmpty(Settings.LastLoadedSceneFilename) &&
                File.Exists(Settings.LastLoadedSceneFilename))
            {
                openedScene = OpenHelper(Settings.LastLoadedSceneFilename);
            }
            
            if (!openedScene)
                NewHelper();

            NewCommand = new RelayCommand(New);
            OpenCommand = new RelayCommand(Open);
            SaveCommand = new RelayCommand(SaveNoReturn);
            SaveAsCommand = new RelayCommand(SaveAs);
            ExitCommand = new RelayCommand(Exit);
            ImportTiledMapCommand = new RelayCommand(ImportTiledMap);
            ExportCFilesCommand = new RelayCommand(ExportCFiles);
            RunSceneCommand = new RelayCommand(RunScene);
        }

        private Dictionary<string, BitmapImage> TileTypeImages { get; set; } = new Dictionary<string, BitmapImage>();

        private void LoadTileTypes()
        {
            string assemblyName = Assembly.GetExecutingAssembly().GetName().Name;

            var loadImage = (string name) => 
            {
                BitmapImage bitmap = new BitmapImage();
                bitmap.BeginInit();
                bitmap.UriSource = new Uri("pack://application:,,,/" + assemblyName + ";component/TileTypes/" + name + ".png");
                bitmap.EndInit();

                TileTypeImages[name] = bitmap;
            };

            foreach (var tileTypeName in Scene.TileTypeNameToInt.Keys)
            {
                if (string.IsNullOrEmpty(tileTypeName))
                    continue;
                loadImage(tileTypeName);
            }
        }

        private void Settings_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            Settings.Save();
        }

        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public ICommand SaveCommand { get; }
        public ICommand SaveAsCommand { get; }
        public ICommand ExitCommand { get; }
        public ICommand ImportTiledMapCommand { get; }
        public ICommand ExportCFilesCommand { get; }
        public ICommand RunSceneCommand { get; }

        private SceneMasterDocument InitDocument()
        {
            var newDocument = new SceneMasterDocument(Settings, EditorObjectLibraryViewModel);
            newDocument.PropertyChanging += Document_PropertyChanging;
            newDocument.PropertyChanged += Document_PropertyChanged;

            return newDocument;
        }

        private void Document_PropertyChanging(object sender, System.ComponentModel.PropertyChangingEventArgs e)
        {
            if (e.PropertyName == nameof(SceneMasterDocument.SceneViewModel))
            {
                CurrentDocument.SceneViewModel.PropertyChanged -= SceneViewModel_PropertyChanged;
            }
        }

        private void Document_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(SceneMasterDocument.SceneViewModel))
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
        }

        private void NewHelper()
        {
            ShutdownDocument();
            CurrentDocument = InitDocument();
            
            Settings.LastLoadedSceneFilename = "";
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
            CurrentDocument = InitDocument();

            if (!CurrentDocument.Load(filePath))
            {
                System.Windows.MessageBox.Show($"Loading {filePath} failed.");
                ShutdownDocument();
                CurrentDocument = InitDocument();
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

            SetSceneMasterFileExtensions(openFileDialog);

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

                SetSceneMasterFileExtensions(saveFileDialog);

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


        private void ImportTiledMap()
        {
            if (!string.IsNullOrEmpty(CurrentDocument.SceneViewModel.Scene.TiledMapFilePath))
            {
                string message = "Replace existing " + SceneMasterDocument.TiledMapFileTypeName + " with new " + SceneMasterDocument.TiledMapFileTypeName + " file?";
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

        private void RunScene()
        {
            if (Save())
                CurrentDocument.SceneViewModel.RunScene();
        }
    }
}