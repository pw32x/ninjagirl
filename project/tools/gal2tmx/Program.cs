using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gal2tmx
{
    class Program
    {
        static int Main(string[] args)
        {
            var gal2Tmx = new Gal2Tmx();

            try
            {
                return gal2Tmx.Run(args);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return -1;
            }
        }
    }
}
