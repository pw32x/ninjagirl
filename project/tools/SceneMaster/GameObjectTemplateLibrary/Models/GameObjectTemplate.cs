using CommunityToolkit.Mvvm.ComponentModel;
using GraphicsGaleWrapper;
using PropertyTools.DataAnnotations;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.IO;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SceneMaster.GameObjectTemplates.Models
{
    public enum GameObjectType
    {
        Undefined = -1,
        Projectile,
        Enemy,
        Effect,
        Player
    }

    public class Visual
    {
        public int Width { get; private set; }
        public int Height { get; private set; }
        public BitmapImage Image { get; private set; }

        public void Load(XmlElement visualNode)
        {
            if (visualNode["GraphicsGale"] is var graphicsGaleNode && graphicsGaleNode != null)
            {
                string graphicsGaleFilename = XmlUtils.GetValue<string>(graphicsGaleNode, "filename");
                int frameNumber = XmlUtils.GetValue<int>(graphicsGaleNode, "framenumber");

                if (!string.IsNullOrEmpty(graphicsGaleFilename)) 
                {
                    var galeFile = GaleFile.Open(graphicsGaleFilename);

                    Width = GaleFile.GetWidth(galeFile);
                    Height = GaleFile.GetHeight(galeFile);

                    var frameBitmap = GaleFile._ggGetBitmap(galeFile, frameNumber, 0);
                    var palette = GaleFile.GetPalette(galeFile, frameNumber);

                    Image = BitmapUtils.ConvertHBitmapToBitmapImage(frameBitmap);

                    GaleFile.Close(galeFile);
                }
            }
        }
    }

    public class GameObjectTemplate
    {
        public string Name { get; set; }

        [Browsable(false)]
        public bool IsEditorVisible { get; protected set; }

        // editor properties
        [Browsable(false)]
        public Visual Visual { get; } = new();

        // game properties
        [System.ComponentModel.ReadOnly(true)]
        public int Health { get; set; }

        [System.ComponentModel.ReadOnly(true)]
        [SelectorStyle(SelectorStyle.ComboBox)]
        public GameObjectType GameObjectType { get; set; }

        public void LoadEditorProperties(XmlElement editorPropertiesNode)
        {
            if (editorPropertiesNode["Visual"] is var visualNode && visualNode != null)
            {
                Visual.Load(visualNode);
            }
        }

        public void LoadGameProperties(XmlElement gamePropertiesNode)
        {
            Health = XmlUtils.GetChildValue<int>(gamePropertiesNode, nameof(Health));
            GameObjectType = XmlUtils.GetChildValue<GameObjectType>(gamePropertiesNode, nameof(GameObjectType));
        }

        public void Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(GameObjectTemplate));

            string oldCurrentDirectory = Directory.GetCurrentDirectory();

            Directory.SetCurrentDirectory(Path.GetDirectoryName(filePath));

            Name = "UnnamedGameObjectTemplate";
            if (root[nameof(Name)] is var nameNode && nameNode != null)
            {
                Name = nameNode.Attributes["value"]?.Value ?? "UnnamedGameObjectTemplate";
            }

            if (root["EditorProperties"] is var editorPropertiesNode && editorPropertiesNode != null)
            {
                IsEditorVisible = true;
                LoadEditorProperties(editorPropertiesNode);
            }

            if (root["GameProperties"] is var gamePropertiesNode && gamePropertiesNode != null) 
            {
                LoadGameProperties(gamePropertiesNode);
            }

            Directory.SetCurrentDirectory(oldCurrentDirectory);
        }

    }
}
