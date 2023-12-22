using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Models;
using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace SceneMaster.ViewModels
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public class SceneViewModel : ObservableObject, IDisposable
    {
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
                SetProperty(ref m_selectedSpriteViewModel, value);
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
                var spriteViewModel = new SpriteViewModel(sprite);
                spriteViewModel.PropertyChanged += Scene_PropertyChanged;
                SpriteViewModels.Add(spriteViewModel);
            }
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

            if (e.NewItems != null)
            { 
                foreach (var newSprite in e.NewItems.OfType<Scene.Sprite>())
                {
                    var newSpriteViewModel = new SpriteViewModel(newSprite);
                    newSpriteViewModel.PropertyChanged += Scene_PropertyChanged;
                    SpriteViewModels.Add(newSpriteViewModel);
                }
            }
            
            if (e.OldItems != null) 
            {
                foreach (var spriteToDelete in e.OldItems.OfType<Scene.Sprite>())
                { 
                    var spriteViewModel = SpriteViewModels.FirstOrDefault(x => x.Sprite == spriteToDelete);
                    if (spriteViewModel != null)
                    {
                        spriteViewModel.PropertyChanged -= Scene_PropertyChanged;
                        SpriteViewModels.Remove(spriteViewModel);
                    }
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

        internal void RefreshSpriteViewModels()
        {
            m_ignoreChanges = true;
            foreach (var spriteView in SpriteViewModels)
            { 
                spriteView.Refresh();
            }
            m_ignoreChanges = false;
        }
    }
}
