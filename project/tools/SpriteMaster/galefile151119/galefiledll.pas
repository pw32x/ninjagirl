unit galefiledll;

interface

uses windows;

function ggOpen(const apath: pChar): pointer; stdcall; external 'galefile.dll';
function ggClose(const pFile: pointer): longbool; stdcall; external 'galefile.dll';
function ggGetLastError: DWord; stdcall; external 'galefile.dll';
function ggGetFrameCount(const pFile: pointer): DWord; stdcall; external 'galefile.dll';
function ggGetLayerCount(const pFile: pointer; frameNo: integer): DWord; stdcall; external 'galefile.dll';
function ggGetInfo(const pFile: pointer; nID: integer): integer; stdcall; external 'galefile.dll';
function ggGetFrameInfo(const pFile: pointer; frameNo,nID: integer): integer; stdcall; external 'galefile.dll';
function ggGetFrameName(const pFile: pointer; frameNo: integer;
  const pName: pChar; len: integer): integer; stdcall; external 'galefile.dll';
function ggGetLayerInfo(const pFile: pointer; frameNo,layerNo,nID: integer): integer; stdcall; external 'galefile.dll';
function ggGetLayerName(const pFile: pointer; frameNo,layerNo: integer;
  const pName: pChar; len: integer): integer; stdcall; external 'galefile.dll';
function ggGetBitmap(const pFile: pointer; frameNo,layerNo: integer): HBITMAP; stdcall; external 'galefile.dll';
function ggGetPalette(const pFile: pointer; frameNo: integer): HPALETTE; stdcall; external 'galefile.dll';
function ggGetAlphaChannel(const pFile: pointer; frameNo,layerNo: integer): HBITMAP; stdcall; external 'galefile.dll';
function ggDrawBitmap(const pFile: pointer; frameNo,layerNo: integer;
  ddc: HDC; x,y: integer): longbool; stdcall; external 'galefile.dll';
function ggExportBitmap(const pFile: pointer; frameNo,layerNo: integer;
  const outPath: pChar): longbool; stdcall; external 'galefile.dll';
function ggExportAlphaChannel(const pFile: pointer; frameNo,layerNo: integer;
  const outPath: pChar): longbool; stdcall; external 'galefile.dll';

implementation

end.

