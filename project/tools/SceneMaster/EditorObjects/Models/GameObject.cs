using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Utils;
using System.IO;
using System.Text;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    public class GameObject : EditorObject
    {
        public GameObject(double x, 
                          double y, 
                          string name, 
                          GameObjectTemplate gameObjectTemplate) : base(x, y, name, gameObjectTemplate)
        {
        }

        public GameObject(XmlElement gameObjectNode, 
                          GameObjectTemplateLibrary gameObjectTemplateLibrary) : base(gameObjectNode)
        {
            string gameObjectTemplateName = XmlUtils.GetValue<string>(gameObjectNode, nameof(GameObject.GameObjectTemplateName));

            if (!gameObjectTemplateLibrary.GameObjectTemplates.TryGetValue(gameObjectTemplateName, out var gameObjectTemplate))
            {
                gameObjectTemplate = gameObjectTemplateLibrary.DefaultGameObjectTemplate;
            }

            EditorObjectInfo = gameObjectTemplate;
        }

        public string GameObjectTemplateName => GameObjectTemplate.Name;
        public GameObjectTemplate GameObjectTemplate => EditorObjectInfo as GameObjectTemplate;

        internal override ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int exportCounter)
        {
            if (GameObjectTemplate.GameObjectType == GameObjectType.CommandRunner)
            {
                string createInfoName = sceneName + "_" + "createInfo" + exportCounter;

                // do nothing
                var exportedCommandData = new ExportedCommandData();
                exportedCommandData.CreateInfoTypeName = createInfoName;

                StringBuilder sb = new();
                sb.Append("const CommandRunnerCreateInfo " + createInfoName + " = { ");
                string templateName = Path.GetFileNameWithoutExtension(GameObjectTemplate.FilePath) + "_template";
                int x = (int)(X < 0 ? 0 : X);
                int y = (int)(Y < 0 ? 0 : Y);
                sb.Append("&" + templateName + ", " + x + ", " + y + ", NULL");
                sb.AppendLine(" };");
                exportedCommandData.ExportedCreateInfo = sb.ToString();

                exportedCommandData.CommandToUse = "ObjectManager_CreateObjectByCreateInfo";
                return exportedCommandData;
            }
            else 
            {
                string createInfoName = sceneName + "_" + "createInfo" + exportCounter;

                var exportedCommandData = new ExportedCommandData();
                exportedCommandData.CreateInfoTypeName = createInfoName;

                StringBuilder sb = new();
                sb.Append("const CreateInfo " + createInfoName + " = { ");
                string templateName = Path.GetFileNameWithoutExtension(GameObjectTemplate.FilePath) + "_template";
                int x = (int)(X < 0 ? 0 : X) + GameObjectTemplate.Visual.OffsetX;
                int y = (int)(Y < 0 ? 0 : Y) + GameObjectTemplate.Visual.OffsetY;
                sb.Append("&" + templateName + ", " + x + ", " + y);
                sb.AppendLine(" };");
                exportedCommandData.ExportedCreateInfo = sb.ToString();
                exportedCommandData.CommandToUse = "ObjectManager_CreateObjectByCreateInfo";
                return exportedCommandData;
            }
            /*
            case GameObjectTemplates.Models.EditorObjectType.Palette:
            {
                var exportedCommandData = new ExportedCommandData();
                exportedCommandData.ExportedCreateInfo = "";
                exportedCommandData.CreateInfoTypeName = "";
                exportedCommandData.CommandToUse = gameObject.GameObjectTemplate.InitFunction;
                exportedCommandDatas.Add(gameObject, exportedCommandData);
                break;
            }
            */
        }

        internal override string BuildSceneCommand(ExportedCommandData exportedCommandData)
        {
            // clamp to 0
            int x = (int)(X < 0 ? 0 : X);

            string finalExportedCommandData = "NULL";
            if (!string.IsNullOrEmpty(exportedCommandData.CreateInfoTypeName))
            {
                finalExportedCommandData = "&" + exportedCommandData.CreateInfoTypeName;

                if (GameObjectTemplate.GameObjectType == GameObjectType.CommandRunner)
                {
                    finalExportedCommandData = "(const CreateInfo*)" + finalExportedCommandData;
                }
            }

            return "{ " + x + ", (CommandFunction)" + exportedCommandData.CommandToUse + ", " + finalExportedCommandData + " },";
        }

        internal override XmlElement ExportToXml(XmlDocument doc)
        {
            var newNode = base.ExportToXml(doc);
            newNode.SetAttribute(nameof(GameObjectTemplateName), GameObjectTemplateName);
            return newNode;
        }
    }
}