using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using System.Xml;

namespace SceneMaster.Commands.Models
{
    public class CommandObject : EditorObject
    {
        public CommandObject(double x, 
                             double y, 
                             string name, 
                             CommandInfo commandInfo) : base(x, y, name, commandInfo)
        {
        }

        public string CommandName => CommandInfo.Name;
        public CommandInfo CommandInfo => EditorObjectInfo as CommandInfo;

        internal override ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int editorCounter)
        {
            return new ExportedCommandData();
        }

        internal override string BuildSceneCommand(ExportedCommandData exportedCommandData)
        {
            throw new System.NotImplementedException();
        }


        internal override XmlElement ExportToXml(XmlDocument doc)
        {
            var newNode = base.ExportToXml(doc);
            newNode.SetAttribute(nameof(CommandInfo.Name), CommandInfo.Name);
            return newNode;
        }
    }
}