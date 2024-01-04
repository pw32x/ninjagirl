using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Scenes.ViewModels;

namespace SceneMaster.GameObjectTemplates.ViewModels
{
    internal class GameObjectViewModel : EditorObjectViewModel
    {
        public GameObjectViewModel(GameObject gameObject, SceneViewModel sceneViewModel) : base(gameObject, sceneViewModel)
        {
        }
    }
}
