namespace BuildMaster
{
    class BuildAction : IAction
    {
        public string Name => "build";

        public static BuildAction Create() { return new BuildAction(); }

        public void Perform(Config config)
        {
            Steps.RunAllTools(config);

            Utils.BenchmarkStep(NewSteps.BuildCode, config, "New Build Code");

            Steps.CopyToDailyFolder(config);
        }
    }
}
