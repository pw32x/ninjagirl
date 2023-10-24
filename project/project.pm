<ProjectMaster>
    <Settings>
        <Setting name="ProjectName" value="NinjaGirl"/>
		<Setting name="WorkingDirectory" value=""/> <!-- root of the project folder -->
		<Setting name="romPath" value = "out" />
		<Setting name="makefile.Path" value="build/Makefile" /> <!-- forward slashes! -->
		<Setting name="dailyVersionsFolder" value="..\dailyversions" />		
	</Settings>
	<Tools>
		<Tool name="gg2c" path="..\..\..\..\GenDev\Projects\gg2c\Release\gg2c.exe" />
		<Tool name="tmx2c" path="..\..\tmx2c\bin\tmx2c.exe" />
	</Tools>
	<Entries>
		<Entry tool="gg2c" source="gamedata\animations" destination="source\client\exported" />
		<Entry tool="tmx2c" source="gamedata\maps" destination="source\client\exported" />
	</Entries>
</ProjectMaster>

<!--
Tools
{
	gg2c: "somepath\gg2c.exe" source destination flags
	gal2tmx: "somepath\gal2tmx.exe"
	tmx2c: "somepath\tmx2c.exe"
	generic_tool: "somepath\generictool.txt"
}

Entries
{
	Entry
	{
		source: "some file or folder"
		destination: 
		tool: "generic_tool"
		flags: "something"
	}

	Entry 
	{
	
		file: "gamedata\animations\*.gal" 
		options: "-sms8x16 -batched -streamed" 
		destination: "source\client\exported"
		bank: "bank1"
		tool: "gg2c"
	}
	
	Entry 
	{
	
		file: "gamedata\animations\ninja_girl.gal" 
		options: "-sms8x16 -batched -streamed" 
		destination: "source\client\exported"
		bank: "bank1"
		tool: "gg2c"
	}
	
	
	Entry 
	{
	
		file: "gamedata\maps\background3.tmx" 
		options: "something" 
		destination: "source\client\exported"
		tileset_bank: "bank2"
		map_bank: "bank3"
		tool: "tmx2c"
	}	
}



// exports the file to .o file. creates a resource_locator struct that goes into bank 0.

typedef 
{
	u16 bankId;
	Resource* resource;
} resource_locator;

adds to the list of objs added to the CC command line

(CC) stuff .... -BANK Whatever file.o ... 





// builds list of destination folders, feeds it to the make file to create and empty

// builds list of files to add to the OBJ
-->