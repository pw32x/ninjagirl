<Scene>
  <TiledMapFilePath>..\maps\level_001.tmx</TiledMapFilePath>
  <EditorObjects>
    <GameObject Name="CommandRunner RightScroll" X="-84.53703703703701" Y="3.4768518518518445" GameObjectTemplateName="CommandRunner RightScroll" />
    <Command Name="RightScroller_Init" X="-83.68981481481494" Y="74.58796296296276" CommandValue="&amp;background3_mapResourceInfo" PreCommandData="" />
    <Command Name="Set Background Palette" X="-88.89351851851863" Y="-67.60185185185179" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <Command Name="Set Sprite Palette" X="-84.24537037037054" Y="143.59722222222243" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <GameObject Name="Gun Girl" X="43.14165881765015" Y="85.29513523395288" GameObjectTemplateName="Gun Girl" />
    <Command Name="MapManager_SetTilesetProperties_Command" X="-87.54399999999976" Y="221.6960000000002" CommandValue="&amp;setTilesetPropertiesParams " PreCommandData="#include &quot;client/tileset_functions.h&quot;&#xD;&#xA;const SetTilesetProperties_Params setTilesetPropertiesParams = &#xD;&#xA;{ &#xD;&#xA; 1, &#xD;&#xA; breakable_rock_tileset_TilesetFunction, &#xD;&#xA; &amp;rock_particle_template&#xD;&#xA;};" />
    <Command Name="Set Background Vertical Scroll" X="-159" Y="-70" CommandValue="4" PreCommandData="" />
    <GameObject Name="Wheeler" X="283.10041223708447" Y="129.9337241369454" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="468.29687619074616" Y="129.27448893080324" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="589.1105252629185" Y="129.9827532007316" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="455.6881179984014" Y="81.38916395176047" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="371.2447452274783" Y="80.50523333904911" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="343.90817901234584" Y="128.83719135802482" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="705.4421772595633" Y="128.8371598031931" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="803.584184123037" Y="47.14347029321042" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="736.744598765434" Y="81.45756172839519" GameObjectTemplateName="Wheeler" />
    <GameObject Name="Wheeler" X="212" Y="130" GameObjectTemplateName="Wheeler" />
    <GameObject Name="ShotgunItem" X="129.34897976680386" Y="144.45224622770965" GameObjectTemplateName="ShotgunItem" />
  </EditorObjects>
</Scene>