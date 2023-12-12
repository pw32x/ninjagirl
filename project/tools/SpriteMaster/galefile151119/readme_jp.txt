-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
                               galefile.dll
                  Copyright 2009 HUMANBALANCE Co.,Ltd.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


■ソフト概要

本ソフトは、GraphicsGaleのファイルフォーマット(*.gal)を外部プログラムから
扱うためのライブラリ(DLL)です。


■関数

LPVOID __stdcall ggOpen(LPCSTR apath);
　機　能：GALファイル開く。
　引　数：apath = ファイルのフルパス
　戻り値：成功した場合はGaleオブジェクトのポインタを返す。失敗した場合は
　　　　　NULLを返す。ポインタを得たら終了する前にggCloseで閉じる必要があ
　　　　　る。

LONG __stdcall ggClose(LPVOID pFile);
　機　能：Galeオブジェクトを破棄する。
　引　数：pFile = Galeオブジェクト
　戻り値：成功した場合は1を返す。失敗した場合は0を返す。

DWORD __stdcall ggGetLastError(void);
　機　能：最新のエラーコードを返す。各関数でエラーが生じた後に呼び出す。
　引　数：なし
　戻り値：エラーコード
　　　　　　1 = ファイルが存在しない
　　　　　　2 = ファイルフォーマットが不正
　　　　　　3 = ファイルクローズに失敗
　　　　　　4 = Galeオブジェクトのポインタが無効
　　　　　　5 = 引数が無効

DWORD __stdcall ggGetFrameCount(LPVOID pFile);
　機　能：フレーム数を返す。
　引　数：pFile = Galeオブジェクト
　戻り値：Galeオブジェクトのフレーム数を返す。失敗した場合は0を返す。

DWORD __stdcall ggGetLayerCount(LPVOID pFile,LONG frameNo);
　機　能：レイヤー数を返す。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　戻り値：Galeオブジェクトのレイヤー数を返す。失敗した場合は0を返す。

LONG __stdcall ggGetInfo(LPVOID pFile,LONG nID);
　機　能：Galeオブジェクトの各種情報を返す。
　引　数：pFile = Galeオブジェクト
　　　　　nID = 取得する情報ID
　　　　　　1 = 背景色
　　　　　　2 = シングルパレットなら1
　　　　　　3 = 最下層レイヤーの透過禁止なら1
　　　　　　4 = bpp(1,4,8,15,16,24)
　　　　　　5 = 幅(ピクセル単位)
　　　　　　6 = 高さ(ピクセル単位)
　戻り値：nIDに応じた値を返す。

LONG __stdcall ggGetFrameInfo(LPVOID pFile,LONG frameNo,LONG nID);
　機　能：指定フレームの各種情報を返す。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　nID = 取得する情報ID
　　　　　　1 = 透過色
　　　　　　2 = 表示時間(ミリ秒単位)
　　　　　　3 = 表示後処理
　　　　　　　0 = 指定しない
　　　　　　　1 = 処分しない
　　　　　　　2 = 背景色で塗りつぶす
　　　　　　　3 = 元に戻す
　戻り値：nIDに応じた値を返す。

LONG __stdcall ggGetFrameName(LPVOID pFile,LONG frameNo,LPSTR pName,LONG len);
　機　能：指定フレームの名前を返す。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　pName = 名前を受け取るバッファのアドレス。NULLを渡すと必要なバ
　　　　　　　　　ッファサイズを返す。
　　　　　len = バッファのサイズ(バイト単位)
　戻り値：成功した場合はコピーされたバイト数を返す。失敗した場合は0を返す。

LONG __stdcall ggGetLayerInfo(LPVOID pFile,LONG frameNo,LONG layerNo,LONG nID);
　機　能：指定レイヤーの各種情報を返す。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス
　　　　　nID = 取得する情報ID
　　　　　　1 = 表示なら1、非表示なら0
　　　　　　2 = 透過色
　　　　　　3 = 不透過度(0～255)
　　　　　　4 = アルファチャンネルが有効なら1
　戻り値：nIDに応じた値を返す。

