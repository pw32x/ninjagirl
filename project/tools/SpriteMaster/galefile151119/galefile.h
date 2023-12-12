#include <windows.h>

LPVOID __stdcall ggOpen(LPCSTR apath);
LONG __stdcall ggClose(LPVOID pFile);
DWORD __stdcall ggGetLastError(void);
DWORD __stdcall ggGetFrameCount(LPVOID pFile);
DWORD __stdcall ggGetLayerCount(LPVOID pFile,LONG frameNo);
LONG __stdcall ggGetInfo(LPVOID pFile,LONG nID);
LONG __stdcall ggGetFrameInfo(LPVOID pFile,LONG frameNo,LONG nID);
LONG __stdcall ggGetFrameName(LPVOID pFile,LONG frameNo,LPSTR pName,LONG len);
LONG __stdcall ggGetLayerInfo(LPVOID pFile,LONG frameNo,LONG layerNo,LONG nID);
LONG __stdcall ggGetLayerName(LPVOID pFile,LONG frameNo,LONG layerNo,LPSTR pName,LONG len);
HBITMAP __stdcall ggGetBitmap(LPVOID pFile,LONG frameNo,LONG layerNo);
HBITMAP __stdcall ggGetAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo);
HPALETTE __stdcall ggGetPalette(LPVOID pFile,LONG frameNo);
LONG __stdcall ggDrawBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,HDC toDC,LONG toX,LONG toY);
LONG __stdcall ggExportBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
LONG __stdcall ggExportAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
