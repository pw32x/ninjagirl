namespace BuildMaster
{
    class RebuildAction : IAction
    {
        public string Name => "rebuild";

        public static RebuildAction Create() { return new RebuildAction(); }

        public bool Perform(Config config)
        {
            var cleanAction = new CleanAction();
            if (!cleanAction.Perform(config))
                return false;

            var buildAction = new BuildAction();
            if (!buildAction.Perform(config))
                return false;

            return true;
        }
    }
}
