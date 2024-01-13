using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.Models;

namespace SceneMaster.Commands.Models
{

    public class CommandInfo : EditorObjectInfo
    {
        public string ParameterTypeName { get; set; }
        public string Filename { get; internal set; }

        public CommandInfo() : base(EditorObjectType.Command)
        { 

        }

        internal override EditorObject CreateEditorObject(int x, int y, Scene scene)
        {
            return new CommandObject(x, y, Name, this);
        }
    }
}