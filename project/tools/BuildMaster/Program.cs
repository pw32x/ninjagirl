using System;

namespace BuildMaster
{
    class Program
    {
        static int Main(string[] args)
        {
            bool result = false;

            try
            {
                var buildMaster = new BuildMaster();
                result = buildMaster.Run(args);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            int exitCode = result ? 0 : -1;

            if (result)
                Console.WriteLine("Run Successful");
            else
                Console.WriteLine("Run Failed. Exit Code: " + exitCode);

            return exitCode;
        }
    }
}
