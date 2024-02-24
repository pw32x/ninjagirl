using CommunityToolkit.Mvvm.ComponentModel;
using MotionMaster.Commands.Models;
using MotionMaster.EditorObjectLibrary.Models;
using MotionMaster.GameObjectTemplates.Models;
using MotionMaster.Main;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows.Data;

namespace MotionMaster.EditorObjectLibrary.ViewModels
{
    public class Group<T> : ObservableCollection<T>
    {
        public string Name { get; }

        public Group(string name)
        {
            Name = name;
        }
    }

    public class EditorObjectLibraryViewModel : ObservableObject
    {
        public GameObjectTemplateLibrary GameObjectTemplateLibrary { get; set; } = new();
        public CommandLibrary CommandLibrary { get; set; } = new();

        public List<EditorObjectInfo> EditorObjectInfos = new();

        public EditorObjectInfo m_selectedEditorObjectInfo;
        public EditorObjectInfo SelectedEditorObjectInfo { get => m_selectedEditorObjectInfo; set => SetProperty(ref m_selectedEditorObjectInfo, value); }

        public void LoadLibraries(Settings settings)
        {
            GameObjectTemplateLibrary.Load(settings.GameObjectTemplatesDirectory);
            CommandLibrary.Load(settings.CommandsSourceDirectory);

            EditorObjectInfos.AddRange(GameObjectTemplateLibrary.GameObjectTemplates.Values);
            EditorObjectInfos.AddRange(CommandLibrary.CommandInfos.Values);


            EditorObjectType[] allEditorObjectTypes = (EditorObjectType[])Enum.GetValues(typeof(EditorObjectType));
            foreach (var editorObjectType in allEditorObjectTypes)
            {
                var group = new Group<EditorObjectInfo>(editorObjectType.ToString());

                var editorObjectsOfType = EditorObjectInfos.Where(e => e.EditorObjectType == editorObjectType);

                foreach (var editorObject in editorObjectsOfType)
                    group.Add(editorObject);

                m_groupedEditorObjectInfos.Add(group);
            }

            EditorObjectInfosCollectionView = CollectionViewSource.GetDefaultView(EditorObjectInfos);
            EditorObjectInfosCollectionView.GroupDescriptions.Add(new PropertyGroupDescription(nameof(EditorObjectInfo.EditorObjectType)));
            EditorObjectInfosCollectionView.SortDescriptions.Add(new SortDescription(nameof(EditorObjectInfo.EditorObjectType), ListSortDirection.Ascending));
        }

        public ICollectionView  EditorObjectInfosCollectionView { get; private set; }

        private List<Group<EditorObjectInfo>> m_groupedEditorObjectInfos = new();
        public  List<Group<EditorObjectInfo>> GroupedEditorObjectInfos { get => m_groupedEditorObjectInfos; }
    }
}
