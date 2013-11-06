# ******************************************************************************
# 
# libcsc: Make Subsystem
# 
# 	----------------------------------------------------------------
# 
# Copyright (c) 2001, 2002 Douglas R. Jerome, Peoria, AZ USA
# 
# 	This program is free software; you can redistribute it and/or modify
# 	it under the terms of the GNU Library General Public License as
# 	published by the Free Software Foundation; either version 2 of the
# 	License, or (at your option) any later version.
# 
# 	This program is distributed in the hope that it will be useful,
# 	but WITHOUT ANY WARRANTY; without even the implied warranty of
# 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# 	GNU General Public License for more details.
# 
# 	You should have received a copy of the GNU Library General Public
# 	License along with this program; if not, write to the Free Software
# 	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# 
# 	----------------------------------------------------------------
# 
# FILE NAME
# 
# 	$RCSfile: Makefile.src,v $
# 	$Revision: 1.13 $
# 	$Date: 2003/03/26 02:02:39 $
# 
# PROGRAM INFORMATION
# 
# 	Developed by:	libcsc project
# 	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>
# 
# FILE DESCRIPTION
# 
# 	This is the main source code make file.
# 
# CHANGE LOG
# 
# 	25mar03	drj	Fixed debug target.
# 
# 	06nov02	drj	Cleaned up echoed message in the doc target.
# 
# 	02may02	drj	Cleaned up making for debug. Added OSTYPE and use it
# 			for -pthread option with linux.
#
# 	19apr02	drj	Added csc_notify.
#
# 	18apr02	drj	Added csc_symtab.
#
# 	15apr02	drj	Added csc_hash and csc_math.
# 
# 	11apr02	drj	Added csc_tree.
#
# 	16feb02	drj	Added csc_list.
# 
# 	25jun01	drj	File generation.
# 
# ******************************************************************************


# *************************************************************************** #
# Macro Definitions                                                           #
# *************************************************************************** #

# -- Configuration
#
VERSION	= $(shell cd .. && ls *.is.version | sed -e 's/\.is\.version//')
OSTYPE	= $(shell                                                             \
	if [ "`uname -s`" = "SunOS" -a "`uname -r | cut -c 1`" = "5" ]; then  \
		echo "SOLARIS";                                               \
	else                                                                  \
		if [ "`uname -s`" = "Linux" ]; then                           \
			echo "LINUX";                                         \
		fi                                                            \
	fi                                                                    \
	)

# -- Input Files
#
HEADERS	=
OBJECTS	=		\
	csc_config.o	\
	csc_file.o	\
	csc_hash.o	\
	csc_io.o	\
	csc_list.o	\
	csc_math.o	\
	csc_mem.o	\
	csc_notify.o	\
	csc_sock.o	\
	csc_string.o	\
	csc_symbol.o	\
	csc_symtab.o	\
	csc_sys.o	\
	csc_timer.o	\
	csc_tree.o	\
	xcsc_debug.o
SOURCES	=		\
	csc_config.c	\
	csc_file.c	\
	csc_hash.c	\
	csc_io.c	\
	csc_list.c	\
	csc_math.c	\
	csc_mem.c	\
	csc_notify.c	\
	csc_sock.c	\
	csc_string.c	\
	csc_symbol.c	\
	csc_symtab.c	\
	csc_sys.c	\
	csc_timer.c	\
	csc_tree.c	\
	xcsc_debug.c

# -- Generated Files
#
ARCHIVE		= libcsc.a
LMODULE		= libcsc.o
ARCHIVE_DEBUG	= libcsc_debug.a
LMODULE_DEBUG	= libcsc_debug.o
PROGRAM		= libcsc-config

# -- Install Locations
#
INSTALLPREFIX	= /usr/local
INSTALLEXE	= ${INSTALLPREFIX}/bin
INSTALLINC	= ${INSTALLPREFIX}/include
INSTALLLIB	= ${INSTALLPREFIX}/lib

# -- Extra, Referenced Files; extra compilation switches, etc.
#
C_HEADER_DIR	= ../include
LOCAL_INCLUDES	= -I. -I${C_HEADER_DIR}
LOCAL_DEFINES	=
LIB_DIRS	=
LIBS		=

ifeq ("${OSTYPE}","LINUX")
LOCAL_DEFINES	+= -pthread
endif


# *************************************************************************** #
# More Macro Definitions                                                      #
# *************************************************************************** #

# -- Tools
#
AR	= ar
CAT	= cat
CC	= gcc
CHMOD	= chmod
CP	= cp
INSTALL	= install -c
LD	= ld
LINK	= ln -f -s
MV	= mv
NM	= nm
RANLIB	= ranlib
RM	= rm -f
STRIP	= strip
SZ	= size

# -- cc Flags
#
CC_COMPILER	= -ansi -c -pipe ${CC_PARAMS}
CC_WARNING	= -Wall -W -Wmissing-prototypes -Wmissing-declarations
CFLAGS		= ${CC_COMPILER} ${CC_WARNING}

