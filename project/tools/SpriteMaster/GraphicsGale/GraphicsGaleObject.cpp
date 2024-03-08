#include "..\stdafx.h"
#include "GraphicsGaleObject.h"
#include "..\thirdparty\galefile151119\galefile.h"
#include <system_error>

namespace SpriteMaster
{

GraphicsGaleObject::GraphicsGaleObject(const std::string& filename)
{
    m_galeFileHandle = ggOpen(filename.c_str());

    if (m_galeFileHandle == NULL)
    {
        THROW_ERROR(Error::OpeningGraphicsGaleFileFailed, "Graphics Gale file not found.");
    }

    m_numberOfFrames = ggGetFrameCount(m_galeFileHandle);

    if (m_numberOfFrames == 0)
    {
        THROW_ERROR(Error::NoFramesInGraphicsGaleFile, "No frames found in file");
    }

    HBITMAP bitmap = ggGetBitmap(m_galeFileHandle, 0, 0);

    THROW_IF_NULL(bitmap, Error::BitmapHandleIsNull, "Error retrieving bitmap data");

    if (GetObject(bitmap, sizeof(BITMAP), &m_bitmap) == 0)
    {
        THROW_ERROR(Error::NoBitmapFound, "BitmapInfo is NULL");
    }

    if (m_bitmap.bmBitsPixel != 4)
    {
        THROW_ERROR(Error::FormatNot4BitsPerPixel, "Bitmap data is not 4 bits per pixel");
    }
}

GraphicsGaleObject::~GraphicsGaleObject()
{
    if (m_galeFileHandle != NULL)
    {
        ggClose(m_galeFileHandle);
    }
}

HBITMAP GraphicsGaleObject::getBitmap(LONG frameNo, LONG layerNo) const
{
    return ggGetBitmap(m_galeFileHandle, frameNo, layerNo);
}


DWORD GraphicsGaleObject::getLayerCount(LONG frameNo) const
{
    return ggGetLayerCount(m_galeFileHandle, frameNo);
}

DWORD GraphicsGaleObject::getFrameCount() const
{
    return ggGetFrameCount(m_galeFileHandle);
}

LONG GraphicsGaleObject::getFrameInfo(LONG frameNo, LONG nID) const
{
    return ggGetFrameInfo(m_galeFileHandle, frameNo, nID);
}

LONG GraphicsGaleObject::getFrameName(LONG frameNo, LPSTR pName, LONG len) const
{
    return ggGetFrameName(m_galeFileHandle, frameNo, pName, len);
}

HPALETTE GraphicsGaleObject::getPalette(LONG frameNo) const
{
    return ggGetPalette(m_galeFileHandle, frameNo);
}

}