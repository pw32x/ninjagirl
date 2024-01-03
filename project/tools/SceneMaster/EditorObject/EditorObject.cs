using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.GameObjectTemplates.Models;
using System;
using System.Xml;

namespace SceneMaster.EditorObjects.Models
{
    public class ExportedCommandData
    {
        public string CreateInfoTypeName { get; set; }
        public string ExportedCreateInfo { get; set; }
        public string CommandToUse { get; set; }
    }

    abstract public class EditorObject
    {
        public EditorObject(double x, 
                            double y, 
                            string name, 
                            EditorObjectInfo editorObjectInfo)
        {
            X = x;
            Y = y;
            Name = name;
            EditorObjectInfo = editorObjectInfo;
        }

        public double X { get; set; }
        public double Y { get; set; }
        public string Name { get; private set; }
        public EditorObjectType EditorObjectType => EditorObjectInfo.EditorObjectType;
        public EditorObjectInfo EditorObjectInfo { get; private set; }

        abstract internal ExportedCommandData BuildExportCommandData(string sceneName, 
                                                                     int exportCounter);
        internal abstract string BuildSceneCommand(ExportedCommandData exportedCommandData);

        internal virtual XmlElement ExportToXml(XmlDocument doc)
        {
            var newNode = doc.CreateElement(EditorObjectType.ToString());

            newNode.SetAttribute(nameof(Name), Name);
            newNode.SetAttribute(nameof(X), X.ToString());
            newNode.SetAttribute(nameof(Y), Y.ToString());
            return newNode;
        }
    }
}