using SceneMaster.ViewModels;
using System;
using System.Windows.Controls;
using System.Windows.Input;
using Wpf.Controls.PanAndZoom;

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

        private void UserControl_DataContextChanged(object sender, System.Windows.DependencyPropertyChangedEventArgs e)
        {
            Scene scene = (Scene)e.NewValue;
            if (scene != null) 
            { 
                var bitmap = scene.TiledMapBitmapSource;
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
                var pos = e.GetPosition(TileMapBitmapImage);
                int bitmapX = (int)((pos.X / TileMapBitmapImage.ActualWidth) * TileMapBitmapImage.Source.Width);
                int bitmapY = (int)((pos.Y / TileMapBitmapImage.ActualHeight) * TileMapBitmapImage.Source.Height);

                scene.LeftClickDown(bitmapX, bitmapY);
            }
        }
    }
}
