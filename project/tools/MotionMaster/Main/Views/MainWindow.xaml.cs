using System.Windows;
using MotionMaster.Main.ViewModels;

namespace MotionMaster
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = MainViewModel;
        }

        public MainViewModel MainViewModel { get; } = new MainViewModel();

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (!MainViewModel.CheckForSave())
                e.Cancel = true;
        }
    }
}
