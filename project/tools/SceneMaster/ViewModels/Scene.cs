
using CommunityToolkit.Mvvm.ComponentModel;
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

namespace SceneMaster.ViewModels
{
    public class Scene : ObservableObject
    {
        public class Sprite
        { 
            public double X { get; set; }
            public double Y { get; set; }
            public BitmapImage Bitmap { get; set; }
        }

        BitmapImage m_spriteImage;

        private ObservableCollection<Sprite> m_sprites = new ObservableCollection<Sprite>();
        public ObservableCollection<Sprite> Sprites {  get => m_sprites; }

        private const string TiledMapFilePathNodeName = "TiledMapFilePath";

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

            m_spriteImage = new BitmapImage();
            // Set the image source to a file stream
            m_spriteImage.BeginInit();
            m_spriteImage.CacheOption = BitmapCacheOption.OnLoad;
            m_spriteImage.UriSource = new Uri("sprite.png", UriKind.RelativeOrAbsolute);
            m_spriteImage.EndInit();

            /*
            m_sprites.Add(new Sprite { X = 0,
                                       Y = 0,
                                       Bitmap = m_spriteImage });

            m_sprites.Add(new Sprite { X = 790,
                                       Y = 224,
                                       Bitmap = m_spriteImage });

            m_sprites.Add(new Sprite { X = 180,
                                       Y = 100,
                                       Bitmap = m_spriteImage });
            */
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
            var doc = new XmlDocument();
            doc.Load(filePath);

            var root = doc[nameof(Scene)];

            if (root == null)
                throw new Exception($"No {nameof(Scene)} node found in {filePath}.");

            var ggFilePathNode = root[TiledMapFilePathNodeName];
            if (ggFilePathNode != null && !string.IsNullOrEmpty(ggFilePathNode.InnerText))
            {
                TiledMapFilePath = Path.Combine(Path.GetDirectoryName(filePath), ggFilePathNode.InnerText);
                LoadTiledMap(TiledMapFilePath);
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
                            var index = (tileY * layer.width) + tileX; // Assuming the default render order is used which is from right to bottom
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

            // Render sprite at position tileX, tileY using the rect

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

        internal Sprite CreateSprite(int x, int y)
        {
            /*
            var tileX = bitmapX / TiledMap.TileWidth;
            var tileY = bitmapY / TiledMap.TileHeight;

            DrawTileToBitmap(TiledMapBitmapSource, tileX, tileY, 2);
            OnPropertyChanged(nameof(TiledMapBitmapSource));
            */

            var sprite = new Sprite();
            sprite.X = x; 
            sprite.Y = y;
            sprite.Bitmap = m_spriteImage;
            Sprites.Add(sprite);

            return sprite;
        }
    }
}