import argparse
import datetime
import time
from glob import glob
import os
import shutil
import subprocess
import sys
import shutil

script_path = os.path.dirname(os.path.realpath(__file__))

sys.path.insert(0, script_path + '/../tools/python_scripts')

import generate_tilesets_res_file
import export_graphicsgale_animations
import export_anim_sequences
import parse_symbols_file
import update_tileset_tilecounts
import update_audio_res

#SGDK_VERSION = "sgdk100"
SGDK_VERSION = "sgdk151"
MAKEFILE_FILENAME = "makefile." + SGDK_VERSION + ".gen"
SGDK_PATH = ""
SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
SOURCE_PATH = os.path.normpath(SCRIPT_PATH + '\\..\\source')
PROJECT_PATH = os.path.normpath(SCRIPT_PATH + '\\..')
SGDK_PROJECT_NAME = ""

returncode = 0
errormessage = ""

def configure_project_name():
    global SGDK_PROJECT_NAME
    projectname = SCRIPT_PATH.split('\\')[-3]
    SGDK_PROJECT_NAME = projectname
    print "- SGDK Project Name: {0}".format(SGDK_PROJECT_NAME)


def configure_environment():
    global SGDK_PATH

    SGDK_PATH = os.path.normpath(SCRIPT_PATH + "\\..\\..\\..\\..\\" + SGDK_VERSION)

    os.environ["GDK"] = SGDK_PATH.replace('\\', '/')
    os.environ["GDK_WIN"] = SGDK_PATH
    os.environ["PATH"] = SGDK_PATH + "\\bin;" + os.environ["PATH"]

    #print "Current Directory {0}".format(os.getcwd())
    #print "GDK: {0}".format(os.environ["GDK"])
    #print "GDK_WIN: {0}".format(os.environ["GDK_WIN"])
    #print "PATH: {0}".format(os.environ["PATH"])


def copy_to_daily_versions_folder():
    daily_versions_folder = "..\dailyversions"
    source = "out\\Genesis\\{0}.bin".format(SGDK_PROJECT_NAME)
    destination = "{0}\\{1}-{2}.bin".format(daily_versions_folder, SGDK_PROJECT_NAME, datetime.datetime.now().date())
    if not os.path.exists(daily_versions_folder):
        if os.makedirs(daily_versions_folder):
            raise Exception("Error encountered while trying to create Daily Versions folder")

    if os.path.isfile(source):
        print "- Copying backup to Daily Versions folder"
        if shutil.copy(source, destination):
            raise Exception("Error encountered while trying to copy to Daily Versions folder")

#def create_folders():

#    generated_folder = 'generated\\'
#    if not os.path.exists(generated_folder):
#        os.makedirs(generated_folder)

#    exported_folder = 'exported\\'
#    if not os.path.exists(exported_folder):
#        os.makedirs(exported_folder)
#
#    generated_folder = 'generated\\'
#    if not os.path.exists(generated_folder):
#        os.makedirs(generated_folder)

def create_folder(path):
    if not os.path.exists(path): 
        os.makedirs(path)

def ensure_folders_created():
    create_folder("..\\out\\exported\\audio")
    create_folder("..\\out\\exported\\blocksets")
    create_folder("..\\out\\exported\\GGAnimations")
    create_folder("..\\out\\exported\\maps")
    create_folder("..\\out\\exported\\scenes")
    create_folder("..\\out\\exported\\tilesets")
    create_folder("..\\out\\exported\\palettes")
    create_folder("..\\out\\generated\\objectmanifests")
    create_folder("..\\out\\generated\\objectphysprops")
    create_folder("..\\out\\Genesis\\source\\game\\objects")
    create_folder("..\\out\\Genesis\\source\\game\\Genesis")
    create_folder("..\\out\\Genesis\\source\\engine\\managers")
    create_folder("..\\out\\Genesis\\source\\engine\\math")
    create_folder("..\\out\\Genesis\\gamedata\\blocksetmaps")
    create_folder("..\\out\\Genesis\\gamedata\\tilesets")
    create_folder("..\\out\\Genesis\\gamedata\\audio")
    create_folder("..\\out\\Genesis\\out\\exported\\palettes")
    create_folder("..\\out\\Genesis\\out\\exported\\tilesets")
    create_folder("..\\out\\Genesis\\out\\exported\\audio")
    create_folder("..\\out\\Genesis\\out\\exported\\blocksets")
    create_folder("..\\out\\Genesis\\out\\exported\\GGAnimations")
    create_folder("..\\out\\Genesis\\out\\exported\\maps")
    create_folder("..\\out\\Genesis\\out\\exported\\scenes")
    create_folder("..\\out\\Genesis\\out\\exported\\tilesets")
    create_folder("..\\out\\Genesis\\out\\generated\\objectmanifests")
    create_folder("..\\out\\Genesis\\out\\generated\\objectphysprops")




