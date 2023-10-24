namespace BuildMaster
{
    class BuildAction : IAction
    {
        public string Name => "build";

        public static BuildAction Create() { return new BuildAction(); }

        public void Perform(Config config)
        {
            Steps.RunAllTools(config);
            Steps.UpdateMakefileConfig(config);
            Steps.BuildCode(config);
            //Steps.RenameRom(config);
            Steps.CopyRom(config);
            Steps.CopyToDailyFolder(config);
        }
    }
}
