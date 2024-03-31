using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace tmx2c
{
    public struct GameObjectProperty
    {
        public enum GameObjectPropertyType
        {
            Int,
            String,
            StringAsVariableName,
            Pointer,
            Array,
            StaticArray
        }

        public GameObjectProperty(string name, string value, GameObjectPropertyType type)
        {
            Name = name;
            Value = value;
            Type = type;
        }

        public string Name { get; private set; }
        public string Value { get; private set; }
        public GameObjectPropertyType Type { get; private set; }
    }

    public class Map
    {
        public enum ExportMode
        {
            Map,
            StripMap
        }

        public string MapName { get; private set; }
        public string MapFilename { get; private set; }

        // get the data we want from the nodes

        string mDestinationSourceFile;
        string mDestinationHeaderFile;

        public int MapWidth { get; private set; }
        public int MapHeight { get; private set; }
        int mTileWidth;
        int mTileHeight;

        private XmlNode mTilemapLayerNode = null;
        private XmlNode mTerrainLayerNode = null;
        private XmlNode mPropertiesNode = null;
        private List<XmlNode> mTilesetNodes = new List<XmlNode>();
        private List<XmlNode> mObjectGroupNodes = new List<XmlNode>();

        const uint TILED_FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        const uint TILED_FLIPPED_VERTICALLY_FLAG = 0x40000000;
        const uint SegaMasterSystemFlippedHorizontallyFlag = (1 << 9);
        const uint SegaMasterSystemFlippedVerticallyFlag = (1 << 10);

        public List<string> ActiveLayers { get; private set; }

        public List<Tileset> Tilesets { get; }  = new List<Tileset>();

        void ParseTilesets(List<XmlNode> tilesetNodes, string sourceFolder)
        {
            List<Tileset> mUsedTilesets = new List<Tileset>();

            foreach (var tilesetNode in tilesetNodes)
            {
                if (mUsedTilesets.Count >= 4)
                    throw new Exception("map: " + MapName + " Hit the limit of tilesets to use in a map. ");

                string tilesetFilename = tilesetNode.Attributes["source"].Value;

                // is this a new tileset or a previously seen one?
                Tileset tileset = Tilesets.FirstOrDefault(t => String.Equals(t.TilesetFilename, tilesetFilename, StringComparison.OrdinalIgnoreCase));

                bool newTileset = (tileset == null);

                if (tileset == null)
                {
                    tileset = new Tileset();

                    tileset.TilesetFilename = tilesetFilename;
                    tileset.TilesetName = Path.GetFileNameWithoutExtension(tileset.TilesetFilename);

                    if (tileset.TilesetFilename.Contains("gameobjects.tsx") ||
                        tileset.TilesetFilename.Contains("tiletypes.tsx"))
                    {
                        tileset.IsEditorTileset = true;
                    }
                    else
                    {
                        tileset.TilesetIndex = (uint)mUsedTilesets.Count;
                        mUsedTilesets.Add(tileset);
                        tileset.LoadTileset(tilesetNode.Attributes["source"].Value, sourceFolder);
                    }
                }

                // create the TileIndexStartEnd object and update the previous one.
                var TileIndex = new Tileset.TileIndexStartEnd();

                TileIndex.StartIndex = uint.Parse(tilesetNode.Attributes["firstgid"].Value);

                if (Tilesets.Count > 0)
                    Tilesets.Last().TileIndexes.Last().EndIndex = TileIndex.StartIndex;

                tileset.TileIndexes.Add(TileIndex);


                if (newTileset)
                    Tilesets.Add(tileset);
            }

            /*
            // for each tileset, sort their tilesetindexes so that the one with the lower
            // start index goes first.
            foreach (var tileset in Tilesets)
            {
                tileset.TileIndexes = tileset.TileIndexes.OrderBy(t => t.StartIndex).ToList();
            }
            */

            // remap the tile ranges so that they leave out any stray gameobject indexes
            if (mUsedTilesets.Count > 0)
            {
                var firstTileset = mUsedTilesets[0];
                firstTileset.ExportStartIndex = firstTileset.TileIndexes.First().StartIndex;
                firstTileset.ExportEndIndex = firstTileset.TileIndexes.First().EndIndex;

                for (int loop = 1; loop < mUsedTilesets.Count; loop++)
                {
                    var tileset = mUsedTilesets[loop];
                    var previousTileset = mUsedTilesets[loop - 1];

                    tileset.ExportStartIndex = previousTileset.ExportEndIndex;

                    if (tileset.IsAnimated)
                    {
                        tileset.ExportEndIndex = tileset.ExportStartIndex + 8;//tileset.AnimationTileStride;
                    }
                    else
                    {
                        tileset.ExportEndIndex = tileset.ExportStartIndex +
                                                 (tileset.TileIndexes.First().EndIndex - tileset.TileIndexes.First().StartIndex);
                    }
                }
            }
        }

        public HashSet<string> UsedAnimations { get; }  = new HashSet<string>();

        void FindUsedAnimations(Dictionary<uint, string[]> defaultAssetsPerGameObject)
        {
            foreach (var usedObject in GameObjects)
            {
                var objectTemplate = mGameObjectTemplates[usedObject.TemplateFilename];

                string[] defaultAssets;

                defaultAssetsPerGameObject.TryGetValue(objectTemplate.Id, out defaultAssets);

                if (usedObject.IsMapSpawner)
                    continue;

                if (defaultAssets == null)
                {
                    //Console.WriteLine("No default assets found for objectId " + usedObject.ObjectId);
                    continue;
                }

                GameObjectProperty gameObjectProperty;
                if (usedObject.Properties.TryGetValue("assets", out gameObjectProperty))
                {
                    var overriddenAssets = gameObjectProperty.Value.Split(' ');

                    if (overriddenAssets.Count() != defaultAssets.Count())
                    {
                        Console.WriteLine("the object with id " + usedObject.ObjectId + " doesn't have the same number of overridden assets as deafult assets.");
                        continue;
                    }

                    foreach (var asset in overriddenAssets)
                    {
                        UsedAnimations.Add(Utils.StripSpriteSplitInstructions(asset));
                    }

                    if (usedObject.ObjectSpawnGameObjectTemplate != null)
                    {
                        var objectSpawnAssets = defaultAssetsPerGameObject[usedObject.ObjectSpawnGameObjectTemplate.Id];
                        foreach (var asset in objectSpawnAssets)
                        {
                            UsedAnimations.Add(Utils.StripSpriteSplitInstructions(asset));
                        }
                    }
                }
                else
                {
                    foreach (var asset in defaultAssets)
                    {
                        UsedAnimations.Add(Utils.StripSpriteSplitInstructions(asset));
                    }

                    if (usedObject.ObjectSpawnGameObjectTemplate != null)
                    {
                        var objectSpawnAssets = defaultAssetsPerGameObject[usedObject.ObjectSpawnGameObjectTemplate.Id];
                        foreach (var asset in objectSpawnAssets)
                        {
                            UsedAnimations.Add(Utils.StripSpriteSplitInstructions(asset));
                        }
                    }
                }
            }
        }


        private bool ObjectTemplatesAreNewer(string sourceFolder, DateTime sourceFileTime, DateTime headerFileTime)
        {
            foreach (var objectTemplateName in GameObjectTemplateNames)
            {
                DateTime objectTemplateFileTime = File.GetLastWriteTime(sourceFolder + objectTemplateName);

                if (objectTemplateFileTime > sourceFileTime || objectTemplateFileTime > headerFileTime)
                {
                    return true;
                }
            }

            return false;
        }

        public class GameObjectTempate
        {
            public int Width;
            public int Height;
            public uint Id { get; set; }
            public string ObjectType;
            public List<GameObjectProperty> DefaultProperties = new List<GameObjectProperty>();
        }

        public Dictionary<string, GameObjectTempate> mGameObjectTemplates = new Dictionary<string, GameObjectTempate>();
        Dictionary<string, List<GameObjectProperty>> propertiesPerGameObject = new Dictionary<string, List<GameObjectProperty>>();


        void LoadObjectTemplates(string sourceFolder, IList<string> sceneNames)
        {
            foreach (var gameObjectTemplateName in GameObjectTemplateNames)
            {
                var gameObjectTemplate = new GameObjectTempate();

                XmlDocument doc = new XmlDocument();
                doc.Load(sourceFolder + gameObjectTemplateName);

                XmlNode templateNode = doc.ChildNodes[1];

                XmlNode tilesetNode = null;
                XmlNode objectNode = null;

                foreach (XmlNode node in templateNode.ChildNodes)
                {
                    if (node.Name == "tileset")
                        tilesetNode = node;
                    else if (node.Name == "object")
                        objectNode = node;
                }

                gameObjectTemplate.Width = int.Parse(objectNode.Attributes["width"].Value);
                gameObjectTemplate.Height = int.Parse(objectNode.Attributes["height"].Value);

                var typeNode = objectNode.Attributes["type"];

                if (typeNode != null)
                    gameObjectTemplate.ObjectType = typeNode.Value;

                XmlNode gidNode = objectNode.Attributes.GetNamedItem("gid");

                if (gidNode != null)
                {
                    uint gameObjectId = uint.Parse(gidNode.Value);

                    if ((gameObjectId & TILED_FLIPPED_HORIZONTALLY_FLAG) > 0)
                        gameObjectId &= ~TILED_FLIPPED_HORIZONTALLY_FLAG;

                    if ((gameObjectId & TILED_FLIPPED_VERTICALLY_FLAG) > 0)
                        gameObjectId &= ~TILED_FLIPPED_VERTICALLY_FLAG;

                    gameObjectTemplate.Id = gameObjectId - 1; // Tiled numbering for objects in a scene starts at one
                }
                else
                {
                    gameObjectTemplate.Id = uint.MaxValue;
                }

                mGameObjectTemplates.Add(gameObjectTemplateName, gameObjectTemplate);

                // properties
                foreach (XmlNode objectChildNode in objectNode.ChildNodes)
                {
                    if (objectChildNode.Name == "properties")
                    {
                        foreach (XmlNode propertyNode in objectChildNode.ChildNodes)
                        {
                            string attributeName = propertyNode.Attributes["name"].Value;
                            string valueString = propertyNode.Attributes["value"].Value;

                            GameObjectProperty.GameObjectPropertyType propertyType = GameObjectProperty.GameObjectPropertyType.String;
                            var attributeTypeNode = propertyNode.Attributes["type"];
                            if (attributeTypeNode != null)
                            {
                                // we always assume int
                                propertyType = GameObjectProperty.GameObjectPropertyType.Int;
                            }

                            if (attributeName == "text")
                            {
                            }

                            // if the object is a door and the property is desinationScene, then switch
                            // the property from string (of the scene name) to an int index (of which
                            // scene in the allscenes array to use.
                            if (attributeName == "destinationScene" &&
                                propertyType == GameObjectProperty.GameObjectPropertyType.String &&
                                (gameObjectTemplate.ObjectType == "door" ||
                                gameObjectTemplate.ObjectType == "doorplant" ||
                                 gameObjectTemplate.ObjectType == "climbdoor" ||
                                 gameObjectTemplate.ObjectType == "climbdowndoor"))
                            {
                                attributeName = "destinationSceneIndex";
                                propertyType = GameObjectProperty.GameObjectPropertyType.Pointer;
                            }

                            // if the object is a aisquencebillboard and the property is aiSequence.
                                if (attributeName == "aiSequence" &&
                                propertyType == GameObjectProperty.GameObjectPropertyType.String)
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.Array;
                            }

                            // if the object is a aisquencebillboard and the property is aiSequence.
                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                (attributeName == "soundeffectid" ||
                                 attributeName == "musicid"))
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;
                            }

                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                attributeName == "gameObjectType")
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                attributeName = "createFunction";

                                if (valueString != "NULL")
                                    valueString = valueString + "Create";
                            }

                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                attributeName == "objectType")
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                if (String.IsNullOrEmpty(valueString))
                                    valueString = valueString + "TYPE_EFFECT";
                            }

                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                attributeName == "drawLayer") 
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                if (String.IsNullOrEmpty(valueString))
                                    valueString = "DRAWLAYER_MIDDLE";
                            }
                            
                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && attributeName.Contains("Array"))
                            {
                                propertyType = GameObjectProperty.GameObjectPropertyType.StaticArray;
                            }

                            if (propertyType == GameObjectProperty.GameObjectPropertyType.String && attributeName.Contains("essage"))
                            {
                                if (String.IsNullOrEmpty(valueString))
                                    valueString = "MESSAGE_NONE";

                                propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;
                            }

                            gameObjectTemplate.DefaultProperties.Add(new GameObjectProperty(attributeName, valueString, propertyType));
                        }
                    }
                }
            }
        }

        public void SetGameObjectTemplates(Dictionary<uint, string[]> defaultAssetsPerGameObject)
        {
            foreach (var gameObject in GameObjects)
            {
                gameObject.GameObjectTemplate = mGameObjectTemplates[gameObject.TemplateFilename];

                if (!String.IsNullOrEmpty(gameObject.ObjectTypeToSpawn))
                {
                    gameObject.ObjectSpawnGameObjectTemplate = mGameObjectTemplates[gameObject.ObjectToSpawnTemplateFilename];
                }

                string[] defaultAssets;
                defaultAssetsPerGameObject.TryGetValue(gameObject.GameObjectTemplate.Id, out defaultAssets);

                GameObjectProperty gameObjectProperty;
                if (gameObject.Properties.TryGetValue("assets", out gameObjectProperty))
                {
                    var overriddenAssets = gameObjectProperty.Value.Split(' ').ToList();

                    if (gameObject.ObjectSpawnGameObjectTemplate != null)
                    {
                        var objectSpawnAssets = defaultAssetsPerGameObject[gameObject.ObjectSpawnGameObjectTemplate.Id];
                        overriddenAssets.AddRange(objectSpawnAssets);
                    }

                    for (int loop = 0; loop < overriddenAssets.Count(); loop++)
                    {
                        overriddenAssets[loop] = Utils.StripSpriteSplitInstructions(overriddenAssets[loop]);
                    }

                    if (overriddenAssets.Count() != defaultAssets.Count() && !gameObject.IsObjectSpawner)
                    {
                        Console.WriteLine("the object with id " + gameObject.ObjectId + " using template \"" + gameObject.GameObjectTemplate.ObjectType + "\" doesn't have the same number of overridden assets as deafult assets.");
                        continue;
                    }

                    gameObject.UsedAssets = overriddenAssets.ToArray();
                }
                else if (defaultAssets != null)
                {
                    
                    var usedAssets = new List<string>();
                    usedAssets.AddRange(defaultAssets);

                    if (gameObject.ObjectSpawnGameObjectTemplate != null)
                    {
                        var objectSpawnAssets = defaultAssetsPerGameObject[gameObject.ObjectSpawnGameObjectTemplate.Id];
                        usedAssets.AddRange(objectSpawnAssets);
                    }

                    gameObject.UsedAssets = usedAssets.ToArray();
                }
            }
        }

        public class GameObject
        {
            public string TemplateFilename;
            public GameObjectTempate GameObjectTemplate;
            public string[] UsedAssets;
            public int X;
            public int Y;
            public Dictionary<string, GameObjectProperty> Properties = new Dictionary<string, GameObjectProperty>();
            public bool IsMapSpawner;
            public bool IsObjectSpawner;
            public string SpawnDataName;
            public string runtimeAnimationDataAddress;
            public int runtimeAnimationDataSize;
            public int ObjectId;
            public int LayerIndex;

            public string ObjectTypeToSpawn;
            public GameObjectTempate ObjectSpawnGameObjectTemplate;
            internal string ObjectToSpawnTemplateFilename;

            public int Width { get; internal set; }
            public int Height { get; internal set; }
        }


        public List<GameObject> GameObjects { get; } = new List<GameObject>();
        HashSet<string> GameObjectTemplateNames = new HashSet<string>();
        public GameObject MapSpawner { get; private set; }

        void ParseObjectGroups(List<XmlNode> objectGroupNodes, IList<string> sceneNames)
        {
            //objectgroupNodes.Add(objectGroup);

            int layerIndex = 0;

            foreach (XmlNode objectGroupNode in objectGroupNodes)
            {
                foreach (XmlNode objectNode in objectGroupNode.ChildNodes)
                {
                    var newObject = new GameObject();

                    newObject.X = (int)Math.Round(float.Parse(objectNode.Attributes["x"].Value));
                    newObject.Y = (int)Math.Round(float.Parse(objectNode.Attributes["y"].Value));

                    // objects without assets might have a size, like trigger areas.
                    if (objectNode.Attributes["width"] != null)
                        newObject.Width = (int)Math.Round(float.Parse(objectNode.Attributes["width"].Value));

                    if (objectNode.Attributes["height"] != null)
                        newObject.Height = (int)Math.Round(float.Parse(objectNode.Attributes["height"].Value));

                    XmlAttribute templateAttribute = objectNode.Attributes["template"];

                    if (templateAttribute == null)
                    {
                        Console.WriteLine("tmx2c -  Can't export object without template. Node: " + objectNode.OuterXml);
                        continue;
                    }

                    newObject.TemplateFilename = templateAttribute.Value;
                    newObject.LayerIndex = layerIndex;

                    GameObjectTemplateNames.Add(newObject.TemplateFilename);


                    // properties
                    foreach (XmlNode objectChildNode in objectNode.ChildNodes)
                    {
                        if (objectChildNode.Name == "properties")
                        {
                            foreach (XmlNode propertyNode in objectChildNode.ChildNodes)
                            {
                                string attributeName = propertyNode.Attributes["name"].Value;
                                string valueString = propertyNode.Attributes["value"].Value;

                                GameObjectProperty.GameObjectPropertyType propertyType = GameObjectProperty.GameObjectPropertyType.String;
                                var attributeTypeNode = propertyNode.Attributes["type"];
                                if (attributeTypeNode != null)
                                {
                                    // we always assume int
                                    propertyType = GameObjectProperty.GameObjectPropertyType.Int;
                                }

                                // if the object is a door and the property is desinationSene, then do this.
                                if (attributeName == "destinationScene" &&
                                    propertyType == GameObjectProperty.GameObjectPropertyType.String &&
                                    (Path.GetFileNameWithoutExtension(newObject.TemplateFilename) == "door" ||
                                    Path.GetFileNameWithoutExtension(newObject.TemplateFilename) == "doorplant" ||
                                     Path.GetFileNameWithoutExtension(newObject.TemplateFilename) == "climbdoor" ||
                                     Path.GetFileNameWithoutExtension(newObject.TemplateFilename) == "climbdowndoor"))
                                {
                                    attributeName = "destinationSceneIndex";
                                    propertyType = GameObjectProperty.GameObjectPropertyType.Pointer;
                                }

                                // if the object is a aisquencebillboard and the property is aiSequence.
                                if (attributeName == "aiSequence" &&
                                    propertyType == GameObjectProperty.GameObjectPropertyType.String)
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.Array;
                                }

                                // if the object is a aisquencebillboard and the property is aiSequence.
                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                    (attributeName == "soundeffectid" ||
                                     attributeName == "musicid"))
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;
                                }

                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                    attributeName == "gameObjectType")
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                    newObject.ObjectTypeToSpawn = valueString;
                                    newObject.ObjectToSpawnTemplateFilename = "../gameobjects/" + newObject.ObjectTypeToSpawn + ".tx";

                                    GameObjectTemplateNames.Add(newObject.ObjectToSpawnTemplateFilename);

                                    attributeName = "createFunction";

                                    if (valueString != "NULL")
                                        valueString = valueString + "Create"; 
                                }

                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                    attributeName == "objectType") 
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                    if (String.IsNullOrEmpty(valueString))
                                        valueString = valueString + "TYPE_EFFECT";
                                }

                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && 
                                    attributeName == "drawLayer") 
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;

                                    if (String.IsNullOrEmpty(valueString))
                                        valueString = "DRAWLAYER_MIDDLE";
                                }

                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && attributeName.Contains("Array"))
                                {
                                    propertyType = GameObjectProperty.GameObjectPropertyType.StaticArray;
                                }

                                if (propertyType == GameObjectProperty.GameObjectPropertyType.String && attributeName.Contains("essage"))
                                {
                                    if (String.IsNullOrEmpty(valueString))
                                        valueString = "MESSAGE_NONE";

                                    propertyType = GameObjectProperty.GameObjectPropertyType.StringAsVariableName;
                                }

                                newObject.Properties.Add(attributeName, new GameObjectProperty(attributeName, valueString, propertyType));
                            }
                        }
                    }

                    GameObjects.Add(newObject);

                    if (newObject.TemplateFilename.IndexOf("MapSpawner", StringComparison.OrdinalIgnoreCase) >= 0)
                    {
                        if (MapSpawner == null)
                        {
                            MapSpawner = newObject;
                            newObject.IsMapSpawner = true;
                        }
                        else
                        {
                            throw new Exception("Only one spawner per map supported.");
                        }
                    }

                    if (newObject.TemplateFilename.IndexOf("spawnObject", StringComparison.OrdinalIgnoreCase) >= 0)
                    {
                        newObject.IsObjectSpawner = true;
                        newObject.X += 16;
                        newObject.Y += 16;
                    }
                }

                layerIndex++;
            }
        }

        public Map(string mapFilename, 
                   Dictionary<uint, string[]> defaultAssetsPerGameObject)
        {
            if (String.IsNullOrEmpty(mapFilename))
                throw new Exception("Invalid path passed to Map");

            MapFilename = mapFilename;
            MapName = Path.GetFileNameWithoutExtension(mapFilename);
            string sourceFolder = Path.GetDirectoryName(mapFilename);

            if (!String.IsNullOrEmpty(sourceFolder) && !sourceFolder.EndsWith(Path.DirectorySeparatorChar.ToString()))
                sourceFolder += Path.DirectorySeparatorChar;

            XmlDocument doc = new XmlDocument();
            doc.Load(mapFilename);

            // find the nodes we're interested in.
            var mapNode = doc.ChildNodes[1];

            MapWidth = int.Parse(mapNode.Attributes["width"].Value);
            MapHeight = int.Parse(mapNode.Attributes["height"].Value);
            mTileWidth = int.Parse(mapNode.Attributes["tilewidth"].Value);
            mTileHeight = int.Parse(mapNode.Attributes["tileheight"].Value);

            if (mTileWidth != 16 && mTileHeight != 16)
                throw new Exception("tile size is not 16 x 16");

            for (int loop = 0; loop < mapNode.ChildNodes.Count; loop++)
            {
                XmlNode childNode = mapNode.ChildNodes[loop];

                switch (childNode.Name)
                {
                    case "properties":
                        mPropertiesNode = childNode;
                        break;
                    case "tileset":
                        mTilesetNodes.Add(childNode);
                        break;
                    case "layer":
                        {
                            var nameAttribute = childNode.Attributes["name"];

                            var dataNode = childNode.ChildNodes[0];

                            if (nameAttribute != null)
                            {
                                if (nameAttribute.Value.ToLower().Contains("terrain") || nameAttribute.Value.ToLower().Contains("collision"))
                                {
                                    if (mTerrainLayerNode == null)
                                        mTerrainLayerNode = dataNode;
                                    else
                                        Console.WriteLine("tmx2c -  Multiple terrain maps not supported. The layer " + nameAttribute.Value + " will be ignored.");
                                    break;
                                }
                            }

                            if (mTilemapLayerNode == null)
                            {
                                mTilemapLayerNode = dataNode;
                            }
                            else
                            {
                                Console.WriteLine("tmx2c -  Multiple tile maps not supported. Subsequent layers will be ignored.");
                            }
                        }
                        break;
                    case "objectgroup":
                        mObjectGroupNodes.Add(childNode);
                        break;
                }
            }

            ParseTilesets(mTilesetNodes, sourceFolder);
            //ParseObjectGroups(mObjectGroupNodes, sceneNames);

            // load the object templates we've encountered.
            //LoadObjectTemplates(sourceFolder, sceneNames);

            if (defaultAssetsPerGameObject != null)
            {
                SetGameObjectTemplates(defaultAssetsPerGameObject);

                // which animations used in object templates are we actually using?
                FindUsedAnimations(defaultAssetsPerGameObject);
            }
        }

        public bool NeedsUpdate(DateTime applicationTime, 
                                DateTime gameObjectsFileTime, 
                                string sourceFolder,
                                string destinationFolder)
        {
            mDestinationSourceFile = destinationFolder + Path.GetFileNameWithoutExtension(MapName) + ".c";
            mDestinationHeaderFile = destinationFolder + Path.GetFileNameWithoutExtension(MapName) + ".h";

            DateTime mapFileDateTime = File.GetLastWriteTime(MapFilename);

            DateTime destinationSourceFileTime = File.GetLastWriteTime(mDestinationSourceFile);
            DateTime destinationHeaderFileTime = File.GetLastWriteTime(mDestinationHeaderFile);

            if (applicationTime > destinationSourceFileTime || applicationTime > destinationHeaderFileTime ||
                mapFileDateTime > destinationSourceFileTime || mapFileDateTime > destinationHeaderFileTime ||
                gameObjectsFileTime > destinationSourceFileTime || gameObjectsFileTime > destinationHeaderFileTime ||
                ObjectTemplatesAreNewer(sourceFolder, destinationSourceFileTime, destinationHeaderFileTime))
            {
                return true;
            }

            foreach (var tileset in Tilesets)
            {
                DateTime tilesetTime = File.GetLastWriteTime(sourceFolder + tileset.TilesetName + ".tsx");

                if (tilesetTime > destinationSourceFileTime || tilesetTime > destinationHeaderFileTime)
                {
                    return true;
                }

                DateTime bitmapFileTime = File.GetLastWriteTime(sourceFolder + tileset.TilesetName + ".bmp");

                if (bitmapFileTime > destinationSourceFileTime || bitmapFileTime > destinationHeaderFileTime)
                {
                    return true;
                }
            }

            /*
            foreach (var usedAnimation in UsedAnimations)
            {
                DateTime animationTime = File.GetLastWriteTime("..\\gamedata\\GGAnimations\\" + usedAnimation + ".gal");

                if (animationTime > destinationSourceFileTime || animationTime > destinationHeaderFileTime)
                {
                    return true;
                }
            }
            */

            return false;
        }

        void ParseProperties(XmlNode properties)
        {
            for (int loop = 0; loop < properties.ChildNodes.Count; loop++)
            {
                XmlNode childNode = properties.ChildNodes[loop];

                if (childNode.Attributes["name"].Value == "activelayers")
                {
                    ActiveLayers = childNode.Attributes["value"].Value.Split().ToList();
                }
            }
        }

        public class Tile
        {
            public Tile()
            {
                Index = 0;
                HorizontalFlip = false;
                VerticalFlip = false;
                Tileset = null;
            }

            public uint Index;
            public bool HorizontalFlip;
            public bool VerticalFlip;
            public Tileset Tileset;
        }

        List<Tile> mTilemap = new List<Tile>();

        void FindTileSetAndIndex(List<Tileset> tilesets, Tile tile, uint tileIndex)
        {
            if (tileIndex == 0)
                return;

            foreach (var tileset in Tilesets)
            {
                foreach (var tilesetIndex in tileset.TileIndexes)
                {
                    if (tileIndex >= tilesetIndex.StartIndex && tileIndex < tilesetIndex.EndIndex && !tileset.IsEditorTileset)
                    {
                        tile.Tileset = tileset;
                        tile.Index = (tileIndex - tilesetIndex.StartIndex) + tileset.TileIndexes.First().StartIndex;
                        return;
                    }
                }
            }

            throw new Exception("Not supposed to be here. Was a game object accidentally used as a tile?");
        }

        void ParseTileMapLayer(XmlNode tilemapLayerNode)
        {
            List<uint> tileValues = tilemapLayerNode.ChildNodes[0].Value.Split(',').Select(uint.Parse).ToList();

            foreach (uint tileValue in tileValues)
            {
                var tile = new Tile();

                tile.HorizontalFlip = (tileValue & TILED_FLIPPED_HORIZONTALLY_FLAG) > 0;
                tile.VerticalFlip = (tileValue & TILED_FLIPPED_VERTICALLY_FLAG) > 0;

                uint tileIndex = tileValue;

                if (tile.HorizontalFlip)
                    tileIndex &= ~TILED_FLIPPED_HORIZONTALLY_FLAG;

                if (tile.VerticalFlip)
                    tileIndex &= ~TILED_FLIPPED_VERTICALLY_FLAG;

                FindTileSetAndIndex(Tilesets, tile, tileIndex);

                mTilemap.Add(tile);
            }
        }

        List<uint> mCollisionMap = new List<uint>();
        //internal int SpawnListCount;

        void ParseTerrainLayer(XmlNode collisionLayerNode)
        {
            var tileAttributeTileset = Tilesets.FirstOrDefault(t => t.TilesetName.ToLower().Contains("tiletypes"));

            if (tileAttributeTileset == null)
            {
                Console.WriteLine("No tile attribute tiles found for collision layer. Collision layer won't get exported.");
                return;
            }

            List<uint> tileCollisionValues = collisionLayerNode.ChildNodes[0].Value.Split(',').Select(uint.Parse).ToList();

            foreach (uint tileCollisionValue in tileCollisionValues)
            {
                uint tileIndex = tileCollisionValue;

                if ((tileCollisionValue & TILED_FLIPPED_HORIZONTALLY_FLAG) > 0)
                    tileIndex &= ~TILED_FLIPPED_HORIZONTALLY_FLAG;

                if ((tileCollisionValue & TILED_FLIPPED_VERTICALLY_FLAG) > 0)
                    tileIndex &= ~TILED_FLIPPED_VERTICALLY_FLAG;

                var tileIndexes = tileAttributeTileset.TileIndexes.First();

                if (tileIndex >= tileIndexes.StartIndex && tileIndex < tileIndexes.EndIndex)
                {
                    tileIndex -= tileIndexes.StartIndex;
                }
                else
                {
                    tileIndex = 0;
                }

                mCollisionMap.Add(tileIndex);
            }
        }

        public void ExportHeaderFile(string bank, ExportMode exportMode)
        {
            // Save to header file
            using (System.IO.StreamWriter headerFile = new System.IO.StreamWriter(mDestinationHeaderFile))
            {
                string headerBlock = MapName.ToUpper() + "_MAP_INCLUDE_H";

                headerFile.WriteLine("// this file was automatically generated by tmx2c. https://github.com/pw32x/tmx2c");
                headerFile.WriteLine("#ifndef " + headerBlock);
                headerFile.WriteLine("#define " + headerBlock);
                headerFile.WriteLine("");
                headerFile.WriteLine("#include \"map_types.h\"");
                headerFile.WriteLine("");

                switch (exportMode)
                {
                case ExportMode.Map:
                    headerFile.WriteLine("RESOURCE(" + bank + ") extern const Map const " + MapName + "_map;");
                break;
                case ExportMode.StripMap:
                    headerFile.WriteLine("RESOURCE(" + bank + ") extern const StripMap const " + MapName + "_map;");
                break;
                }

                
                

                headerFile.WriteLine("");
                headerFile.WriteLine("#endif");
            }
        }

        private void ExportMapArray(StringBuilder exported, string tilemapArrayName)
        {
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int counter = 0;
            int totalSize = MapWidth * MapHeight;

            exported.Append("// array of metatile indexes. use the metatile look up table to figure out which actual 8x8 tiles to use.\n");
            exported.Append("const unsigned short const " + tilemapArrayName + "[" + totalSize + "] = \n");
            exported.Append("{\n");
            exported.Append("    ");


            for (int loop = 0; loop < totalSize; loop++)
            {
                Tile tile = mTilemap[loop];

                ExportTile(exported, tile, loop);

                counter++;

                if (counter == MapWidth)
                {
                    exported.Append("\n    ");
                    counter = 0;
                }
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        private void ExportStripMapArray(StringBuilder exported, string stripmapArrayName)
        {
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int totalSize = MapWidth * MapHeight * 4;

            exported.Append("const unsigned short const " + stripmapArrayName + "[" + totalSize + "] = // " + (MapWidth * 2) + " x " + (MapHeight * 2) + "\n");
            exported.Append("{\n");
            exported.Append("    ");

            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            var tileset = usedTilesets.First();
            uint vdpTileOffset = 448 - tileset.NumTiles;

            for (int widthLoop = 0; widthLoop < MapWidth * 2; widthLoop++)
            {
                int metaTileRow = widthLoop & 1;

                for (int heightLoop = 0; heightLoop < MapHeight; heightLoop++)
                {
                    Tile tile = mTilemap[(widthLoop / 2) + (heightLoop * MapWidth)];

                    uint tileIndex = tile.Index;

                    if (tileIndex == 0)
                    {
                        exported.Append("0, 0, ");
                    }
                    else
                    {
                        tileIndex = (tileIndex - 1);

                        var tuple = tileset.MetaTiles[(int)tileIndex];

                        if (metaTileRow == 0)
                        {
                            exported.Append((tuple.Item1 + vdpTileOffset) + ", " + (tuple.Item3 + vdpTileOffset) + ", ");
                        }
                        else
                        {
                            exported.Append((tuple.Item2+ vdpTileOffset)  + ", " + (tuple.Item4 + vdpTileOffset) + ", ");
                        }
                    }
                }

                exported.Append("\n    ");
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        // this has to match the ones in the game engine
        const int TILE_EMPTY = 0;
        const int TILE_SOLID = 1;
        const int TILE_TOPSOLID = 2;
        const int TILE_CLIMB = 3;
        const int TILE_HURT = 4;
        const int TILE_SLOPE45RIGHT = 5;
        const int TILE_SLOPE45LEFT = 6;
        const int TILE_SLOPE30RIGHT1 = 7;
        const int TILE_SLOPE30RIGHT2 = 8;
        const int TILE_SLOPE30LEFT1 = 9;
        const int TILE_SLOPE30LEFT2 = 10;
        const int TILE_WATER = 11;

        private void ExportStripMapTerrain(StringBuilder exported, string terrainMapArrayName)
        {
            
            // unsigned short const ChooseShipScreen_map_mapstrips_data[728] = // 728
            exported.Append("\n");

            int totalSize = MapWidth * MapHeight;

            exported.Append("const unsigned char const " + terrainMapArrayName + "[" + totalSize + "] = // " + MapWidth + " x " + MapHeight + "\n");
            exported.Append("{\n");
            exported.Append("    ");

            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);
            var tileset = usedTilesets.First();

            for (int widthLoop = 0; widthLoop < MapWidth; widthLoop++)
            {
                int metaTileRow = widthLoop & 1;

                for (int heightLoop = 0; heightLoop < MapHeight; heightLoop++)
                {
                    int location = widthLoop + (heightLoop * MapWidth);
                    Tile tile = mTilemap[location];

                    uint tileAttribute = TILE_EMPTY;

                    uint tileIndex = tile.Index;

                    tileIndex -= tileset.TileIndexes.First().StartIndex - tileset.ExportStartIndex;

                    tileIndex -= tileset.ExportStartIndex;

                    if (tileIndex > 0)
                    {
                        // if we have a terrain layer, use the data from it.
                        // if not, use the default terrain from the tileset
                        if (mTerrainLayerNode != null)
                        {
                            tileAttribute = mCollisionMap[location];
                        }
                        else
                        {
                            // tile attribute
                            var tileAttributeString = "";

                            if (tileIndex < tileset.TileAttributes.Count())
                            {
                                tileAttributeString = tileset.TileAttributes[tileIndex];
                            }

                            switch (tileAttributeString)
                            {
                                case "solid": tileAttribute = TILE_SOLID; break;
                                case "topsolid": tileAttribute = TILE_TOPSOLID; break;
                                case "climb": tileAttribute = TILE_CLIMB; break;
                                case "hurt": tileAttribute = TILE_HURT; break;
                                case "slope45right": tileAttribute = TILE_SLOPE45RIGHT; break;
                                case "slope45left": tileAttribute = TILE_SLOPE45LEFT; break;
                                case "slope30right1": tileAttribute = TILE_SLOPE30RIGHT1; break;
                                case "slope30right2": tileAttribute = TILE_SLOPE30RIGHT2; break;
                                case "slope30left1": tileAttribute = TILE_SLOPE30LEFT1; break;
                                case "slope30left2": tileAttribute = TILE_SLOPE30LEFT2; break;
                                case "water": tileAttribute = TILE_WATER; break;
                            }
                        }
                    }

                    exported.Append(tileAttribute + ",");
                }

                exported.Append("\n    ");
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }



        private void ExportTile(StringBuilder exported, Tile tile, int mapLocationIndex)
        {
            uint tileAttribute = TILE_EMPTY;
            uint tileIndex = tile.Index;
            uint originalTileIndex = tileIndex;

            /*
            // Don't think the bit format supports flipping now.
            if (tile.HorizontalFlip)
                tileIndex |= GenesisFlippedHorizontallyFlag;

            if (tile.VerticalFlip)
                tileIndex |= GenesisFlippedVerticallyFlag;
                */

            var tileset = tile.Tileset;

            if (tileset == null)
            {
                tileIndex = 0; // leave tiles that come from the game object tileset as blank.
            }
            else
            {
                tileIndex -= tileset.TileIndexes.First().StartIndex - tileset.ExportStartIndex;

                tileIndex -= tileset.ExportStartIndex;

                // exported format of map values
                // tile_type     | blockmap_index | block_index
                // 1111            111              111111111
                // 0 - 15          0 - 7            0 - 511

                // tileset index
                uint tilesetIndex = (tileset.TilesetIndex << 9);

                // if we have a terrain layer, use the data from it.
                // if not, use the default terrain from the tileset
                if (mTerrainLayerNode != null)
                {
                    tileAttribute = mCollisionMap[mapLocationIndex];
                }
                else
                {
                    // tile attribute
                    var tileAttributeString = "";

                    if (tileIndex < tileset.TileAttributes.Count())
                    {
                        tileAttributeString = tileset.TileAttributes[tileIndex];
                    }

                    switch (tileAttributeString)
                    {
                        case "solid": tileAttribute = TILE_SOLID; break;
                        case "topsolid": tileAttribute = TILE_TOPSOLID; break;
                        case "climb": tileAttribute = TILE_CLIMB; break;
                        case "hurt": tileAttribute = TILE_HURT; break;
                        case "slope45right": tileAttribute = TILE_SLOPE45RIGHT; break;
                        case "slope45left": tileAttribute = TILE_SLOPE45LEFT; break;
                        case "slope30right1": tileAttribute = TILE_SLOPE30RIGHT1; break;
                        case "slope30right2": tileAttribute = TILE_SLOPE30RIGHT2; break;
                        case "slope30left1": tileAttribute = TILE_SLOPE30LEFT1; break;
                        case "slope30left2": tileAttribute = TILE_SLOPE30LEFT2; break;
                        case "water": tileAttribute = TILE_WATER; break;
                    }
                }

                tileIndex |= (tileAttribute << 12) | tilesetIndex;

                //tileIndex -= 1;
            }

            exported.Append(tileIndex + ",");
        }
        

        private void ExportTerrainMap(StringBuilder exported, string terrainMapArrayName)
        {
            if (string.IsNullOrEmpty(terrainMapArrayName))
                return;

            exported.Append("\n");

            int counter = 0;
            int totalSize = MapWidth * MapHeight;

            exported.Append("const unsigned short const " + terrainMapArrayName + "[" + totalSize + "] = \n");
            exported.Append("{\n");
            exported.Append("    ");

            for (int loop = 0; loop < totalSize; loop++)
            {
                uint tileIndex = mCollisionMap[loop];

                exported.Append(tileIndex + ",");

                counter++;

                if (counter == MapWidth)
                {
                    exported.Append("\n    ");
                    counter = 0;
                }
            }

            exported.Append("\n};\n");
            exported.Append("\n");
        }

        private void ExportTilesets(StringBuilder exported)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("\n");
            foreach (var tileset in usedTilesets)
            {
                exported.Append("extern const ResourceInfo ");
                exported.Append(tileset.TilesetName + "ResourceInfo;\n");
            }
            exported.Append("\n");
        }


        private void ExportTilesetArray(StringBuilder exported)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("\n");
            exported.Append("const ResourceInfo* " + MapName + "_tilesetResourceInfos[" + Tilesets.Count + "] = \n");
            exported.Append("{\n");

            foreach (var tileset in usedTilesets)
            {
                exported.Append("    &" + tileset.TilesetName + "ResourceInfo, // ");
                exported.Append(tileset.IsAnimated ? "AnimatedTileset" : "Tileset");
                exported.AppendLine();
            }

            exported.Append("};\n");
            exported.Append("\n");
        }

        private void ExportMapStruct(StringBuilder exported, string tilemapArrayName, string bank)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("RESOURCE(" + bank + ") const Map const " + MapName + "_map = \n");
            exported.Append("{\n");
            exported.AppendLine("    MAP_RESOURCE_TYPE,");
            exported.Append("    " + tilemapArrayName + ", // metatile index map data\n");
            //exported.Append("    " + tilemapArrayName + "_terrain, // terrain\n");
            exported.Append("    " + MapName + "_tilesetResourceInfos, // tilesets used in the map\n");
            exported.Append("    " + usedTilesets.Count() + ", // number of tilesets used by this map\n");
            exported.Append("    " + MapWidth + ", // metatile map width\n");
            exported.Append("    " + MapHeight + ", // metatile map height\n");
            exported.Append("};\n");
            exported.Append("\n");
        }

        private void ExportStripMapStruct(StringBuilder exported, string tilemapArrayName, string terrainMapArrayName, string bank)
        {
            var usedTilesets = Tilesets.Where(ts => ts.IsEditorTileset == false);

            exported.Append("RESOURCE(" + bank + ") const StripMap const " + MapName + "_map = \n");
            exported.Append("{\n");
            exported.AppendLine("    STRIP_MAP_RESOURCE_TYPE,");
            exported.Append("    " + tilemapArrayName + ", // strip map data\n");

            exported.Append("    &" + usedTilesets.First().TilesetName + "ResourceInfo, \n");

            exported.Append("    " + MapWidth * 2 + ", // map width\n");
            exported.Append("    " + MapHeight * 2 + ", // map height\n");

            exported.Append("    " + terrainMapArrayName + ", // terrain map data\n");
            exported.Append("    " + MapWidth + ", // terrain map width\n");
            exported.Append("    " + MapHeight + ", // terrain map height\n");

            exported.Append("};\n");
            exported.Append("\n");
        }


        public void ExportSourceFile(Dictionary<string, Tuple<int, int, int>> tileCounts, string bank, ExportMode exportMode)
        {
            StringBuilder exported = new StringBuilder();
            ExportInclude(exported);

            // uncomment to debug
            /*
            if (mTerrainLayerNode != null)
            {
                ExportTerrainMap(exported, MapName + "_terrainmap_array");
            }
            */

            //ExportBlocksets(exported);
            //ExportBlocksetSizes(exported, tileCounts);

            ExportMap(exported, bank, exportMode);

            //ExportStripBlockMap(exported);

            using (System.IO.StreamWriter sourceFile = new System.IO.StreamWriter(mDestinationSourceFile))
            {
                sourceFile.Write(exported.ToString());
            }
        }

        private void ExportBlocksetSizes(StringBuilder exported, Dictionary<string, Tuple<int, int, int>> tileCounts)
        {
            exported.Append("\n");
            exported.Append("const unsigned short const " + MapName + "_blockset_tile_offsets[" + Tilesets.Count + "] = \n");
            exported.Append("{\n");

            uint offset = 0;


            foreach (var tileset in Tilesets)
            {
                string tilesetName = Utils.ReplaceLastOccurrence(tileset.TilesetName, "_blocks", "_tileset");

                if (tilesetName == "gameobjects")
                    continue;

                exported.Append("    " + offset + ",\n");

                if (tileset.IsAnimated)
                    offset += tileset.NumTilesPerFrame;
                else
                    offset += (uint)tileCounts[tilesetName].Item1;
            }

            exported.Append("};\n");
            exported.Append("\n");

        }

        private void ExportBlocksets(StringBuilder exported)
        {
            foreach (var tileset in Tilesets)
            {

                if (tileset.TilesetName == "gameobjects")
                    continue;

                exported.Append("#include \"..\\blocksets\\" + tileset.TilesetName + "et.h\"\n");
            }

            exported.Append("\n");
            exported.Append("const Blockset* const " + MapName + "_blocksets[" + Tilesets.Count + "] = \n");
            exported.Append("{\n");

            foreach (var tileset in Tilesets)
            {
                if (tileset.TilesetName == "gameobjects")
                    continue;

                exported.Append("    &" + tileset.TilesetName + "et,\n");
            }

            exported.Append("};\n");
            exported.Append("\n");
        }

        private void ExportMap(StringBuilder exported, string bank, ExportMode exportMode)
        {
            ExportTilesets(exported);

            if (exportMode == ExportMode.Map)
            {
                ExportTilesetArray(exported);

                string mapArrayName = MapName + "_metatile_map";
                ExportMapArray(exported, mapArrayName);
                ExportMapStruct(exported, mapArrayName, bank);
            }
            else if (exportMode == ExportMode.StripMap)
            {
                ExportStripMap(exported, bank);
            }
        }

        private void ExportStripMap(StringBuilder exported, string bank)
        {
            string stripmapArrayName = MapName + "_strip_map";

            ExportStripMapArray(exported, stripmapArrayName);

            string terrainMapArrayName = MapName + "_terrain_map";
            ExportStripMapTerrain(exported, terrainMapArrayName);

            ExportStripMapStruct(exported, stripmapArrayName, terrainMapArrayName, bank);
        }



        private void ExportInclude(StringBuilder exported)
        {
            exported.Append("// this file was automatically generated by tmx2c. https://github.com/pw32x/tmx2c\n");
            exported.Append("#include \"" + MapName + ".h\"\n");
            exported.Append("#include \"resource_types.h\"\n");
        }

        public void Export(Dictionary<string, Tuple<int, int, int>> tileCounts, string bank, ExportMode exportMode)
        {
            if (mPropertiesNode != null)
                ParseProperties(mPropertiesNode);

            ParseTileMapLayer(mTilemapLayerNode);

            if (mTerrainLayerNode != null)
                ParseTerrainLayer(mTerrainLayerNode);

            ExportHeaderFile(bank, exportMode);
            ExportSourceFile(tileCounts, bank, exportMode);
        }
    }
}
