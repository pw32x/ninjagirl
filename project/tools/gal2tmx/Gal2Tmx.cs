using GraphicsGaleWrapper;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;

// -tiletypes <file.gal>
// - add export tile count limit checker "-maxtiles <number>"

namespace gal2tmx
{
    internal class Gal2Tmx
    {
        // per-file options
        private class JobSpec
        {
            public string SourceName { get; set; }
            public string SourcePath { get; set; }


            public string TilesetFilename { get; set; }
            public string TiledTilesetName { get; set; }
            public string TiledTilesetFilename { get; set; }
            public string TiledTilesetBitmapName { get; set; }
            public string TilemapDestinationPath { get; set; }
            public string TSXDestinationPath { get; set; }
            public string TiledTilesetBmpDestinationPath { get; set; }
            public string TilesetBmpDestinationPath { get; set; }

            public bool IsTilesetOnly { get; set; } = false;
            public bool IsTilesetAnimated { get; set; } = false;
            public bool IsBreakable { get; set; } = false;

            public bool ExportMap => !IsTilesetAnimated && !IsTilesetOnly;
        }

        // global options
        private string DestinationFolder { get; set; }
        private string TilesetDestinationFolder { get; set; }

        // optional flags
        private bool ForceOverwrite { get; set; } = false;

        private string TileTypesPath { get; set; }

        private string Bank { get; set; } = "";

        private const int MetatileWidth = 16;
        private const int MetatileHeight = 16;

        private  DateTime m_applicationTime;

        public int Run(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("No filename or path specified");
                return -1;
            }

            string appPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            m_applicationTime = System.IO.File.GetLastWriteTime(appPath);

            List<string> filenames = BuildFilenameList(args[0]);

            ProcessArguments(args);

            SplitBitmap tileTypesblocks = LoadTileTypes();

            foreach (var filename in filenames)
            {
                string sourceNameAndOptions = Path.GetFileNameWithoutExtension(filename);

                var jobSpec = new JobSpec();

                var tokens = sourceNameAndOptions.Split('.');

                jobSpec.SourceName = tokens[0];
                jobSpec.SourcePath = filename;

                foreach (var token in tokens)
                {
                    if (token == "animatedtileset")
                    {
                        jobSpec.IsTilesetAnimated = true;
                    }

                    if (token == "tileset")
                    {
                        jobSpec.IsTilesetOnly = true;
                    }

                    if (token == "breakable")
                    {
                        jobSpec.IsBreakable = true;
                    }
                }

                BuildExportPaths(jobSpec, DestinationFolder);

                // check if it needs updating. if it doesn't, skip.
                if (!NeedsUpdate(jobSpec, DestinationFolder))
                {
                    Console.WriteLine(filename + " is already up to date.");
                    continue;
                }

                Console.WriteLine("Exporting " + filename);

                ProcessJob(jobSpec, tileTypesblocks);
            }

            Console.WriteLine("Conversion complete.");

            return 0;
        }

        private bool NeedsUpdate(JobSpec jobSpec, string destinationFolder)
        {
            if (ForceOverwrite)
            {
                return true;
            }

            string tilesetHeaderName = jobSpec.TilesetFilename + ".h";
            string tilesetHeaderPath = TilesetDestinationFolder + tilesetHeaderName;
            string tilesetSourcePath = TilesetDestinationFolder + jobSpec.TilesetFilename + ".c";

            var destinationPaths = new List<string>() { tilesetHeaderPath,
                                                        tilesetSourcePath };

            if (jobSpec.ExportMap)
            {
                destinationPaths.Add(jobSpec.TiledTilesetBmpDestinationPath);
                destinationPaths.Add(jobSpec.TilemapDestinationPath);
                destinationPaths.Add(jobSpec.TSXDestinationPath);
            }

            // if any of the destination files are missing, it needs an update
            if (destinationPaths.Where(p => !File.Exists(p)).Any())
                return true;

            // check the destination file dates. 
            var destinationDateTimes = destinationPaths.Select(p => System.IO.File.GetLastWriteTime(p));

            // if the application is newer, then update
            if (destinationDateTimes.Where(t => t < m_applicationTime).Any()) 
                return true;

            // if the source is newer, then update
            DateTime sourceTime = System.IO.File.GetLastWriteTime(jobSpec.SourcePath);
            if (destinationDateTimes.Where(t => t < sourceTime).Any())
                return true;

            return false;
        }

