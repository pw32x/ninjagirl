using System;

namespace BuildMasterSystem
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var buildMasterSystem = new BuildMasterSystem();
                buildMasterSystem.Run(args);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
