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
            sb.AppendLine("#include \"scene_types.h\"");
            sb.AppendLine();
            sb.AppendLine("extern const Scene " + sceneName + ";");
            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(destinationFilename, sb.ToString());
        }

        private class ExportedCommandData
        {
            public string Name { get; set; }
            public string ExportedString { get; set; }
        }


        private static Dictionary<GameObject, ExportedCommandData> BuildExportCommandDatas(IEnumerable<GameObject> gameObjects, 
                                                                                           string sceneName)
        {
            Dictionary<GameObject, ExportedCommandData> exportedCommandDatas = new();

            int counter = 0;
            foreach (var gameObject in gameObjects)
            {
                switch (gameObject.GameObjectTemplate.EditorObjectType)
                {
                    case GameObjectTemplates.Models.EditorObjectType.CommandRunner:
                    {
                        // do nothing
                        break;
                    }
                    case GameObjectTemplates.Models.EditorObjectType.GameObject:
                    {
                        string createInfoName = sceneName + "_" + "createInfo" + counter;
                        counter++;

                        var exportedCommandData = new ExportedCommandData();
                        exportedCommandData.Name = createInfoName;

                        StringBuilder sb = new();
                        sb.Append("const CreateInfo " + createInfoName + " = { ");
                        int x = (int)(gameObject.X < 0 ? 0 : gameObject.X);
                        int y = (int)(gameObject.Y < 0 ? 0 : gameObject.Y);
                        string templateName = Path.GetFileNameWithoutExtension(gameObject.GameObjectTemplate.FilePath) + "_template";
                        sb.Append(x + ", " + y + ", &" + templateName);
                        sb.AppendLine("};");
                        exportedCommandData.ExportedString = sb.ToString();

                        exportedCommandDatas.Add(gameObject, exportedCommandData);
                        break;
                    }
                }


            }

            return exportedCommandDatas;
        }

        private static void ExportCommandDatas(StringBuilder sb,
                                              Dictionary<GameObject, ExportedCommandData> exportedCommandDatas)
        {
            foreach (var exportedCommandData in exportedCommandDatas.Values.Where(e => !string.IsNullOrEmpty(e.ExportedString)))
            {
                sb.Append(exportedCommandData.ExportedString);
            }

            sb.AppendLine();
        }


        private static void ExportResourceCommands(StringBuilder sb, IEnumerable<GameObject> gameObjects)
        {
            string commandFunction = "ResourceManager_LoadResource";

            var resources = gameObjects.Select(g => g.GameObjectTemplate.ResourceInfo).Where(g => !string.IsNullOrEmpty(g)).Distinct();

            foreach (var resource in resources)
            {
                // { 0, (CommandFunction)RightScroller_Create, &background3_mapResourceInfo },
                sb.AppendLine("    { 0, (CommandFunction)" + commandFunction + ", &" + resource + " },");
            }
        }

        private static void ExportGameObjectCommands(StringBuilder sb, 
                                                     IEnumerable<GameObject> gameObjects,
                                                     Dictionary<GameObject, ExportedCommandData> exportedCommandDatas)
        {
            foreach (var gameObject in gameObjects)
            {
                int x = (int)(gameObject.X < 0 ? 0 : gameObject.X);

                string finalExportedCommandData = "NULL";
                if (exportedCommandDatas.TryGetValue(gameObject, out var exportedCommandData))
                    finalExportedCommandData = "&" + exportedCommandData.Name;

                sb.AppendLine("    { " + x + ", (CommandFunction)" + gameObject.GameObjectTemplate.CreateFunction + ", " + finalExportedCommandData + " },");
            }
        }


        private static void ExportCommands(StringBuilder sb, 
                                           IEnumerable<GameObject> gameObjects, 
                                           string sceneName, 
                                           Dictionary<GameObject, ExportedCommandData> exportedCommandDatas)
        {
            sb.AppendLine("const Command " + sceneName + "_commands[] = ");
            sb.AppendLine("{");

            ExportResourceCommands(sb, gameObjects);
            ExportGameObjectCommands(sb, gameObjects, exportedCommandDatas);

            sb.AppendLine("    { 0, (CommandFunction)NULL, NULL}");

            sb.AppendLine("};");
            sb.AppendLine();
        }

        private static void ExportSource(Scene scene, string sceneName, string destinationFolder)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";

            var gameObjects = scene.GameObjects.OrderBy(g => g.X);

            var sb = new StringBuilder();

            sb.AppendLine("#include \"" + sceneName + ".h\"");
            sb.AppendLine("#include \"..\\..\\generated\\gameobjecttemplates\\gameobject_templates.h\"");
            sb.AppendLine();

            // export exportedCommandDatas
            var exportedCommandDatas = BuildExportCommandDatas(gameObjects, sceneName);
            ExportCommandDatas(sb, exportedCommandDatas);

            ExportCommands(sb, gameObjects, sceneName, exportedCommandDatas);

            sb.AppendLine("const Scene " + sceneName + " = ");
            sb.AppendLine("{");
            sb.AppendLine("    " + sceneName + "_commands,");
            sb.AppendLine("};");

            File.WriteAllText(destinationFilename, sb.ToString());
        }



    }
}