        private void ProcessJob(JobSpec jobSpec, SplitBitmap tileTypesblocks)
        {
            var ggObject = new GaleObject(jobSpec.SourcePath);

            if (!GraphicsGaleObjectIsAcceptable(ggObject))
            {
                Console.WriteLine("Graphics gale file " + jobSpec.SourcePath + " doesn't have the format we want.");
                Console.WriteLine("Conversion skipped.");
                return;
            }

            var frame = ggObject.Frames[0];

            var ggFrameBitmap = frame.Layers[0].CreateBitmap();

            Bitmap ggTileTypesBitmap = null;

            var tiletypesLayer = frame.Layers.FirstOrDefault(l => l.Name.StartsWith("tiletypes"));

            if (tiletypesLayer != null)
            {
                ggTileTypesBitmap = tiletypesLayer.CreateBitmap();
            }

            // the ggbitmap is 32 bit. convert to 4bit
            var ggFrame4bppBitmap = BitmapUtils.Create4bppBitmap(ggFrameBitmap, ggObject.Palette);
            //fbppBitmap.Save(testResultsFolder + "4bppBitmap.bmp", ImageFormat.Bmp);

            // split the image into blocks.
            var tiledTilesetSplitBitmap = new SplitBitmap();
            tiledTilesetSplitBitmap.SplitLinearly(ggFrame4bppBitmap,
                                                  ggTileTypesBitmap,
                                                  tileTypesblocks,
                                                  MetatileWidth,
                                                  MetatileHeight,
                                                  true,
                                                  SplitBitmap.ExportFlipType.None);

            int rowWidth = jobSpec.IsTilesetAnimated ? 1 : Math.Min(tiledTilesetSplitBitmap.UniqueBitmapTiles.Count(), 10);

            Bitmap tiledTilesetBitmap = BitmapUtils.PackTilesetBitmap(tiledTilesetSplitBitmap.UniqueBitmapTiles,
                                                                      rowWidth,
                                                                      MetatileWidth,
                                                                      MetatileHeight);
            tiledTilesetBitmap.Save(jobSpec.TiledTilesetBmpDestinationPath, ImageFormat.Bmp);

            // split the blocks into a tileset
            int tileWidth = 8;
            int tileHeight = 8;

            var tilesetSplitBitmap = new SplitBitmap();
            tilesetSplitBitmap.SplitLinearly(tiledTilesetBitmap,
                                             null,
                                             null,
                                             tileWidth,
                                             tileHeight,
                                             true,
                                             SplitBitmap.ExportFlipType.SegaMasterSystem);

            // Save the tsx
            TiledUtils.SaveTSX(jobSpec.TSXDestinationPath,
                               jobSpec.TiledTilesetBitmapName,
                               jobSpec.TiledTilesetName,
                               tiledTilesetBitmap.Width,
                               tiledTilesetBitmap.Height,
                               MetatileWidth,
                               MetatileHeight,
                               jobSpec.IsTilesetAnimated,
                               tilesetSplitBitmap.UniqueBitmapTiles.Count,
                               tiledTilesetSplitBitmap.UniqueBitmapTiles);

            // save the tmx but not for animated or just tilesets
            if (jobSpec.ExportMap)
            {
                TiledUtils.SaveTMX(jobSpec.TilemapDestinationPath, 
                                   jobSpec.TiledTilesetFilename, 
                                   MetatileWidth, 
                                   MetatileHeight, 
                                   tiledTilesetSplitBitmap.BitmapTileMap);
            }

            Bitmap tilesetBitmap = null;

            tilesetBitmap = BitmapUtils.PackTilesetBitmap(tilesetSplitBitmap.UniqueBitmapTiles, 2, tileWidth, tileHeight);

            // uncomment to save the contents of the 8x8 tile set bitmap
            //tilesetBitmap.Save(TilesetBmpDestinationPath, ImageFormat.Bmp);

            TilesetUtils.ExportTileset(TilesetDestinationFolder,
                                       jobSpec.TilesetFilename,
                                       jobSpec.SourceName,
                                       tilesetSplitBitmap,
                                       Bank,
                                       jobSpec.IsTilesetAnimated,
                                       jobSpec.IsBreakable);
        }

        private SplitBitmap LoadTileTypes()
        {
            SplitBitmap tileTypesblocks = null;

            // load the tiletypes file, if given, and split into blocks.
            if (!String.IsNullOrEmpty(TileTypesPath))
            {
                var tileTypesGGObject = new GaleObject(TileTypesPath);
                var tileTypesBitmap = tileTypesGGObject.Frames[0].Layers[0].CreateBitmap();
                var tileTypes4bppBitmap = BitmapUtils.Create4bppBitmap(tileTypesBitmap, tileTypesGGObject.Palette);
                tileTypesblocks = new SplitBitmap();
                tileTypesblocks.SplitLinearly(tileTypes4bppBitmap,
                                              null,
                                              null,
                                              MetatileWidth,
                                              MetatileHeight,
                                              false,
                                              SplitBitmap.ExportFlipType.None);
            }

            return tileTypesblocks;
        }

