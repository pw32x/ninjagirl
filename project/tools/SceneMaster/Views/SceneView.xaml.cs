using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.ViewModels;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using static SceneMaster.ViewModels.Scene;

namespace SceneMaster
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public partial class SceneView : UserControl
    {
        // Sprites in the scene are relative to the bitmap of the tiled map
        // but the sprites we see in the view are relative to the MainGrid
        public class SpriteView : ObservableObject
        { 
            public SpriteView(Sprite sprite)
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

        public ObservableCollection<SpriteView> SpriteViews { get; set; } = new();

        Scene m_scene;

        public SceneView()
        {
            InitializeComponent();
        }

        private void UserControl_DataContextChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
        {
            if (m_scene != null) 
            { 
                SpriteViews.Clear();
                m_scene.Sprites.CollectionChanged -= Sprites_CollectionChanged;
                m_scene = null;
            }

            m_scene = (Scene)e.NewValue;
            if (m_scene != null) 
            {
                m_scene.Sprites.CollectionChanged += Sprites_CollectionChanged;

                foreach (var sprite in m_scene.Sprites)
                { 
                    SpriteViews.Add(new SpriteView(sprite));
                }
            }
        }

        private void Sprites_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            { 
                foreach (var newSprite in e.NewItems.OfType<Scene.Sprite>())
                    SpriteViews.Add(new SpriteView(newSprite));
            }
            
            if (e.OldItems != null) 
            {
                foreach (var spriteToDelete in e.OldItems.OfType<Scene.Sprite>())
                { 
                    var spriteView = SpriteViews.FirstOrDefault(x => x.Sprite == spriteToDelete);
                    if (spriteView != null)
                    {
                        SpriteViews.Remove(spriteView);
                    }
                }
            }
        }

        private void Button_ClickReset(object sender, System.Windows.RoutedEventArgs e)
        {
            ZoomBorder?.Reset();
        }

        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (m_scene != null) 
            { 
                // convert the position clicked on the TileMapBitmapImage 
                // to a position on the tilemap.
                var mapPos = e.GetPosition(TileMapBitmapImage);
                int mapX = (int)((mapPos.X / TileMapBitmapImage.ActualWidth) * TileMapBitmapImage.Source.Width);
                int mapY = (int)((mapPos.Y / TileMapBitmapImage.ActualHeight) * TileMapBitmapImage.Source.Height);

                m_scene.CreateSprite(mapX, mapY);
            }
        }

        private void TileMapBitmapImage_LayoutUpdated(object sender, EventArgs e)
        {
            // GridToImageRatio and ImageToMapRatio tell us how to transform a point from the grid to the image.
            GeneralTransform transform = TileMapBitmapImage.TransformToAncestor(MainGrid);
            SpriteView.GridToImageOffset = transform.Transform(new Point(0, 0));

            if (TileMapBitmapImage.Source is not null)
            {
                SpriteView.ImageToMapRatio = TileMapBitmapImage.ActualHeight / TileMapBitmapImage.Source.Height;
            }

            foreach (var spriteView in SpriteViews)
            { 
                spriteView.Refresh();
            }
        }
    }
}
