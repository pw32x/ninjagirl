#pragma once
#include <string>

namespace SpriteMaster
{
	class GraphicsGaleObject sealed
	{
	public:
		GraphicsGaleObject(const std::string& filename);
		~GraphicsGaleObject();

		//void* getGaleFileHandle() { return m_galeFileHandle; }

		HBITMAP getBitmap(LONG frameNo, LONG layerNo) const;
		DWORD getFrameCount() const;
		DWORD getLayerCount(LONG frameNo) const;

		LONG getFrameInfo(LONG frameNo, LONG nID) const;
		LONG getFrameName(LONG frameNo, LPSTR pName, LONG len) const;
		HPALETTE getPalette(LONG frameNo) const;

	private:
		void*							m_galeFileHandle = NULL;
		unsigned int					m_numberOfFrames = 1;
		BITMAP							m_bitmap;
	};
}