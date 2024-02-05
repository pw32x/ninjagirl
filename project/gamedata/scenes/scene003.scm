<Scene>
  <TiledMapFilePath>..\maps\background3_test.tmx</TiledMapFilePath>
  <EditorObjects>
    <GameObject Name="CommandRunner RightScroll" X="-84.53703703703701" Y="3.4768518518518445" GameObjectTemplateName="CommandRunner RightScroll" />
    <Command Name="RightScroller_Init" X="-83.68981481481494" Y="74.58796296296276" CommandValue="&amp;background3_mapResourceInfo" PreCommandData="" />
    <Command Name="Set Background Palette" X="-88.89351851851863" Y="-67.60185185185179" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <Command Name="Set Sprite Palette" X="-84.24537037037054" Y="143.59722222222243" CommandValue="&amp;globalPaletteResourceInfo" PreCommandData="" />
    <GameObject Name="Gun Girl" X="7.528232891724933" Y="-0.19714871666357436" GameObjectTemplateName="Gun Girl" />
    <Command Name="MapManager_SetTilesetProperties_Command" X="-87.54399999999976" Y="221.6960000000002" CommandValue="&amp;setTilesetPropertiesParams " PreCommandData="#include &quot;client/tileset_functions.h&quot;&#xD;&#xA;const SetTilesetProperties_Params setTilesetPropertiesParams = &#xD;&#xA;{ &#xD;&#xA; 1, &#xD;&#xA; breakable_rock_tileset_TilesetFunction, &#xD;&#xA; &amp;rock_particle_template&#xD;&#xA;};" />
    <GameObject Name="Robot Runner" X="125.2225308641974" Y="60.01296296296317" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Robot Runner" X="259.3333333333339" Y="0.6202381973024222" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Walker" X="288.36310879457596" Y="47.64751386840361" GameObjectTemplateName="Walker" />
    <GameObject Name="Walker (Big)" X="331.28612235177536" Y="112.14710862482843" GameObjectTemplateName="Walker (Big)" />
    <GameObject Name="Walker (Big)" X="585.9371768970454" Y="49.0699149256603" GameObjectTemplateName="Walker (Big)" />
    <GameObject Name="Robot Runner" X="391.17746913580254" Y="-0.5385802469135821" GameObjectTemplateName="Robot Runner" />
    <GameObject Name="Walker (Big)" X="456.4306121399176" Y="81.16387774348422" GameObjectTemplateName="Walker (Big)" />
  </EditorObjects>
</Scene>