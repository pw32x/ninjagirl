using TemplateMaster.Utils;
using System.Xml;

namespace TemplateMaster
{
    public class GameObjectTemplate
    {
        public string Name { get; set; } = "";
        public string Health { get; set; } = "0";
        public string Damage { get; set; } = "0";
        public string RectLeft { get; set; } = "0";
        public string RectTop { get; set; } = "0";
        public string RectRight { get; set; } = "0";
        public string RectBottom { get; set; } = "0";
        public string GameObjectType { get; set; } = "";
        public string ResourceInfo { get; set; } = "";
        public string CreateFunction { get; set; } = "";

        public void LoadGameProperties(XmlElement gamePropertiesNode)
        {
            Health = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Health));
            Damage = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(Damage));

            RectLeft = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectLeft));
            RectTop = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectTop));
            RectRight = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectRight));
            RectBottom = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(RectBottom));

            GameObjectType = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(GameObjectType));
            ResourceInfo = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(ResourceInfo));
            CreateFunction = XmlUtils.GetChildValue<string>(gamePropertiesNode, nameof(CreateFunction));
        }

        public void Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            if (root[nameof(Name)] is var nameNode && nameNode != null)
            {
                Name = nameNode.Attributes["value"]?.Value ?? "UnnamedGameObjectTemplate";
            }

            if (root["GameProperties"] is var gamePropertiesNode && gamePropertiesNode != null) 
            {
                LoadGameProperties(gamePropertiesNode);
            }
        }
    }
}
