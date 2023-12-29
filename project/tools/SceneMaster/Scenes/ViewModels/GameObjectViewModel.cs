using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Scenes.Models;

namespace SceneMaster.Scenes.ViewModels
{
    public class GameObjectViewModel : ObservableObject
    {
        public GameObjectViewModel(GameObject gameObject,
                                   SceneViewModel sceneViewModel)
        {
            GameObject = gameObject;
            SceneViewModel = sceneViewModel;
        }

        internal void Select()
        {
            SceneViewModel.Select(this);
        }

        internal void Deselect()
        {
            SceneViewModel.Deselect(this);
        }

        public double X
        {
            get => GameObject.X;
            set
            {
                GameObject.X = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedX));
            }
        }

        public double Y
        {
            get => GameObject.Y;
            set
            {
                GameObject.Y = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedY));
            }
        }

        public double SnappedX { get => (int)GameObject.X; }
        public double SnappedY { get => (int)GameObject.Y; }

        public double Width { get => GameObject.GameObjectTemplate.Visual.Width; }
        public double Height { get => GameObject.GameObjectTemplate.Visual.Height; }

        public GameObject GameObject { get; set; }

        public SceneViewModel SceneViewModel { get; internal set; }

        private bool m_isSelected = false;
        public bool IsSelected
        {
            get => m_isSelected;
            set
            {
                SetProperty(ref m_isSelected, value);
            }
        }
    }
}
