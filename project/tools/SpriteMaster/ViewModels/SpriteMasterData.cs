using CommunityToolkit.Mvvm.ComponentModel;
using System.IO;

namespace SpriteMaster.ViewModels
{
    public class SpriteMasterData : ObservableObject
    {
        private string m_galFilePath;
        public string GalFilePath
        {
            get => m_galFilePath;
            set
            {
                SetProperty(ref m_galFilePath, value);
                GalFilename = Path.GetFileName(m_galFilePath);
            }
        }

        private string m_galFilename;
        public string GalFilename
        {
            get => m_galFilename;
            private set => SetProperty(ref m_galFilename, value);
        }

        /*
        internal bool Load(string filePath)
        {
            return true;
        }

        internal bool Save(string filePath)
        {
            return true;
        }
        */
    }
}