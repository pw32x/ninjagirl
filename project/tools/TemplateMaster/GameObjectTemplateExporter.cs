
using System.Text;

namespace TemplateMaster
{
    internal class GameObjectTemplateExporter
    {
        internal static void Export(GameObjectTemplate gameObjectTemplate, 
                                    string templateName, 
                                    string sourceDestinationPath,
                                    string headerDestinationPath)
        {
            ExportSource(gameObjectTemplate, templateName, sourceDestinationPath);
            ExportHeader(gameObjectTemplate, templateName, headerDestinationPath);
        }

        private static void ExportSource(GameObjectTemplate gameObjectTemplate, string templateName, string sourceDestinationPath)
        {
            var sb = new StringBuilder();
            sb.AppendLine("#include \"engine\\gameobject_template_types.h\"");
            sb.AppendLine("#include \"engine\\object_types.h\"");
            sb.AppendLine("#include \"engine\\createinfo_types.h\"");
            sb.AppendLine("#include \"client\\generated\\resource_infos.h\"");
            sb.AppendLine();

            // declare the extra resource infos used
            ExportExtraResourceInfos(gameObjectTemplate, templateName, sb);

            // forward declare the init function
            sb.AppendLine("GameObject* " + gameObjectTemplate.InitFunction + "(GameObject* object, const CreateInfo* createInfo);");
            sb.AppendLine();
            ExportGameTemplateStruct(gameObjectTemplate, templateName, sb);

            File.WriteAllText(sourceDestinationPath, sb.ToString());
        }

        private static void ExportHeader(GameObjectTemplate gameObjectTemplate, string templateName, string headerDestinationPath)
        {
            // we only export the custom objct struct for now.
            if (gameObjectTemplate.CustomDataFields.Count == 0) 
                return;

            var sb = new StringBuilder();

            sb.AppendLine("#ifndef " + templateName.ToUpper() + "_INCLUDE_H");
            sb.AppendLine("#define " + templateName.ToUpper() + "_INCLUDE_H");
            sb.AppendLine();
            sb.AppendLine("#include \"engine\\object_types.h\"");
            sb.AppendLine();

            ExportCustomObjectStruct(gameObjectTemplate, templateName, sb);

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(headerDestinationPath, sb.ToString());
        }

        private static void ExportCustomObjectStruct(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {

            // declare the template struct
            sb.AppendLine("typedef struct");
            sb.AppendLine("{");
            sb.AppendLine("    GAME_OBJECT_FIELDS;");

            foreach (var customDataField in gameObjectTemplate.CustomDataFields)
            {
                sb.AppendLine("    " + customDataField + ";");
            }

            sb.AppendLine("} "  + gameObjectTemplate.Name.Replace(" ", "") + "ObjectType;");
        }

        private static void ExportGameTemplateStruct(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {

            // declare the template struct
            sb.AppendLine("const GameObjectTemplate " + templateName + " = ");
            sb.AppendLine("{");
            AppendField(gameObjectTemplate.Health, sb, "0", "health");
            AppendField(gameObjectTemplate.Damage, sb, "0", "damage");
            AppendField(gameObjectTemplate.RectLeft, sb, "0", "rect left");
            AppendField(gameObjectTemplate.RectTop, sb, "0", "rect top");
            AppendField(gameObjectTemplate.RectRight, sb, "0", "rect right");
            AppendField(gameObjectTemplate.RectBottom, sb, "0", "rect bottom");
            AppendField("OBJECTTYPE_" + gameObjectTemplate.GameObjectType.ToUpper(), sb, "Error", "object type");

            string resourceInfo = "NULL";
            if (!string.IsNullOrEmpty(gameObjectTemplate.ResourceInfo))
                resourceInfo = "&" + gameObjectTemplate.ResourceInfo;

            AppendField(resourceInfo, sb, "Error", "resource info");

            string extraResourceInfos = "NULL";
            if (gameObjectTemplate.ExtraResourceInfos.Count > 0)
            {
                extraResourceInfos = templateName + "ExtraResourceInfos";
            }

            AppendField(extraResourceInfos, sb, "Error", "extra resource infos");

            AppendField(gameObjectTemplate.InitFunction, sb, "Error", "init function");

            sb.AppendLine("};");

            static void AppendField(string field, StringBuilder sb, string defaultValue, string description)
            {
                string fieldToUse = field;
                if (string.IsNullOrEmpty(field))
                    fieldToUse = defaultValue;

                sb.AppendLine("    " + fieldToUse + ", // " + description);
            }
        }

        private static void ExportExtraResourceInfos(GameObjectTemplate gameObjectTemplate, string templateName, StringBuilder sb)
        {
            if (gameObjectTemplate.ExtraResourceInfos.Count == 0)
                return;

            sb.AppendLine("ResourceInfo* " + templateName + "ExtraResourceInfos[] = ");
            sb.AppendLine("{");

            foreach (var resourceInfo in gameObjectTemplate.ExtraResourceInfos)
            {
                sb.AppendLine("    &" + resourceInfo + ",");
            }

            sb.AppendLine("};");

            sb.AppendLine();
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
                sb.AppendLine("extern const GameObjectTemplate " + templateName + "_template;");
            }

            sb.AppendLine();
            sb.AppendLine("#endif");

            File.WriteAllText(destinationFolder + "gameobject_templates.h", sb.ToString());
        }
    }
}