# -- cpp Flags
#
CPP_DEFINES	= ${CDEBUGFLAGS} ${LOCAL_DEFINES} -D${OSTYPE}
CPP_INCLUDES	= ${LOCAL_INCLUDES} ${EXTRA_INCLUDES} -I-
CPPFLAGS	= -MMD ${CPP_DEFINES} ${CPP_INCLUDES}

# -- ld Flags
#
LDFLAGS		= -r


# *************************************************************************** #
# Make Rules                                                                  #
# *************************************************************************** #

%::	${PROJECTDIR}/RCS/%,v
	$(CO) $(COFLAGS) $@ $<

.c.o:
	@echo ""
	@echo "***** $<"
	time ${CC} ${CFLAGS} ${CPPFLAGS} $<


# *************************************************************************** #
# Make Targets                                                                #
# *************************************************************************** #

.PHONEY:	default
.PHONEY:	clean cleanall cleandoc config docclean doc incbuild
.PHONEY:	install installlibrary installheaders installprogram
.PHONEY:	testhclean testh
.PHONEY:	archive debug exe headers lib library lmodule objects sources

# ---------------------------------------------------------------------------
# -- Default Target
# ---------------------------------------------------------------------------

default:	${ARCHIVE} ${LMODULE} ${PROGRAM}

# ---------------------------------------------------------------------------
# -- Housekeeping Targets
# ---------------------------------------------------------------------------

clean:
	${RM} ${OBJECTS} ${OBJECTS:.o=.d} .depend
	${RM} ${ARCHIVE_DEBUG} ${ARCHIVE_DEBUG}.names
	${RM} ${LMODULE_DEBUG} ${LMODULE_DEBUG}.names
	${RM} ${ARCHIVE} ${ARCHIVE}.names
	${RM} ${LMODULE} ${LMODULE}.names
	${RM} ${PROGRAM} config-main.o config-main.d csc_config.h core

cleanall:	clean
	${RM} ../lib/${ARCHIVE} ../lib/${ARCHIVE_DEBUG}
	${RM} ../lib/${LMODULE} ../lib/${LMODULE_DEBUG}
	${RM} ../bin/${PROGRAM}

cleandoc:
	${RM} ../doc/man?/*

config:
	@${RM} csc_config.h
	@echo "/*"                                           >> csc_config.h
	@echo " * This file is generated by Makefile.src"    >> csc_config.h
	@echo " * Edits to this file will be lost."          >> csc_config.h
	@echo " */"                                          >> csc_config.h
	@echo ""                                             >> csc_config.h
	@echo "#define  CSC_CFLAGS      \"${CPP_INCLUDES}\"" >> csc_config.h
	@echo "#define  CSC_LDFLAGS     \"${LIB_DIRS}\""     >> csc_config.h
	@echo "#define  CSC_LIBS        \"${LIBS}\""         >> csc_config.h
	@buildnum=0;					\
	if [ -f .build ]; then				\
		buildnum=`cat .build`;			\
	fi;						\
	echo  "#define  CSC_BUILD       \"$${buildnum}\""  >> csc_config.h
	@builddate="";					\
	if [ -f .date ]; then				\
		builddate=`cat .date`;			\
		${RM} .date;				\
	fi;						\
	echo  "#define  CSC_DATE        \"$${builddate}\"" >> csc_config.h
	@echo "#define  CSC_VERSION     \"${VERSION}\""    >> csc_config.h

