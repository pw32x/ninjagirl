using TemplateMaster.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace TemplateMaster
{
    internal class TemplateMasterMain
    {
        private string SourceFolder { get; set; } = "";
        private string DestinationFolder { get; set; } = "";

        internal void Run(string[] args)
        {
            if (args.Length != 2)
                throw new Exception("Needs source and destination folders.");

            SourceFolder = StringUtils.EnsureTrailingSlash(args[0]);
            DestinationFolder = StringUtils.EnsureTrailingSlash(args[1]);

            DirectoryInfo directoryInfo = new DirectoryInfo(SourceFolder);
            FileInfo[] fileInfos = directoryInfo.GetFiles();

            string[] fileExtensions = { ".xml" };
            var foundFileInfos = fileInfos.Where(file => fileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

            if (!foundFileInfos.Any()) 
            {
                return;
            }

            if (!Directory.Exists(DestinationFolder))
            {
                Directory.CreateDirectory(DestinationFolder);
            }

            string appPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            var lastApplicationWriteTime = System.IO.File.GetLastWriteTime(appPath);

            foreach (var fileInfo in foundFileInfos)
            {
                string templateName = Path.GetFileNameWithoutExtension(fileInfo.Name) + "_template";
                string destinationPath = DestinationFolder + templateName + ".c";

                // get source and destination file times
                DateTime sourceLastWriteTime = File.GetLastWriteTime(fileInfo.FullName);
                DateTime destinationLastWriteTime = File.GetLastWriteTime(destinationPath);

                // only build if the source file is newer.
                // or the app is newer.
                if (destinationLastWriteTime > sourceLastWriteTime &&
                    destinationLastWriteTime > lastApplicationWriteTime)
                {
                    continue;
                }

                var gameObjectTemplate = new GameObjectTemplate();
                gameObjectTemplate.Load(fileInfo.FullName);

                GameObjectTemplateExporter.Export(gameObjectTemplate, 
                                                  templateName, 
                                                  destinationPath);
            }
        }
    }
}
