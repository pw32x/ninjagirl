<Scene>
  <TiledMapFilePath>..\generated\themes\background3.tmx</TiledMapFilePath>
  <EditorObjects>
    <GameObject Name="CommandRunner RightScroll" X="-84.53703703703701" Y="3.4768518518518445" GameObjectTemplateName="CommandRunner RightScroll" />
    <Command Name="RightScroller_Init" X="-83.68981481481494" Y="74.58796296296276" CommandValue="&amp;background3_mapResourceInfo" PreCommandData="" />
    <Command Name="Set Background Palette" X="-88.89351851851863" Y="-67.60185185185179" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <Command Name="Set Sprite Palette" X="-84.24537037037054" Y="143.59722222222243" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <GameObject Name="Ninja Girl" X="7.580644342384559" Y="112.3584730577314" GameObjectTemplateName="Ninja Girl" />
    <Command Name="MapManager_SetTilesetProperties_Command" X="-87.54399999999976" Y="221.6960000000002" CommandValue="&amp;setTilesetPropertiesParams " PreCommandData="#include &quot;client/tileset_functions.h&quot;&#xD;&#xA;const SetTilesetProperties_Params setTilesetPropertiesParams = &#xD;&#xA;{ &#xD;&#xA; 1, &#xD;&#xA; breakable_rock_tileset_TilesetFunction, &#xD;&#xA; &amp;rock_particle_template&#xD;&#xA;};" />
  </EditorObjects>
</Scene>