using SceneMaster.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SceneMaster.Controls
{
    /// <summary>
    /// Interaction logic for ObjectView.xaml
    /// </summary>
    public partial class ObjectView : UserControl
    {
        private Point m_startPoint;
        private bool m_isDragging = false;
        private SpriteViewModel m_spriteViewModel;

        public ObjectView()
        {
            InitializeComponent();
        }

        private void UserControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            m_spriteViewModel = (SpriteViewModel)e.NewValue;
        }

        private void ObjectView_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_spriteViewModel.Select();

                m_startPoint = e.GetPosition(Parent as UIElement);
                m_isDragging = true;

                // Bring the control to the front when clicked
                Panel.SetZIndex(this, 1);

                (sender as UIElement)?.CaptureMouse();
            }
        }

        private void ObjectView_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_isDragging)
            {
                Point currentPoint = e.GetPosition(null);

                double offsetX = currentPoint.X - m_startPoint.X;
                double offsetY = currentPoint.Y - m_startPoint.Y;

                offsetX /= SceneViewModel.ZoomFactor;
                offsetY /= SceneViewModel.ZoomFactor;

                m_spriteViewModel.X += offsetX;
                m_spriteViewModel.Y += offsetY;

                m_startPoint = currentPoint;
            }
        }

        private void ObjectView_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                m_isDragging = false;
                (sender as UIElement)?.ReleaseMouseCapture();
            }
        }

        private void ObjectView_MouseLeave(object sender, MouseEventArgs e)
        {
            //isDragging = false;
            //var spriteViewModel = (SpriteViewModel)DataContext;
            //if (spriteViewModel != null)
            //{ 
            //    spriteViewModel.IsSelected = false;
            //}
        }


    }
}
