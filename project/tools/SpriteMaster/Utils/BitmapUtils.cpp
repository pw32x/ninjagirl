#include "..\stdafx.h"
#include "BitmapUtils.h"

namespace SpriteMaster
{

BYTE* BitmapUtils::CreateByteDataFromBitmap(BITMAP & bitmapInfo)
{
	const BYTE* imageData = (const BYTE*)bitmapInfo.bmBits;
	// Graphics Gale exports the bitmap upside down. Fugh.

	// convert to one pixel per byte format.
	BYTE* byteData = new BYTE[bitmapInfo.bmWidth * bitmapInfo.bmHeight];

	//printf("Graphics Gale: \n");

	for (int loopy = 0; loopy < bitmapInfo.bmHeight; loopy++)
	{
		for (int loopx = 0; loopx < (bitmapInfo.bmWidth / 2); loopx++)
		{
			BYTE byte = imageData[loopx + (((bitmapInfo.bmHeight - 1) - loopy) * (bitmapInfo.bmWidth / 2))];

			int bytex = loopx * 2;

			byteData[bytex + (loopy * bitmapInfo.bmWidth)] = (byte >> 4);
			byteData[(bytex + 1) + (loopy * bitmapInfo.bmWidth)] = byte & 0x0f;

			//printf("%02d, %02d, ", (byte >> 4), byte & 0x0f);
		}

		//printf("\n");
	}

	return byteData;
}

}