using System.IO;

namespace SceneMaster.Utils
{
    class StringUtils
    {
        public static string EnsureTrailingSlash(string path)
        {
            // Use Path.Combine to ensure a trailing slash
            if (string.IsNullOrEmpty(path))
                return Path.DirectorySeparatorChar.ToString();

            if (!path.EndsWith(Path.DirectorySeparatorChar.ToString()))
                path += Path.DirectorySeparatorChar;

            return path;
        }
    }
}
