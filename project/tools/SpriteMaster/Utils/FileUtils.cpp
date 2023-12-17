#include "..\stdafx.h"
#include "FileUtils.h"

namespace SpriteMaster
{
    FILETIME FileUtils::getLastWriteTime(const std::string& path)
    {
        FILETIME lastWriteTime = { 0 };

        HANDLE hFile = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hFile != INVALID_HANDLE_VALUE)
        {
            if (GetFileTime(hFile, NULL, NULL, &lastWriteTime))
            {
                SYSTEMTIME st;
                FileTimeToSystemTime(&lastWriteTime, &st);
            }
        }

        CloseHandle(hFile);

        return lastWriteTime;
    }

    bool FileUtils::isNewer(FILETIME a, FILETIME b)
    {
        if (CompareFileTime(&a, &b) > 0)
            return true;

        return false;
    }

    bool FileUtils::folderExists(const char* folderPath)
    {
        DWORD dwAttrib = GetFileAttributesA(folderPath);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool FileUtils::createFolder(const char* folderPath)
    {
        if (!CreateDirectoryA(folderPath, NULL))
        {
            if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
                return false;
            }
        }

        return true;
    }

    bool FileUtils::needsUpdate(const std::string& filename, 
                                const std::string& outputFolder, 
                                const std::string& outputFilename)
    {
        // we need an update if the app or the filename is newer than the exported files.

        char filePath[MAX_PATH];
        DWORD size = GetModuleFileNameA(nullptr, filePath, MAX_PATH);

        FILETIME appTime = getLastWriteTime(filePath);
        FILETIME fileTime = getLastWriteTime(filename.c_str());

        if (!folderExists(outputFolder.c_str()))
            return true;

        std::string sourceFilename = outputFolder + outputFilename + ".c";
        FILETIME sourceTime = getLastWriteTime(sourceFilename.c_str());

        std::string headerFilename = outputFolder + outputFilename + ".h";
        FILETIME headerTime = getLastWriteTime(headerFilename.c_str());

        // if app or filename is newer than source and header, then update.    

        if (isNewer(appTime, sourceTime))
            return true;

        if (isNewer(appTime, headerTime))
            return true;

        if (isNewer(fileTime, sourceTime))
            return true;

        if (isNewer(fileTime, headerTime))
            return true;

        return false;
    }

    std::string FileUtils::ensureBackslash(const std::string& path) 
    {
        if (!path.empty() && path.back() != '\\') 
        {
            return path + '\\';
        } 
        else 
        {
            return path;
        }
    }

    void FileUtils::getFilenames(const std::string& fileOrPath, std::vector<std::string>& outFilenames)
    {
        // if ends with gal, then it's indivdual file.
        int findIndex = fileOrPath.rfind(".gal");
        if (findIndex != -1)
        {
            outFilenames.push_back(fileOrPath);
        }
        else // else assume it's a folder
        {
            std::string extension = ".gal";

            WIN32_FIND_DATAA findFileData;

            HANDLE hFind;

            std::string searchPattern = fileOrPath + "*.gal";
            hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);

            if (hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    std::string fileName = findFileData.cFileName;
                    outFilenames.push_back(fileOrPath + fileName);

                } while (FindNextFileA(hFind, &findFileData) != 0);

                FindClose(hFind);
            }
            else
            {
                printf("No animations found in %s.\n", fileOrPath.c_str());
                exit(-1);
            }
        }
    }
}