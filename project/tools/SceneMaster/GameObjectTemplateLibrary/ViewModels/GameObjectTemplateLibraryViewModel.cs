using CommunityToolkit.Mvvm.ComponentModel;
using SceneMaster.GameObjectTemplates.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SceneMaster.GameObjectTemplates.ViewModels
{
    public class GameObjectTemplateLibraryViewModel : ObservableObject
    {
        public GameObjectTemplateLibrary GameObjectTemplateLibrary { get; set; } = new();

        GameObjectTemplate m_selectedGameObjectTemplate;
        public GameObjectTemplate SelectedGameObjectTemplate { get => m_selectedGameObjectTemplate; set => SetProperty(ref m_selectedGameObjectTemplate, value); }
    }
}
