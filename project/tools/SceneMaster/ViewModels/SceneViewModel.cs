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

        public ObservableCollection<SpriteViewModel> SpriteViewModels { get; set; } = new();

        private SpriteViewModel m_selectedSpriteViewModel;
        public SpriteViewModel SelectedSpriteViewModel 
        { 
            get => m_selectedSpriteViewModel;

            set
            { 
                m_ignoreChanges = true;
                if (m_selectedSpriteViewModel != null)
                    m_selectedSpriteViewModel.IsSelected = false;

                SetProperty(ref m_selectedSpriteViewModel, value);

                if (m_selectedSpriteViewModel != null)
                    m_selectedSpriteViewModel.IsSelected = true;

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
            Scene.Sprites.CollectionChanged += Sprites_CollectionChanged;

            foreach (var sprite in m_scene.Sprites)
            { 
                var spriteViewModel = new SpriteViewModel(sprite, this);
                spriteViewModel.PropertyChanged += Scene_PropertyChanged;
                SpriteViewModels.Add(spriteViewModel);
            }

            DeleteCommand = new RelayCommand(DeleteSelectedSprite, CanDeleteSelectedSprite);
        }

        public ICommand DeleteCommand { get; }

        private void DeleteSelectedSprite()
        {
            if (SelectedSpriteViewModel == null) 
                return;

            m_scene.Sprites.Remove(SelectedSpriteViewModel.Sprite);
        }

        private bool CanDeleteSelectedSprite()
        {
            return SelectedSpriteViewModel != null;
        }

        private void DeleteSpriteViewModel(Scene.Sprite spriteToDelete)
        {
            var spriteViewModel = SpriteViewModels.FirstOrDefault(x => x.Sprite == spriteToDelete);
            if (spriteViewModel == null)
                return;

            SpriteViewModels.Remove(spriteViewModel);
            spriteViewModel.PropertyChanged -= Scene_PropertyChanged;

            Deselect(spriteViewModel);
        }

        public void Dispose()
        {
            // detach
            if (Scene != null) 
            { 
                foreach (var spriteViewModel in SpriteViewModels)
                { 
                    spriteViewModel.PropertyChanged -= Scene_PropertyChanged;
                }
                SpriteViewModels.Clear();

                Scene.PropertyChanged -= Scene_PropertyChanged;
                Scene.Sprites.CollectionChanged -= Sprites_CollectionChanged;
                Scene = null;
            }
        }

        private void Scene_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            IsModified = true;
        }

        private void Sprites_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            IsModified = true;

            Deselect(SelectedSpriteViewModel);

            if (e.NewItems != null)
            { 
                foreach (var newSprite in e.NewItems.OfType<Scene.Sprite>())
                {
                    var newSpriteViewModel = new SpriteViewModel(newSprite, this);
                    newSpriteViewModel.PropertyChanged += Scene_PropertyChanged;
                    SpriteViewModels.Add(newSpriteViewModel);
                }
            }
            
            if (e.OldItems != null) 
            {
                foreach (var spriteToDelete in e.OldItems.OfType<Scene.Sprite>())
                { 
                    DeleteSpriteViewModel(spriteToDelete);
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

        internal void Select(SpriteViewModel spriteViewModel)
        {
            if (SelectedSpriteViewModel == spriteViewModel)
                return;

            SelectedSpriteViewModel = spriteViewModel;
        }

        internal void Deselect(SpriteViewModel spriteViewModel)
        {
            if (SelectedSpriteViewModel == spriteViewModel)
            {
                SelectedSpriteViewModel = null;
            }
        }
    }
}
