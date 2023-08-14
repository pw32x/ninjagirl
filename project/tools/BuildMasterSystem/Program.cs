using System;

namespace BuildMasterSystem
{
    class Program
    {
        static int Main(string[] args)
        {
            try
            {
                var buildMasterSystem = new BuildMasterSystem();
                buildMasterSystem.Run(args);
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
