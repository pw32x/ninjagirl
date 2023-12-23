using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.ViewModels;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using SceneMaster.Models;

namespace SceneMaster
{
    /// <summary>
    /// Interaction logic for SceneView.xaml
    /// </summary>
    public partial class SceneView : UserControl
    {
        public SceneView()
        {
            InitializeComponent();
        }

        private void Button_ClickReset(object sender, System.Windows.RoutedEventArgs e)
        {
            ZoomBorder?.Reset();
        }

        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            SceneViewModel sceneViewModel = (SceneViewModel)DataContext;
            if (sceneViewModel != null) 
            { 
                // convert the position clicked on the TileMapBitmapImage 
                // to a position on the tilemap.
                var mapPos = e.GetPosition(TileMapBitmapImage);
                int mapX = (int)((mapPos.X / TileMapBitmapImage.ActualWidth) * TileMapBitmapImage.Source.Width);
                int mapY = (int)((mapPos.Y / TileMapBitmapImage.ActualHeight) * TileMapBitmapImage.Source.Height);

                sceneViewModel.Scene.CreateSprite(mapX, mapY);
            }
        }

        private void TileMapBitmapImage_LayoutUpdated(object sender, EventArgs e)
        {
            // the spriteviewmodels depend on the size/width of the TileMapBitmapImage and
            // MainGrid to place themselves correctly. This is a weird way of updating their
            // ratios I'll admit. 

            // GridToImageRatio and ImageToMapRatio tell us how to transform a point from the grid to the image.
            GeneralTransform transform = TileMapBitmapImage.TransformToAncestor(MainGrid);
            var gridToImageOffset = transform.Transform(new Point(0, 0));
            var imageToMapRatio = SpriteViewModel.ImageToMapRatio;

            SpriteViewModel.GridToImageOffset = gridToImageOffset;

            if (TileMapBitmapImage.Source is not null)
            {
                imageToMapRatio = TileMapBitmapImage.ActualHeight / TileMapBitmapImage.Source.Height;
            }

            SpriteViewModel.ZoomFactor = ZoomBorder.ZoomX;

            if ((gridToImageOffset != SpriteViewModel.GridToImageOffset || 
                imageToMapRatio != SpriteViewModel.ImageToMapRatio) &&
                DataContext is SceneViewModel sceneViewModel)
            {
                SpriteViewModel.GridToImageOffset = gridToImageOffset;
                SpriteViewModel.ImageToMapRatio = imageToMapRatio;

                sceneViewModel.RefreshSpriteViewModels();
            }
        }
    }
}
