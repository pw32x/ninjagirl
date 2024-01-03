using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjects.Models;

namespace SceneMaster.Commands.Models
{

    public class CommandInfo : EditorObjectInfo
    {
        public string ParameterTypeName;

        public CommandInfo() : base(EditorObjectType.Command)
        { 
            
        }

        internal override EditorObject CreateEditorObject(int x, int y)
        {
            return new CommandObject(x, y, Name, this);
        }
    }
}