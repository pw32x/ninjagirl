using TemplateMaster.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

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

            bool processedAtLeastOne = false;

            foreach (var fileInfo in foundFileInfos)
            {
                string templateName = Path.GetFileNameWithoutExtension(fileInfo.Name) + "_template";
                string sourceDestinationPath = DestinationFolder + templateName + ".c";
                string headerDestinationPath = DestinationFolder + templateName + ".h";

                // we'd need to load the game object template to know if we have custom
                // data to know if we need to export a header. I don't want to read the 
                // templates every time, so we'll just rely on just the source for now.

                // get source and destination file times
                DateTime sourceLastWriteTime = File.GetLastWriteTime(fileInfo.FullName);
                DateTime sourceDestinationLastWriteTime = File.GetLastWriteTime(sourceDestinationPath);
                //DateTime headerDestinationLastWriteTime = File.GetLastWriteTime(headerDestinationPath);

                // only build if the source file is newer.
                // or the app is newer.
                if (sourceDestinationLastWriteTime > sourceLastWriteTime &&
                    sourceDestinationLastWriteTime > lastApplicationWriteTime 
                    //&& headerDestinationLastWriteTime > sourceLastWriteTime 
                    //&& headerDestinationLastWriteTime > lastApplicationWriteTime
                    )
                {
                    Console.WriteLine(fileInfo.Name + " is already up to date.");
                    continue;
                }

                Console.WriteLine("Exporting " + fileInfo.Name);

                var gameObjectTemplate = new GameObjectTemplate();
                gameObjectTemplate.Load(fileInfo.FullName);

                GameObjectTemplateExporter.Export(gameObjectTemplate, 
                                                  templateName, 
                                                  sourceDestinationPath,
                                                  headerDestinationPath);

                processedAtLeastOne = true;
            }

            if (processedAtLeastOne || !File.Exists(DestinationFolder + "gameobject_templates.h"))
            {
                Console.WriteLine("Exporting gameobject_templates.h");
                var templateNames = foundFileInfos.Select(fileInfo => Path.GetFileNameWithoutExtension(fileInfo.Name));

                GameObjectTemplateExporter.ExportAllHeader(templateNames,
                                                           DestinationFolder);
            }
        }
    }
}
