using System.Windows;
using SceneMaster.ViewModels;

namespace SceneMaster
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
    }
}
