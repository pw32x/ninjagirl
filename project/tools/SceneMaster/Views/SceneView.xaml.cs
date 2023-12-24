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

                sceneViewModel.Scene.CreateGameObject(mapX, mapY);
            }
        }

        private void TileMapBitmapImage_LayoutUpdated(object sender, EventArgs e)
        {
            SceneViewModel.ZoomFactor = ZoomBorder.ZoomX;
        }
    }
}
