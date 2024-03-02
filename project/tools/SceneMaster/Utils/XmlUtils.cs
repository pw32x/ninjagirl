using System;
using System.Xml;

namespace SceneMaster.Utils
{
    internal class XmlUtils
    {
        public static XmlElement OpenXmlDocument(string filePath, string rootNodeName)
        {
            var doc = new XmlDocument();
            doc.Load(filePath);

            var root = doc[rootNodeName];

            if (root == null)
                throw new Exception($"No {rootNodeName} node found in {filePath}.");

            return root;
        }

        public static T GetValue<T>(XmlElement node, string attributeName = "value", T defaultValue = default(T))
        {
            string attributeValue = node.Attributes[attributeName]?.Value ?? "";

            if (TryParse<T>(attributeValue, out var parsedValue))
            {
                return parsedValue;
            }
            else
            {
                return defaultValue;
            }
        }

        public static T GetChildValue<T>(XmlElement node, string childNodeName, string attributeName = "value")
        {
             var childNode = node[childNodeName];

            if (childNode == null)
                return default(T);

            string attributeValue = childNode.Attributes[attributeName]?.Value ?? "";

            if (TryParse<T>(attributeValue, out var parsedValue))
            {
                return parsedValue;
            }
            else
            {
                return default(T);
            }
        }


        private static bool TryParse<T>(string value, out T result)
        {
            try
            {
                if (typeof(T).IsEnum)
                    result = (T)Enum.Parse(typeof(T), value);
                else 
                    result = (T)Convert.ChangeType(value, typeof(T));

                return true;
            }
            catch (Exception)
            {
                result = default(T);
                return false;
            }
        }

        internal static bool HasChild(XmlElement node, string childNodeName)
        {
            var childNode = node[childNodeName];

            return (childNode != null);
        }
    }
}
