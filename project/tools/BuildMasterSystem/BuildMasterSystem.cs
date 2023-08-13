using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace BuildMasterSystem
{
    class BuildMasterSystem
    {
        Config m_config = new Config();

        IAction m_actionToPerform;
        Dictionary<string, IAction> m_actions = new Dictionary<string, IAction>();

        private void ProcessArgs(string[] args)
        {
            if (args.Length < 2)
                throw new Exception("BuildMasterSystem config file and build action both need to be specified.");

            m_config.Load(args[0]);

            m_actionToPerform = GetActionByName(args[1]);
        }

        private IAction GetActionByName(string actionName)
        {
            if (!m_actions.ContainsKey(actionName))
                throw new Exception("No action by that name exists in the BuildMasterSystem");

            return m_actions[actionName]; // calls the static Create function on the Action
        }

        internal void Run(string[] args)
        {
            CollectActions();
            ProcessArgs(args);

            Console.WriteLine("Running Action \"" + m_actionToPerform.Name + "\".");

            var startTime = DateTime.Now;

            m_actionToPerform.Perform(m_config);

            var elapsedTime = DateTime.Now - startTime;

            Console.WriteLine("Action \"" + m_actionToPerform.Name + "\" complete.");
            Console.WriteLine("Elapsed time: " + elapsedTime.Duration());
        }

        private void CollectActions()
        {
            var assembly = Assembly.GetExecutingAssembly();
            var derivedTypes = assembly.GetTypes().Where(type => typeof(IAction).IsAssignableFrom(type) && !type.IsInterface);

            foreach (var type in derivedTypes)
            {
                var instance = (IAction)Activator.CreateInstance(type);

                m_actions[instance.Name] = instance;
            }
        }
    }
}
