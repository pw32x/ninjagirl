using SceneMaster.Scenes.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SceneMaster.Controls
{
    /// <summary>
    /// Interaction logic for GameObjectControl.xaml
    /// </summary>
    public partial class GameObjectControl : UserControl
    {
        private Point m_startPoint;
        private bool m_isDragging = false;
        private GameObjectViewModel m_gameObjectViewModel;

        public GameObjectControl()
        {
            InitializeComponent();
        }

        private void GameObjectControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            m_gameObjectViewModel = (GameObjectViewModel)e.NewValue;
        }

        private void GameObjectControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_gameObjectViewModel.Select();

                m_startPoint = e.GetPosition(Parent as UIElement);
                m_isDragging = true;

                // Bring the control to the front when clicked
                Panel.SetZIndex(this, 1);

                (sender as UIElement)?.CaptureMouse();
            }
        }

        private void GameObjectControl_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_isDragging)
            {
                Point currentPoint = e.GetPosition(null);

                double offsetX = currentPoint.X - m_startPoint.X;
                double offsetY = currentPoint.Y - m_startPoint.Y;

                offsetX /= SceneViewModel.ZoomFactor;
                offsetY /= SceneViewModel.ZoomFactor;

                if (offsetX == 0 && offsetY == 0)
                    return;

                m_gameObjectViewModel.X += offsetX;
                m_gameObjectViewModel.Y += offsetY;

                m_startPoint = currentPoint;
            }
        }

        private void GameObjectControl_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_isDragging = false;
                (sender as UIElement)?.ReleaseMouseCapture();
            }
        }

        private void GameObjectControl_MouseLeave(object sender, MouseEventArgs e)
        {
            //isDragging = false;
            //var gameObjectViewModel = (GameObjectViewModel)DataContext;
            //if (gameObjectViewModel != null)
            //{ 
            //    gameObjectViewModel.IsSelected = false;
            //}
        }


    }
}
