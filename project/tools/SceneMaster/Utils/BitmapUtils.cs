﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using System.Windows.Media.Imaging;
using System.Windows;

namespace SceneMaster.Utils
{
    internal class BitmapUtils
    {
        public static BitmapImage ConvertHBitmapToBitmapImage(IntPtr hBitmap)
        {
            // Create a BitmapSource from the HBitmap
            BitmapSource bitmapSource = Imaging.CreateBitmapSourceFromHBitmap(
                hBitmap,
                IntPtr.Zero,
                Int32Rect.Empty,
                BitmapSizeOptions.FromEmptyOptions());

            // Convert BitmapSource to BitmapImage
            BitmapImage bitmapImage = new BitmapImage();
            using (MemoryStream memoryStream = new MemoryStream())
            {
                BitmapEncoder encoder = new PngBitmapEncoder(); // You can choose a different encoder if needed
                encoder.Frames.Add(BitmapFrame.Create(bitmapSource));
                encoder.Save(memoryStream);

                // Set the BitmapImage source to the MemoryStream
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memoryStream;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();

                // Ensure the BitmapImage is fully loaded before using it
                bitmapImage.Freeze();
            }

            return bitmapImage;
        }

        public static BitmapImage LoadBitmapImage(string imagePath)
        {
            try
            {
                // Create a BitmapImage
                BitmapImage bitmapImage = new BitmapImage();

                // Set the UriSource to the file path
                bitmapImage.BeginInit();
                bitmapImage.UriSource = new Uri(imagePath, UriKind.RelativeOrAbsolute);
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();

                return bitmapImage;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error loading image: {ex.Message}");
                return null;
            }
        }
    }
}
