using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Models;
using System;
using System.Windows;

namespace SceneMaster.ViewModels
{

    // Sprites in the scene are relative to the bitmap of the tiled map
    // but the sprites we see in the view are relative to the MainGrid
    public class SpriteViewModel : ObservableObject
    { 
        public SpriteViewModel(Scene.Sprite sprite, 
                               SceneViewModel sceneViewModel)
        {
            Sprite = sprite;
            SceneViewModel = sceneViewModel;
        }

        public void RefreshVisual()
        {
            OnPropertyChanged("X");
            OnPropertyChanged("Y");
            OnPropertyChanged("Width");
            OnPropertyChanged("Height");
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
            get => (Sprite.X * ImageToMapRatio) + GridToImageOffset.X;
            set 
            { 
                Sprite.X = (value - GridToImageOffset.X) / ImageToMapRatio;
                OnPropertyChanged();
            }
        }

        public double Y 
        { 
            get => (Sprite.Y * ImageToMapRatio) + GridToImageOffset.Y;
            set
            { 
                Sprite.Y = (value - GridToImageOffset.Y) / ImageToMapRatio;
                OnPropertyChanged();
            }
        }

        public double Width { get => Sprite.Bitmap.Width * ImageToMapRatio; }
        public double Height { get => Sprite.Bitmap.Height * ImageToMapRatio; }

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

        // GridToImageRatio and ImageToMapRatio tell us how to transform a point from the grid to the image.
        public static Point GridToImageOffset { get; set; } = new Point(0, 0);
        public static double ImageToMapRatio { get; set; } = 1;
        public static double ZoomFactor { get; set; } = 1;
    }
}
