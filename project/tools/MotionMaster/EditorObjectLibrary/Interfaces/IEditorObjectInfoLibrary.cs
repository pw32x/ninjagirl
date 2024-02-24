using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MotionMaster.EditorObjectLibrary.Interfaces
{
    public interface IEditorObjectInfoLibrary<T>
    {
        public T GetEditorObjectInfo(string editorObjectInfoName);
    }
}