docclean:
	${RM} ../doc/man?/*

doc:
	@echo ""
	@echo "---------------------------------------------------------------"
	@echo ""
	@echo "Removing old documentation (function overviews)."
	@${RM} ../doc/man3/*
	@echo "Removing old documentation (subsystem overviews)."
	@${RM} ../doc/manl/*
	@echo ""
	@echo "Ripping documentation from sources:"
	@mrip="";							\
	if [ -f ../../Cmrip ]; then					\
		mrip="../../Cmrip";					\
	fi;								\
	if [ -f ../tools/mrip ]; then					\
		mrip="../tools/mrip";					\
	fi;								\
	echo "SUBSYSTEM(s)";						\
	for file in ${SOURCES}; do					\
		$${mrip} -v 1 -r $${file} -d ../doc/manl -k SUBSYSTEM;	\
		${RM} $${file}.rip;					\
	done;								\
	echo "SUBROUTINE(s)";						\
	for file in ${SOURCES}; do					\
		$${mrip} -v 1 -r $${file} -d ../doc/man3 -k SUBROUTINE;	\
		${RM} $${file}.rip;					\
	done
	@echo ""
	@echo "Look in ../doc/manl and ../doc/man3 for documentaion."
	@echo ""

incbuild:
	@buildnum=0;					\
	if [ -f .build ]; then				\
		buildnum=`cat .build`;			\
		buildnum=`expr $${buildnum} + 1`;	\
		${RM} .build;				\
	fi;						\
	echo $${buildnum} > .build
	@${RM} .date; echo `date '+%a. %h %d, 20%y, %r'` > .date

# ---------------------------------------------------------------------------
# -- Installation Targets
# ---------------------------------------------------------------------------

install:	installlibrary installheaders installprogram

installlibrary:	${ARCHIVE} ${LMODULE}
	cd ../lib && make -f Makefile.lib install "INSTALLLIB=${INSTALLLIB}"

installheaders:	headers
	cd ../include && \
		make -f Makefile.include install "INSTALLINC=${INSTALLINC}"

installprogram:	${PROGRAM}
	cd ../bin && make -f Makefile.bin install "INSTALLEXE=${INSTALLEXE}"

# ---------------------------------------------------------------------------
# -- Test Targets
# ---------------------------------------------------------------------------

TEST_DEPS	= _HEADERlibcsc.d	\
		  _HEADERlibcsc_debug.d

TEST_OBJS	= _HEADERlibcsc.o	\
		  _HEADERlibcsc_debug.o

testhclean:
	${RM} ${TEST_DEPS} ${TEST_OBJS}

testh:	headers ${HEADERS} ${SOURCES} ${TEST_OBJS}
	@${RM} ${TEST_DEPS} ${TEST_OBJS}
	@echo "Done."

# ---------------------------------------------------------------------------
# -- Build Targets
# ---------------------------------------------------------------------------

archive:	${ARCHIVE}

debug:
	make clean
	make CDEBUGFLAGS=-DDEBUG CC_PARAMS=-g
	${MV} ../lib/${LMODULE} ../lib/${LMODULE_DEBUG}
	${MV} ../lib/${ARCHIVE} ../lib/${ARCHIVE_DEBUG}
	${LINK} ${LMODULE_DEBUG} ../lib/${LMODULE}
	${LINK} ${ARCHIVE_DEBUG} ../lib/${ARCHIVE}
	make clean

exe:		${PROGRAM}

headers:	${HEADERS}
	cd ${C_HEADER_DIR} && make -f Makefile.include headers

lib library lmodule:	${LMODULE}

objects:	config ${OBJECTS}

sources:	${SOURCES}

${ARCHIVE}:	headers ${HEADERS} ${SOURCES} config ${OBJECTS}
	@echo ""
	@echo "----------------------------------------------------------------"
	@echo ""
	@${RM} .depend
	${CAT} ${OBJECTS:.o=.d} > .depend
	@echo ""
	@echo "##### Removing old library '${ARCHIVE}'..."
	${RM} ${ARCHIVE}
	@echo ""
	@echo "##### Archiving objects ${OBJECTS} into '${ARCHIVE}'."
	@echo ""
	@echo "##### Building new archive ..."
	${AR} r ${ARCHIVE} ${OBJECTS}
	${RANLIB} ${ARCHIVE}
	@echo ""
	@echo "##### New archive '${ARCHIVE}' built from:"
	${AR} vt ${ARCHIVE}
	@echo ""
	@echo "##### Size statistics for ${ARCHIVE}:"
	${SZ} ${ARCHIVE}
	@echo ""
	${NM} ${ARCHIVE} > ${ARCHIVE}.names
	${CHMOD} 644 ${ARCHIVE}
	${CHMOD} 644 ${ARCHIVE}.names
	${RM} ../lib/${ARCHIVE}
	${CP} ${ARCHIVE} ../lib
	@echo ""
	@echo "##### Finished making the '${ARCHIVE}' object archive."
	@echo ""

${LMODULE}:	headers ${HEADERS} ${SOURCES} config ${OBJECTS}
	@echo ""
	@echo "----------------------------------------------------------------"
	@echo ""
	@${RM} .depend
	${CAT} ${OBJECTS:.o=.d} > .depend
	@echo ""
	@echo "##### Removing old object module '${LMODULE}'..."
	${RM} ${LMODULE}
	@echo ""
	@echo "##### Time statistics for linking '${LMODULE}' with command:"
	time ${LD} ${LDFLAGS} -o ${LMODULE} ${OBJECTS}
	@echo ""
	@echo "##### Size statistics for ${LMODULE}:"
	${SZ} ${LMODULE}
	@echo ""
	${NM} ${LMODULE} > ${LMODULE}.names
	${CHMOD} 644 ${LMODULE}
	${CHMOD} 644 ${LMODULE}.names
	${RM} ../lib/${LMODULE}
	${CP} ${LMODULE} ../lib
	@echo ""
	@echo "##### Finished making the '${LMODULE}' object module file."
	@echo ""

${PROGRAM}:	config config-main.o csc_config.o
	@echo ""
	@echo "---------------------------------------------------------------"
	@echo ""
	@echo "##### Time statistics for linking '${PROGRAM}' with command:"
	time ${CC} -o ${PROGRAM} config-main.o csc_config.o 
	@echo ""
	${STRIP} ${PROGRAM}
	${CHMOD} 775 ${PROGRAM}
	${CP} ${PROGRAM} ../bin
	${CHMOD} 755 ../bin/${PROGRAM}
	@echo ""
	@echo "##### Finished making the '${PROGRAM}' executable program."
	@echo ""


# The .depend file contains the header file dependencies.
#
-include .depend


# end of Makefile
