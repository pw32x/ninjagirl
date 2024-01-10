namespace BuildMaster
{
    class CleanAction : IAction
    {
        public string Name => "clean";

        public static CleanAction Create() { return new CleanAction(); }

        public bool Perform(Config config)
        {
            NewSteps.CleanOutputFolder(config);
            NewSteps.CleanExportFolder(config);

            return true;
        }
    }
}
