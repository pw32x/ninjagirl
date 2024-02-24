using MotionMaster.EditorObjects.ViewModels;
using MotionMaster.GameObjectTemplates.Models;
using MotionMaster.Scenes.ViewModels;

namespace MotionMaster.GameObjectTemplates.ViewModels
{
    internal class GameObjectViewModel : EditorObjectViewModel
    {
        public GameObjectViewModel(GameObject gameObject, SceneViewModel sceneViewModel) : base(gameObject, sceneViewModel)
        {
        }
    }
}
