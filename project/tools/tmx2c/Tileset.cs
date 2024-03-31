using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace tmx2c
{
    public class Tileset
    {
        public class TileIndexStartEnd
        {
            public TileIndexStartEnd()
            {
                StartIndex = uint.MinValue;
                EndIndex = uint.MaxValue;
            }

            public uint StartIndex;
            public uint EndIndex;
        }

        public Tileset()
        {
            ExportStartIndex = uint.MinValue;
            ExportEndIndex = uint.MaxValue;
        }

        public List<TileIndexStartEnd> TileIndexes = new List<TileIndexStartEnd>();

        public uint ExportStartIndex;
        public uint ExportEndIndex;

        public string TilesetFilename { get; set; }
        public bool IsEditorTileset;
        public string TilesetName { get; set; }

        public bool IsAnimated { get; set; }
        public bool IsBreakable { get; set; }
        public uint NumTilesPerFrame { get; set; }
        //public int AnimationTime { get; set; }
        //public uint AnimationTileStride { get; set; }
        //public int AnimationTileIndex { get; internal set; }
        //public int AnimationFramesCount { get; internal set; }
        public string Name { get; private set; }
        public uint TilesetIndex { get; internal set; } = uint.MinValue;
        public string[] TileAttributes { get; private set; }

        public uint NumTiles { get; private set; }
        public uint NumMetaTiles { get; private set; }

        public List<Tuple<uint, uint, uint, uint>> MetaTiles = new List<Tuple<uint, uint, uint, uint>>();

        internal void LoadTileset(string path, string sourceFolder)
        {
            LoadXml(path, sourceFolder);

            string infoPath = Path.GetDirectoryName(path) + "\\" + Path.GetFileNameWithoutExtension(path) + ".info";
            LoadInfo(infoPath, sourceFolder);
        }


        private void LoadXml(string path, string sourceFolder)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(sourceFolder + path);

            XmlNode tilesetNode = doc["tileset"];

            // init tile attributes
            int tileCount = int.Parse(tilesetNode.Attributes["tilecount"].Value);

            TileAttributes = new string[tileCount];
            for (int loop = 0; loop < tileCount; loop++)
            {
                TileAttributes[loop] = "empty";
            }

            for (int loop = 0; loop < tilesetNode.ChildNodes.Count; loop++)
            {
                XmlNode childNode = tilesetNode.ChildNodes[loop];

                if (childNode.Name == "properties")
                {
                    for (int propertiesNodeLoop = 0; propertiesNodeLoop < childNode.ChildNodes.Count; propertiesNodeLoop++)
                    {
                        XmlNode propertyNode = childNode.ChildNodes[propertiesNodeLoop];

                        string attributeName = propertyNode.Attributes["name"].Value;

                        switch (attributeName)
                        {
                            case "animated":
                                {
                                    int animated;
                                    if (int.TryParse(propertyNode.Attributes["value"].Value, out animated))
                                    {
                                        IsAnimated = (animated > 0);
                                    }

                                    break;
                                }
                            case "numtilesperframe":
                                {
                                    uint numtilesperframe;
                                    if (uint.TryParse(propertyNode.Attributes["value"].Value, out numtilesperframe))
                                    {
                                        NumTilesPerFrame = numtilesperframe;
                                    }

                                    break;
                                }
                            case "breakable":
                                {
                                    int breakable;
                                    if (int.TryParse(propertyNode.Attributes["value"].Value, out breakable))
                                    {
                                        IsBreakable = (breakable > 0);
                                    }

                                    break;
                                }
                            default:
                                throw new Exception("no attribute by that name exists: " + attributeName);
                        }
                    }
                }

                if (childNode.Name == "tile")
                {
                    int tileId = int.Parse(childNode.Attributes["id"].Value);

                    XmlNode propertiesNode = childNode.ChildNodes[0];
                    XmlNode propertyNode = propertiesNode.ChildNodes[0];

                    string name = propertyNode.Attributes["name"].Value;

                    TileAttributes[tileId] = name;
                }
            }
        }

        private void LoadInfo(string infoPath, string sourceFolder)
        {
            var lines = File.ReadAllLines(sourceFolder + infoPath);

            NumTiles = uint.Parse(lines[0]);
            NumMetaTiles = uint.Parse(lines[1]);

            for (uint loop = 2; loop < NumMetaTiles + 2; loop++) 
            {
                var elements = lines[loop].Split(',');

                var values = new Tuple<uint, uint, uint, uint>(uint.Parse(elements[0]), 
                                                               uint.Parse(elements[1]), 
                                                               uint.Parse(elements[2]), 
                                                               uint.Parse(elements[3]));

                MetaTiles.Add(values);
            }
        }
    }
}