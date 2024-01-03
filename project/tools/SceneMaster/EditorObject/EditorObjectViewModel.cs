using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.ViewModels;

namespace SceneMaster.EditorObjects.ViewModels
{
    public class EditorObjectViewModel : ObservableObject
    {
        public EditorObjectViewModel(EditorObject editorObject,
                                     SceneViewModel sceneViewModel)
        {
            EditorObject = editorObject;
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
            get => EditorObject.X;
            set
            {
                EditorObject.X = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedX));
            }
        }

        public double Y
        {
            get => EditorObject.Y;
            set
            {
                EditorObject.Y = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SnappedY));
            }
        }

        public double SnappedX { get => (int)EditorObject.X; }
        public double SnappedY { get => (int)EditorObject.Y; }

        public double Width { get => EditorObject.EditorObjectInfo.Visual.Width; }
        public double Height { get => EditorObject.EditorObjectInfo.Visual.Height; }

        public EditorObject EditorObject { get; set; }

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
