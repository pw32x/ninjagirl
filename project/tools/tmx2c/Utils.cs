using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tmx2c
{
    class Utils
    {
        public static string ReplaceLastOccurrence(string Source, string Find, string Replace)
        {
            int place = Source.LastIndexOf(Find);

            if (place == -1)
                return Source;

            string result = Source.Remove(place, Find.Length).Insert(place, Replace);
            return result;
        }

        public static string StripSpriteSplitInstructions(string galFilename)
        {
            int index = galFilename.IndexOf('.');

            return galFilename.Substring(0, index) + ".gal";
        }
    }
}
