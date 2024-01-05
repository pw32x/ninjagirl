using SceneMaster.Commands.Models;
using SceneMaster.EditorObjects.ViewModels;
using SceneMaster.Scenes.ViewModels;
using System.ComponentModel.DataAnnotations;

namespace SceneMaster.EditorObjects.CommandLibrary.ViewModels
{
    internal class CommandObjectViewModel : EditorObjectViewModel
    {
        public CommandObjectViewModel(CommandObject commandObject, SceneViewModel sceneViewModel) : base(commandObject, sceneViewModel)
        {
        }

        public string CommandValue 
        { 
            get => (EditorObject as CommandObject).CommandValue;
            set 
            {
                (EditorObject as CommandObject).CommandValue = value;
                OnPropertyChanged(nameof(CommandValue));
            }
        }

        [DataType(DataType.MultilineText)]
        public string PreCommandData
        { 
            get => (EditorObject as CommandObject).PreCommandData;
            set 
            {
                (EditorObject as CommandObject).PreCommandData = value;
                OnPropertyChanged(nameof(PreCommandData));
            }
        }
    }
}