        private bool GraphicsGaleObjectIsAcceptable(GaleObject ggObject)
        {
            if (ggObject.FrameCount == 0)
            {
                Console.WriteLine("Needs at least one frame.");
                return false;
            }

            if (ggObject.Frames[0].LayerCount == 0)
            {
                Console.WriteLine("Needs at least one layer.");
                return false;
            }

            var palette = ggObject.Palette;

            if (palette == null || palette.Entries.Length != 16)
            {
                Console.WriteLine("Only works on 4bpp images.");
                return false;
            }

            return true;
        }



        private void ProcessArguments(string[] args)
        {
            string sourcePath = args[0];

            int argStartIndex = 1;

            // figure out the destination folder
            if (args.Length == 1)
            {
                DestinationFolder = Path.GetDirectoryName(sourcePath);
            }
            else
            {
                string arg = args[1];

                if (arg.StartsWith("-"))
                {
                    DestinationFolder = Path.GetDirectoryName(sourcePath);
                }
                else
                {
                    DestinationFolder = arg;
                    argStartIndex++;
                }
            }

            if (!String.IsNullOrEmpty(DestinationFolder) && !DestinationFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                DestinationFolder += Path.DirectorySeparatorChar;

            if (!String.IsNullOrWhiteSpace(DestinationFolder) && !Directory.Exists(DestinationFolder))
            {
                Directory.CreateDirectory(DestinationFolder);
            }

            if (!String.IsNullOrWhiteSpace(TilesetDestinationFolder) && !Directory.Exists(TilesetDestinationFolder))
            {
                Directory.CreateDirectory(TilesetDestinationFolder);
            }

            // process the other flags
            for (int loop = argStartIndex; loop < args.Length; loop++)
            {
                string arg = args[loop];

                if (arg == "-y" || arg == "-o")
                    ForceOverwrite = true;

                if (arg.StartsWith("-bank"))
                {
                    Bank = arg.Substring("-".Length).ToUpper();
                }

                if (arg == "-tiletypes")
                {
                    if (loop + 1 < args.Length)
                    {
                        TileTypesPath = args[loop + 1];
                        if (TileTypesPath.StartsWith("-"))
                        {
                            throw new Exception("No valid value given for TileTypes .gal file");
                        }

                        if (!File.Exists(TileTypesPath))
                        {
                            throw new Exception("Tiletypes .gal file not found");
                        }
                    }
                }

                if (arg == "-tilesetdest")
                {
                    if (loop + 1 < args.Length)
                    {
                        TilesetDestinationFolder = args[loop + 1];
                        if (TilesetDestinationFolder.StartsWith("-"))
                        {
                            throw new Exception("No valid value given for tileset destination");
                        }

                        TilesetDestinationFolder += '\\';

                        if (!Directory.Exists(TilesetDestinationFolder))
                        {
                            Directory.CreateDirectory(TilesetDestinationFolder);
                        }
                    }
                }
            }
        }

        private List<string> BuildFilenameList(string sourcePath)
        {
            var filenames = new List<string>();

            if (Utils.IsFile(sourcePath))
            {
                if (!File.Exists(sourcePath))
                {
                    throw new Exception("File " + sourcePath + " not found");
                }

                filenames.Add(sourcePath);
            }
            else if (Utils.HasWildcard(sourcePath))
            {
                var filenamesFromWildcard = Utils.GetFilesFromWildcardPath(sourcePath);

                foreach (var filename in filenamesFromWildcard)
                {
                    filenames.Add(filename);
                }
            }
            else if (Directory.Exists(sourcePath))
            {
                DirectoryInfo directoryInfo = new DirectoryInfo(sourcePath);
                FileInfo[] files = directoryInfo.GetFiles();

                var filteredFiles = files.Where(file => string.Compare(file.Extension, ".gal", true) == 0);

                foreach (var filteredFile in filteredFiles)
                {
                    filenames.Add(filteredFile.FullName);
                }
            }

            return filenames;
        }

        private void BuildExportPaths(JobSpec jobSpec, string destinationFolder)
        {
            jobSpec.TiledTilesetName = jobSpec.SourceName + "_tileset";
            jobSpec.TiledTilesetBitmapName = jobSpec.TiledTilesetName + "_tsx.bmp";
            jobSpec.TiledTilesetFilename = jobSpec.TiledTilesetName + ".tsx";

            jobSpec.TilesetFilename = jobSpec.SourceName + "_tileset";

            // use the same destination folder for everything right now, but
            // leave the option to set different ones.
            jobSpec.TSXDestinationPath = destinationFolder + jobSpec.TiledTilesetFilename;
            jobSpec.TilemapDestinationPath = destinationFolder + jobSpec.SourceName + ".tmx";
            jobSpec.TiledTilesetBmpDestinationPath = destinationFolder + jobSpec.TiledTilesetBitmapName;
            jobSpec.TilesetBmpDestinationPath = destinationFolder + jobSpec.SourceName + "_tileset.bmp";
        }        
    }
}