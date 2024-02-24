
using CommunityToolkit.Mvvm.ComponentModel;
using GraphicsGaleWrapper;
using MotionMaster.Commands.Models;
using MotionMaster.EditorObjectLibrary.Models;
using MotionMaster.EditorObjectLibrary.ViewModels;
using MotionMaster.EditorObjects.Models;
using MotionMaster.GameObjectTemplates.Models;
using MotionMaster.Utils;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Xml;
using TiledCS;

namespace MotionMaster.Scenes.Models
{
    public class Scene : ObservableObject, IDisposable
    {
        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";

        public Scene(string graphicsGaleFilename)
        {
        }

        public Scene()
        {
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
            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                var tiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                m_tiledMapManager.LoadTiledMap(tiledMapFilePath);
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
            var ggFilePathNode = doc.CreateElement(TiledMapFilePathNodeName);
            ggFilePathNode.InnerText = string.IsNullOrEmpty(m_tiledMapManager.TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), m_tiledMapManager.TiledMapFilePath);
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