LONG __stdcall ggGetLayerName(LPVOID pFile,LONG frameNo,LONG layerNo,LPSTR pName,LONG len);
　機　能：指定レイヤーの名前を返す。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス
　　　　　pName = 名前を受け取るバッファのアドレス。NULLを渡すと必要なバ
　　　　　　　　　ッファサイズを返す。
　　　　　len = バッファのサイズ(バイト単位)
　戻り値：成功した場合はコピーされたバイト数を返す。失敗した場合は0を返す。

HBITMAP __stdcall ggGetBitmap(LPVOID pFile,LONG frameNo,LONG layerNo);
　機　能：指定フレーム、指定レイヤーの画像のビットマップハンドルを返す。
　　　　　取得したハンドルを破棄してはならない。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス。-1なら合成した画像
　戻り値：成功した場合はビットマップハンドルを返す。失敗した場合はNULLを返す。

HBITMAP __stdcall ggGetAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo);
　機　能：指定フレーム、指定レイヤーのアルファチャンネルのビットマップハ
　　　　　ンドルを返す。
　　　　　取得したハンドルを破棄してはならない。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス
　戻り値：成功した場合はビットマップハンドルを返す。失敗した場合はNULLを返す。

HPALETTE __stdcall ggGetPalette(LPVOID pFile,LONG frameNo);
　機　能：指定フレームの画像のパレットハンドルを返す。
　　　　　取得したハンドルを破棄してはならない。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　戻り値：成功した場合はパレットハンドルを返す。失敗した場合はNULLを返す。

LONG __stdcall ggDrawBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,HDC toDC,LONG toX,LONG toY);
　機　能：指定フレーム、指定レイヤーの画像を描画する。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス。-1なら合成した画像
　　　　　toDC = 描画先のデバイスコンテキストのハンドル
　　　　　toX = 描画先のx座標
　　　　　toY = 描画先のy座標
　戻り値：成功した場合は1を返す。失敗した場合は0を返す。

LONG __stdcall ggExportBitmap(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
　機　能：指定フレーム、指定レイヤーの画像をBMPファイルに出力する。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス。-1なら合成した画像
　　　　　outPath = 出力するファイルのフルパス
　戻り値：成功した場合は1を返す。失敗した場合は0を返す。

LONG __stdcall ggExportAlphaChannel(LPVOID pFile,LONG frameNo,LONG layerNo,LPCSTR outPath);
　機　能：指定フレーム、指定レイヤーのアルファチャンネルをBMPファイルに
　　　　　出力する。
　引　数：pFile = Galeオブジェクト
　　　　　frameNo = 0から始まるフレームインデックス
　　　　　layerNo = 0から始まるレイヤーインデックス
　　　　　outPath = 出力するファイルのフルパス
　戻り値：成功した場合は1を返す。失敗した場合は0を返す。


■使用許諾

このソフトウェアは、フリーウェアとして配付されます。即ち、無償で使用し、
また第三者に配付することができます。このソフトウェアの著作権は有限会社ヒ
ューマンバランスに帰属します。商用目的での配付には有限会社ヒューマンバラ
ンスの承諾が必要です。
このソフトウェアを貸与、リース、また、修正、変換、翻訳、リバースエンジニ
アリング、逆コンパイル、解析することは禁じられています。この許諾書の如何
なる部分にも抵触した場合には、このソフトウェアを使用する権利は自動的に消
滅し、このソフトウェアに関する全てのファイルを削除しなければなりません。
このソフトウェア及び関連書類は、単純にそのままの形態で提供されるものであ
り、いかなる保証も付いていません。有限会社ヒューマンバランスは、明示的で
あれ暗示的であれ、このソフトウェアの使用に関し、一切の保証をするものでは
ありません。
また、いかなる状況においても、有限会社ヒューマンバランスは、このソフトウ
ェアを使用することによって万が一生じた損害に対し、何ら責任を負うものでは
ありません。


■更新履歴

●15.11.19
・新ファイル形式に対応

●09.12.07
・ggGetBitmapとggGetPaletteを修正
・ggGetAlphaChannelとggExportAlphaChannelを追加

●09.06.30
・ver.2のファイル形式に対応

●09.03.08
・初公開



有限会社ヒューマンバランス

gale@humanbalance.net
http://www.humanbalance.net/
