
using System.Text;

namespace TemplateMaster
{
    internal class GameObjectTemplateExporter
    {
        internal static void Export(GameObjectTemplate gameObjectTemplate, 
                                    string templateName, 
                                    string destinationPath)
        {
            var sb = new StringBuilder();

            sb.AppendLine("#include \"..\\..\\..\\engine\\gameobject_template_types.h\"");
            sb.AppendLine("#include \"..\\..\\..\\engine\\object_types.h\"");
            sb.AppendLine("#include \"..\\resource_infos.h\"");
            sb.AppendLine();

            sb.AppendLine("const GameObjectTemplate " + templateName + " = ");
            sb.AppendLine("{");
            AppendField(gameObjectTemplate.Health, sb, "0", "health");
            AppendField(gameObjectTemplate.Damage, sb, "0", "damage");
            AppendField(gameObjectTemplate.RectLeft, sb, "0", "rect left");
            AppendField(gameObjectTemplate.RectTop, sb, "0", "rect top");
            AppendField(gameObjectTemplate.RectRight, sb, "0", "rect right");
            AppendField(gameObjectTemplate.RectBottom, sb, "0", "rect bottom");
            AppendField("OBJECTTYPE_" + gameObjectTemplate.GameObjectType.ToUpper(), sb, "Error", "object type");
            AppendField("&" + gameObjectTemplate.ResourceInfo, sb, "Error", "resource info");
            sb.AppendLine("};");
            File.WriteAllText(destinationPath, sb.ToString());

            static void AppendField(string field, StringBuilder sb, string defaultValue, string description)
            {
                string fieldToUse = field;
                if (string.IsNullOrEmpty(field))
                    fieldToUse = defaultValue;
                    
                sb.AppendLine("    " + fieldToUse + ", // " + description);
            }
        }

        internal static void ExportAllHeader(IEnumerable<string> templateNames, 
                                             string destinationFolder)
        {
            var sb = new StringBuilder();

            sb.AppendLine("#ifndef GAMEOBJECT_TEMPLATES_INCLUDE_H");
            sb.AppendLine("#define GAMEOBJECT_TEMPLATES_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("#include \"..\\..\\..\\engine\\gameobject_template_types.h\"");
            sb.AppendLine();

            foreach (var templateName in templateNames)
            {
                sb.AppendLine("extern const GameObjectTemplate " + templateName + ";");
            }

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(destinationFolder + "gameobject_templates.h", sb.ToString());
        }
    }
}