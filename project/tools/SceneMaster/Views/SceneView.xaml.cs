﻿using CommunityToolkit.Mvvm.ComponentModel;
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

        private void DrawGridLines()
        {
            SceneViewModel sceneViewModel = (SceneViewModel)DataContext;
            if (sceneViewModel == null)
                return;


            int tileWidth = sceneViewModel.Scene.TiledMap.TileWidth;
            int tileHeight = sceneViewModel.Scene.TiledMap.TileHeight;

            int mapWidth = sceneViewModel.Scene.TiledMap.Width * tileWidth;
            int mapHeight = sceneViewModel.Scene.TiledMap.Height * tileHeight;

            GridCanvas.Children.Clear();


            DrawingVisual drawingVisual = new DrawingVisual();
            using (DrawingContext drawingContext = drawingVisual.RenderOpen())
            {
                Pen pen = new Pen(Brushes.Black, 1); // Change color and thickness as needed

                // Draw vertical grid lines
                for (double x = 0; x <= mapWidth; x += tileWidth) // Adjust the interval as needed
                {
                    drawingContext.DrawLine(pen, new Point(x, 0), new Point(x, mapHeight));
                }

                // Draw horizontal grid lines
                for (double y = 0; y <= mapHeight; y += tileHeight) // Adjust the interval as needed
                {
                    drawingContext.DrawLine(pen, new Point(0, y), new Point(mapWidth, y));
                }
            }

            // Create a DrawingImage from the DrawingVisual
            DrawingImage drawingImage = new DrawingImage(drawingVisual.Drawing);

            // Create an Image control and set its Source to the DrawingImage
            Image image = new Image { Source = drawingImage };

            // Add the Image control to the Canvas
            GridCanvas.Children.Add(image);
        }

        private void SceneMasterSceneView_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            //DrawGridLines();
        }

        private void SceneMasterSceneView_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (DataContext is SceneViewModel sceneViewModel)
            {
                sceneViewModel.PropertyChanged += SceneViewModel_PropertyChanged;
            }


            DrawGridLines();

        }

        private void SceneViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (DataContext is SceneViewModel sceneViewModel)
            {
                if (e.PropertyName == nameof(sceneViewModel.Scene))
                    DrawGridLines();
            }
        }
    }
}
