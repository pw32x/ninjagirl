include Build/Makefile.config

#change to your preferred name
#pass the PROGNAME name as a parameter to set a new rom name. "make PROGNAME=my_new_name"
PROGNAME?=untitled_project

#change to your devkitSMS folder
DEVKITSMS_BASE=../../../devkitSMS-master

CC=sdcc
IHX2SMS=$(DEVKITSMS_BASE)/ihx2sms/Linux/ihx2sms
SMSLIB_BASE=$(DEVKITSMS_BASE)/SMSlib
SMSLIB_INCDIR=$(SMSLIB_BASE)/src
PEEP_RULES=$(SMSLIB_BASE)/src/peep-rules.txt
CRT0=$(DEVKITSMS_BASE)/crt0/crt0_sms.rel
SMSLIB_LIB=$(SMSLIB_BASE)/SMSlib.lib          # Use distributed lib
#SMSLIB_LIB=$(SMSLIB_BASE)/src/SMSlib.lib      # Use locally compiled lib

PSGLIB_BASE=$(DEVKITSMS_BASE)/PSGlib
PSGLIB_INCDIR=$(PSGLIB_BASE)/src
PSGLIB_LIB=$(PSGLIB_BASE)/PSGlib.rel



FOLDER_TO_CREATE  = $(SOURCE_OUTPUT_DIR) 
FOLDER_TO_CREATE += $(SOURCE_OUTPUT_DIR)/client/
FOLDER_TO_CREATE += $(SOURCE_OUTPUT_DIR)/client/exported 
FOLDER_TO_CREATE += $(SOURCE_OUTPUT_DIR)/client/generated 
FOLDER_TO_CREATE += $(SOURCE_OUTPUT_DIR)/client/objects
FOLDER_TO_CREATE += $(SOURCE_OUTPUT_DIR)/engine
FOLDER_TO_CREATE += $(foreach dir, $(DEST_DIRECTORIES), $(OUTPUT_DIR)/$(dir))

SOURCE_DIR = source
OUTPUT_DIR = out

CFLAGS=-mz80 -I$(SOURCE_DIR) -I$(SMSLIB_INCDIR) -I$(PSGLIB_INCDIR) -I$(SOURCE_DIR)/engine --peep-file $(PEEP_RULES)
LDFLAGS=-mz80 --no-std-crt0 --data-loc 0xC000

SOURCE_OUTPUT_DIR = $(OUTPUT_DIR)/$(SOURCE_DIR)

CS    = $(wildcard $(SOURCE_DIR)/*.c)
CS    += $(wildcard $(SOURCE_DIR)/client/*.c)
CS    += $(wildcard $(SOURCE_DIR)/client/exported/*.c)
CS    += $(wildcard $(SOURCE_DIR)/client/generated/*.c)
CS    += $(wildcard $(SOURCE_DIR)/client/objects/*.c)
CS    += $(wildcard $(SOURCE_DIR)/engine/*.c)
CS    += $(foreach dir, $(DEST_DIRECTORIES), $(wildcard $(dir)/*.c))

OBJ = $(CS:.c=.rel)
OBJS= $(addprefix $(OUTPUT_DIR)/, $(OBJ))


all: directories $(OUTPUT_DIR)/$(PROGNAME).sms

directories: $(FOLDER_TO_CREATE)

$(FOLDER_TO_CREATE):
	mkdir -p $(FOLDER_TO_CREATE)

$(SOURCE_OUTPUT_DIR)/%.rel: $(SOURCE_DIR)/%.c
	@echo  $(FOLDER_TO_CREATE)
	$(CC) $(CFLAGS) -c $< -o $@

$(SOURCE_OUTPUT_DIR)/%.rel: $(SOURCE_DIR)/%.c $(SOURCE_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_DIR)/$(PROGNAME).ihx: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(CRT0) $(SMSLIB_LIB) $(PSGLIB_LIB) $^

$(OUTPUT_DIR)/$(PROGNAME).sms: $(OUTPUT_DIR)/$(PROGNAME).ihx
	$(IHX2SMS) $< $@

clean:

	rm -f $(SOURCE_OUTPUT_DIR)/*.*
	rm -f $(SOURCE_OUTPUT_DIR)/client/*.*
	rm -f $(SOURCE_OUTPUT_DIR)/client/objects/*.*
	rm -f $(SOURCE_OUTPUT_DIR)/client/exported/*.*
	rm -f $(SOURCE_OUTPUT_DIR)/client/generated/*.*
	rm -f $(SOURCE_OUTPUT_DIR)/engine/*.*
	rm -f $(OUTPUT_DIR)/*.* 
	for dir in $(DEST_DIRECTORIES); do \
		rm -rf $(OUTPUT_DIR)/$$dir/*.*; \
	done



# When a linking error occurs, sdcc returns an error and make fails. However
# a .ihx output file still gets created. This leads to make thinking that the .ihx
# file is up to date the next time it runs... This forces linking to take place
# every time make is called.
.PHONY: $(PROGNAME).ihx directories
