using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace BuildMaster
{
    class BuildMaster
    {
        Config m_config = new Config();

        IAction m_actionToPerform;
        Dictionary<string, IAction> m_actions = new Dictionary<string, IAction>();

        private void ProcessArgs(string[] args)
        {
            if (args.Length < 2)
                throw new Exception("BuildMaster config file and build action both need to be specified.");

            m_config.Load(args[0]);

            m_actionToPerform = GetActionByName(args[1]);

            List<string> defines = new();

            // check for additional parameters
            if (args.Length > 2)
            {
                for (int i = 2; i < args.Length; i++) 
                {
                    if (args[i].StartsWith("-D"))
                    {
                        m_config.CompilationSettings.Defines.Add(args[i]);
                   }
                }
            }
        }

        private IAction GetActionByName(string actionName)
        {
            if (!m_actions.ContainsKey(actionName))
                throw new Exception("No action by that name exists in the BuildMaster");

            return m_actions[actionName]; // calls the static Create function on the Action
        }

        internal bool Run(string[] args)
        {
            CollectActions();
            ProcessArgs(args);

            Console.WriteLine("Setting working directory: " + Path.GetFullPath(m_config.WorkingDirectory));
            Directory.SetCurrentDirectory(m_config.WorkingDirectory);

            Console.WriteLine("Running Action \"" + m_actionToPerform.Name + "\".");

            var startTime = DateTime.Now;

            bool result = m_actionToPerform.Perform(m_config);

            var elapsedTime = DateTime.Now - startTime;

            Console.WriteLine("Action \"" + m_actionToPerform.Name + "\" complete.");
            Console.WriteLine("Elapsed time: " + elapsedTime.Duration());

            return result;
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
