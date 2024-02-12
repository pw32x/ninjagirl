<Scene>
  <TiledMapFilePath>..\maps\background3_test.tmx</TiledMapFilePath>
  <EditorObjects>
    <GameObject Name="CommandRunner RightScroll" X="-84.53703703703701" Y="3.4768518518518445" GameObjectTemplateName="CommandRunner RightScroll" />
    <Command Name="RightScroller_Init" X="-83.68981481481494" Y="74.58796296296276" CommandValue="&amp;background3_mapResourceInfo" PreCommandData="" />
    <Command Name="Set Background Palette" X="-88.89351851851863" Y="-67.60185185185179" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <Command Name="Set Sprite Palette" X="-84.24537037037054" Y="143.59722222222243" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <GameObject Name="Gun Girl" X="7.528232891724933" Y="-0.19714871666357436" GameObjectTemplateName="Gun Girl" />
    <Command Name="MapManager_SetTilesetProperties_Command" X="-87.54399999999976" Y="221.6960000000002" CommandValue="&amp;setTilesetPropertiesParams " PreCommandData="#include &quot;client/tileset_functions.h&quot;&#xD;&#xA;const SetTilesetProperties_Params setTilesetPropertiesParams = &#xD;&#xA;{ &#xD;&#xA; 1, &#xD;&#xA; breakable_rock_tileset_TilesetFunction, &#xD;&#xA; &amp;rock_particle_template&#xD;&#xA;};" />
    <GameObject Name="Robot Runner" X="100" Y="64" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Robot Runner" X="324" Y="112" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Walker (Big)" X="442" Y="80" GameObjectTemplateName="Walker (Big)" />
    <GameObject Name="Walker" X="240" Y="50" GameObjectTemplateName="Walker" />
    <GameObject Name="Walker" X="316" Y="47" GameObjectTemplateName="Walker" />
    <GameObject Name="Robot Runner" X="600" Y="49" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Robot Runner" X="154" Y="113" GameObjectTemplateName="Robot Runner" />
  </EditorObjects>
</Scene>