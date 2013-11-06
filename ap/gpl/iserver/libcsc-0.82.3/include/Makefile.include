# ******************************************************************************
# 
# libcsc: Make Subsystem
# 
# 	----------------------------------------------------------------
# 
# Copyright (c) 2001, Douglas R. Jerome, Peoria, AZ USA
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
# 	$RCSfile: Makefile.include,v $
# 	$Revision: 1.1 $
# 	$Date: 2001/07/10 04:21:55 $
# 
# PROGRAM INFORMATION
# 
# 	Developed by:	libcsc project
# 	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>
# 
# FILE DESCRIPTION
# 
# 	This is the libcsc make file for the include directory. It does the
# 	fetching from RCS and installation of the csc header files.
# 
# CHANGE LOG
# 
# 	25jun01	drj	File generation.
# 
# ******************************************************************************


# *************************************************************************** #
# Macro Definitions                                                           #
# *************************************************************************** #

C_HEADER_FILES	= libcsc.h	\
		  libcsc_debug.h


# *************************************************************************** #
# More Macro Definitions                                                      #
# *************************************************************************** #

INSTALL	= install -c


# *************************************************************************** #
# Make Rules
# *************************************************************************** #

%::	${PROJECTDIR}/RCS/%,v
	$(CO) $(COFLAGS) $@ $<


# *************************************************************************** #
# Make Targets                                                                #
# *************************************************************************** #

headers:	${C_HEADER_FILES}

install:	${C_HEADER_FILES}
	@for file in ${C_HEADER_FILES}; do				\
		if [ -r $${file} -a -n "${INSTALLINC}" ]; then		\
			${INSTALL} -m 644 $${file} ${INSTALLINC};	\
		else							\
			echo "ERROR ***** (displayed on next line)";	\
			echo "${INSTALL} -m 644 $${file} ${INSTALLINC}";\
		fi							\
	done

clean:


# end of Makefile
