using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace gal2tmx
{
    internal class BitmapTile
    {
        public BitmapTile(int index, Bitmap bitmap, int attribute)
        {
            Index = index;
            Bitmap = bitmap;
            Attribute = attribute;
        }

        public int Index { get; }
        public Bitmap Bitmap { get; }
        public int Attribute { get; }
    }

    internal class BitmapTileMap
    {
        public int Width { get; }
        public int Height { get; }
        public List<uint> Map { get; } // contains the index of the unique tile used at this map location. 

        public BitmapTileMap(int width, int height)
        {
            Width = width;
            Height = height;
            Map = new List<uint>(Width * Height);
        }
    }

    internal class SplitBitmap
    {
        public enum ExportFlipType
        {
            None,
            SegaMasterSystem,
            Tiled
        }

        public List<BitmapTile> UniqueBitmapTiles { get; } = new List<BitmapTile>();

        public BitmapTileMap BitmapTileMap { get; private set; }

        public SplitBitmap()
        {

        }

        public unsafe void SplitLinearly(Bitmap bitmap, 
                                         Bitmap tileTypesBitmap, 
                                         SplitBitmap tileTypes,
                                         int splitWidth, 
                                         int splitHeight, 
                                         bool removeDuplicates, 
                                         ExportFlipType exportFlipType)
        {


            int tilesWidth = bitmap.Width / splitWidth;
            int tilesHeight = bitmap.Height / splitHeight;

            int tileIndex = 0;

            BitmapTileMap = new BitmapTileMap(tilesWidth, tilesHeight);

            for (int tiley = 0; tiley < tilesHeight; tiley++)
            {
                for (int tilex = 0; tilex < tilesWidth; tilex++)
                {
                    int bitmapx = tilex * splitWidth;
                    int bitmapy = tiley * splitHeight;

                    Rectangle rect = new Rectangle(bitmapx,
                                                   bitmapy, 
                                                   splitWidth,
                                                   splitHeight);

                    ProcessTile(rect,
                                bitmap,
                                tileTypesBitmap, 
                                tileTypes,
                                removeDuplicates,
                                exportFlipType,
                                ref tileIndex);
                }
            }
        }


        public unsafe void SplitByBlocks(Bitmap bitmap, 
                                         Bitmap attributeBitmap, 
                                         SplitBitmap tileTypes,
                                         int splitWidth, 
                                         int splitHeight, 
                                         int blockWidth,
                                         int blockHeight,
                                         bool removeDuplicates, 
                                         ExportFlipType exportFlipType)
        {
            int horizontalBlocks = bitmap.Width / blockWidth;
            int verticalBlocks = bitmap.Height / blockHeight;

            int tilesWidth = bitmap.Width / splitWidth;
            int tilesHeight = bitmap.Height / splitHeight;

            int tilesPerBlockX = blockWidth / splitWidth;
            int tilesPerBlockY = blockHeight / splitHeight;

            int tileIndex = 0;

            BitmapTileMap = new BitmapTileMap(tilesWidth, tilesHeight);

            for (int blockY = 0; blockY < verticalBlocks; blockY++)
            {
                for (int blockX = 0; blockX < horizontalBlocks; blockX++)
                {
                    int tileStartX = blockX * 2;
                    int tileStartY = blockY * 2;

                    for (int loopx = 0; loopx < tilesPerBlockX; loopx++)
                    {
                        for (int loopy = 0; loopy < tilesPerBlockY; loopy++)
                        {
                            int tileIndexX = tileStartX + loopx;
                            int tileIndexY = tileStartY + loopy;

                            int bitmapx = tileIndexX * splitWidth;
                            int bitmapy = tileIndexY * splitHeight;

                            Rectangle rect = new Rectangle(bitmapx,
                                                           bitmapy, 
                                                           splitWidth,
                                                           splitHeight);

                            ProcessTile(rect,
                                        bitmap,
                                        attributeBitmap, 
                                        tileTypes,
                                        removeDuplicates,
                                        exportFlipType,
                                        ref tileIndex);
                        }
                    }
                }
            }


            /*

            for (int tiley = 0; tiley < tilesHeight; tiley++)
            {
                for (int tilex = 0; tilex < tilesWidth; tilex++)
                {
                    int bitmapx = tilex * splitWidth;
                    int bitmapy = tiley * splitHeight;

                    Rectangle rect = new Rectangle(bitmapx,
                                                   bitmapy, 
                                                   splitWidth,
                                                   splitHeight);

                    ProcessTile(rect,
                                bitmap,
                                attributeBitmap, 
                                tileTypes,
                                removeDuplicates,
                                exportFlipType,
                                ref tileIndex);
                }
            }
            */
        }

        private void ProcessTile(Rectangle rect,
                                 Bitmap bitmap,
                                 Bitmap tileTypesBitmap, 
                                 SplitBitmap tileTypes,
                                 bool removeDuplicates,
                                 ExportFlipType exportFlipType,
                                 ref int tileIndex)
        {


            // get attribute for tile
            int tileAttribute = 0;

            // the attribute (TILE_SOLID, etc) comes from the index of the color in the second layer
            // of the image.
            if (tileTypesBitmap != null && tileTypes != null)
            {
                var attributeBitmapTile = tileTypesBitmap.Clone(rect, System.Drawing.Imaging.PixelFormat.DontCare);

                var foundTile = tileTypes.getTileWithSameBitmap(attributeBitmapTile, ExportFlipType.None);

                if (foundTile != null)
                    tileAttribute = foundTile.Item1.Index;

                //BitmapData sourceBitmapData = attributeBitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);
                //byte* sourceBuffer = (byte*)sourceBitmapData.Scan0.ToPointer();
                //tileAttribute = sourceBuffer[0];
                //tileAttribute &= 0x0f;
                //attributeBitmap.UnlockBits(sourceBitmapData);

            }

            uint tileIndexToUse;

            if (removeDuplicates)
            {
                var bitmapTile = bitmap.Clone(rect, System.Drawing.Imaging.PixelFormat.DontCare);


                RotateFlipType flipFlag = RotateFlipType.RotateNoneFlipNone;

                var tuple = getTileWithSameBitmap(bitmapTile, exportFlipType);

                if (tuple == null)
                {
                    var newtile = new BitmapTile(tileIndex, bitmapTile, tileAttribute);

                    UniqueBitmapTiles.Add(newtile);

                    tileIndexToUse = (uint)tileIndex;

                    tileIndex++;
                }
                else
                {
                    var tile = tuple.Item1; // tile
                    tileIndexToUse = (uint)tile.Index;
                    flipFlag = tuple.Item2;
                }

                tileIndexToUse = ApplyFlip(tileIndexToUse, flipFlag, exportFlipType);
            }
            else
            {
                var bitmapTile = bitmap.Clone(rect, System.Drawing.Imaging.PixelFormat.DontCare);
                var newtile = new BitmapTile(tileIndex, bitmapTile, tileAttribute);

                UniqueBitmapTiles.Add(newtile);

                tileIndexToUse = (uint)tileIndex;

                tileIndex++;
            }



            BitmapTileMap.Map.Add(tileIndexToUse);
        }

        private uint ApplyFlip(uint tileIndexToUse, RotateFlipType flipFlag, ExportFlipType exportFlipType)
        {
            const uint SegaMasterSystemFlippedHorizontallyFlag = (1 << 9);
            const uint SegaMasterSystemFlippedVerticallyFlag = (1 << 10);
            const uint TILED_FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
            const uint TILED_FLIPPED_VERTICALLY_FLAG = 0x40000000;

            if (exportFlipType == ExportFlipType.Tiled)
            {
                switch (flipFlag)
                {
                    case RotateFlipType.RotateNoneFlipX:
                        tileIndexToUse |= TILED_FLIPPED_HORIZONTALLY_FLAG;
                        break;
                    case RotateFlipType.RotateNoneFlipY:
                        tileIndexToUse |= TILED_FLIPPED_VERTICALLY_FLAG;
                        break;
                    case RotateFlipType.RotateNoneFlipXY:
                        tileIndexToUse |= TILED_FLIPPED_VERTICALLY_FLAG;
                        tileIndexToUse |= TILED_FLIPPED_HORIZONTALLY_FLAG;
                        break;
                }
            }
            else
            {
                switch (flipFlag)
                {
                    case RotateFlipType.RotateNoneFlipX:
                        tileIndexToUse |= SegaMasterSystemFlippedHorizontallyFlag;
                        break;
                    case RotateFlipType.RotateNoneFlipY:
                        tileIndexToUse |= SegaMasterSystemFlippedVerticallyFlag;
                        break;
                    case RotateFlipType.RotateNoneFlipXY:
                        tileIndexToUse |= SegaMasterSystemFlippedVerticallyFlag;
                        tileIndexToUse |= SegaMasterSystemFlippedHorizontallyFlag;
                        break;
                }
            }
            return tileIndexToUse;
        }

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int memcmp(IntPtr b1, IntPtr b2, long count);

        public static bool CompareMemCmp(Bitmap b1, Bitmap b2)
        {
            if ((b1 == null) != (b2 == null)) return false;
            if (b1.Size != b2.Size) return false;

            var bd1 = b1.LockBits(new Rectangle(new Point(0, 0), b1.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            var bd2 = b2.LockBits(new Rectangle(new Point(0, 0), b2.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

            try
            {
                IntPtr bd1scan0 = bd1.Scan0;
                IntPtr bd2scan0 = bd2.Scan0;

                int stride = bd1.Stride;
                int len = stride * b1.Height;

                return memcmp(bd1scan0, bd2scan0, len) == 0;
            }
            finally
            {
                b1.UnlockBits(bd1);
                b2.UnlockBits(bd2);
            }
        }

        private static RotateFlipType? BitmapsMatch(Bitmap b1, Bitmap b2, ExportFlipType exportFlipType)
        {
            if ((b1 == null) != (b2 == null)) return null;
            if (b1.Size != b2.Size) return null;

            var bd1 = b1.LockBits(new Rectangle(new Point(0, 0), b1.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            var bd2 = b2.LockBits(new Rectangle(new Point(0, 0), b2.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

            try
            {
                IntPtr bd1scan0 = bd1.Scan0;
                IntPtr bd2scan0 = bd2.Scan0;

                int stride = bd1.Stride / sizeof(int);
                int len = stride * b1.Height;
                int byteLen = bd1.Stride * b1.Height;

                // we want to check if they're exactly the same
                if (memcmp(bd1scan0, bd2scan0, byteLen) == 0)
                {
                    return RotateFlipType.RotateNoneFlipNone;
                }

                // we want to check if they're the same but flipped
                //
                if (exportFlipType != ExportFlipType.None)
                {
                    int[] bd1Values = new int[len];
                    int[] bd2Values = new int[len];

                    // Copy the RGB values into the array
                    Marshal.Copy(bd1scan0, bd1Values, 0, len);
                    Marshal.Copy(bd2scan0, bd2Values, 0, len);

                    Func<bool> isFlippedOnX = () =>
                    {
                        // flipped on X
                        for (int loopy = 0; loopy < b1.Height; loopy++)
                        {
                            for (int loopx = 0; loopx < stride; loopx++)
                            {
                                if (bd1Values[loopx + (loopy * stride)] != bd2Values[((stride - 1) - loopx) + (loopy * stride)])
                                    return false;
                            }
                        }

                        return true;
                    };

                    if (isFlippedOnX())
                        return RotateFlipType.RotateNoneFlipX;

                    Func<bool> isFlippedOnY = () =>
                    {
                        // flipped on Y
                        for (int loopy = 0; loopy < b1.Height; loopy++)
                        {
                            for (int loopx = 0; loopx < stride; loopx++)
                            {
                                if (bd1Values[loopx + (loopy * stride)] != bd2Values[loopx + (((b1.Height - 1) - loopy) * stride)])
                                    return false;
                            }
                        }

                        return true;
                    };

                    if (isFlippedOnY())
                        return RotateFlipType.RotateNoneFlipY;
                    
                    Func<bool> isFlippedOnXY = () =>
                    {
                        // flipped on X
                        for (int loopy = 0; loopy < b1.Height; loopy++)
                        {
                            for (int loopx = 0; loopx < stride; loopx++)
                            {
                                if (bd1Values[loopx + (loopy * stride)] != bd2Values[((stride - 1) - loopx) + (((b1.Height - 1) - loopy) * stride)])
                                    return false;
                            }
                        }

                        return true;
                    };

                    if (isFlippedOnXY())
                        return RotateFlipType.RotateNoneFlipXY;
                }
            }
            finally
            {
                b1.UnlockBits(bd1);
                b2.UnlockBits(bd2);
            }


            return null;
        }

        private Tuple<BitmapTile, RotateFlipType> getTileWithSameBitmap(Bitmap bitmap, ExportFlipType exportFlipType)
        {
            foreach (var tile in UniqueBitmapTiles)
            {
                RotateFlipType? flipType = BitmapsMatch(tile.Bitmap, bitmap, exportFlipType);

                if (flipType != null)
                    return new Tuple<BitmapTile, RotateFlipType>(tile, flipType.Value);
            }

            return null;
        }


    }
}