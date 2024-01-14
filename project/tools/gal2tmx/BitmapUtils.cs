
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;

namespace gal2tmx
{
    class BitmapUtils
    {
        static public unsafe Bitmap PackTilesetBitmap(List<BitmapTile> tiles, 
                                                      int tilesAcross, 
                                                      int tileWidth, 
                                                      int tileHeight)
        {
            // 5 tiles - 10 tiles accross -> 5 packed width, 1 packed height
            // 13 tiles - 10 tiles across -> 10 packed width, 
            int tilesCount = tiles.Count;

            int packedTileWidth = (tilesCount < tilesAcross ? tilesCount : tilesAcross);
            int packedWidth = packedTileWidth * tileWidth;
            int padding = (tilesCount % tilesAcross == 0) ? 0 : 1;
            int packedHeight = ((tilesCount / packedTileWidth) + padding) * tileHeight;

            Bitmap destinationBitmap = new Bitmap(packedWidth, packedHeight, System.Drawing.Imaging.PixelFormat.Format4bppIndexed);
            destinationBitmap.Palette = tiles[0].Bitmap.Palette;

            Rectangle rect = new Rectangle(0, 0, destinationBitmap.Width, destinationBitmap.Height);

            BitmapData destinationBitmapData = destinationBitmap.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format4bppIndexed);

            int destinationTileStride = destinationBitmapData.Stride / packedTileWidth;

            int x = 0;
            int y = 0;

            byte* destinationBuffer = (byte*)destinationBitmapData.Scan0.ToPointer();

            Rectangle sourceRect = new Rectangle(new Point(0, 0), new Size(tileWidth, tileHeight));

            foreach (var tile in tiles)
            {
                Rectangle destinationRect = new Rectangle(new Point(x, y), new Size(tileWidth, tileHeight));

                BitmapData sourceBitmapData = tile.Bitmap.LockBits(sourceRect, ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);

                byte* sourceBuffer = (byte*)sourceBitmapData.Scan0.ToPointer();

                // copy byte by byte. Yeah, it's not great.
                for (int loopy = 0; loopy < tileHeight; loopy++)
                {
                    for (int loopx = 0; loopx < destinationTileStride; loopx++)
                    {
                        destinationBuffer[((x >> 1) + loopx) + ((y + loopy) * destinationBitmapData.Stride)] = sourceBuffer[loopx + (loopy * destinationTileStride)];
                    }
                }

                x += tileWidth;

                if ((x % destinationBitmap.Width) == 0) // if we've hit the end of a row, move down
                {
                    y += tileHeight;
                    x = 0;
                }

                tile.Bitmap.UnlockBits(sourceBitmapData);
            }

            destinationBitmap.UnlockBits(destinationBitmapData);

            return destinationBitmap;
        }

        public static unsafe Bitmap Create4bppBitmap(Bitmap sourceGGBitmap, ColorPalette palette)
        {
            int width = sourceGGBitmap.Width;
            int height = sourceGGBitmap.Height;

            Bitmap bitmap = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format4bppIndexed);
            bitmap.Palette = palette;

            Rectangle rect = new Rectangle(0, 0, width, height);

            BitmapData bitmapData = bitmap.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format4bppIndexed);

            byte* scan0 = (byte*)bitmapData.Scan0.ToPointer();

            int pixelCounter = 0;

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Color sourceColor = sourceGGBitmap.GetPixel(x, y);

                    byte paletteIndex = 0;

                    for (byte loop = 0; loop < palette.Entries.Length; loop++)
                    {
                        if (palette.Entries[loop] == sourceColor)
                        {
                            paletteIndex = loop;
                            break;
                        }
                    }

                    byte pixelValue;

                    if (x % 2 == 1)
                    {
                        pixelValue = (byte)((paletteIndex & 0xf));
                    }
                    else
                    {
                        pixelValue = (byte)((paletteIndex & 0xf) << 4);
                    }

                    scan0[(x >> 1) + (y * bitmapData.Stride)] |= pixelValue;

                    pixelCounter++;
                }
            }

            bitmap.UnlockBits(bitmapData);

            return bitmap;
        }

        internal static Bitmap PackAnimatedTilesetBitmap(List<BitmapTile> tiles, int tileWidth, int tileHeight)
        {
            // tiles are stored
            // 0, 1,  4, 5,   8, 9
            // 2, 3,  6, 7,  10, 11

            return null;
        }
    }
}