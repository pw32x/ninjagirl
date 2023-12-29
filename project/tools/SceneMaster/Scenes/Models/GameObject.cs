using SceneMaster.GameObjectTemplates.Models;
using System.Windows.Media.Imaging;

namespace SceneMaster.Scenes.Models
{
    public class GameObject
    {
        public double X { get; set; }
        public double Y { get; set; }
        public string GameObjectTemplateName { get; set; }
        public GameObjectTemplate GameObjectTemplate { get; set; }
    }
}