def should_build():
    rom_filename = "out\\{0}.bin".format(SGDK_PROJECT_NAME)
    
    if not os.path.exists(rom_filename):
        print "rom doesn't exist, rebuilding"
        return True

    rom_filetime = os.path.getmtime(rom_filename)

    tilesetfolderfiles = glob('gamedata\\tilesets\\*.*')
    latest_file = max(tilesetfolderfiles, key=os.path.getmtime)
    if os.path.getmtime(latest_file) > rom_filetime:
        print "tilesets are newer, rebuilding"
        return True

    walk_dir = 'source'
    for root, subdirs, filenames in os.walk(walk_dir):
        for filename in filenames:
            if filename.endswith(('.c', '.h')):
                fullpath = root + "\\" + filename
                filetime = os.path.getmtime(fullpath)
                if filetime > rom_filetime:
                    print fullpath
                    print "file is newer, rebuilding"
                    return True

    print "No need to rebuild rom"
    return False

def builddata():
    ensure_folders_created()

    #the scripts assume that we're in the source directory
    os.chdir(SOURCE_PATH)

    #ensure folders exist
    #create_folders()

    print "Processing audio..."
    update_audio_res.update_audio_res()
    print "Done"

    #print "Generating tilesets.res..."
    #generate_tilesets_res_file.generate_tilesets_res_file()
    #print "Done"

    print "Exporting tilesets..."
    sys.stdout.flush()
    bmp2cPath = os.path.realpath('.') + "\\..\\Tools\\bmp2c\\bin\\bmp2c.exe"
    if os.system(bmp2cPath) != 0:
        print "Error running bmp2cPath.exe"
        exit(1)
    print "Done"

    print "Exporting palettes..."
    sys.stdout.flush()
    bmppalette2cPath = os.path.realpath('.') + "\\..\\Tools\\bmppalette2c\\bin\\bmppalette2c.exe"
    if os.system(bmppalette2cPath) != 0:
        print "Error running bmppalette2c.exe"
        exit(1)
    print "Done"

    print "Updating tileset tile counts..."
    update_tileset_tilecounts.update_tileset_tilecounts()
    print "Done"

    print "Exporting Graphics Gale animations..."
    export_graphicsgale_animations.export_graphicsgale_animations()
    print "Done"

    print "Object Manifest Generation Pass"
    sys.stdout.flush()
    ManifestGeneratorPath = os.path.realpath('.') + "\\..\\Tools\\ManifestGenerator\\bin\\ManifestGenerator.exe"

    if os.system(ManifestGeneratorPath) != 0:
        sys.stdout.flush()
        print "Error running ManifestGenerator.exe"
        exit(1)
    print "Done"

    print "Object PhysProps Generation Pass"
    sys.stdout.flush()
    PhysPropsGeneratorPath = os.path.realpath('.') + "\\..\\Tools\\PhysPropsGenerator\\bin\\PhysPropsGenerator.exe"

    if os.system(PhysPropsGeneratorPath) != 0:
        sys.stdout.flush()
        print "Error running PhysPropsGenerator.exe"
        exit(1)
    print "Done"

    print "Exporting scenes..."
    sys.stdout.flush()
    scene2cPath = os.path.realpath('.') + "\\..\\Tools\\scene2c\\bin\\scene2c.exe"
    if os.system(scene2cPath) != 0:
        print "Error running scene2c.exe"
        exit(1)

    print "Done"

