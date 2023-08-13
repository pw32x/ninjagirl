namespace BuildMasterSystem
{
    class BuildAction : IAction
    {
        public string Name => "build";

        public static BuildAction Create() { return new BuildAction(); }

        public void Perform(Config config)
        {
            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string powerShellCommand = "powershell.exe /c C:\\Windows\\System32\\wsl.exe make -f build/Makefile";
            Utils.RunCommandLine(powerShellCommand, config.WorkingDirectory);
        }
    }
}
