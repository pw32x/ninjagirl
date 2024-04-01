using SceneMaster.Commands.Models;
using SceneMaster.EditorObjects.CommandLibrary.ViewModels;
using SceneMaster.EditorObjects.Models;
using SceneMaster.Scenes.Models;
using SceneMaster.Utils;
using System;
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
                                       string destinationFolder,
                                       CommandLibrary commandLibrary)
        {
            ExportHeader(scene, sceneName, destinationFolder);
            ExportSource(scene, sceneName, destinationFolder, commandLibrary);
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

                if (exportedCommandData == null)
                    continue;

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

            var resources = editorObjects.SelectMany(e => e.EditorObjectInfo.ResourceInfos()).Where(e => !string.IsNullOrEmpty(e)).Distinct();

            foreach (var resource in resources)
            {
                // { 0, (CommandFunction)RightScroller_Create, &background3_mapResourceInfo },
                sb.AppendLine("    { 0, (CommandFunction)" + commandFunction + ", &" + resource + " },");
            }

            // add the background
            if (!string.IsNullOrEmpty(scene.TiledMapFilename))
            {
                string backgroundResourceInfoName = Path.GetFileNameWithoutExtension(scene.TiledMapFilename) + "_mapResourceInfo";
                sb.AppendLine("    { 0, (CommandFunction)ResourceManager_LoadResource, &" + backgroundResourceInfoName + "},");
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

        private static void ExportCommandHeaders(StringBuilder sb, CommandLibrary commandLibrary)
        {
            var headers = new HashSet<string>();

            foreach (var commandInfo in commandLibrary.CommandInfos.Values)
            {
                headers.Add(commandInfo.Filename);
            }

            foreach (var header in headers)
            {
                sb.AppendLine("#include \"" + header + "\"");
            }

            sb.AppendLine();
        }

        private static void ExportSource(Scene scene, 
                                         string sceneName, 
                                         string destinationFolder,
                                         CommandLibrary commandLibrary)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";

            var editorObjects = scene.EditorObjects.OrderBy(g => g.X);

            var sb = new StringBuilder();

            sb.AppendLine("#include \"" + sceneName + ".h\"");
            sb.AppendLine("#include \"client\\generated\\gameobjecttemplates\\gameobject_templates.h\"");
            sb.AppendLine("#include \"client\\generated\\resource_infos.h\"");

            sb.AppendLine("#include \"engine\\object_manager_create.h\"");
            sb.AppendLine("#include \"engine\\resource_manager.h\"");
            sb.AppendLine("#include \"engine\\createinfo_types.h\"");
            sb.AppendLine("#include \"engine\\commandrunner_runall.h\"");
            sb.AppendLine();

            ExportCommandHeaders(sb, commandLibrary);

            // export exportedCommandDatas
            var exportedCommandDatas = BuildExportCommandDatas(editorObjects, sceneName);
            ExportCommandDatas(sb, exportedCommandDatas, sceneName);

            ExportPreCommandData(sb, editorObjects.OfType<CommandObject>());

            ExportCommands(sb, scene, editorObjects, sceneName, exportedCommandDatas);

            sb.AppendLine("const Scene " + sceneName + " = ");
            sb.AppendLine("{");
            sb.AppendLine("    " + sceneName + "_commands,");
            sb.AppendLine("};");

            File.WriteAllText(destinationFilename, sb.ToString());
        }

        private static void ExportPreCommandData(StringBuilder sb, IEnumerable<CommandObject> commandObjectViewModels)
        {
            foreach (var commandObjectViewModel in commandObjectViewModels) 
            {
                if (string.IsNullOrEmpty(commandObjectViewModel.PreCommandData))
                    continue;

                sb.AppendLine(commandObjectViewModel.PreCommandData);
                sb.AppendLine();
            }
        }
    }
}
