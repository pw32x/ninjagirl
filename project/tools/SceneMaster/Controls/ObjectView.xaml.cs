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
        private Point startPoint;
        private bool isDragging = false;

        public ObjectView()
        {
            InitializeComponent();
        }

        private void ObjectView_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                startPoint = e.GetPosition(Parent as UIElement);
                isDragging = true;

                // Bring the control to the front when clicked
                Panel.SetZIndex(this, 1);
            }
        }

        private void ObjectView_MouseMove(object sender, MouseEventArgs e)
        {
            if (isDragging)
            {
                Point currentPoint = e.GetPosition(Parent as UIElement);

                double offsetX = currentPoint.X - startPoint.X;
                double offsetY = currentPoint.Y - startPoint.Y;

                var spriteViewModel = (SpriteViewModel)DataContext;
                if (spriteViewModel != null)
                { 
                    spriteViewModel.X += offsetX;
                    spriteViewModel.Y += offsetY;
                }

                startPoint = currentPoint;
            }
        }

        private void ObjectView_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                isDragging = false;
            }
        }
    }
}
