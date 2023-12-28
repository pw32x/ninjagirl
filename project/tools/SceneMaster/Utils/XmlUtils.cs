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
    }
}
