using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.IO;

namespace SpriteMaster.ViewModels
{
    public class SpriteMasterData : ObservableObject
    {
        private string m_filePath;
        public string FilePath
        {
            get => m_filePath;
            set
            {
                SetProperty(ref m_filePath, value);
                Filename = Path.GetFileName(m_filePath);
            }
        }

        private string m_filename;
        public string Filename
        {
            get => m_filename;
            private set => SetProperty(ref m_filename, value);
        }

        internal bool Load(string filePath)
        {
            FilePath = filePath;

            return true;
        }

        internal bool Save(string filePath)
        {
            return true;
        }
    }
}