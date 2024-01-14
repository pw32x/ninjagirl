# gal2tmx
A tool that converts a Graphics Gale file to a Tiled TMX map for Sega Master System homebrew development. It's intended for creating level "themes" in Graphics Gale. Create a theme in GG, then use this tool to export to TMX. Use the resulting TMX as a base to make new levels from. 

This tool is part of the toolkit that includes tmx2c and gg2c, used to work with game assets  Sega Master System projects like basicsmsproject project and others. 

Once level TMXs are ready to used in the game, use tmx2c.

The gal2tmx tool will convert the Graphics Gale image into these files:

* A TMX file that can be loaded in Tiled
* Its corresponding TSX tileset using 16x16 tiles
* The bitmap used by the TSX tileset using 16x16 tiles
* A C language source and header file containing the tileset which includes the 8x8 tiles and its metatiles map

For example, converting "background.gal" will give these files:

* background_tileset_tsx.bmp // bitmap for the Tiled tileset 
* background_tileset.h // the header file for the tileset
* background_tileset.c // the source file for the tileset
* background_tileset.tsx // the Tiled map tileset in 16x16 tiles
* background.tmx // the Tiled map

The Tiled tileset are 16x16 while the actual game tiles are 8x8. The reason they're different is that the 16x16 tiles makes it easier to build maps in Tiled while the 8x8 tiles are meant to be used on consoles. The metatile look up table is used at runtime to tell how a 16x16 tile is built up of 8x8 tiles.

# Assumptions
* the image's width and height are a multiple of 16
* the image is 16 colors (4 bits per pixel)

# Command Line

    gal2tmx [source_gal_file] [destination folder] [-y or -o]

  The tool checks for overwrites and prompts the user. Pass -y or -o to the command line to suppress the prompt. 


# Layers

A gal file can have layers for additional features

* animated tile markers. that indicates that the tile underneath is animated. This will export a list of tile indexes that be overriden. 

it's up to the developer to setup and update the animated tiles at those tile indexes for the effect to work

the layer can be called anything as long as it starts with "anim" for gal2tmx to find it