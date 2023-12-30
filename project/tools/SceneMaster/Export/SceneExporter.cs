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

        private static void ExportSource(Scene scene, string sceneName, string destinationFolder)
        {
            string destinationFilename = StringUtils.EnsureTrailingSlash(destinationFolder) + sceneName + ".c";


            var sb = new StringBuilder();

            sb.AppendLine("#include \"" + sceneName + ".h\"");
            sb.AppendLine();

            // export createinfos
            // export commands

            sb.AppendLine("const Scene " + sceneName + " = ");
            sb.AppendLine("{");
            sb.AppendLine("    " + sceneName + "_commands,");
            sb.AppendLine("};");

            File.WriteAllText(destinationFilename, sb.ToString());
        }
    }
}
