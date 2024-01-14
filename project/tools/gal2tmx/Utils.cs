using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace gal2tmx
{
    class Utils
    {
        unsafe public static bool IsTileEmpty(Bitmap bitmap)
        {
            if (bitmap == null)
            {
                throw new ArgumentNullException(nameof(bitmap));
            }

            // Check if the bitmap has zero width or height.
            if (bitmap.Width == 0 || bitmap.Height == 0)
            {
                return true;
            }

            // Lock the bitmap data to access pixel values.
            BitmapData bitmapData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), 
                                                 ImageLockMode.ReadOnly, 
                                                 bitmap.PixelFormat);


            byte* bitmapBuffer = (byte*)bitmapData.Scan0.ToPointer();

            int size = bitmapData.Stride * bitmapData.Height;

            for (int loop = 0; loop < size; loop++)
            {
                if (bitmapBuffer[loop] != 0)
                    return false;
            }

            bitmap.UnlockBits(bitmapData);

            return true;
        }

        internal static bool IsFile(string path)
        {
            return File.Exists(path);
        }

        internal static bool IsFileOrFileSpec(string path)
        {
            return path.Contains('*') || path.Contains('.');
        }

        internal static bool HasWildcard(string path)
        {
            return path.Contains('*');
        }

        public static IEnumerable<string> GetFilesFromWildcardPath(string path)
        {
            List<string> filenames = new List<string>();

            path = Path.Combine(path.Split('/'));
            int lastSlashIndex = path.LastIndexOf(System.IO.Path.DirectorySeparatorChar);

            string directoryPath = "";

            if (lastSlashIndex > 0)
                directoryPath = path.Substring(0, lastSlashIndex + 1);

            string searchPattern = Path.GetFileName(path);

            string[] matchingFiles = Directory.GetFiles(directoryPath, 
                                                        searchPattern, 
                                                        SearchOption.TopDirectoryOnly);

            foreach (string matchingFile in matchingFiles)
            {
                filenames.Add(matchingFile);
            }

            return filenames;
        }
    }
}
