using GraphicsGaleWrapper;
using SceneMaster.Utils;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SceneMaster.EditorObjectLibrary.Models
{
    public class Visual
    {
        public int Width => (int)Image.Width;
        public int Height => (int)Image.Height;
        public int OffsetX { get; private set; } = 0;
        public int OffsetY { get; private set; } = 0;
        public BitmapImage Image { get; set; }

        public void Load(XmlElement visualNode)
        {
            if (visualNode["Image"] is var imageNode && imageNode != null)
            {
                string imageFilename = XmlUtils.GetValue<string>(imageNode, "filename");
                if (!string.IsNullOrEmpty(imageFilename)) 
                {
                    Image = BitmapUtils.LoadBitmapImage(imageFilename);
                }
            }
            else if (visualNode["GraphicsGale"] is var graphicsGaleNode && graphicsGaleNode != null)
            {
                string graphicsGaleFilename = XmlUtils.GetValue<string>(graphicsGaleNode, "filename");
                int frameNumber = XmlUtils.GetValue<int>(graphicsGaleNode, "framenumber");

                if (!string.IsNullOrEmpty(graphicsGaleFilename)) 
                {
                    var galeFile = GaleFile.Open(graphicsGaleFilename);

                    var frameBitmap = GaleFile._ggGetBitmap(galeFile, frameNumber, 0);
                    var palette = GaleFile.GetPalette(galeFile, frameNumber);

                    Image = BitmapUtils.ConvertHBitmapToBitmapImage(frameBitmap);

                    FindOffset(galeFile);

                    GaleFile.Close(galeFile);
                }
            }
        }

        private void FindOffset(nint galeFile)
        {
            for (int loop = 0; loop < GaleFile.GetFrameCount(galeFile); loop++) 
            {
                string frameName = GaleFile.GetFrameName(galeFile, loop);

                if (frameName == null)
                    continue;

                var tokens = new Queue<string>(frameName.Split(' '));

                while (tokens.Any())
                {   
                    string token = tokens.Dequeue();
		            if (token == "OFFSET")
		            {
                        if (!tokens.Any())
                            continue; 

			            token = tokens.Dequeue();
                        if (int.TryParse(token, out var offsetx))
			                OffsetX = offsetx;

                        if (!tokens.Any())
                            continue; 

                        token = tokens.Dequeue();
                        if (int.TryParse(token, out var offsety))
			                OffsetY = offsety;
		            }
                }
            }
        }
    }
}
