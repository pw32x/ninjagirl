namespace BuildMaster
{
    class BuildAction : IAction
    {
        public string Name => "build";

        public static BuildAction Create() { return new BuildAction(); }

        public bool Perform(Config config)
        {
            Steps.RunAllTools(config);

            NewSteps.GenerateResourceInfos(config);

            bool result = Utils.BenchmarkStep(NewSteps.BuildCode, config, "New Build Code");

            if (result)
            {
                Steps.CopyToDailyFolder(config);
            }

            return result;
        }
    }
}
