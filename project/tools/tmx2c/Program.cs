using System;

namespace tmx2c
{
    class Program
    {
        static int Main(string[] args)
        {
            try
            {
                var Scene2C = new Tmx2CRunner(args);

                return Scene2C.Run();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }
        }
    }
}
