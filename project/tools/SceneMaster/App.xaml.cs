using SceneMaster.EditorObjectLibrary.ViewModels;
using SceneMaster.Export;
using SceneMaster.GameObjectTemplates.Models;
using SceneMaster.Main;
using SceneMaster.Scenes.Models;
using SceneMaster.Scenes.ViewModels;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace SceneMaster
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            string[] args = Environment.GetCommandLineArgs();

            if (args.Length == 3)
            {
                // Run in command-line mode without UI
                RunInCommandLineMode(args);
            }
            else
            {
                // Run with UI
                RunWithUI();
            }
        }

        private void RunWithUI()
        {
            // Standard WPF application startup code
            var mainWindow = new MainWindow();
            mainWindow.Show();
        }

        private void RunInCommandLineMode(string[] args)
        {
            Console.WriteLine("*** RUNNING IN BATCH MODE");

            string sourceFolder = StringUtils.EnsureTrailingSlash(args[1]);
            string destinationFolder = StringUtils.EnsureTrailingSlash(args[2]);

            DirectoryInfo directoryInfo = new DirectoryInfo(sourceFolder);
            FileInfo[] fileInfos = directoryInfo.GetFiles();

            string[] fileExtensions = { ".scm" };
            var foundFileInfos = fileInfos.Where(file => fileExtensions.Contains(file.Extension, StringComparer.OrdinalIgnoreCase));

            if (!foundFileInfos.Any()) 
            {
                return;
            }

            if (!Directory.Exists(destinationFolder))
            {
                Directory.CreateDirectory(destinationFolder);
            }

            string appPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            var lastApplicationWriteTime = System.IO.File.GetLastWriteTime(appPath);

            //bool processedAtLeastOne = false;

            var settings = new Settings();
            settings.Load();

            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var dllDirectory = baseDirectory + @"thirdparty\GraphicsGale"; // ensures galefile.dll gets loaded.
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllDirectory);

            var editorObjectLibraryViewModel = new EditorObjectLibraryViewModel();
            editorObjectLibraryViewModel.LoadLibraries(settings);

            foreach (var fileInfo in foundFileInfos)
            {
                string sceneName = Path.GetFileNameWithoutExtension(fileInfo.Name).Replace(" ", "_");
                string destinationHeaderFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".h";
                string destinationSourceFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";

                // get source and destination file times
                DateTime sourceLastWriteTime = File.GetLastWriteTime(fileInfo.FullName);
                DateTime destinationHeaderLastWriteTime = File.GetLastWriteTime(destinationHeaderFilename);
                DateTime destinationSourceLastWriteTime = File.GetLastWriteTime(destinationSourceFilename);

                // only build if the source file is newer.
                // or the app is newer.
                if (destinationHeaderLastWriteTime > sourceLastWriteTime &&
                    destinationHeaderLastWriteTime > lastApplicationWriteTime &&
                    destinationSourceLastWriteTime > sourceLastWriteTime &&
                    destinationSourceLastWriteTime > lastApplicationWriteTime)
                {
                    Console.WriteLine(fileInfo.Name + " is already up to date.");
                    continue;
                }

                Console.WriteLine("Exporting " + fileInfo.Name);

                var root = XmlUtils.OpenXmlDocument(fileInfo.FullName, nameof(Scene));

                var scene = new Scene(/*null*/);
                scene.LoadFromXml(root, fileInfo.FullName, editorObjectLibraryViewModel);
                SceneExporter.ExportScene(scene, sceneName, destinationFolder, editorObjectLibraryViewModel.CommandLibrary);

                //processedAtLeastOne = true;
            }

            /*
            if (processedAtLeastOne || !File.Exists(destinationFolder + "gameobject_templates.h"))
            {
                Console.WriteLine("Exporting gameobject_templates.h");
                var templateNames = foundFileInfos.Select(fileInfo => Path.GetFileNameWithoutExtension(fileInfo.Name));

                //GameObjectTemplateExporter.ExportAllHeader(templateNames,
                //                                           destinationFolder);
            }
            */

            Shutdown();
        }
    }
}
