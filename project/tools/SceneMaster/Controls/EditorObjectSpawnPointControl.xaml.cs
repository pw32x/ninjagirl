using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.Scenes.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SceneMaster.Controls
{
    /// <summary>
    /// Interaction logic for EditorObjectSpawnPointControl.xaml
    /// </summary>
    public partial class EditorObjectSpawnPointControl : UserControl
    {
        private Point m_startPoint;
        private bool m_isDragging = false;
        private EditorObjectViewModel m_editorObjectViewModel;

        public EditorObjectSpawnPointControl()
        {
            InitializeComponent();
        }

        private void EditorObjectSpawnPointControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            m_editorObjectViewModel = (EditorObjectViewModel)e.NewValue;
        }

        private void EditorObjectSpawnPointControl_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_editorObjectViewModel.Select();

                m_startPoint = e.GetPosition(Parent as UIElement);
                m_isDragging = true;

                // Bring the control to the front when clicked
                Panel.SetZIndex(this, 1);

                (sender as UIElement)?.CaptureMouse();
            }
        }

        private void EditorObjectSpawnPointControl_MouseMove(object sender, MouseEventArgs e)
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

                m_editorObjectViewModel.SpawnX += offsetX;
                m_editorObjectViewModel.SpawnY += offsetY;

                m_startPoint = currentPoint;
            }
        }

        private void EditorObjectSpawnPointControl_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_isDragging = false;
                (sender as UIElement)?.ReleaseMouseCapture();
            }
        }

        private void EditorObjectSpawnPointControl_MouseLeave(object sender, MouseEventArgs e)
        {
            //isDragging = false;
            //var editorObjectViewModel = (EditorObjectViewModel)DataContext;
            //if (editorObjectViewModel != null)
            //{ 
            //    editorObjectViewModel.IsSelected = false;
            //}
        }


    }
}
