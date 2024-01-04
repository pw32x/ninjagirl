using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Utils;
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

        public string m_commandValue = "";
        public string CommandValue { get => m_commandValue; set => m_commandValue = value; }

        public string CommandName => CommandInfo.Name;
        public CommandInfo CommandInfo => EditorObjectInfo as CommandInfo;

        public CommandObject(XmlElement commandObjectNode, 
                             CommandLibrary commandLibrary) : base(commandObjectNode)
        {
            string commandInfoName = XmlUtils.GetValue<string>(commandObjectNode, nameof(CommandInfo.Name));

            if (!commandLibrary.CommandInfos.TryGetValue(commandInfoName, out var commandInfo))
                throw new System.Exception("No command info for \" " + commandInfoName + " found.");

            EditorObjectInfo = commandInfo;
        }

        internal override ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int editorCounter)
        {
            return new ExportedCommandData();
        }

        internal override string BuildSceneCommand(ExportedCommandData exportedCommandData)
        {
            // clamp to 0
            int x = (int)(X < 0 ? 0 : X);

            return "{ " + x + ", (CommandFunction)" + CommandInfo.Name.Replace(" ", "") + ", " + CommandValue + " },";
        }


        internal override XmlElement ExportToXml(XmlDocument doc)
        {
            var newNode = base.ExportToXml(doc);
            newNode.SetAttribute(nameof(CommandInfo.Name), CommandInfo.Name);
            return newNode;
        }
    }
}