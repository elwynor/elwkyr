###############################################################################
#####               This makefile generates ELWKYR.DLL                    #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

VIRDIR = .\GCVIRDAT

# for ASM output
#PARSEOPTS = $(PARSEOPTS) -DIS30 -S
PARSEOPTS = $(PARSEOPTS) -DIS30

DEFILE = 

VIRFILES =          \
     GCVIRDAT\elwkyr.vir

DLLLIB =            \
     $(DLLLIB)      \
     wgserver.lib   \
     galgsbl.lib

OBJFILES =          \
     kyraloc.obj    \
     kyrandia.obj   \
     kyranim.obj    \
     kyrcmds.obj    \
     kyrlocs.obj    \
     kyrobjr.obj    \
     kyrobjs.obj    \
     kyrprot.obj    \
     kyrrous.obj    \
     kyrspel.obj    \
     kyrsysp.obj    \
     kyrutil.obj    \
     gamutils.obj

elwkyr.dll:         \
     $(GCBUILD)     \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
