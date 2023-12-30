using GraphicsGaleWrapper;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SceneMaster.Export
{
    internal class SceneExporter
    {
        public static void ExportScene(Scene scene, 
                                       string sceneName, 
                                       string destinationFolder)
        {
            ExportHeader(scene, sceneName, destinationFolder);
            ExportSource(scene, sceneName, destinationFolder);
        }

        private static void ExportHeader(Scene scene, string sceneName, string destinationFolder)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".h";

            var sb = new StringBuilder();

            sb.AppendLine("#ifndef " + sceneName.ToUpper() + "_SCENE_INCLUDE_H");
            sb.AppendLine("#define " + sceneName.ToUpper() + "_SCENE_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("extern const Scene " + sceneName + ";");
            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(destinationFilename, sb.ToString());
        }

        private class ExportedCreateInfo
        {
            public string Name;
            public int X { get; set; }
            public int Y { get; set; }
            public string TemplateName;
        }

        private static void ExportSource(Scene scene, string sceneName, string destinationFolder)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";

            var gameObjects = scene.GameObjects.OrderBy(g => g.X);

            var sb = new StringBuilder();

            sb.AppendLine("#include \"" + sceneName + ".h\"");
            sb.AppendLine("#include \"..\\..\\generated\\gameobjecttemplates\\gameobject_templates.h\"");
            sb.AppendLine();

            // export createinfos
            var createInfos = BuildCreateInfos(gameObjects, sceneName);
            ExportCreateInfos(sb, createInfos);

            ExportCommands(sb, gameObjects, sceneName, createInfos);

            sb.AppendLine("const Scene " + sceneName + " = ");
            sb.AppendLine("{");
            sb.AppendLine("    " + sceneName + "_commands,");
            sb.AppendLine("};");

            File.WriteAllText(destinationFilename, sb.ToString());
        }

        private static void ExportCommands(StringBuilder sb, 
                                           IEnumerable<GameObject> gameObjects, 
                                           string sceneName, 
                                           Dictionary<GameObject, ExportedCreateInfo> createInfos)
        {
            sb.AppendLine("const Command " + sceneName + "_commands[] = ");
            sb.AppendLine("{");

            ExportResourceCommands(sb, gameObjects);
            ExportGameObjectCommands(sb, gameObjects, createInfos);

            sb.AppendLine("    { 0, (CommandFunction)NULL, NULL}");

            sb.AppendLine("};");
            sb.AppendLine();
        }

        private static void ExportResourceCommands(StringBuilder sb, IEnumerable<GameObject> gameObjects)
        {
            string commandFunction = "ResourceManager_LoadResource";

            var resources = gameObjects.Select(g => g.GameObjectTemplate.ResourceInfo).Distinct();

            foreach (var resource in resources)
            {
                // { 0, (CommandFunction)RightScroller_Create, &background3_mapResourceInfo },
                sb.AppendLine("    { 0, (CommandFunction)" + commandFunction + ", &" + resource + " },");
            }
        }

        private static void ExportGameObjectCommands(StringBuilder sb, 
                                                     IEnumerable<GameObject> gameObjects,
                                                     Dictionary<GameObject, ExportedCreateInfo> createInfos)
        {
            foreach (var gameObject in gameObjects)
            {
                var createInfo = createInfos[gameObject];
                sb.AppendLine("    { " + gameObject.X + ", (CommandFunction)" + gameObject.GameObjectTemplate.CreateFunction + ", &" + createInfo.Name + " },");
            }
        }

        private static Dictionary<GameObject, ExportedCreateInfo> BuildCreateInfos(IEnumerable<GameObject> gameObjects, 
                                                                                   string sceneName)
        {
            Dictionary<GameObject, ExportedCreateInfo> createInfos = new();

            int counter = 0;
            foreach (var gameObject in gameObjects)
            {
                string createInfoName = sceneName + "_" + "createInfo" + counter;
                counter++;

                createInfos.Add(gameObject, new ExportedCreateInfo()
                {
                    X = (int)gameObject.X,
                    Y = (int)gameObject.Y,
                    TemplateName = Path.GetFileNameWithoutExtension(gameObject.GameObjectTemplate.FilePath) + "_template",
                    Name = createInfoName
                });
            }

            return createInfos;
        }

        private static void ExportCreateInfos(StringBuilder sb,
                                              Dictionary<GameObject, ExportedCreateInfo> createInfos)
        {
            foreach (var createInfo in createInfos.Values)
            {
                sb.Append("const CreateInfo " + createInfo.Name + " = { ");
                sb.Append(createInfo.X + ", " + createInfo.Y + ", &" + createInfo.TemplateName);
                sb.AppendLine("};");
            }
            sb.AppendLine();
        }
    }
}
