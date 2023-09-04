using System;

namespace SoundMaster
{
    class Program
    {
        static int Main(string[] args)
        {
            try
            {
                var soundMaster = new SoundMaster();
                soundMaster.Run(args);
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
