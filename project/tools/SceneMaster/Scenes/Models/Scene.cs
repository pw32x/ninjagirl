
using CommunityToolkit.Mvvm.ComponentModel;
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
    public class Scene : ObservableObject
    {
        BitmapImage m_defaultImage;

        private ObservableCollection<GameObject> m_gameObjects = new ObservableCollection<GameObject>();
        public ObservableCollection<GameObject> GameObjects { get => m_gameObjects; }

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string GameObjectsNodeName = "GameObjects";
        private const string GameObjectNodeName = "GameObject";

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
            ImportTiledMap(@"C:\Dropbox\SegaMasterSystem\projects\ninjagirl\project\gamedata\generated\themes\background3.tmx");

            m_defaultImage = new BitmapImage();
            // Set the image source to a file stream
            m_defaultImage.BeginInit();
            m_defaultImage.CacheOption = BitmapCacheOption.OnLoad;
            m_defaultImage.UriSource = new Uri("sprite.png", UriKind.RelativeOrAbsolute);
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

        public bool Load(string filePath)
        {
            var root = XmlUtils.OpenXmlDocument(filePath, nameof(Scene));

            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                TiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                LoadTiledMap(TiledMapFilePath);
            }

            var gameObjectsNode = root[GameObjectsNodeName];
            if (gameObjectsNode != null)
            {
                foreach (var gameObjectNode in gameObjectsNode.ChildNodes.OfType<XmlElement>())
                {
                    var gameObject = new GameObject();

                    gameObject.X = XmlUtils.GetValue<double>(gameObjectNode, nameof(GameObject.X));
                    gameObject.Y = XmlUtils.GetValue<double>(gameObjectNode, nameof(GameObject.Y));

                    gameObject.Bitmap = m_defaultImage;

                    GameObjects.Add(gameObject);
                }
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

            // gameobjects
            var gameObjectsNode = doc.CreateElement(GameObjectsNodeName);
            root.AppendChild(gameObjectsNode);

            foreach (var gameObject in GameObjects)
            {
                var gameObjectNode = doc.CreateElement(GameObjectNodeName);
                gameObjectsNode.AppendChild(gameObjectNode);

                gameObjectNode.SetAttribute(nameof(GameObject.X), gameObject.X.ToString());
                gameObjectNode.SetAttribute(nameof(GameObject.Y), gameObject.Y.ToString());
            }

            // Save
            doc.Save(filePath);

            return true;
        }

        private void LoadTiledMap(string tiledMapFilePath)
        {
            m_tiledMap = new TiledMap(tiledMapFilePath);

            m_tiledMapDirectory = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tiledMapFilePath));

            m_tiledMapTilesets = m_tiledMap.GetTiledTilesets(m_tiledMapDirectory);
            m_tileMapTileLayers = m_tiledMap.Layers.Where(x => x.type == TiledLayerType.TileLayer);

            m_tilesetBitmaps = new Dictionary<string, BitmapSource>();
            foreach (var tileset in m_tiledMapTilesets.Values)
            {
                string source = tileset.Image.source;
                BitmapImage bitmapImage = new BitmapImage(new Uri(m_tiledMapDirectory + source, UriKind.RelativeOrAbsolute));

                FormatConvertedBitmap convertedBitmap = new FormatConvertedBitmap(bitmapImage, PixelFormats.Bgr32, null, 0);

                m_tilesetBitmaps.Add(source, convertedBitmap);
            }

            TiledMapBitmapSource = BuildTiledMapBitmapSource();
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

        internal GameObject CreateGameObject(int x, int y)
        {
            var gameObject = new GameObject();
            gameObject.X = x;
            gameObject.Y = y;
            gameObject.Bitmap = m_defaultImage;
            GameObjects.Add(gameObject);

            OnPropertyChanged(nameof(GameObjects));

            return gameObject;
        }
    }
}