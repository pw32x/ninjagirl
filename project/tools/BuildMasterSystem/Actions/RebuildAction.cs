namespace BuildMasterSystem
{
    class RebuildAction : IAction
    {
        public string Name => "rebuild";

        public static RebuildAction Create() { return new RebuildAction(); }

        public void Perform(Config config)
        {
            var cleanAction = new CleanAction();
            cleanAction.Perform(config);

            var buildAction = new BuildAction();
            buildAction.Perform(config);
        }
    }
}
