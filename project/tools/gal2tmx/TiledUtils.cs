using System.Collections.Generic;
using System.Text;

namespace gal2tmx
{
    class TiledUtils
    {
        public static void SaveTMX(string tmxFilename, string tsxFilename, int tileWidth, int tileHeight, BitmapTileMap tileMap)
        {
            StringBuilder stringBuilder = new StringBuilder();

            stringBuilder.Append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            stringBuilder.Append("<map version=\"1.2\" tiledversion=\"1.2.3\" orientation=\"orthogonal\" renderorder=\"right-down\" ");
            stringBuilder.Append("width=\"" + tileMap.Width + "\" height=\"" + tileMap.Height + "\" ");
            stringBuilder.Append("tilewidth=\"" + tileWidth + "\" tileheight=\"" + tileHeight + "\" ");
            stringBuilder.Append("infinite=\"0\" nextlayerid=\"3\" nextobjectid=\"1\">\n");
            stringBuilder.Append("<tileset firstgid=\"1\" source=\"" + tsxFilename + "\"/>\n");
            stringBuilder.Append(" <layer id=\"1\" name=\"Tile Layer 1\" width=\"" + tileMap.Width + "\" height=\"" + tileMap.Height + "\">\n");
            stringBuilder.Append("  <data encoding=\"csv\">\n");

            for (int loopy = 0; loopy < tileMap.Height; loopy++)
            {
                for (int loopx = 0; loopx < tileMap.Width; loopx++)
                {
                    int position = loopx + (loopy * tileMap.Width);

                    uint tileIndex = tileMap.Map[position];

                    stringBuilder.Append((tileIndex + 1).ToString());

                    if (position != (tileMap.Width * tileMap.Height) - 1)
                        stringBuilder.Append(", ");
                }

                stringBuilder.Append("\n");
            }


            stringBuilder.Append("  </data>\n");
            stringBuilder.Append(" </layer>\n");
            stringBuilder.Append("  <objectgroup id=\"2\" name=\"Object Layer 1\"/>\n");
            stringBuilder.Append("</map>\n");


            System.IO.StreamWriter file = new System.IO.StreamWriter(tmxFilename);
            file.WriteLine(stringBuilder.ToString());
            file.Close();
        }


        public const int TILE_EMPTY = 0;
        public const int TILE_SOLID = 1;
        public const int TILE_TOPSOLID = 2;
        public const int TILE_CLIMB = 3;
        public const int TILE_HURT = 4;
        public const int TILE_SLOPE45RIGHT = 5;
        public const int TILE_SLOPE45LEFT = 6;
        public const int TILE_SLOPE30RIGHT1 = 7;
        public const int TILE_SLOPE30RIGHT2 = 8;
        public const int TILE_SLOPE30LEFT1 = 9;
        public const int TILE_SLOPE30LEFT2 = 10;
        public const int TILE_WATER = 11;


        public static string TileAttributeToString(int tileAttribute)
        {
            switch (tileAttribute)
            {
                case TILE_SOLID: return "solid";
                case TILE_TOPSOLID: return "topsolid";
                case TILE_CLIMB: return "climb";
                case TILE_HURT: return "hurt";
                case TILE_SLOPE45RIGHT: return "slope45right";
                case TILE_SLOPE45LEFT: return "slope45left";
                case TILE_SLOPE30RIGHT1: return "slope30right1";
                case TILE_SLOPE30RIGHT2: return "slope30right2";
                case TILE_SLOPE30LEFT1: return "slope30left1";
                case TILE_SLOPE30LEFT2: return "slope30left2";
                case TILE_WATER: return "water";
            }

            return "";
        }

        public static void SaveTSX(string tsxFilename, 
                                   string tilesetBitmapName, 
                                   string tilesetName, 
                                   int bitmapWidth, 
                                   int bitmapHeight, 
                                   int tileWidth, 
                                   int tileHeight,
                                   bool isAnimated,
                                   int numtilesperframe,
                                   List<BitmapTile> tiles)
        {
            int tilecount = (bitmapWidth / tileWidth) * (bitmapHeight / tileHeight);

            

            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            stringBuilder.Append("<tileset name=\"" + tilesetName + "\" tilewidth=\"" + tileWidth + "\" tileheight=\"" + tileHeight + "\" tilecount=\"" + tilecount + "\">\n");
            if (isAnimated)
            {
                stringBuilder.Append(" <properties>\n");
                stringBuilder.Append("   <property name=\"animated\" type=\"int\" value=\"1\"/>\n");
                stringBuilder.Append("   <property name=\"numtilesperframe\" type=\"uint\" value=\"" + numtilesperframe + "\"/>\n");
                stringBuilder.Append(" </properties>\n");
            }
            stringBuilder.Append("<image source=\"" + tilesetBitmapName + "\" width=\"" + bitmapWidth + "\" height=\"" + bitmapHeight + "\" />\n");

            for (int loop = 0; loop < tilecount; loop++)
            {
                if (loop < tiles.Count)
                {
                    string tileAttribute = TileAttributeToString(tiles[loop].Attribute);

                    stringBuilder.Append("  <tile id=\"" + loop + "\">\n");

                    stringBuilder.Append("    <properties>\n");
                    stringBuilder.Append("      <property name = \"" + tileAttribute + "\" value = \"\" />\n");
                    stringBuilder.Append("    </properties>\n");

                    stringBuilder.Append("  </tile>\n");
                }
            }

            stringBuilder.Append("</tileset>");

            System.IO.StreamWriter file = new System.IO.StreamWriter(tsxFilename);
            file.WriteLine(stringBuilder.ToString());
            file.Close();
        }
    }
}