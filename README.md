# Untitled Ninja Girl game
A Sega Master System game of some kind.

Follow along as I try to build a game for the Sega Master System. It'll be fun!


# Building

You'll need: 

DevkitSMS
https://github.com/sverx/devkitSMS

SDCC
https://sdcc.sourceforge.net/

Use the batch files in /build to perform build actions (build/clean/rebuild/etc)

# BuildMasterSystem

The project uses the BuildMasterSystem. It is the primary interface with which to manage the project. The BMS handles generating gamedata and building code. The build folder contains batch files that call the BMS to perform various actions like build, clean, rebuild, etc.

The BuildMasterSystem project is located in project/tools/BuildMasterSystem
