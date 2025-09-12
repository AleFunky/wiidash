#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif


#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source libraries
DATA		:=	data data/objects data/glow data/portals data/icons data/levels data/sfx data/back_grounds data/perspective data/menu
INCLUDES	:=  libraries

include $(patsubst %/$(BUILD),%,$(CURDIR))/wii_rules

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------


WII_FLAGS = -fomit-frame-pointer -ffast-math -fno-math-errno -ffinite-math-only -fno-strict-aliasing -fno-align-functions -fno-align-labels -fno-align-loops -fno-align-jumps
CFLAGS	= -g -O2 -Wall $(MACHDEP) $(INCLUDE) -MMD -MP -I$(DEVKITPRO)/libogc/include/ogc $(WII_FLAGS)
CXXFLAGS	=	$(CFLAGS)

LDFLAGS	=	-g $(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	-lgrrlib -lpngu -lwiiuse -lfat -lbte -lvorbisidec -lmad -logg -lasnd -logc -lm -lz -lmxml `$(PREFIX)pkg-config freetype2 libpng libjpeg --libs` 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(CURDIR)/$(GRRLIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o) $(SFILES:.S=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -iquote $(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD) \
					-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:= -L$(LIBOGC_LIB) $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

ifeq (,$(wildcard $(DEVKITPRO)/portlibs/ppc/include/tremor/ivorbiscodec.h))

$(BUILD):
	@echo
	@echo "*------------------------------------------------------------------------------------------*"
	@echo
	@echo "Please install libvorbisidec using (dkp-)pacman -S ppc-libvorbisidec"
	@echo
	@echo "See https://devkitpro.org/viewtopic.php?f=13&t=8702 for details"
	@echo
	@echo "*------------------------------------------------------------------------------------------*"
	@echo
else

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

endif
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

#---------------------------------------------------------------------------------
run:
	wiiload $(TARGET).dol


#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

# Put the response file in the build dir so it gets cleaned with other intermediates
OBJFILE := $(DEPSDIR)/objects.rsp

# Helper for a newline
define NL :=


endef

$(OUTPUT).dol: $(OUTPUT).elf

$(OUTPUT).elf: $(OBJFILE) 
	$(SILENTMSG) linking ... $(notdir $@)
	$(SILENTCMD)$(LD) @$(OBJFILE) $(LDFLAGS) $(LIBPATHS) $(LIBS) -o $@

$(OBJFILE): $(OFILES)
	$(SILENTMSG) objecting ... $(notdir $@)
	@$(file >$@,$(foreach o,$(OFILES),$(o)$(NL)))


$(OFILES_SOURCES) : $(HFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .ogg extension
#---------------------------------------------------------------------------------
%.ogg.o	%_ogg.h :	%.ogg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .mp3 extension
#---------------------------------------------------------------------------------
%.mp3.o	%_mp3.h :	%.mp3
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .ttf extension
#---------------------------------------------------------------------------------
%.ttf.o %_ttf.h	:	%.ttf
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .gmd extension
#---------------------------------------------------------------------------------
%.gmd.o	%_gmd.h :	%.gmd
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .jpg extension
#---------------------------------------------------------------------------------
%.jpg.o	%_jpg.h	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .png extension
#---------------------------------------------------------------------------------
%.png.o	%_png.h:	%.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
