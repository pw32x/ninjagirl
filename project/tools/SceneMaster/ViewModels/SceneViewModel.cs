using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SceneMaster.Models;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Input;

namespace SceneMaster.ViewModels
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

        public ObservableCollection<GameObjectViewModel> GameObjectViewModels { get; set; } = new();

        private GameObjectViewModel m_selectedGameObjectViewModel;
        public GameObjectViewModel SelectedGameObjectViewModel 
        { 
            get => m_selectedGameObjectViewModel;

            set
            { 
                m_ignoreChanges = true;
                if (m_selectedGameObjectViewModel != null)
                    m_selectedGameObjectViewModel.IsSelected = false;

                SetProperty(ref m_selectedGameObjectViewModel, value);

                if (m_selectedGameObjectViewModel != null)
                    m_selectedGameObjectViewModel.IsSelected = true;

                m_ignoreChanges = false;
            }
        }

        private Scene m_scene;
        public Scene Scene { get => m_scene; private set => m_scene = value; }

        public SceneViewModel()
        { 
            Scene = new Scene();

            // attach
            Scene.PropertyChanged += Scene_PropertyChanged;
            Scene.GameObjects.CollectionChanged += GameObjects_CollectionChanged;

            foreach (var gameObject in Scene.GameObjects)
            { 
                var gameObjectViewModel = new GameObjectViewModel(gameObject, this);
                gameObjectViewModel.PropertyChanged += Scene_PropertyChanged;
                GameObjectViewModels.Add(gameObjectViewModel);
            }

            DeleteCommand = new RelayCommand(DeleteSelectedGameObjectViewModel, CanDeleteSelectedGameObjectViewModel);
        }

        public ICommand DeleteCommand { get; }

        private void DeleteSelectedGameObjectViewModel()
        {
            if (SelectedGameObjectViewModel == null) 
                return;

            Scene.GameObjects.Remove(SelectedGameObjectViewModel.GameObject);
        }

        private bool CanDeleteSelectedGameObjectViewModel()
        {
            return SelectedGameObjectViewModel != null;
        }

        private void DeleteGameObjectViewModel(GameObject gameObjectToDelete)
        {
            var gameObjectViewModel = GameObjectViewModels.FirstOrDefault(x => x.GameObject == gameObjectToDelete);
            if (gameObjectViewModel == null)
                return;

            GameObjectViewModels.Remove(gameObjectViewModel);
            gameObjectViewModel.PropertyChanged -= Scene_PropertyChanged;

            Deselect(gameObjectViewModel);
        }

        public void Dispose()
        {
            // detach
            if (Scene != null) 
            { 
                foreach (var gameObjectViewMode in GameObjectViewModels)
                { 
                    gameObjectViewMode.PropertyChanged -= Scene_PropertyChanged;
                }
                GameObjectViewModels.Clear();

                Scene.PropertyChanged -= Scene_PropertyChanged;
                Scene.GameObjects.CollectionChanged -= GameObjects_CollectionChanged;
                Scene = null;
            }
        }

        private void Scene_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        private void GameObjects_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            IsModified = true;

            Deselect(SelectedGameObjectViewModel);

            if (e.NewItems != null)
            { 
                foreach (var newGameObject in e.NewItems.OfType<GameObject>())
                {
                    var newGameObjectViewModel = new GameObjectViewModel(newGameObject, this);
                    newGameObjectViewModel.PropertyChanged += Scene_PropertyChanged;
                    GameObjectViewModels.Add(newGameObjectViewModel);
                }
            }
            
            if (e.OldItems != null) 
            {
                foreach (var gameObjectToDelete in e.OldItems.OfType<GameObject>())
                { 
                    DeleteGameObjectViewModel(gameObjectToDelete);
                }
            }
        }

        internal void Load(string filePath)
        {
            m_ignoreChanges = true;
            Scene.Load(filePath);
            m_ignoreChanges = false;

            IsModified = false;
            OnPropertyChanged(nameof(Scene));
        }

        internal void Save(string filePath)
        {
            Scene.Save(filePath);
            IsModified = false;
        }

        internal void Select(GameObjectViewModel gameObjectViewModel)
        {
            if (SelectedGameObjectViewModel == gameObjectViewModel)
                return;

            SelectedGameObjectViewModel = gameObjectViewModel;
        }

        internal void Deselect(GameObjectViewModel gameObjectViewModel)
        {
            if (SelectedGameObjectViewModel == gameObjectViewModel)
            {
                SelectedGameObjectViewModel = null;
            }
        }
    }
}
