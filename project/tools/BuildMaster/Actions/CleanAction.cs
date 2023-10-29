namespace BuildMaster
{
    class CleanAction : IAction
    {
        public string Name => "clean";

        public static CleanAction Create() { return new CleanAction(); }

        public void Perform(Config config)
        {
            Steps.CleanOutputFolder(config);
            NewSteps.CleanOutputFolder(config);
        }
    }
}
