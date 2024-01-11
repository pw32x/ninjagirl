using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.CommandLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.Export;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Main;
using SceneMaster.Scenes.Models;
using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Input;

namespace SceneMaster.Scenes.ViewModels
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public class SceneViewModel : ObservableObject, IDisposable
    {
        // not the best place to put this, but it'll do for now.
        public static double ZoomFactor { get; set; } = 1;

        private bool m_ignoreChanges = false;
        private bool m_isModified = false;
        public bool IsModified
        {
            get => m_isModified;
            private set
            {
                if (!m_ignoreChanges)
                    SetProperty(ref m_isModified, value);
            }
        }

        public ObservableCollection<EditorObjectViewModel> EditorObjectViewModels { get; set; } = new();

        private EditorObjectViewModel m_selectedEditorObjectViewModel;
        public EditorObjectViewModel SelectedEditorObjectViewModel
        {
            get => m_selectedEditorObjectViewModel;

            set
            {
                m_ignoreChanges = true;
                if (m_selectedEditorObjectViewModel != null)
                    m_selectedEditorObjectViewModel.IsSelected = false;

                SetProperty(ref m_selectedEditorObjectViewModel, value);

                if (m_selectedEditorObjectViewModel != null)
                    m_selectedEditorObjectViewModel.IsSelected = true;

                m_ignoreChanges = false;
            }
        }

        private Scene m_scene;
        public Scene Scene { get => m_scene; private set => m_scene = value; }

        private Settings m_settings;

        EditorObjectLibraryViewModel EditorObjectInfoLibraryViewModel { get; set; }

        public SceneViewModel(Settings settings,
                              EditorObjectLibraryViewModel editorObjectInfoLibraryViewModel)
        {
            m_settings = settings;
            EditorObjectInfoLibraryViewModel = editorObjectInfoLibraryViewModel;
            Scene = new Scene();

            // attach
            Scene.PropertyChanged += Scene_PropertyChanged;
            Scene.EditorObjects.CollectionChanged += EditorObjects_CollectionChanged;

            foreach (var editorObject in Scene.EditorObjects)
            {
                var editorObjectViewModel = CreateEditorObjectViewModel(editorObject);
                EditorObjectViewModels.Add(editorObjectViewModel);
            }

            DeleteCommand = new RelayCommand(DeleteSelectedEditorObjectViewModel, 
                                             CanDeleteSelectedEditorObjectViewModel);

            RunSceneCommand = new RelayCommand(RunScene);
        }

        private void RunScene()
        {
            string tempLevelName = "sceneMasterTemp";

            // export to temporary file
            SceneExporter.ExportScene(Scene, 
                                      tempLevelName, 
                                      m_settings.SourceExportDirectory, 
                                      EditorObjectInfoLibraryViewModel.CommandLibrary);

            string buildMasterPath = Path.GetFullPath(m_settings.BuildMasterPath);
            string workingDirectory = Path.GetFullPath(m_settings.GameBuildDirectory);
            string emulatorPath = Path.GetFullPath(m_settings.EmulatorPath);
            string pathToGameRom = Path.GetFullPath(m_settings.PathToGameRom);
            
            ProcessStartInfo buildMasterProcess = new ProcessStartInfo
            {
                FileName = buildMasterPath,
                Arguments = "config.bm build -DUSE_SCENEMASTER_LEVEL -SProjectName=" + Settings.GameRomName + " -SCopyToDailyFolder=false",
                WorkingDirectory = workingDirectory,
                UseShellExecute = true, // Set this to true if you want to use the system's default shell
                //RedirectStandardOutput = true,
                //RedirectStandardError = true,
                //CreateNoWindow = true
            };

            // Start the BuildMaster process
            try
            {
                using (Process process = Process.Start(buildMasterProcess))
                {
                    //string output = process.StandardOutput.ReadToEnd();
                    //StreamReader errorReader = process.StandardError;
                    //var errorString = errorReader.ReadToEnd();

                    //while (!process.StandardOutput.EndOfStream)
                    //{
                    //    string outputLine = process.StandardOutput.ReadLine();
                    //    Console.WriteLine(outputLine);
                    //}


                    // Wait for the process to exit
                    process.WaitForExit();
                    // Get the return code
                    int exitCode = process.ExitCode;

                    if (exitCode != 0) 
                    {
                        MessageBox.Show("BuildMaster build error. Error code: " + exitCode);
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error running BuildMaster process. Error: " + ex.Message);
                return;
            }

            /*
            // kill all the instances of the emulator
            var processes = Process.GetProcesses();
            var matchingProcesses = processes.Where(p => p.MainWindowTitle.Contains("Emulicious", StringComparison.OrdinalIgnoreCase));
            foreach (var process in processes)
            { 
                process.Kill(); 
            }
            */

            // start the game
            ProcessStartInfo emulatorProcess = new ProcessStartInfo
            {
                FileName = emulatorPath,
                Arguments = pathToGameRom,
                UseShellExecute = false, // Set this to true if you want to use the system's default shell
                RedirectStandardOutput = true
            };

            try
            {
                using (Process process = Process.Start(emulatorProcess))
                {
                    string output = process.StandardOutput.ReadToEnd();
                    // Wait for the process to exit
                    process.WaitForExit();
                    // Get the return code
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error running emulator process. Error: " + ex.Message);
                return;
            }
        }

        public ICommand DeleteCommand { get; }
        public ICommand RunSceneCommand { get; }

        private void DeleteSelectedEditorObjectViewModel()
        {
            if (SelectedEditorObjectViewModel == null)
                return;

            Scene.EditorObjects.Remove(SelectedEditorObjectViewModel.EditorObject);
        }

        private bool CanDeleteSelectedEditorObjectViewModel()
        {
            return SelectedEditorObjectViewModel != null;
        }

        private void DeleteEditorObjectViewModel(EditorObject editorObjectToDelete)
        {
            var editorObjectViewModel = EditorObjectViewModels.FirstOrDefault(x => x.EditorObject == editorObjectToDelete);
            if (editorObjectViewModel == null)
                return;

            EditorObjectViewModels.Remove(editorObjectViewModel);
            editorObjectViewModel.PropertyChanged -= Scene_PropertyChanged;

            Deselect(editorObjectViewModel);
        }

        public void Dispose()
        {
            // detach
            if (Scene != null)
            {
                foreach (var editorObjectViewModel in EditorObjectViewModels)
                {
                    editorObjectViewModel.PropertyChanged -= Scene_PropertyChanged;
                }
                EditorObjectViewModels.Clear();

                Scene.PropertyChanged -= Scene_PropertyChanged;
                Scene.EditorObjects.CollectionChanged -= EditorObjects_CollectionChanged;
                Scene.Dispose();
                Scene = null;
            }
        }

        private void Scene_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        private void EditorObjects_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            IsModified = true;

            Deselect(SelectedEditorObjectViewModel);

            if (e.NewItems != null)
            {
                foreach (var newEditorObject in e.NewItems.OfType<EditorObject>())
                {
                    var newEditorObjectViewModel = CreateEditorObjectViewModel(newEditorObject);
                    EditorObjectViewModels.Add(newEditorObjectViewModel);
                }
            }

            if (e.OldItems != null)
            {
                foreach (var editorObjectToDelete in e.OldItems.OfType<EditorObject>())
                {
                    DeleteEditorObjectViewModel(editorObjectToDelete);
                }
            }
        }

        private EditorObjectViewModel CreateEditorObjectViewModel(EditorObject newEditorObject)
        {
            EditorObjectViewModel newEditorObjectViewModel = null;

            if (newEditorObject is CommandObject commandObject)
            {
                newEditorObjectViewModel = new CommandObjectViewModel(commandObject, this);
            }
            else if (newEditorObject is GameObject gameObject)
            {
                newEditorObjectViewModel = new GameObjectViewModel(gameObject, this);
            }

            newEditorObjectViewModel.PropertyChanged += Scene_PropertyChanged;
            return newEditorObjectViewModel;
        }

        internal void Load(string filePath)
        {
            m_ignoreChanges = true;
            Scene.Load(filePath, EditorObjectInfoLibraryViewModel);
            m_ignoreChanges = false;

            IsModified = false;
            OnPropertyChanged(nameof(Scene));
        }

        internal void Save(string filePath)
        {
            Scene.Save(filePath);
            IsModified = false;
        }

        internal void Select(EditorObjectViewModel editorObjectViewModel)
        {
            if (SelectedEditorObjectViewModel == editorObjectViewModel)
                return;

            SelectedEditorObjectViewModel = editorObjectViewModel;
        }

        internal void Deselect(EditorObjectViewModel editorObjectViewModel)
        {
            if (SelectedEditorObjectViewModel == editorObjectViewModel)
            {
                SelectedEditorObjectViewModel = null;
            }
        }

        internal void CreateEditorObject(int mapX, int mapY)
        {
            if (EditorObjectInfoLibraryViewModel.SelectedEditorObjectInfo == null)
                return;

            Scene.CreateEditorObject(mapX, mapY, EditorObjectInfoLibraryViewModel.SelectedEditorObjectInfo);
        }
    }
}
