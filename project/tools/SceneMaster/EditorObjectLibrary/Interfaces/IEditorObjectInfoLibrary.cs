using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SceneMaster.EditorObjectLibrary.Interfaces
{
    public interface IEditorObjectInfoLibrary<T>
    {
        public T GetEditorObjectInfo(string editorObjectInfoName);
    }
}
