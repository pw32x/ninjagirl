using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    internal class GameObjectTemplate
    {
        public string Name { get; private set; }

        public class EditorProperties
        {
        }

        public class GameProperties
        {

        }

        private EditorProperties m_editorProperties = new EditorProperties();
        public EditorProperties EditorProps { get => m_editorProperties; }

        private GameProperties m_gameProperties = new GameProperties();
        public GameProperties GameProps { get => m_gameProperties; }

        private const string EditorPropertiesNodeName = "EditorProperties";
        private const string GamePropertiesNodeName = "GameProperties";

        internal void Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            Name = "UnnamedGameObjectTemplate";
            if (root[nameof(Name)] is var nameNode)
            {
                Name = nameNode.Attributes[nameof(Name)]?.Value ?? "UnnamedGameObjectTemplate";
            }


            if (root[EditorPropertiesNodeName] is var editorPropertiesNode)
            {

            }

            if (root[GamePropertiesNodeName] is var gamePropertiesNode) 
            {

            }
        }

    }
}
