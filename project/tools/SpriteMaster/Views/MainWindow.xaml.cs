using System.Windows;
using SpriteMaster.ViewModels;

namespace SpriteMaster
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
