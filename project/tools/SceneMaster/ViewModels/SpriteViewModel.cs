using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Models;
using System;
using System.Windows;

namespace SceneMaster.ViewModels
{
    public class SpriteViewModel : ObservableObject
    { 
        public SpriteViewModel(Scene.Sprite sprite, 
                               SceneViewModel sceneViewModel)
        {
            Sprite = sprite;
            SceneViewModel = sceneViewModel;
        }

        internal void Select()
        {
            SceneViewModel.Select(this);
        }

        internal void Deselect()
        {
            SceneViewModel.Deselect(this);
        }

        public double X 
        { 
            get => Sprite.X;
            set 
            { 
                Sprite.X = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedX));
            }
        }

        public double Y 
        { 
            get => Sprite.Y;
            set
            { 
                Sprite.Y = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedY));
            }
        }

        public double SnappedX { get => (int)Sprite.X; }
        public double SnappedY { get => (int)Sprite.Y; }

        public double Width { get => Sprite.Bitmap.Width; }
        public double Height { get => Sprite.Bitmap.Height; }

        public Scene.Sprite Sprite { get; set; }

        public SceneViewModel SceneViewModel { get; internal set; }

        private bool m_isSelected = false;
        public bool IsSelected 
        { 
            get => m_isSelected; 
            set
            {
                SetProperty(ref m_isSelected, value); 
            }
        } 
    }
}
