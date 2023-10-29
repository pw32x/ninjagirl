namespace BuildMaster
{
    class BuildAction : IAction
    {
        public string Name => "build";

        public static BuildAction Create() { return new BuildAction(); }

        public void Perform(Config config)
        {
            Steps.RunAllTools(config);
            Utils.BenchmarkStep(Steps.UpdateMakefileConfig, config, "update make file");

            Utils.BenchmarkStep(Steps.BuildCode, config, "Old Build Code");


            Utils.BenchmarkStep(NewSteps.BuildCode, config, "New Build Code");

            //Steps.RenameRom(config);
            Steps.CopyRom(config);
            Steps.CopyToDailyFolder(config);
        }
    }
}
