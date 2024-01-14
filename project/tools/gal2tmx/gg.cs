/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 This GraphicsGale CSharp-Wrapper was programmed by SebaGamesDev (http://sebagamesdev.com).
 
 This code is divided in two optional ways to be used:
 1) Traditional way: There's a "gg" static class, which work as a slightly simplified interface to use the main functions of the GraphicsGale dll.
 2) Object oriented way: The instantiable GaleObject class which fits more for an object-oriented way to read each GraphicsGale file.

 Remember that it's only a wrapper, so, you will need the official GraphicsGale dll which is provided at https://graphicsgale.com/us/ and has it's own usage rights.
 The current version of the GraphicsGale dll used in this code was "Ver 15.11.19" (direct link: https://graphicsgale.com/files/galefile151119.zip)
 
 You can use, edit or distribute this wrapper code in any way you want. Selling it as an individual thing is stricly prohibited.
 
 Licence: This code is provided as is, without warranty of any kind. The author shall not be liable for damages of any kind. Use of this software indicates you agree to this.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
namespace GraphicsGaleWrapper
{

    #region Enums
    public enum ERROR_CODE
    {
        NO_ERROR = 0,
        FILE_NOT_FOUND = 1,
        FILE_INVALID_FORMAT = 2,
        FILE_CANT_BE_CLOSED = 3,
        INVALID_ADDRESS_OF_GALE_OBJECT = 4,
        INVALID_PARAMETER = 5
    }

    public enum DOC_INFO
    {
        BACKGROUND_COLOR_VALUE = 1,
        IS_PALETTE_SINGLE = 2,
        IS_BOTTOM_LAYER_TRANSPARENCY_DISABLED = 3,
        BITS_PER_PIXEL = 4,
        WIDTH = 5,
        HEIGHT = 6
    }

    public enum FRAME_INFO
    {
        TRANSPARENT_COLOR = 1,
        DELAY_IN_MS = 2,
        DISPOSAL_TYPE = 3
    }

    public enum DISPOSAL_TYPE
    {
        NOT_SPECIFIED = 0,
        NOT_DISPOSED = 1,
        FILLED_WITH_BG_COLOR = 2,
        RESTORED_PREVIOUS_STATE = 3
    }

    public enum LAYER_INFO
    {
        IS_VISIBLE = 1,
        TRANSPARENT_COLOR = 2,
        OPACITY = 3,
        IS_ALPHA_CHANNEL_ENABLED = 4
    } 
    #endregion

    /// <summary>
    /// GraphicsGale dll official functions.
    /// </summary>
    public static class gg
    {
        public const int ALL_LAYERS = -1;

        /// <summary>
        /// Opens a gal file.
        /// </summary>
        /// <param name="fname">Filename of the gal file.</param>
        /// <returns>If the function succeeds, the return value is the address of the gale object. The gale object must be deleted by gg.Close. If the function fails, the return value is null.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggOpen")]
        public static extern IntPtr Open(String fname);

        /// <summary>
        /// Deletes a gale object.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <returns>If the function succeeds, the return value is 1. If the function fails, the return value is 0.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggClose")]
        public static extern int Close(IntPtr pFile);
        
        [DllImport("galefile.dll", EntryPoint = "ggGetLastError")]
        private static extern int _ggGetLastError();

        /// <summary>
        /// Retrieves the latest error code.
        /// </summary>
        public static ERROR_CODE GetLastError() {
            return (ERROR_CODE)_ggGetLastError();
        }

        /// <summary>
        /// Retrieves the amount of frames. If the function fails, the return value is 0.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        [DllImport("galefile.dll", EntryPoint = "ggGetFrameCount")]
        public static extern int GetFrameCount(IntPtr pFile);

        /// <summary>
        /// Retrieves the amount of layers. If the function fails, the return value is 0.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        [DllImport("galefile.dll", EntryPoint = "ggGetLayerCount")]
        public static extern int GetLayerCount(IntPtr pFile, int frameIndex);
        
        [DllImport("galefile.dll", EntryPoint = "ggGetInfo")]
        private static extern int _ggGetInfo(IntPtr pFile, int docInfoID);

        /// <summary>
        /// Retrieves information of the gale object.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="info">The Info that must be returned.</param>
        public static int GetInfo(IntPtr pFile, DOC_INFO info) {
            return _ggGetInfo(pFile, (int)info);
        }

        /// <summary>
        /// Retrieves the width of image in pixels.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static int GetWidth(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.WIDTH);
        }

        /// <summary>
        /// Retrieves the height of image in pixels.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static int GetHeight(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.HEIGHT);
        }

        /// <summary>
        /// Returns true if all frames uses the same palette.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static bool IsSinglePalette(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.IS_PALETTE_SINGLE) == 1;
        }

        /// <summary>
        /// Retrieves background color value.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static int GetBackgroundColor(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.BACKGROUND_COLOR_VALUE);
        }

        /// <summary>
        /// Returns true if transparency is disabled on bottom layer.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static bool IsBottomLayerTransparencyDisabled(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.IS_BOTTOM_LAYER_TRANSPARENCY_DISABLED) == 1;
        }

        /// <summary>
        /// Get current bits per pixel (bpp) (1,4,8,15,16 or 24).
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        public static int GetBitsPerPixel(IntPtr pFile) {
            return GetInfo(pFile, DOC_INFO.BITS_PER_PIXEL);
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetFrameInfo")]
        private static extern int _ggGetFrameInfo(IntPtr pFile, int frameIndex, int frameInfoID);

        /// <summary>
        /// Retrieves frame info.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="info">The Info that must be returned.</param>
        public static int GetFrameInfo(IntPtr pFile, int frameIndex, FRAME_INFO info) {
            return _ggGetFrameInfo(pFile, frameIndex, (int)info);
        }

        /// <summary>
        /// Retrieves frame transparent color.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        public static int GetFrameTransparentColor(IntPtr pFile, int frameIndex) {
            return GetFrameInfo(pFile, frameIndex, FRAME_INFO.TRANSPARENT_COLOR);
        }

        /// <summary>
        /// Retrieves frame disposal type.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        public static DISPOSAL_TYPE GetFrameDisposalType(IntPtr pFile, int frameIndex) {
            return (DISPOSAL_TYPE)GetFrameInfo(pFile, frameIndex, FRAME_INFO.DISPOSAL_TYPE);
        }

        /// <summary>
        /// Retrieves frame delay in milliseconds.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        public static int GetFrameDelay(IntPtr pFile, int frameIndex) {
            return GetFrameInfo(pFile, frameIndex, FRAME_INFO.DELAY_IN_MS);
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetFrameName")]
        private static extern int _ggGetFrameName(IntPtr pFile, int frameIndex, StringBuilder pName, int len);

        /// <summary>
        /// Retrieves frame name.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="maxLenght">The max lenght of the name string.</param>
        public static string GetFrameName(IntPtr pFile, int frameIndex, int maxLenght = 256) {
            StringBuilder strName = new StringBuilder(maxLenght);
            if(_ggGetFrameName(pFile, frameIndex, strName, strName.Capacity) == 0) return null;
            return strName.ToString();
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetLayerInfo")]
        private static extern int _ggGetLayerInfo(IntPtr pFile, int frameIndex, int layerIndex, int layerInfoID);

        /// <summary>
        /// Retrieves layer info.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        /// <param name="info">The Info that must be returned.</param>
        public static int GetLayerInfo(IntPtr pFile, int frameIndex, int layerIndex, LAYER_INFO info) {
            return _ggGetLayerInfo(pFile, frameIndex, layerIndex, (int)info);
        }

        /// <summary>
        /// Returns if layer is visible.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        public static bool IsLayerVisible(IntPtr pFile, int frameIndex, int layerIndex) {
            return GetLayerInfo(pFile, frameIndex, layerIndex, LAYER_INFO.IS_VISIBLE) == 1;
        }

        /// <summary>
        /// Retrieves layer transparent color.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        public static int GetLayerTransparentColor(IntPtr pFile, int frameIndex, int layerIndex) {
            return GetLayerInfo(pFile, frameIndex, layerIndex, LAYER_INFO.TRANSPARENT_COLOR);
        }

        /// <summary>
        /// Retrieves layer opacity level (between 0 and 255).
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        public static int GetLayerOpacityLevel(IntPtr pFile, int frameIndex, int layerIndex) {
            return GetLayerInfo(pFile, frameIndex, layerIndex, LAYER_INFO.OPACITY);
        }

        /// <summary>
        /// Returns if is alpha channel enabled.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        public static bool IsAlphaChannelEnabled(IntPtr pFile, int frameIndex, int layerIndex) {
            return GetLayerInfo(pFile, frameIndex, layerIndex, LAYER_INFO.IS_ALPHA_CHANNEL_ENABLED) == 1;
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetLayerName")]
        private static extern int _ggGetLayerName(IntPtr pFile, int frameIndex, int layerIndex, StringBuilder pName, int len);

        /// <summary>
        /// Retrieves layer name.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        /// <param name="maxLenght">The max lenght of the name string.</param>
        public static string GetLayerName(IntPtr pFile, int frameIndex, int layerIndex, int maxLenght = 256) {
            StringBuilder strName = new StringBuilder(maxLenght);
            if(_ggGetLayerName(pFile, frameIndex, layerIndex, strName, strName.Capacity) == 0) return null;
            return strName.ToString();
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetBitmap")]
        private static extern IntPtr _ggGetBitmap(IntPtr pFile, int frameIndex, int layerIndex);

        /// <summary>
        /// Retrieves a new Bitmap of specific frame and layer.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero). (Use -1 to include all layers)</param>
        public static Bitmap GetBitmap(IntPtr pFile, int frameIndex, int layerIndex) {
            IntPtr hBitmap = _ggGetBitmap(pFile, frameIndex, layerIndex);
            if(hBitmap.ToInt32() == 0) return null;
            return Bitmap.FromHbitmap(hBitmap);
        }

        [DllImport("galefile.dll", EntryPoint = "ggGetAlphaChannel")]
        private static extern IntPtr _ggGetAlphaChannel(IntPtr pFile, int frameIndex, int layerIndex);

        /// <summary>
        /// Retrieves a new Bitmap of specific frame and layer alpha channel.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        public static Bitmap GetAlphaChannel(IntPtr ptr, int frameIndex, int layerIndex) {
            IntPtr hBitmap = _ggGetAlphaChannel(ptr, frameIndex, layerIndex);
            if(hBitmap.ToInt32() == 0) return null;
            return Bitmap.FromHbitmap(hBitmap);
        }

        /// <summary>
        /// Retrieves the handle of palette of specified frame.
        /// The handle must not be deleted.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <returns>If the function succeeds, the return value is the handle of palette. If the function fails, the return value is 0.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggGetPalette")]
        public static extern IntPtr GetPalette(IntPtr pFile, int frameIndex);

        /// <summary>
        /// Draws the image of specified frame and layer to specified device context.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero). (Use -1 to combine all visible layers)</param>
        /// <param name="toDC">The handle of device context of the destination.</param>
        /// <param name="toX">Specifies the x-coordinate of the destination.</param>
        /// <param name="toY">Specifies the y-coordinate of the destination.</param>
        /// <returns>If the function succeeds, the return value is 1. If the function fails, the return value is 0.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggDrawBitmap")]
        public static extern int DrawBitmap(IntPtr pFile, int frameIndex, int layerIndex, IntPtr toDC, int toX, int toY);

        /// <summary>
        /// Creates a bmp file from the image of specified frame and layer.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero). (Use -1 to combine all visible layers)</param>
        /// <param name="outPath">The filename for output.</param>
        /// <returns>If the function succeeds, the return value is 1. If the function fails, the return value is 0.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggExportBitmap")]
        public static extern int ExportBitmap(IntPtr pFile, int frameIndex, int layerIndex, String outPath);

        /// <summary>
        /// Creates a bmp file from the alpha channel of specified frame and layer.
        /// </summary>
        /// <param name="pFile">The address of the gale object.</param>
        /// <param name="frameIndex">The frame index (which begin from zero).</param>
        /// <param name="layerIndex">The layer index (which begin from zero).</param>
        /// <param name="outPath">The filename for output.</param>
        /// <returns>If the function succeeds, the return value is 1. If the function fails, the return value is 0.</returns>
        [DllImport("galefile.dll", EntryPoint = "ggExportAlphaChannel")]
        public static extern int ExportAlphaChannel(IntPtr pFile, int frameIndex, int layerIndex, String outPath);

    }

    /// <summary>
    /// Object-oriented GaleObject class.
    /// </summary>
    public class GaleObject:IDisposable
    {
        public IntPtr Handle { get; private set; }

        public int BackgroundColor { get; private set; }

        public int Width { get; private set; }
        public int Height { get; private set; }

        public int FrameCount { get; private set; }

        internal string _ZeroDigitFormat { get; private set; }

        private Frame[] frames = null;
        public Frame[] Frames {
            get {
                if(frames == null) {
                    frames = new Frame[FrameCount];
                    for(int i = 0; i < FrameCount; i++) {
                        frames[i] = new Frame(this, i);
                    }
                }
                return frames;
            }
        }

        public bool SinglePalette { get; private set; }

        public bool IndexedColor { get; private set; }

        public bool DisabledBottomLayerTransparency { get; private set; }

        public int BitsPerPixel { get; private set; }

        private ColorPalette palette = null;
        public ColorPalette Palette {
            get {
                if(!SinglePalette || !IndexedColor) return null;
                if(palette == null) {
                    using(var bmp = gg.GetBitmap(Handle, 0, 0)) {
                        palette = bmp.Palette;
                    }
                }
                return palette;
            }
        }

        public GaleObject(string path) {
            Handle = gg.Open(path);

            if(Handle.ToInt64() == 0) {
                switch(gg.GetLastError()) {
                    case ERROR_CODE.NO_ERROR: break;
                    case ERROR_CODE.FILE_NOT_FOUND: throw new FileNotFoundException("File not found!", path);
                    case ERROR_CODE.FILE_INVALID_FORMAT: throw new Exception("Invalid format at file: " + path);
                    default: throw new Exception("Unknow Error while read: " + path);
                }
            }

            Width = gg.GetWidth(Handle);
            Height = gg.GetHeight(Handle);

            SinglePalette = gg.IsSinglePalette(Handle);
            BackgroundColor = gg.GetBackgroundColor(Handle);

            DisabledBottomLayerTransparency = gg.IsBottomLayerTransparencyDisabled(Handle);

            BitsPerPixel = gg.GetBitsPerPixel(Handle);
            IndexedColor = BitsPerPixel <= 8;

            FrameCount = gg.GetFrameCount(Handle);
            _ZeroDigitFormat = new String('0', FrameCount.ToString().Length);

        }

        public void Dispose() {
            gg.Close(Handle);
            frames = null;
            Handle = IntPtr.Zero;
        }
    }

    public class Frame
    {
        private GaleObject galeObject;
        private int frameIndex;

        public string Name { get; private set; } = "";
        public string InternalName { get; private set; }

        public int LayerCount { get; private set; }

        private Layer[] layers = null;
        public Layer[] Layers {
            get {
                if(layers == null) {
                    layers = new Layer[LayerCount];
                    for(int i = 0; i < LayerCount; i++) {
                        layers[i] = new Layer(galeObject, frameIndex, i);
                    }
                }
                return layers;
            }
        }
        public int TransparentColor { get; private set; }
        public DISPOSAL_TYPE DisposalType { get; private set; }
        public int Delay { get; private set; }

        private ColorPalette palette = null;
        public ColorPalette Palette {
            get {
                if(!galeObject.IndexedColor) return null;
                if(galeObject.SinglePalette) return galeObject.Palette;
                if(palette == null) {
                    using(var bmp = gg.GetBitmap(galeObject.Handle, frameIndex, 0)) {
                        palette = bmp.Palette;
                    }
                }
                return palette;
            }
        }

        public int Width { get { return galeObject.Width; } }
        public int Height { get { return galeObject.Height; } }

        internal Frame(GaleObject galeObject, int frameIndex) {
            this.galeObject = galeObject;
            this.frameIndex = frameIndex;

            InternalName = gg.GetFrameName(galeObject.Handle, frameIndex);

            if (InternalName != null)
            {
                Name = InternalName?.Replace("%framenumber%", (frameIndex + 1).ToString())
                                    .Replace("%framenumber_zero%", (frameIndex + 1).ToString(galeObject._ZeroDigitFormat))
                                    .Replace("%frameindex%", frameIndex.ToString())
                                    .Replace("%frameindex_zero%", frameIndex.ToString(galeObject._ZeroDigitFormat));
            }


            TransparentColor = gg.GetFrameTransparentColor(galeObject.Handle, this.frameIndex);
            DisposalType = gg.GetFrameDisposalType(galeObject.Handle, this.frameIndex);
            Delay = gg.GetFrameDelay(galeObject.Handle, this.frameIndex);

            LayerCount = gg.GetLayerCount(galeObject.Handle, frameIndex);
        }

        public Bitmap CreateBitmap() {
            var bmp = gg.GetBitmap(galeObject.Handle, frameIndex, gg.ALL_LAYERS);
            if(!galeObject.DisabledBottomLayerTransparency) bmp.MakeTransparent();
            return bmp;
        }

        public override string ToString() {
            return Name;
        }
    }

    public class Layer
    {
        private GaleObject galeObject;
        private int frameIndex;
        private int layerIndex;

        public string Name { get; private set; }
        public bool Visible { get; private set; }
        public bool AlphaChannelEnabled { get; private set; }
        public int TransparentColor { get; private set; }
        public int Opacity { get; private set; }

        public int Width { get { return galeObject.Width; } }
        public int Height { get { return galeObject.Height; } }

        internal Layer(GaleObject galeObject, int frameIndex, int layerIndex) {
            this.galeObject = galeObject;

            this.frameIndex = frameIndex;
            this.layerIndex = layerIndex;

            Name = gg.GetLayerName(galeObject.Handle, frameIndex, layerIndex);

            Visible = gg.IsLayerVisible(galeObject.Handle, frameIndex, layerIndex);
            AlphaChannelEnabled = gg.IsAlphaChannelEnabled(galeObject.Handle, frameIndex, layerIndex);

            TransparentColor = gg.GetLayerTransparentColor(galeObject.Handle, frameIndex, layerIndex);
            Opacity = gg.GetLayerOpacityLevel(galeObject.Handle, frameIndex, layerIndex);
        }

        public Bitmap CreateBitmap() {
            var bmp = gg.GetBitmap(galeObject.Handle, frameIndex, layerIndex);
            //bmp.MakeTransparent(); // for some reason this makes pixel index 4 transparent. disable this because I dont need it.
            return bmp;
        }

        public override string ToString() {
            return Name;
        }
    }

}
