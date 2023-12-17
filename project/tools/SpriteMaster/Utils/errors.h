#pragma once

namespace SpriteMaster
{
	enum Error
	{
		None,
		OpeningGraphicsGaleFileFailed,
		NoFramesInGraphicsGaleFile,
		BitmapHandleIsNull,
		NoBitmapFound,
		FormatNot4BitsPerPixel,
		ParsingArgumentsFailed,
		UnsupportedAnimationType,
		UnknownCommandLineFlag
	};

#define THROW_ERROR(code, message) \
{\
	std::error_code errorCode(code, std::system_category());\
	throw std::system_error(errorCode, message);\
}

#define THROW_IF_NULL(value, code, message)\
	if (value == nullptr)\
		THROW_ERROR(code, message)
}