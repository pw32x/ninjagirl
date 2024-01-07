using PropertyTools.DataAnnotations;
using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.Xml;

namespace SceneMaster.EditorObjectLibrary.Models
{
    public enum EditorObjectType
    {
        GameObject,
        Command
    }

    public abstract class EditorObjectInfo
    {
        public EditorObjectInfo(EditorObjectType editorObjectType)
        {
            EditorObjectType = editorObjectType;
        }

        [System.ComponentModel.ReadOnly(true)]
        public string Name { get; set; }

        [Browsable(false)]
        public bool IsEditorVisible { get; protected set; }

        [System.ComponentModel.ReadOnly(true)]
        [SelectorStyle(SelectorStyle.ComboBox)]
        public EditorObjectType EditorObjectType { get; }

        // editor properties
        [Browsable(false)]
        public Visual Visual { get; } = new();

        [System.ComponentModel.ReadOnly(true)]
        public string ResourceInfo { get; set; }

        [System.ComponentModel.Browsable(false)]
        public List<string> TemplateNameReferences { get; } = new List<string>();

        [System.ComponentModel.Browsable(false)]
        public List<GameObjectTemplate> TemplateReferences { get; } = new();

        public IEnumerable<string> ResourceInfos()
        {
            yield return ResourceInfo;

            foreach (var resourceInfo in TemplateReferences)
                yield return resourceInfo.ResourceInfo;
        }

        abstract internal EditorObject CreateEditorObject(int x, int y);

        private void LoadReferences(XmlElement referencesNode)
        {
            XmlNodeList templateNodes = referencesNode.GetElementsByTagName("Template");

            foreach (XmlElement templateNode in templateNodes) 
            {
                string templateReference = XmlUtils.GetValue<string>(templateNode);
                TemplateNameReferences.Add(templateReference);
            }
        }

        protected virtual void LoadContents(XmlElement root)
        {
            if (root["References"] is var referencesNode && referencesNode != null)
            {
                LoadReferences(referencesNode);
            }
        }
    }
}
