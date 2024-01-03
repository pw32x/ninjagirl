using PropertyTools.DataAnnotations;
using SceneMaster.EditorObjects.Models;

namespace SceneMaster.EditorObjectLibrary.Models
{
    public enum EditorObjectType
    {
        GameObject,
        Command
    }

    public abstract class EditorObjectInfo
    {
        public EditorObjectInfo(EditorObjectType editorObjectType)
        {
            EditorObjectType = editorObjectType;
        }

        [System.ComponentModel.ReadOnly(true)]
        public string Name { get; set; }

        [Browsable(false)]
        public bool IsEditorVisible { get; protected set; }

        [System.ComponentModel.ReadOnly(true)]
        [SelectorStyle(SelectorStyle.ComboBox)]
        public EditorObjectType EditorObjectType { get; }

        // editor properties
        [Browsable(false)]
        public Visual Visual { get; } = new();

        [System.ComponentModel.ReadOnly(true)]
        public string ResourceInfo { get; set; }

        abstract internal EditorObject CreateEditorObject(int x, int y);
    }
}
