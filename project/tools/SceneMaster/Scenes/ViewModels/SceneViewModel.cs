using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.CommandLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.GameObjectTemplates.ViewModels;
using SceneMaster.Scenes.Models;
using System;
using System.Collections.ObjectModel;
using System.Linq;
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

        EditorObjectLibraryViewModel EditorObjectInfoLibraryViewModel { get; set; }

        public SceneViewModel(EditorObjectLibraryViewModel editorObjectInfoLibraryViewModel)
        {
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
        }

        public ICommand DeleteCommand { get; }

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
