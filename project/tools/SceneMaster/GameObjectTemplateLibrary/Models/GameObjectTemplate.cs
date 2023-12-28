using CommunityToolkit.Mvvm.ComponentModel;
using GraphicsGaleWrapper;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    internal enum GameObjectType
    {
        Undefined,
        Projectile,
        Enemy,
        Effect
    }

    internal class EditorProperties
    {
        internal void Load(XmlElement editorPropertiesNode)
        {
            
        }
    }

    internal class GameProperties
    {
        public int Health { get; set; }
        public GameObjectType GameObjectType { get; set; }
        public double Something { get; set; }

        internal void Load(XmlElement gamePropertiesNode)
        {
            Health = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(Health));
            GameObjectType = XmlUtils.GetChildValue<GameObjectType>(gamePropertiesNode, nameof(GameObjectType));
            Something = XmlUtils.GetChildValue<double>(gamePropertiesNode, nameof(Something));
        }
    }

    internal class GameObjectTemplate
    {
        public string Name { get; private set; }

        private EditorProperties m_editorProperties = new EditorProperties();
        public EditorProperties EditorProperties { get => m_editorProperties; }

        private GameProperties m_gameProperties = new GameProperties();
        public GameProperties GameProperties { get => m_gameProperties; }

        internal void Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            Name = "UnnamedGameObjectTemplate";
            if (root[nameof(Name)] is var nameNode)
            {
                Name = nameNode.Attributes["value"]?.Value ?? "UnnamedGameObjectTemplate";
            }

            if (root[nameof(EditorProperties)] is var editorPropertiesNode)
            {
                EditorProperties.Load(editorPropertiesNode);
            }

            if (root[nameof(GameProperties)] is var gamePropertiesNode) 
            {
                GameProperties.Load(gamePropertiesNode);
            }
        }

    }
}
