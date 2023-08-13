namespace BuildMasterSystem
{
    class RebuildAction : IAction
    {
        public string Name => "rebuild";

        public static RebuildAction Create() { return new RebuildAction(); }

        public void Perform(Config config)
        {
            // This app calls powershell, which calls wsl. Yeah, not great probably.
            string powerShellCommand = "powershell.exe /c C:\\Windows\\System32\\wsl.exe make clean -f build/Makefile ";
            Utils.RunCommandLine(powerShellCommand, config.WorkingDirectory);

            powerShellCommand = "powershell.exe /c C:\\Windows\\System32\\wsl.exe make -f build/Makefile ";
            Utils.RunCommandLine(powerShellCommand, config.WorkingDirectory);
        }
    }
}
