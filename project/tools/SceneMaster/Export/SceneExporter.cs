using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

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



        private static Dictionary<EditorObject, ExportedCommandData> BuildExportCommandDatas(IEnumerable<EditorObject> editorObjects, 
                                                                                             string sceneName)
        {
            Dictionary<EditorObject, ExportedCommandData> exportedCommandDatas = new();

            int exportCounter = 0;
            foreach (var editorObject in editorObjects)
            {
                var exportedCommandData = editorObject.BuildExportCommandData(sceneName, exportCounter);
                exportCounter++;

                exportedCommandDatas.Add(editorObject, exportedCommandData);
            }

            return exportedCommandDatas;
        }

        private static void ExportCommandDatas(StringBuilder sb,
                                              Dictionary<EditorObject, ExportedCommandData> exportedCommandDatas,
                                              string sceneName)
        {
            // start with bootstrapper command runner
            string bootStrapper = "const CommandRunnerCreateInfo " + sceneName + "_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };";
            sb.AppendLine(bootStrapper);

            foreach (var exportedCommandData in exportedCommandDatas.Values.Where(e => !string.IsNullOrEmpty(e.ExportedCreateInfo)))
            {
                sb.Append(exportedCommandData.ExportedCreateInfo);
            }

            sb.AppendLine();
        }


        private static void ExportResourceCommands(StringBuilder sb, 
                                                   Scene scene, 
                                                   IEnumerable<EditorObject> editorObjects)
        {
            string commandFunction = "ResourceManager_LoadResource";

            var resources = editorObjects.Select(e => e.EditorObjectInfo.ResourceInfo).Where(e => !string.IsNullOrEmpty(e)).Distinct();

            // add the background
            if (!string.IsNullOrEmpty(scene.TiledMapFilename))
            {
                string backgroundResourceInfoName = Path.GetFileNameWithoutExtension(scene.TiledMapFilename) + "_mapResourceInfo";
                sb.AppendLine("    { 0, (CommandFunction)ResourceManager_LoadResource, &" + backgroundResourceInfoName + "},");
            }

            foreach (var resource in resources)
            {
                // { 0, (CommandFunction)RightScroller_Create, &background3_mapResourceInfo },
                sb.AppendLine("    { 0, (CommandFunction)" + commandFunction + ", &" + resource + " },");
            }
        }

        private static void ExportSceneCommands(StringBuilder sb, 
                                                IEnumerable<EditorObject> editorObjects,
                                                Dictionary<EditorObject, ExportedCommandData> exportedCommandDatas)
        {
            foreach (var editorObject in editorObjects)
            {
                if (exportedCommandDatas.TryGetValue(editorObject, out var exportedCommandData))
                {
                    string sceneCommand = editorObject.BuildSceneCommand(exportedCommandData);
                    sb.AppendLine("    " + sceneCommand);
                }
                else
                {
                    sb.AppendLine("    Error exporting object");
                }
            }
        }


        private static void ExportCommands(StringBuilder sb,
                                           Scene scene,
                                           IEnumerable<EditorObject> editorObjects, 
                                           string sceneName, 
                                           Dictionary<EditorObject, ExportedCommandData> exportedCommandDatas)
        {
            sb.AppendLine("const Command " + sceneName + "_commands[] = ");
            sb.AppendLine("{");

            // start with bootstrapper
            sb.AppendLine("    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&" + sceneName + "_createInfoBootstrapper },");

            ExportResourceCommands(sb, scene, editorObjects);
            ExportSceneCommands(sb, editorObjects, exportedCommandDatas);

            sb.AppendLine("    { 0, (CommandFunction)NULL, NULL}");

            sb.AppendLine("};");
            sb.AppendLine();
        }

        private static void ExportSource(Scene scene, string sceneName, string destinationFolder)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";

            var editorObjects = scene.EditorObjects.OrderBy(g => g.X);

            var sb = new StringBuilder();

            sb.AppendLine("#include \"" + sceneName + ".h\"");
            sb.AppendLine("#include \"client\\generated\\gameobjecttemplates\\gameobject_templates.h\"");

            sb.AppendLine("#include \"engine\\object_manager.h\"");
            sb.AppendLine("#include \"engine\\resource_manager.h\"");
            sb.AppendLine("#include \"client\\generated\\resource_infos.h\"");
            sb.AppendLine("#include \"engine\\createinfo_types.h\"");
            sb.AppendLine("#include \"engine\\commandrunner_runall.h\"");
            sb.AppendLine();

            // export exportedCommandDatas
            var exportedCommandDatas = BuildExportCommandDatas(editorObjects, sceneName);
            ExportCommandDatas(sb, exportedCommandDatas, sceneName);

            ExportCommands(sb, scene, editorObjects, sceneName, exportedCommandDatas);

            sb.AppendLine("const Scene " + sceneName + " = ");
            sb.AppendLine("{");
            sb.AppendLine("    " + sceneName + "_commands,");
            sb.AppendLine("};");

            File.WriteAllText(destinationFilename, sb.ToString());
        }



    }
}
