
using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.Commands.Models;
using SceneMaster.EditorObjectLibrary.Models;
using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using TiledCS;

namespace SceneMaster.Scenes.Models
{
    public class Scene : ObservableObject, IDisposable
    {
        BitmapImage m_defaultImage;

        FileSystemWatcher m_tiledMapFileWatcher = null;

        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";

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
            //ImportTiledMap(@"C:\Dropbox\SegaMasterSystem\projects\ninjagirl\project\gamedata\generated\themes\background3.tmx");

            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);

            m_defaultImage = new BitmapImage();
            // Set the image source to a file stream
            m_defaultImage.BeginInit();
            m_defaultImage.CacheOption = BitmapCacheOption.OnLoad;
            m_defaultImage.UriSource = new Uri(appFolder + "sprite.png", UriKind.RelativeOrAbsolute);
            m_defaultImage.EndInit();

            /*
            m_gameObjects.Add(new GameObject { X = 0,
                                               Y = 0,
                                               Bitmap = m_defaultImage });

            m_gameObjects.Add(new GameObject { X = 640,
                                               Y = 224,
                                               Bitmap = m_defaultImage });

            m_gameObjects.Add(new GameObject { X = 180,
                                               Y = 100,
                                               Bitmap = m_defaultImage });
            */
            //Load(@"C:\Dropbox\SegaMasterSystem\projects\ninjagirl\project\tools\SceneMaster\test.scm");



        }

        private TiledMap m_tiledMap;
        private string m_tiledMapDirectory;

        public TiledMap TiledMap { get => m_tiledMap; private set => SetProperty(ref m_tiledMap, value); }

        private Dictionary<int, TiledTileset> m_tiledMapTilesets;
        private IEnumerable<TiledLayer> m_tileMapTileLayers;
        private Dictionary<string, BitmapSource> m_tilesetBitmaps;

        // visual of the actual Tiled map
        private Bitmap m_tiledMapBitmap;
        public Bitmap TiledMapBitmap { get => m_tiledMapBitmap; private set => SetProperty(ref m_tiledMapBitmap, value); }
        private WriteableBitmap m_tiledMapBitmapSource;
        public WriteableBitmap TiledMapBitmapSource { get => m_tiledMapBitmapSource; private set => SetProperty(ref m_tiledMapBitmapSource, value); }

        public void ImportTiledMap(string tiledMapFilePath)
        {
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            TiledMapFilePath = tiledMapFilePath;
            LoadTiledMap(tiledMapFilePath);
        }

        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                TiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                LoadTiledMap(TiledMapFilePath);
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
            ggFilePathNode.InnerText = string.IsNullOrEmpty(TiledMapFilePath) ? "" : Path.GetRelativePath(Path.GetDirectoryName(filePath), TiledMapFilePath);
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

        public void StartWatchingTiledMap(string filePath)
        {
            m_tiledMapFileWatcher = new FileSystemWatcher(Path.GetDirectoryName(Path.GetFullPath(filePath)));
            m_tiledMapFileWatcher.Filter = Path.GetFileName(filePath);
            
            // When saving a Tiled map, it saves it under a temporary filename, deletes the original
            // and renames it to the same filename. 
            m_tiledMapFileWatcher.Renamed += M_tiledMapFileWatcher_Renamed;
            m_tiledMapFileWatcher.Changed += M_tiledMapFileWatcher_Changed;
            

            m_tiledMapFileWatcher.EnableRaisingEvents = true;
        }

        private void M_tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath); });
        }

        private void M_tiledMapFileWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath); });
        }

        public void StopWatchingTiledMap()
        {
            if (m_tiledMapFileWatcher == null)
                return;

            m_tiledMapFileWatcher.EnableRaisingEvents = false;
            m_tiledMapFileWatcher.Changed -= tiledMapFileWatcher_Changed;
            m_tiledMapFileWatcher.Dispose();
            m_tiledMapFileWatcher = null;
        }

        private void tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            
        }

        private void LoadTiledMap(string tiledMapFilePath)
        {
            StopWatchingTiledMap();

            m_tiledMap = new TiledMap(tiledMapFilePath);

            m_tiledMapDirectory = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tiledMapFilePath));

            m_tiledMapTilesets = m_tiledMap.GetTiledTilesets(m_tiledMapDirectory);
            m_tileMapTileLayers = m_tiledMap.Layers.Where(x => x.type == TiledLayerType.TileLayer);

            m_tilesetBitmaps = new Dictionary<string, BitmapSource>();
            foreach (var tileset in m_tiledMapTilesets.Values)
            {
                string source = tileset.Image.source;
                BitmapImage bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.UriSource = new Uri(m_tiledMapDirectory + source, UriKind.RelativeOrAbsolute);
                bitmapImage.EndInit();

                FormatConvertedBitmap convertedBitmap = new FormatConvertedBitmap(bitmapImage, PixelFormats.Bgr32, null, 0);

                m_tilesetBitmaps.Add(source, convertedBitmap);

            }

            TiledMapBitmapSource = BuildTiledMapBitmapSource();

            StartWatchingTiledMap(tiledMapFilePath);
        }

        private WriteableBitmap BuildTiledMapBitmapSource()
        {
            WriteableBitmap writeableBitmap = new WriteableBitmap(m_tiledMap.Width * m_tiledMap.TileWidth,
                                                                 m_tiledMap.Height * m_tiledMap.TileHeight,
                                                                 96,
                                                                 96,
                                                                 PixelFormats.Bgr32,
                                                                 null);

            try
            {
                writeableBitmap.Lock();

                foreach (var layer in m_tileMapTileLayers)
                {
                    for (var tileY = 0; tileY < layer.height; tileY++)
                    {
                        for (var tileX = 0; tileX < layer.width; tileX++)
                        {
                            var index = tileY * layer.width + tileX; // Assuming the default render order is used which is from right to bottom
                            var gid = layer.data[index]; // The tileset tile index

                            DrawTileToBitmapHelper(writeableBitmap, tileX, tileY, gid);
                        }
                    }
                }
            }
            finally
            {
                // Unlock the WriteableBitmap when done
                writeableBitmap.Unlock();
            }

            return writeableBitmap;
        }

        private void DrawTileToBitmap(WriteableBitmap writeableBitmap, int tileX, int tileY, int gid)
        {
            try
            {
                writeableBitmap.Lock();

                DrawTileToBitmapHelper(writeableBitmap, tileX, tileY, gid);
            }
            finally
            {
                // Unlock the WriteableBitmap when done
                writeableBitmap.Unlock();
            }
        }

        private void DrawTileToBitmapHelper(WriteableBitmap writeableBitmap, int tileX, int tileY, int gid)
        {
            // Gid 0 is used to tell there is no tile set
            if (gid == 0)
            {
                return;
            }

            // Helper method to fetch the right TieldMapTileset instance. 
            // This is a connection object Tiled uses for linking the correct tileset to the gid value using the firstgid property.
            var mapTileset = m_tiledMap.GetTiledMapTileset(gid);

            // Retrieve the actual tileset based on the firstgid property of the connection object we retrieved just now
            var tileset = m_tiledMapTilesets[mapTileset.firstgid];

            // Use the connection object as well as the tileset to figure out the source rectangle.
            var rect = m_tiledMap.GetSourceRect(mapTileset, tileset, gid);

            // Render gameobject at position tileX, tileY using the rect

            var bitmapImage = m_tilesetBitmaps[tileset.Image.source];

            // Copy pixel data from the BitmapImage to the WriteableBitmap
            Int32Rect sourceRect = new Int32Rect(rect.x, rect.y, rect.width, rect.height);
            var stride = (sourceRect.Width * bitmapImage.Format.BitsPerPixel + 7) / 8; // here

            byte[] pixelData = new byte[stride * sourceRect.Height];
            bitmapImage.CopyPixels(sourceRect, pixelData, stride, 0);

            Int32Rect destRect = new Int32Rect(tileX * m_tiledMap.TileWidth,
                                               tileY * m_tiledMap.TileHeight,
                                               m_tiledMap.TileWidth,
                                               m_tiledMap.TileHeight);

            writeableBitmap.WritePixels(destRect,
                                        pixelData,
                                        stride,
                                        0);
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
            StopWatchingTiledMap();
        }
    }
}