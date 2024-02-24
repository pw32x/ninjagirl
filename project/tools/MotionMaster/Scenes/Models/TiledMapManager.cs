using CommunityToolkit.Mvvm.ComponentModel;
using MotionMaster.Utils;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;
using System.Windows.Media.Imaging;
using TiledCS;
using System.IO;

namespace MotionMaster.Scenes.Models
{
    public class TiledMapManager : ObservableObject, IDisposable
    {
        FileSystemWatcher m_tiledMapFileWatcher = null;

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


        private void ShutdownTiledMap()
        {
            m_tiledMap = null;
            m_tiledMapDirectory = null;
            m_tileMapTileLayers = null;
            m_tiledMapTilesets = null;
            m_tilesetBitmaps = null;
            TiledMapBitmapSource = null;
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

        public void StopWatchingTiledMap()
        {
            if (m_tiledMapFileWatcher == null)
                return;

            m_tiledMapFileWatcher.EnableRaisingEvents = false;
            m_tiledMapFileWatcher.Changed -= M_tiledMapFileWatcher_Changed;
            m_tiledMapFileWatcher.Dispose();
            m_tiledMapFileWatcher = null;
        }

        private void M_tiledMapFileWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath); });
        }

        private void M_tiledMapFileWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() => { LoadTiledMap(TiledMapFilePath); });
        }

        public void LoadTiledMap(string tiledMapFilePath)
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

        public void Dispose()
        {
            StopWatchingTiledMap();
        }
    }
}
