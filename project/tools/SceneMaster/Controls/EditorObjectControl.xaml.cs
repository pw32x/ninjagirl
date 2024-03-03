using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.Scenes.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SceneMaster.Controls
{
    /// <summary>
    /// Interaction logic for EditorObjectControl.xaml
    /// </summary>
    public partial class EditorObjectControl : UserControl
    {
        private Point m_startPoint;
        private bool m_isDragging = false;
        private EditorObjectViewModel m_editorObjectViewModel;

        public EditorObjectControl()
        {
            InitializeComponent();
        }

        private void EditorObjectControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            m_editorObjectViewModel = (EditorObjectViewModel)e.NewValue;
        }

        private void EditorObjectControl_MouseDown(object sender, MouseButtonEventArgs e)
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

        private void EditorObjectControl_MouseMove(object sender, MouseEventArgs e)
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

                if (m_editorObjectViewModel.SpawnX == m_editorObjectViewModel.X &&
                    m_editorObjectViewModel.SpawnY == m_editorObjectViewModel.Y &&
                    !m_editorObjectViewModel.SpawnPointIsIndependant)
                {
                    // move the spawn point to if it's the same spot and 
                    // we're not using it.
                    m_editorObjectViewModel.SpawnX += offsetX;
                    m_editorObjectViewModel.SpawnY += offsetY;
                }

                m_editorObjectViewModel.X += offsetX;
                m_editorObjectViewModel.Y += offsetY;


                m_startPoint = currentPoint;
            }
        }

        private void EditorObjectControl_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_isDragging = false;
                (sender as UIElement)?.ReleaseMouseCapture();
            }
        }

        private void EditorObjectControl_MouseLeave(object sender, MouseEventArgs e)
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
