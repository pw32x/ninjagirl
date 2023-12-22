using SceneMaster.ViewModels;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using Wpf.Controls.PanAndZoom;
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
        public class SpriteView
        { 
            public SpriteView(Sprite sprite)
            {
                X = (sprite.X * ImageToMapRatio) + GridToImageOffset.X;
                Y = (sprite.Y * ImageToMapRatio) + GridToImageOffset.Y;
                Width = (sprite.Bitmap.Width * ImageToMapRatio);
                Height = (sprite.Bitmap.Height * ImageToMapRatio);
                Sprite = sprite;
            }

            public double X { get; set; }
            public double Y { get; set; }
            public double Width { get; set; }
            public double Height { get; set; }
            public Scene.Sprite Sprite { get; set; }
            public static Point GridToImageOffset { get; set; } = new Point(0, 0);
            public static double ImageToMapRatio { get; set; } = 1;
        }

        public ObservableCollection<SpriteView> SpriteViews { get; set; } = new ObservableCollection<SpriteView> { };

        public SceneView()
        {
            InitializeComponent();
        }

        private void UserControl_DataContextChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
        {
            Scene scene = (Scene)e.NewValue;
            if (scene != null) 
            { 
                var bitmap = scene.TiledMapBitmapSource;

                SpriteViews.Clear();
                foreach (var sprite in scene.Sprites)
                { 
                    SpriteViews.Add(new SpriteView(sprite));
                }
            }
        }

        private void Button_ClickReset(object sender, System.Windows.RoutedEventArgs e)
        {
            ZoomBorder?.Reset();
        }

        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Scene scene = (Scene)DataContext;
            if (scene != null) 
            { 
                var viewPos = e.GetPosition(MainGrid);

                var mapPos = e.GetPosition(TileMapBitmapImage);
                int mapX = (int)((mapPos.X / TileMapBitmapImage.ActualWidth) * TileMapBitmapImage.Source.Width);
                int mapY = (int)((mapPos.Y / TileMapBitmapImage.ActualHeight) * TileMapBitmapImage.Source.Height);

                var sprite = scene.CreateSprite(mapX, mapY);

                SpriteViews.Add(new SpriteView(sprite));
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
        }
    }
}
