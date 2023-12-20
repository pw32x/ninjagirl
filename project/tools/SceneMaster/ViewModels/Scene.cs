using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.IO;
using System.Xml;

namespace SceneMaster.ViewModels
{
    public class Scene : ObservableObject
    {
        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        //private const string FrameInfosNodeName = "FrameInfos";
        //private const string FrameInfoNodeName = "FrameInfo";

        private string m_tiledMapFilePath = "";
        public string TiledMapFilePath
        {
            get => m_tiledMapFilePath;
            private set
            {
                SetProperty(ref m_tiledMapFilePath, value);
                TiledMapFilename = Path.GetFileName(m_tiledMapFilePath);
            }
        }

        private string m_tiledMapFilename = "";
        public string TiledMapFilename
        {
            get => m_tiledMapFilename;
            private set => SetProperty(ref m_tiledMapFilename, value);
        }

        public Scene()
        {
        }

        //private GaleObject m_tiledMap;
        //public GaleObject TiledMap { get => m_tiledMap; private set => SetProperty(ref m_tiledMap, value); }

        public void ImportTiledMap(string tiledMapFilePath)
        { 
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            TiledMapFilePath = tiledMapFilePath;

            //m_tiledMap = new GaleObject(m_tiledMapFilePath);
        }

        public bool Load(string filePath)
        {
            var doc = new XmlDocument();
            doc.Load(filePath);

            var root = doc[nameof(Scene)];

            if (root == null)
                throw new Exception($"No {nameof(Scene)} node found in {filePath}.");

            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                TiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
            }

            return true;
        }

        public bool Save(string filePath)
        {
            var doc = new XmlDocument();

            // root
            var root = doc.CreateElement(nameof(Scene));
            doc.AppendChild(root);

            // tiled map file path
            var ggFilePathNode = doc.CreateElement(TiledMapFilePathNodeName);
            ggFilePathNode.InnerText = string.IsNullOrEmpty(TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), TiledMapFilePath);
            root.AppendChild(ggFilePathNode);

            // Save
            doc.Save(filePath);

            return true;
        }
    }
}