namespace BuildMasterSystem
{
    interface IAction
    {
        string Name { get; }
        void Perform(Config config);
    }
}