def build():
    builddata()

    #go to the project root
    os.chdir(PROJECT_PATH)

   
    if should_build():

        # delete old bin files
        if glob("out\\Genesis\\*.bin"):
            print "- Delete old bin files"
            if os.system("del out\\Genesis\\*.bin"):
                raise Exception("Error encountered while trying to delete *.bin files")

        print "rebuilding rom"
        if os.system("%GDK_WIN%\\bin\\make -f build\\" + MAKEFILE_FILENAME):
            raise Exception("Error encountered during build")

        #rename the rom
        newname = "{0}.bin".format(SGDK_PROJECT_NAME)
        print "- Renaming to {0}".format(newname)
        print os.getcwd()
        if os.system("ren out\\Genesis\\rom.bin {0}".format(newname)):
            raise Exception("Error trying to rename rom.bin")
    
        #copy a backup of the rom
        copy_to_daily_versions_folder()

        parse_symbols_file.parse_symbols_file()

    #back to the original path
    os.chdir(SCRIPT_PATH)

    return True

def run():
    filename = "{0}.bin".format(SGDK_PROJECT_NAME)
    path = os.path.normpath("..\\out\\Genesis\\{0}".format(filename))

    if not os.path.isfile(path):
        raise Exception("File {0} not found".format(path))

    if os.system("start " + path):
        raise Exception("Error trying to run " + path)


def buildrun():
    build()
    print "blah"
    run()


def cleangeneratedsource():
    if os.path.exists("..\\out\\exported"):
        print "- Cleaning exported source folder"
        shutil.rmtree("..\\out\\exported")

    if os.path.exists("..\\out\\generated"):
        print "- Cleaning generated source folder"
        shutil.rmtree("..\\out\\generated")

def cleanoutfolder():
    if os.path.exists("..\\out"):
        print "- Cleaning out folder"
        shutil.rmtree("..\\out")

def clean():
    cleangeneratedsource()
    cleanoutfolder()

def rebuild():
    clean()
    build()

def rebuildrun():
    rebuild()
    run()

def parse_args():
    parser = argparse.ArgumentParser(description='SGDK project builder tool')
    subparser = parser.add_subparsers(dest='command')
    run_build = subparser.add_parser('build', help='builds project')
    run_build = subparser.add_parser('builddata', help='builds data only')
    run_buildrun = subparser.add_parser('buildrun', help='builds project and runs it')
    run_run = subparser.add_parser('run', help='runs the project')
    run_clean = subparser.add_parser('clean', help='cleans project')
    run_cleangeneratedsource = subparser.add_parser('cleangeneratedsource', help='cleans just the generated source files of the project')
    run_cleanoutfolder = subparser.add_parser('cleanoutfolder', help='cleans just the out folder of the project')
    run_rebuild = subparser.add_parser('rebuild', help='cleans and builds project')
    run_rebuildrun = subparser.add_parser('rebuildrun', help='cleans, builds and runs project')

    if len(sys.argv) == 1:
        parser.print_help()
        sys.exit(1)
        
    return parser.parse_args()


def hms_string(sec_elapsed):
    h = int(sec_elapsed / (60 * 60))
    m = int((sec_elapsed % (60 * 60)) / 60)
    s = sec_elapsed % 60.
    return "{}:{:>02}:{:>05.2f}".format(h, m, s)

def main():
    global returncode

    configure_project_name()
    configure_environment()

    # get command line parameters
    args = parse_args()

    print "- Command: {0}".format(args.command)

    # which command?
    if args.command == 'build':
        command = build
    elif args.command == 'run':
        command = run
    elif args.command == 'clean':
        command = clean
    elif args.command == 'rebuild':
        command = rebuild

    # go!
    try:
        startTime = time.time()
        command()
        endTime = time.time()

        print "Elapsed time: " + hms_string(endTime - startTime)


    except Exception as ex:
        print "- {0}".format(ex)
        return 1

if __name__ == "__main__":
    sys.exit(main())
