using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Models;
using System.Windows;

namespace SceneMaster.ViewModels
{

    // Sprites in the scene are relative to the bitmap of the tiled map
    // but the sprites we see in the view are relative to the MainGrid
    public class SpriteViewModel : ObservableObject
    { 
        public SpriteViewModel(Scene.Sprite sprite)
        {
            Sprite = sprite;
        }

        public void Refresh()
        {
            OnPropertyChanged("X");
            OnPropertyChanged("Y");
            OnPropertyChanged("Width");
            OnPropertyChanged("Height");
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

        // GridToImageRatio and ImageToMapRatio tell us how to transform a point from the grid to the image.
        public static Point GridToImageOffset { get; set; } = new Point(0, 0);
        public static double ImageToMapRatio { get; set; } = 1;
    }
}
