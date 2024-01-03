using GraphicsGaleWrapper;
using SceneMaster.Utils;
using System.Drawing;
using System.Windows.Media.Imaging;
using System.Xml;

namespace SceneMaster.EditorObjectLibrary.Models
{
    public class Visual
    {
        public int Width => (int)Image.Width;
        public int Height => (int)Image.Height;
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

                    GaleFile.Close(galeFile);
                }
            }
        }
    }
}
