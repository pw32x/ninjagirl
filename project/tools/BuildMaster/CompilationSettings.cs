using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Xml.Linq;

namespace BuildMaster
{
    class CompilationSettings
    {
        public CompilationSettings(string devkitSmsPath, string outFolder)
        {
            DevkitSmsPath = Utils.NormalizePath(devkitSmsPath);
            OutFolder = Utils.NormalizePath(outFolder);

            //IHX2SMS_Path = DevkitSmsPath + "/ihx2sms/Windows/ihx2sms.exe";
            IHX2SMS_Path = "ihx2sms.exe";

            SmsLib_BasePath = DevkitSmsPath + "/SMSlib";
            SmsLib_IncludePath = SmsLib_BasePath + "/src";
            SmsLib_LibraryPath = SmsLib_BasePath + "/SMSlib.lib";

            PeepRules_Path = SmsLib_BasePath + "/src/peep-rules.txt";
            CRT0_Path = DevkitSmsPath + "/crt0/crt0_sms.rel";

            PsgLib_BasePath = DevkitSmsPath + "/PSGlib/";
            PsgLib_IncludePath = PsgLib_BasePath + "/src";
            PsgLib_LibraryPath = PsgLib_BasePath + "/PSGlib.rel";
        }

        public List<string> Defines { get; } = new();

        public string DevkitSmsPath { get; }
        public string OutFolder { get; }

        public string IHX2SMS_Path { get; }
        public string SmsLib_BasePath { get; }
        public string SmsLib_IncludePath { get; }
        public string SmsLib_LibraryPath { get; }

        public string PeepRules_Path { get; }
        public string CRT0_Path { get; }

        public string PsgLib_BasePath { get; }
        public string PsgLib_IncludePath { get; }
        public string PsgLib_LibraryPath { get; }

        public string Compiler => "sdcc";
        public string BuildCompilerFlags(IEnumerable<string> includeFolders)
        {
            var sb = new StringBuilder();

            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag(Compiler);
            addFlag("-mz80");
            //addFlag("-M");

            addFlag("--peep-file " + PeepRules_Path);


            //addFlag("--max-allocs-per-node 100000");
            addFlag("--opt-code-speed");
            addFlag("--vc");

            addFlag("-I" + SmsLib_IncludePath);
            addFlag("-I" + PsgLib_IncludePath);

            foreach (var includeFolder in includeFolders)
            {
                addFlag("-I" + includeFolder);
            }

            foreach (var define in Defines)
            {
                addFlag(define);
            }

            return sb.ToString();
        }

        public string GetLinkerFlags(IEnumerable<uint> usedBankNumbers)
        {
            var sb = new StringBuilder();
            void addFlag(string flag) { sb.Append(flag); sb.Append(" "); };

            addFlag("-mz80");
            addFlag("--no-std-crt0");
            addFlag("--data-loc 0xC000");

            foreach (var bankNumber in usedBankNumbers)
            {
                addFlag("-Wl-b_BANK" + bankNumber + "=0x8000");
            }

            addFlag(CRT0_Path);
            addFlag(SmsLib_LibraryPath);
            addFlag(PsgLib_LibraryPath);

            return sb.ToString();
        }
    }

}
