#pragma once
#include <string>

namespace SpriteMaster
{
	class FileUtils
	{
    public:
        static FILETIME getLastWriteTime(const std::string& path);
        static bool isNewer(FILETIME a, FILETIME b);
        static bool folderExists(const char* folderPath);

        static bool createFolder(const char* folderPath);
        static bool needsUpdate(const std::string& filename, 
                                const std::string& outputFolder, 
                                const std::string& outputFilename);
	};
}