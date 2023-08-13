namespace BuildMasterSystem
{
    class CleanAction : IAction
    {
        public string Name => "clean";

        public static CleanAction Create() { return new CleanAction(); }

        public void Perform(Config config)
        {
            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string powerShellCommand = "powershell.exe /c C:\\Windows\\System32\\wsl.exe make clean -f build/Makefile";
            Utils.RunCommandLine(powerShellCommand, config.WorkingDirectory);
        }
    }
}
