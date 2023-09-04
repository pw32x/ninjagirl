namespace BuildMaster
{
    interface IAction
    {
        string Name { get; }
        void Perform(Config config);
    }
}
