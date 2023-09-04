using System;

namespace BuildMaster
{
    class Program
    {
        static int Main(string[] args)
        {
            try
            {
                var buildMaster = new BuildMaster();
                buildMaster.Run(args);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return -1;
            }

            return 0;
        }
    }
}
