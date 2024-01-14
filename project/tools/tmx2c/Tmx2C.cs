using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace tmx2c
{

    class Tmx2CRunner
    {
        string [] mArgs;

        // todo:
        // if arg is filename, then export that one
        // if arg is folder, export everything inside
        // if arg ends with .tmx export them
        // destination folder


        private string SourceFolder;
        //private string GameObjectsLocation = "..\\gamedata\\gameobjects\\";
        private string TmxExtension = "tmx";

        private string DestinationFolder;
        private string Bank = "";

        public Tmx2CRunner(string [] args)
        {
            mArgs = args;
        }

        private void ParseArguments(string[] args)
        {
            if (args.Length == 0)
                throw new Exception("No arguments passed");

            SourceFolder = args[0];

            if (!String.IsNullOrEmpty(SourceFolder) && !SourceFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                SourceFolder += Path.DirectorySeparatorChar;

            if (args.Length > 1)
                DestinationFolder = args[1];

            if (!String.IsNullOrEmpty(DestinationFolder) && !DestinationFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                DestinationFolder += Path.DirectorySeparatorChar;

            if (args.Length > 2)
                Bank = args[2].Substring("-".Length).ToUpper();
        }

        public int Run()
        {

            // Get application stuff
            string applicationLocation = System.Reflection.Assembly.GetEntryAssembly().Location;
            DateTime applicationTime = File.GetLastWriteTime(applicationLocation);

            // Global game objects stuff
            //
            //string mGameObjectsFilename = GameObjectsLocation + "gameobjects.tsx";
            //DateTime gameObjectsFileTime = File.GetLastWriteTime(mGameObjectsFilename);
            //Dictionary<uint, string[]> assetsPerGameObject = LoadGameObjects(mGameObjectsFilename);

            //// Load tile counts of animations and tilesets
            ////
            //string tileCountsFilename = "exported\\TileCounts.txt";
            //Dictionary<string, Tuple<int, int, int>> tileCounts = LoadTileCountsFile(tileCountsFilename);
            //DateTime tileCountsFileTime = File.GetLastWriteTime(tileCountsFilename);

            //if (tileCounts == null)
            //{
            //    return -1;
            //}

            ParseArguments(mArgs);

            // Get all the maps files in the maps folder.
            var mapFilenames = Directory.GetFiles(SourceFolder, "*." + TmxExtension);
            //var mapNames = mapFilenames.Select(s => Path.GetFileNameWithoutExtension(s)).ToArray();

            /*
            // Check for scene files that are missing output files or are older than various things without
            // looking at the content of the map files they reference.
            HashSet<string> sceneNamesThatNeedUpdating = CheckForScenesThatNeedBasicUpdate(mapFiles, 
                                                                                           applicationTime, 
                                                                                           tileCountsFileTime);
            */

            /*
            // Get the list of maps and the various ways maps are used or referenced by scenes
            //
            var mapFilesAndDependencyTuple = GetMapNamesAndScenesAndDependencies(mapFiles);

            HashSet<string> mapNames = mapFilesAndDependencyTuple.Item1;
            Dictionary<string, HashSet<string>> mapToSceneDependencies = mapFilesAndDependencyTuple.Item2;
            Dictionary<string, Scene> scenes = mapFilesAndDependencyTuple.Item3;
            */

            // Load maps
            // 
            List<Map> maps = LoadMaps(mapFilenames, null/*assetsPerGameObject*/);

            // Check for any maps that need to be updated
            // 
            List<Map> mapsThatNeedUpdating = GetMapsThatNeedUpdating(maps, 
                                                                     applicationTime, 
                                                                     new DateTime() /*gameObjectsFileTime*/);

            /*
            // Scenes that use maps that need updating also need to be updated.
            foreach (var mapThatNeedsUpdating in mapsThatNeedUpdating)
            {
                var mappedSceneName = mapToSceneDependencies[mapThatNeedsUpdating.MapName];

                foreach (var sceneName in mappedSceneName)
                {
                    sceneNamesThatNeedUpdating.Add(sceneName);
                }
            }
            */

            if (mapsThatNeedUpdating.Count() > 0 && !Directory.Exists(DestinationFolder))
                Directory.CreateDirectory(DestinationFolder);

            if (mapsThatNeedUpdating.Count > 0)
            {
                ExportMaps(mapsThatNeedUpdating, DestinationFolder, null/*tileCounts*/, Bank);
            }
            else
            {
                Console.WriteLine("No maps need updating.");
            }

            /*
            ExportScenes(sceneNamesThatNeedUpdating, 
                         scenes, 
                         maps, 
                         ScenesExportLocation,
                         tileCounts);

            ExportBlocksets(mapsThatNeedUpdating, BlocksetExportLocation);

            if (sceneNamesThatNeedUpdating.Count > 0)
                ExportSceneHeader(mapNames);
            */

            return 0;
        }


        /*
        private void ExportSceneHeader(IEnumerable<string> sceneNames)
        {
            StringBuilder content = new StringBuilder();

            // All Scenes Header file
            content.AppendLine("#ifndef ALL_SCENES_INCLUDE_H");
            content.AppendLine("#define ALL_SCENES_INCLUDE_H");
            content.AppendLine("");
            content.AppendLine("#include \"..\\..\\Scene.h\"");

            foreach (var sceneName in sceneNames)
            {
                content.AppendLine("#include \"" + sceneName + "_scene.h\"");
            }

            content.AppendLine("");
            content.AppendLine("RESOURCE extern const Scene* const allScenes[" + sceneNames.Count() + "];");
            content.AppendLine("");
            content.AppendLine("#endif");

            string allScenesHeaderFilename = ScenesExportLocation + "AllScenes.h";

            using (System.IO.StreamWriter sourceFile = new System.IO.StreamWriter(allScenesHeaderFilename))
            {
                sourceFile.Write(content.ToString());
            }

            // All Scenes C file
            content.Clear();
            content.AppendLine("#include \"AllScenes.h\"");



            content.AppendLine("");
            content.AppendLine("const Scene* const allScenes[" + sceneNames.Count() + "] = ");
            content.AppendLine("{");

            foreach (var sceneName in sceneNames)
            {
                content.AppendLine("    &" + sceneName + "_scene,");
            }

            content.AppendLine("};");
            string allScenesSourceFilename = ScenesExportLocation + "AllScenes.c";

            using (System.IO.StreamWriter sourceFile = new System.IO.StreamWriter(allScenesSourceFilename))
            {
                sourceFile.Write(content.ToString());
            }
        }
        

        private void ExportScenes(HashSet<string> sceneNamesThatNeedUpdating, 
                                  Dictionary<string, Scene> scenes, 
                                  Dictionary<string, Map> maps,
                                  string scenesExportLocation,
                                  Dictionary<string, Tuple<int, int, int>> tileCounts)
        {
            if (!Directory.Exists(scenesExportLocation))
                Directory.CreateDirectory(scenesExportLocation);

            foreach (var sceneName in sceneNamesThatNeedUpdating)
            {
                if (scenes.ContainsKey(sceneName))
                {
                    var sceneExporter = new SceneExporter();

                    Console.WriteLine("tmx2c -  Exporting Scene " + sceneName);

                    sceneExporter.ExportScene(sceneName, scenes, maps, scenesExportLocation, tileCounts);
                }
                else
                {
                    Console.WriteLine("tmx2c -  The Scene " + sceneName + " will not be exported.");
                }
            }
        }

        private Dictionary<string, Tuple<int, int, int>> LoadTileCountsFile(string tileCountsFilename)
        {
            Dictionary<string, Tuple<int, int, int>> mTileCounts = new Dictionary<string, Tuple<int, int, int>>();

            try
            {
                var lines = File.ReadLines(tileCountsFilename).ToList();

                int count = 0;

                while (count < lines.Count)
                {
                    string animationName = lines[count++];
                    int tileCount = int.Parse(lines[count++]);
                    int width = int.Parse(lines[count++]);
                    int height = int.Parse(lines[count++]);

                    mTileCounts[animationName] = new Tuple<int, int, int>(tileCount, width, height);
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Tile counts file not found.");
                return null;
            }

            return mTileCounts;
        }
        */

        private void ExportMaps(List<Map> mapsToExport, 
                                string mapsExportLocation, 
                                Dictionary<string, Tuple<int, int, int>> tileCounts,
                                string bank)
        {
            foreach (var mapToExport in mapsToExport)
            {
                Console.WriteLine("Exporting Map: \"" + mapToExport.MapName + "\"");
                mapToExport.Export(tileCounts, bank);
            }
        }

        /*
        private void ExportBlocksets(List<Map> mapsToExport, string blocksetExportLocation)
        {

            Dictionary<string, Tileset> uniqueTilesets = new Dictionary<string, Tileset>();

            foreach (var mapToExport in mapsToExport)
            {
                foreach (var tileset in mapToExport.Tilesets)
                {
                    if (!uniqueTilesets.ContainsKey(tileset.TilesetName))
                        uniqueTilesets.Add(tileset.TilesetName, tileset);
                }
            }

            if (!Directory.Exists(blocksetExportLocation))
                Directory.CreateDirectory(blocksetExportLocation);

            foreach (var tileset in uniqueTilesets.Values)
            {
                if (tileset.TilesetName == "gameobjects")
                    continue;

                BlocksetExporter.ExportBlockAttributes(tileset, BlocksetExportLocation);
                BlocksetExporter.ExportBlockset(BlocksetExportLocation, tileset.TilesetName, tileset.TileAttributes.Length);
            }
        }


        Dictionary<uint, string[]> LoadGameObjects(string gameObjectsFilename)
        {
            Dictionary<uint, string[]> defaultAssetsPerGameObject = new Dictionary<uint, string[]>();

            XmlDocument doc = new XmlDocument();
            doc.Load(gameObjectsFilename);

            XmlNode tilesetNode = doc.ChildNodes[1];

            for (int tilesetNodeLoop = 0; tilesetNodeLoop < tilesetNode.ChildNodes.Count; tilesetNodeLoop++)
            {
                XmlNode tilesetChildNode = tilesetNode.ChildNodes[tilesetNodeLoop];

                if (tilesetChildNode.Name != "tile")
                    continue;

                XmlNode tileNode = tilesetChildNode;

                uint id = uint.Parse(tileNode.Attributes["id"].Value);

                for (int tileNodeLoop = 0; tileNodeLoop < tileNode.ChildNodes.Count; tileNodeLoop++)
                {
                    XmlNode tileChildNode = tileNode.ChildNodes[tileNodeLoop];

                    if (tileChildNode.Name == "properties")
                    {
                        XmlNode propertiesNode = tileChildNode;

                        for (int propertiesNodeLoop = 0; propertiesNodeLoop < propertiesNode.ChildNodes.Count; propertiesNodeLoop++)
                        {
                            XmlNode propertyNode = propertiesNode.ChildNodes[propertiesNodeLoop];

                            string attributeName = propertyNode.Attributes["name"].Value;

                            if (attributeName == "assets")
                            {
                                string assetsString = propertyNode.Attributes["value"].Value;

                                //assetsString = assetsString.Replace(".gal", "");

                                if (assetsString != "")
                                {
                                    var assets = assetsString.Split(' ');

                                    for (int loop = 0; loop < assets.Count(); loop++)
                                    {
                                        assets[loop] = Utils.StripSpriteSplitInstructions(assets[loop]);
                                    }

                                    defaultAssetsPerGameObject.Add(id, assets);
                                }
                           } 
                        }
                    }
                }
            }

            return defaultAssetsPerGameObject;
        }
        */

        private List<Map> LoadMaps(IEnumerable<string> mapFilenames, 
                                   Dictionary<uint, string[]> defaultAssetsPerGameObject)
        {
            var maps = new List<Map>();

            foreach (var mapFilename in mapFilenames)
            {
                maps.Add(new Map(mapFilename, defaultAssetsPerGameObject));
            }

            return maps;
        }

        private List<Map> GetMapsThatNeedUpdating(List<Map> maps, 
                                                  DateTime applicationTime, 
                                                  DateTime gameObjectsFileTime)
        {
            var mapsThatNeedUpdating = new List<Map>();

            foreach (var map in maps)
            {
                if (map.NeedsUpdate(applicationTime, gameObjectsFileTime, SourceFolder, DestinationFolder) ||
                    Debugger.IsAttached)
                {
                    mapsThatNeedUpdating.Add(map);
                }
            }

            return mapsThatNeedUpdating;
        }
        

        /*
        private HashSet<string> CheckForScenesThatNeedBasicUpdate(string[] sceneFiles, DateTime applicationTime, DateTime tileCountsFileTime)
        {
            var scenesThatNeedUpdating = new HashSet<string>();

            foreach (var sceneFile in sceneFiles)
            {
                if (SceneNeedsExport(sceneFile, applicationTime, tileCountsFileTime))
                {
                    scenesThatNeedUpdating.Add(Path.GetFileNameWithoutExtension(sceneFile));
                }
            }

            return scenesThatNeedUpdating;
        }

        private bool SceneNeedsExport(string sceneFile, DateTime applicationTime, DateTime tileCountsFileTime)
        {
            string sceneName = Path.GetFileNameWithoutExtension(sceneFile);
            DateTime sceneFileTime = File.GetLastWriteTime(sceneFile);

            // destination files don't exist
            // tool is newer than destination files 
            // destination files are older than source scene file
             
            string sceneSourceFilename = ScenesExportLocation + sceneName + "_scene.c";
            string sceneHeaderFilename = ScenesExportLocation + sceneName + "_scene.h";

            if (!File.Exists(sceneSourceFilename) || !File.Exists(sceneHeaderFilename))
            {
                return true;
            }

            DateTime sceneSourceFileTime = File.GetLastWriteTime(sceneSourceFilename);
            DateTime sceneHeaderFileTime = File.GetLastWriteTime(sceneHeaderFilename);

            if (sceneSourceFileTime < tileCountsFileTime || sceneHeaderFileTime < tileCountsFileTime)
            {
                return true;
            }

            if (sceneSourceFileTime < applicationTime || sceneHeaderFileTime < applicationTime)
            {
                return true;
            }

            if (sceneSourceFileTime < sceneFileTime || sceneHeaderFileTime < sceneFileTime)
            {
                return true;
            }

            return false;
        }
        */
    }
}
