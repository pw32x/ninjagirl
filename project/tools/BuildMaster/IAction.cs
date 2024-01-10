namespace BuildMaster
{
    interface IAction
    {
        string Name { get; }
        bool Perform(Config config);
    }
}
