
using CommunityToolkit.Mvvm.ComponentModel;
using GraphicsGaleWrapper;
using MotionMaster.Commands.Models;
using MotionMaster.EditorObjectLibrary.Models;
using MotionMaster.EditorObjectLibrary.ViewModels;
using MotionMaster.EditorObjects.Models;
using MotionMaster.GameObjectTemplates.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Xml;

namespace MotionMaster.Scenes.Models
{
    public class Frame
    {
        public int frameNumber { get; set; }
        public int frameTime { get; set; }
    }

    public class Animation
    {
        public List<Frame> Frames { get; } = new List<Frame>();
    }

    public class Scene : ObservableObject, IDisposable
    {
        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        private const string GraphicsGaleFilePathNodeName = "GraphicsGaleFilePath";
        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";

        public string GraphicsGaleFilepath { get; private set; }
        public GaleObject GraphicsGaleObject { get; private set; }

        public ObservableCollection<Animation> Animations { get; } = new ObservableCollection<Animation>();

        public Scene(string graphicsGaleFilename)
        {
            LoadGraphicsGaleFile(graphicsGaleFilename);
        }

        public Scene()
        {
        }

        public void LoadGraphicsGaleFile(string graphicsGaleFilename)
        {
            var ggObject = new GaleObject(graphicsGaleFilename);

            if (!GraphicsGaleObjectIsAcceptable(ggObject))
            {
                Console.WriteLine("Graphics gale file " + graphicsGaleFilename + " doesn't have the format we want.");
                Console.WriteLine("Conversion skipped.");
                return;
            }

            GraphicsGaleFilepath = graphicsGaleFilename;
            GraphicsGaleObject = ggObject;
        }

        private bool GraphicsGaleObjectIsAcceptable(GaleObject ggObject)
        {
            if (ggObject.FrameCount == 0)
            {
                Console.WriteLine("Needs at least one frame.");
                return false;
            }

            if (ggObject.Frames[0].LayerCount == 0)
            {
                Console.WriteLine("Needs at least one layer.");
                return false;
            }

            var palette = ggObject.Palette;

            if (palette == null || palette.Entries.Length != 16)
            {
                Console.WriteLine("Only works on 4bpp images.");
                return false;
            }

            return true;
        }

        private TiledMapManager m_tiledMapManager = new TiledMapManager();
        public TiledMapManager TiledMapManager { get => m_tiledMapManager; }

        public void ImportTiledMap(string tiledMapFilePath)
        {
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            m_tiledMapManager.LoadTiledMap(tiledMapFilePath);
        }

        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var tiledMapFilePathNode = root[TiledMapFilePathNodeName];
            if (tiledMapFilePathNode != null && !string.IsNullOrEmpty(tiledMapFilePathNode.InnerText))
            {
                var tiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), tiledMapFilePathNode.InnerText);
                m_tiledMapManager.LoadTiledMap(tiledMapFilePath);
            }

            var ggFilePathNode = root[GraphicsGaleFilePathNodeName];

            if (ggFilePathNode == null)
                throw new Exception("No graphics gale file found in MotionMater file.");

            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                var graphicsGaleFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                LoadGraphicsGaleFile(graphicsGaleFilePath);
            }

            var editorObjectsNode = root[EditorObjectsNodeName];
            if (editorObjectsNode != null)
            {
                foreach (var editorObjectNode in editorObjectsNode.ChildNodes.OfType<XmlElement>())
                {
                    string nodeType = editorObjectNode.Name;
                    EditorObject editorObject = null;

                    switch (nodeType) 
                    {
                    case nameof(EditorObjectType.GameObject):
                        editorObject = new GameObject(editorObjectNode, editorObjectLibraryViewModel.GameObjectTemplateLibrary);
                    break;
                    case nameof(EditorObjectType.Command):
                        editorObject = new CommandObject(editorObjectNode, editorObjectLibraryViewModel.CommandLibrary);
                    break;
                    }

                    EditorObjects.Add(editorObject);
                }
            }
        }

        internal void SaveToXmlElement(XmlDocument doc, XmlElement root, string filePath)
        {
            // tiled map file path
            var tiledMapFilePathNode = doc.CreateElement(TiledMapFilePathNodeName);
            tiledMapFilePathNode.InnerText = string.IsNullOrEmpty(m_tiledMapManager.TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), m_tiledMapManager.TiledMapFilePath);
            root.AppendChild(tiledMapFilePathNode);

            // graphics gale file path
            var ggFilePathNode = doc.CreateElement(GraphicsGaleFilePathNodeName);
            ggFilePathNode.InnerText = GraphicsGaleFilepath;
            root.AppendChild(ggFilePathNode);

            // gameobjects
            var editorObjectsNode = doc.CreateElement(EditorObjectsNodeName);
            root.AppendChild(editorObjectsNode);

            foreach (var editorObject in EditorObjects)
            {
                var editorObjectNode = editorObject.ExportToXml(doc);
                editorObjectsNode.AppendChild(editorObjectNode);
            }
        }




        private void tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            
        }

        internal EditorObject CreateEditorObject(int x, int y, EditorObjectInfo editorObjectInfo)
        {
            var editorObject = editorObjectInfo.CreateEditorObject(x, y, this);

            if (editorObject == null)
                return null;

            EditorObjects.Add(editorObject);
            OnPropertyChanged(nameof(EditorObjects));

            return editorObject;
        }

        public void Dispose()
        {
            m_tiledMapManager.Dispose();
        }
    }
}