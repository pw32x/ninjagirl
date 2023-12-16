-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                               galefile.dll
                  Copyright 2009 HUMANBALANCE Co.,Ltd.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


--- About ---------------------------------------------------------------
This is library(DLL) for using gal file by external program.


--- Function ------------------------------------------------------------
LPVOID __stdcall ggOpen(LPCSTR apath);
  Contents:   Opens a gal file.
  Parameters: apath = Filename of the gal file.
  Return:     If the function succeeds, the return value is the address 
              of the gale object. The gale object must be deleted by 
              ggClose.
              If the function fails, the return value is NULL.

LONG __stdcall ggClose(LPVOID pFile);
  Contents:   Deletes a gale object.
  Parameters: pFile = The address of the gale object.
  Return:     If the function succeeds, the return value is 1.
              If the function fails, the return value is 0.

DWORD __stdcall ggGetLastError(void);
  Contents:   Retrieves the latest error code.
  Parameters: Nothing.
  Return:     Error code.
                1 = File does not exist.
                2 = File format is invalid.
                3 = File can not be closed.
                4 = The address of gale object is invalid.
                5 = Parameter is invalid.

DWORD __stdcall ggGetFrameCount(LPVOID pFile);
  Contents:   Retrieves number of frame.
  Parameters: pFile = The address of the gale object.
  Return:     If the function succeeds, the return value is number of 
              frame.
              If the function fails, the return value is 0.

DWORD __stdcall ggGetLayerCount(LPVOID pFile,LONG frameNo);
  Contents:   Retrieves number of layer.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
  Return:     If the function succeeds, the return value is number of 
              layer of specified frame.
              If the function fails, the return value is 0.

LONG __stdcall ggGetInfo(LPVOID pFile,LONG nID);
  Contents:   Retrieves information of gale object.
  Parameters: pFile = The address of the gale object.
              nID = Specifies information ID.
                1 = Return value is background-color.
                2 = If the palette is single, return value is 1.
                3 = If the transparency of bottom layer is disabled, 
                    return value is 1.
                4 = Return value is bpp(1,4,8,15,16,24).
                5 = Return value is width of image by pixel.
                6 = Return value is height of image by pixel.
  Return:     See the Parameters.

LONG __stdcall ggGetFrameInfo(LPVOID pFile,LONG frameNo,LONG nID);
  Contents:   Retrieves information of specified frame.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              nID = Specifies information ID.
                1 = Return value is the transparent color.
                2 = Return value is the delay by milli-second.
                3 = Return value is the disposal type after display.
                  0 = Not specified.
                  1 = Not disposed.
                  2 = Filled by the background-color.
                  3 = Restored to previous state.
  Return:     See the Parameters.

LONG __stdcall ggGetFrameName(LPVOID pFile,LONG frameNo,LPSTR pName,LONG len);
  Contents:   Retrieves the name of specified frame.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              pName = The address of string buffer that receives the 
                      null-terminated string specifying the name.
                      If it is NULL, return value is necessary size of 
                      buffer.
              len = Specifies the size in byte of the buffer.
  Return:     If the function succeeds, the return value is the length in 
              byte, of the string copied to pName.
              If the function fails, the return value is 0.

LONG __stdcall ggGetLayerInfo(LPVOID pFile,LONG frameNo,LONG layerNo,LONG nID);
  Contents:   Retrieves information of specified layer.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
              nID = Specifies information ID.
                1 = If the layer is visible, return value is 1.
                2 = Return value is the transparent color.
                3 = Return value is the opacity(0~255).
                4 = If the alpha-channel is effective, return value is 1.
  Return:     See the Parameters.

LONG __stdcall ggGetLayerName(LPVOID pFile,LONG frameNo,LONG layerNo,LPSTR pName,LONG len);
  Contents:   Retrieves the name of specified layer.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
              pName = The address of string buffer that receives the 
                      null-terminated string specifying the name.
                      If it is NULL, return value is necessary size of 
                      buffer.
              len = Specifies the size in byte of the buffer.
  Return:     If the function succeeds, the return value is the length in 
              byte, of the string copied to pName.
              If the function fails, the return value is 0.

HBITMAP __stdcall ggGetBitmap(LPVOID pFile,LONG frameNo,LONG layerNo);
  Contents:   Retrieves the handle of bitmap of specified frame and 
              layer. The handle must not be deleted.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
                        If it is -1, combined image is retrieved.
  Return:     If the function succeeds, the return value is the handle of 
              bitmap.
              If the function fails, the return value is 0.

HBITMAP __stdcall ggGetAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo);
  Contents:   Retrieves the handle of bitmap of alpha channel of specified 
              frame and layer. The handle must not be deleted.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
  Return:     If the function succeeds, the return value is the handle of 
              bitmap.
              If the function fails, the return value is 0.

HPALETTE __stdcall ggGetPalette(LPVOID pFile,LONG frameNo);
  Contents:   Retrieves the handle of palette of specified frame.
              The handle must not be deleted.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
  Return:     If the function succeeds, the return value is the handle of 
              palette.
              If the function fails, the return value is 0.

LONG __stdcall ggDrawBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,HDC toDC,LONG toX,LONG toY);
  Contents:   Draws the image of specified frame and layer to specified 
              device context.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
                        If it is -1, combined image is retrieved.
              toDC = The handle of device context of the destination.
              toX = Specifies the x-coordinate of the destination.
              toY = Specifies the y-coordinate of the destination.
  Return:     If the function succeeds, the return value is 1.
              If the function fails, the return value is 0.

LONG __stdcall ggExportBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
  Contents:   Creates a bmp file from the image of specified frame and 
              layer.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
                        If it is -1, combined image is created.
              outPath = The filename for output.
  Return:     If the function succeeds, the return value is 1.
              If the function fails, the return value is 0.

LONG __stdcall ggExportAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
  Contents:   Creates a bmp file from the alpha channel of specified frame 
              and layer.
  Parameters: pFile = The address of the gale object.
              frameNo = The frame index which begin from zero.
              layerNo = The layer index which begin from zero.
              outPath = The filename for output.
  Return:     If the function succeeds, the return value is 1.
              If the function fails, the return value is 0.


--- Licensing Agreement ------------------------------------------------
You can not distribute the software without our permission.
You may not loan, lease, alter, decompile, disassemble, decrypt, extract 
or otherwise reverse-engineer the Software. If you run afoul of this 
licensing agreement, right of use for the Software lapses automatically, 
and you must delete all files of the Software.

The package is provided as is, without warranty of any kind. The author 
shall not be liable for damages of any kind. Use of this software 
indicates you agree to this.


--- History ------------------------------------------------------------
[15.11.19]
 Supports new file format
[09.12.07]
 Fixed a bug of ggGetBitmap and ggGetPalette
 Added ggGetAlphaChannel and ggExportAlphaChannel
[09.06.30]
 Supports a file format of ver.2
[09.03.08]
 First release


HumanBalance Co.,Ltd.

gale@humanbalance.net
http://www.humanbalance.net/
