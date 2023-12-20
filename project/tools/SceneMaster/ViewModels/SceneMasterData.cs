using CommunityToolkit.Mvvm.ComponentModel;
using System.IO;
using System.Xml.Serialization;
using GraphicsGaleWrapper;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Xml;
using System;
using System.Diagnostics;
using System.Linq;

namespace SceneMaster.ViewModels
{
    public enum SceneSplitStyle
    {
        Normal,
        Grid,
        Rows,
        Columns
    }

    public class FrameInfo : ObservableObject
    {
        private SceneSplitStyle m_sceneSplitStyle;
        public SceneSplitStyle SceneSplitStyle 
        { 
            get => m_sceneSplitStyle;
            set => SetProperty(ref m_sceneSplitStyle, value); 
        }
    }

    public class SceneMasterData : ObservableObject
    {
        private const string GraphicsGaleFilePathNodeName = "GraphicsGaleFilePath";
        private const string FrameInfosNodeName = "FrameInfos";
        private const string FrameInfoNodeName = "FrameInfo";

        private string m_galFilePath;
        public string GalFilePath
        {
            get => m_galFilePath;
            private set
            {
                if (m_galeObject != null) 
                { 
                    m_galeObject.Dispose();
                    m_galeObject = null;
                }

                SetProperty(ref m_galFilePath, value);
                GalFilename = Path.GetFileName(m_galFilePath);
            }
        }

        private ObservableCollection<FrameInfo> m_frameInfos = new ObservableCollection<FrameInfo>();
        public ObservableCollection<FrameInfo> FrameInfos
        {
            get => m_frameInfos;
        }

        
        private string m_galFilename;
        public string GalFilename
        {
            get => m_galFilename;
            private set => SetProperty(ref m_galFilename, value);
        }

        private GaleObject m_galeObject;

        public void ImportGraphicsGaleFile(string galFilePath)
        { 
            if (!File.Exists(galFilePath))
                throw new Exception($"File {galFilePath} doesn't exist.");

            GalFilePath = galFilePath;

            m_galeObject = new GaleObject(m_galFilePath);

            FrameInfos.Clear();

            for (int loop = 0; loop < m_galeObject.FrameCount; loop++)
            { 
                FrameInfos.Add(new FrameInfo());
            }
        }

        public bool Load(string filePath)
        {
            var doc = new XmlDocument();
            doc.Load(filePath);

            var root = doc[nameof(SceneMasterData)];

            if (root == null)
                throw new Exception($"No {nameof(SceneMasterData)} node found in {filePath}.");

            var ggFilePathNode = root[GraphicsGaleFilePathNodeName];
            if (ggFilePathNode == null)
                throw new Exception($"No {GraphicsGaleFilePathNodeName} node found in {filePath}.");

            GalFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);

            var frameInfosNode = root["FrameInfos"];
            if (frameInfosNode != null)
            {
                foreach (var childNode in frameInfosNode.ChildNodes.OfType<XmlElement>()) 
                { 
                    var frameInfo = new FrameInfo();

                    string sceneSplitStyleValue = childNode.GetAttribute(nameof(FrameInfo.SceneSplitStyle));

                    if (!string.IsNullOrEmpty(sceneSplitStyleValue))
                    {
                        Enum.TryParse(sceneSplitStyleValue, out SceneSplitStyle sceneSplitStyle);
                        frameInfo.SceneSplitStyle = sceneSplitStyle;
                    }

                    FrameInfos.Add(frameInfo);
                }
            }

            return true;
        }

        public bool Save(string filePath)
        {
            var doc = new XmlDocument();

            // root
            var root = doc.CreateElement(nameof(SceneMasterData));
            doc.AppendChild(root);

            // graphics gale file path
            var ggFilePathNode = doc.CreateElement(GraphicsGaleFilePathNodeName);
            ggFilePathNode.InnerText = Path.GetRelativePath(Path.GetDirectoryName(filePath), GalFilePath);
            root.AppendChild(ggFilePathNode);

            // frame infos
            var frameInfosNode = doc.CreateElement(FrameInfosNodeName);
            root.AppendChild(frameInfosNode);
            foreach (var frameInfo in FrameInfos) 
            {
                var frameInfoNode = doc.CreateElement(FrameInfoNodeName);
                frameInfosNode.AppendChild(frameInfoNode);
                frameInfoNode.SetAttribute(nameof(FrameInfo.SceneSplitStyle), frameInfo.SceneSplitStyle.ToString());
            }

            // Save
            doc.Save(filePath);

            return true;
        }
    }
}