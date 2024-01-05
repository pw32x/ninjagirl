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

        public string m_preCommandData = ""; // declares a struct or anything before the list of commands in the exported scene
        public string PreCommandData { get => m_preCommandData; set => m_preCommandData = value; }

        public string CommandName => CommandInfo.Name;
        public CommandInfo CommandInfo => EditorObjectInfo as CommandInfo;

        public CommandObject(XmlElement commandObjectNode, 
                             CommandLibrary commandLibrary) : base(commandObjectNode)
        {
            string commandInfoName = XmlUtils.GetValue<string>(commandObjectNode, nameof(CommandInfo.Name));

            if (!commandLibrary.CommandInfos.TryGetValue(commandInfoName, out var commandInfo))
                throw new System.Exception("No command info for \"" + commandInfoName + " found.");

            CommandValue = XmlUtils.GetValue<string>(commandObjectNode, nameof(CommandValue));
            PreCommandData = XmlUtils.GetValue<string>(commandObjectNode, nameof(PreCommandData));

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
            newNode.SetAttribute(nameof(CommandValue), CommandValue);
            newNode.SetAttribute(nameof(PreCommandData), PreCommandData);
            return newNode;
        }
    }
}