# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LcdEmulator
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : LcdEmulator
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : LcdEmulator_0xe76d00e8.hlp
LcdEmulator_0xe76d00e8.hlp : LcdEmulator.xml LcdEmulator.cshlp Custom.xml
	cshlpcmp.bat LcdEmulator.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy LcdEmulator_0xe76d00e8.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del LcdEmulator_0xe76d00e8.hlp
	del LcdEmulator_0xe76d00e8.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo LcdEmulator_0xe76d00e8.hlp

FINAL : do_nothing
