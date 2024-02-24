
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
        FileSystemWatcher m_tiledMapFileWatcher = null;

        private ObservableCollection<EditorObject> m_editorObjects = new ObservableCollection<EditorObject>();
        public ObservableCollection<EditorObject> EditorObjects { get => m_editorObjects; }

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";
        private const string EditorObjectsNodeName = "EditorObjects";
        private const string TerrainNodeName = "Terrain";

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



        public Scene(/*List<BitmapImage> tileTypeImages*/)
        {
            //m_tileTypeImages = tileTypeImages;
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



        /*
        public const int TILE_EMPTY = 0;
        public const int TILE_SOLID = 1;
        public const int TILE_TOPSOLID = 2;
        public const int TILE_CLIMB = 3;
        public const int TILE_HURT = 4;
        public const int TILE_SLOPE45RIGHT = 5;
        public const int TILE_SLOPE45LEFT = 6;
        public const int TILE_SLOPE30RIGHT1 = 7;
        public const int TILE_SLOPE30RIGHT2 = 8;
        public const int TILE_SLOPE30LEFT1 = 9;
        public const int TILE_SLOPE30LEFT2 = 10;
        public const int TILE_WATER = 11;

        static public Dictionary<string, int> TileTypeNameToInt = new Dictionary<string, int>()
        {
            {"empty",           0},
            {"solid",           1},
            {"topsolid",        2},
            {"climb",           3},
            {"hurt",            4},
            {"slope45right",    5},
            {"slope45left",     6},
            {"slope30right1",   7},
            {"slope30right2",   8},
            {"slope30left1",    9},
            {"slope30left2",    10},
            {"water",           11}
        };

        public static string TileAttributeToString(int tileAttribute)
        {
            switch (tileAttribute)
            {
                case TILE_SOLID: return "solid";
                case TILE_TOPSOLID: return "topsolid";
                case TILE_CLIMB: return "climb";
                case TILE_HURT: return "hurt";
                case TILE_SLOPE45RIGHT: return "slope45right";
                case TILE_SLOPE45LEFT: return "slope45left";
                case TILE_SLOPE30RIGHT1: return "slope30right1";
                case TILE_SLOPE30RIGHT2: return "slope30right2";
                case TILE_SLOPE30LEFT1: return "slope30left1";
                case TILE_SLOPE30LEFT2: return "slope30left2";
                case TILE_WATER: return "water";
            }

            return "";
        }

        List<BitmapImage> m_tileTypeImages;

        List<int> m_terrain = new List<int>();
        int m_terrainWidth = 0;
        int m_terrainHeight = 0;

        private WriteableBitmap m_terrainBitmapSource;
        public WriteableBitmap TerrainBitmapSource { get => m_terrainBitmapSource; private set => SetProperty(ref m_terrainBitmapSource, value); }
        */

        public void ImportTiledMap(string tiledMapFilePath)
        {
            if (!File.Exists(tiledMapFilePath))
                throw new Exception($"File {tiledMapFilePath} doesn't exist.");

            TiledMapFilePath = tiledMapFilePath;
            LoadTiledMap(tiledMapFilePath);
            //BuildTerrain();
        }

        /*
        public void SetTerrainTileType(int tileX, int tileY, int tileType)
        {
            m_terrain[tileX + (tileY * m_terrainWidth)] = tileType;
            var bitmapImage = m_tileTypeImages[tileType];

            DrawBitmapHelper(TerrainBitmapSource, tileX, tileY, bitmapImage);

            OnPropertyChanged(nameof(TerrainBitmapSource));
        }

        private void BuildTerrain()
        {
            m_terrain.Clear();

            var layer = m_tileMapTileLayers.First();

            m_terrain.Capacity = layer.width * layer.height;

            m_terrainWidth = layer.width;
            m_terrainHeight = layer.height;

            for (var tileY = 0; tileY < m_terrainHeight; tileY++)
            {
                for (var tileX = 0; tileX < m_terrainWidth; tileX++)
                {
                    var index = tileY * layer.width + tileX; // Assuming the default render order is used which is from right to bottom
                    var gid = layer.data[index]; // The tileset tile index

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
                    var tiledTile = m_tiledMap.GetTiledTile(mapTileset, tileset, gid);

                    var property = tiledTile.properties.First();

                    if (!string.IsNullOrEmpty(property.name))
                        m_terrain.Add(TileTypeNameToInt[property.name]);
                    else
                        m_terrain.Add(TILE_EMPTY);
                }
            }

            TerrainBitmapSource = BuildTerrainImage(m_tileTypeImages);
        }

        private WriteableBitmap BuildTerrainImage(List<BitmapImage> tileTypeImages)
        {
            WriteableBitmap writeableBitmap = new WriteableBitmap(m_tiledMap.Width * m_tiledMap.TileWidth,
                                                                 m_tiledMap.Height * m_tiledMap.TileHeight,
                                                                 96,
                                                                 96,
                                                                 PixelFormats.Bgra32,
                                                                 null);

            for (var tileY = 0; tileY < m_terrainHeight; tileY++)
            {
                for (var tileX = 0; tileX < m_terrainWidth; tileX++)
                {

                    var tileType = m_terrain[tileX + (tileY * m_terrainWidth)];

                    var bitmapImage = tileTypeImages[tileType];
                    DrawBitmapHelper(writeableBitmap, tileX, tileY, bitmapImage);
                }
            }

            return writeableBitmap;
        }
        
        private void DrawBitmapHelper(WriteableBitmap writeableBitmap, int tileX, int tileY, BitmapImage bitmapImage)
        {
            // Copy pixel data from the BitmapImage to the WriteableBitmap
            Int32Rect sourceRect = new Int32Rect(0,
                                                 0,
                                                 m_tiledMap.TileWidth,
                                                 m_tiledMap.TileHeight);
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
        */

        public void LoadFromXml(XmlElement root, string filePath, EditorObjectLibraryViewModel editorObjectLibraryViewModel)
        {
            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                TiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                LoadTiledMap(TiledMapFilePath);
                //BuildTerrain();
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

            /*
            var terrainNode = root[TerrainNodeName];
            if (terrainNode != null)
            {
                try
                {
                    m_terrain.Clear();
                    string widthString = terrainNode.GetAttribute("width");
                    string heightString = terrainNode.GetAttribute("height");

                    int width = int.Parse(widthString);
                    int height = int.Parse(heightString);

                    var tokens = terrainNode.InnerText.Trim().Split(' ');

                    if (tokens.Length != width * height)
                        throw new Exception("Specified terrain size and terrain node contents don't match");

                    foreach (var token in tokens)
                    {
                        m_terrain.Add(int.Parse(token));
                    }

                    TerrainBitmapSource = BuildTerrainImage(m_tileTypeImages);
                }
                catch (Exception)
                {
                    BuildTerrain();
                }
            }
            */
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

            /*
            // Terrain
            var terrainNode = doc.CreateElement(TerrainNodeName);
            root.AppendChild(terrainNode);

            terrainNode.SetAttribute("width", m_terrainWidth.ToString());
            terrainNode.SetAttribute("height", m_terrainHeight.ToString());

            var sb = new StringBuilder();
            foreach (var tileType in m_terrain)
            {
                sb.Append(tileType + " ");
            }

            terrainNode.InnerText = sb.ToString().Trim();
            */
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

        private void ShutdownTiledMap()
        {
            m_tiledMap = null;
            m_tiledMapDirectory = null;
            m_tileMapTileLayers = null;
            m_tiledMapTilesets = null;
            m_tilesetBitmaps = null;
            TiledMapBitmapSource = null;
            //m_terrain.Clear();
        }

        private void LoadTiledMap(string tiledMapFilePath)
        {
            StopWatchingTiledMap();

            try
            {
                ShutdownTiledMap();

                m_tiledMap = new TiledMap(tiledMapFilePath);

                m_tiledMapDirectory = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tiledMapFilePath));

                m_tiledMapTilesets = m_tiledMap.GetTiledTilesets(m_tiledMapDirectory);
                m_tileMapTileLayers = m_tiledMap.Layers.Where(x => x.type == TiledLayerType.TileLayer);

                m_tilesetBitmaps = new Dictionary<string, BitmapSource>();
                foreach (var tileset in m_tiledMapTilesets.Values)
                {
                    string tilesetFolder = StringUtils.EnsureTrailingSlash(Path.GetDirectoryName(tileset.FilePath));
                    string source = tileset.Image.source;
                    BitmapImage bitmapImage = new BitmapImage();
                    bitmapImage.BeginInit();
                    bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                    bitmapImage.UriSource = new Uri(tilesetFolder + source, UriKind.RelativeOrAbsolute);
                    bitmapImage.EndInit();

                    FormatConvertedBitmap convertedBitmap = new FormatConvertedBitmap(bitmapImage, PixelFormats.Bgr32, null, 0);

                    m_tilesetBitmaps.Add(source, convertedBitmap);

                }

                TiledMapBitmapSource = BuildTiledMapBitmapSource();

                StartWatchingTiledMap(tiledMapFilePath);
            }
            catch (Exception e) 
            {
                ShutdownTiledMap();
                MessageBox.Show("Failed loading " + tiledMapFilePath + ". Error: " + e.Message);
            }
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