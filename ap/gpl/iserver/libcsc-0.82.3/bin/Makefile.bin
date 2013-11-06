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
# 	$RCSfile: Makefile.bin,v $
# 	$Revision: 1.1 $
# 	$Date: 2001/07/10 04:21:28 $
# 
# PROGRAM INFORMATION
# 
# 	Developed by:	libcsc project
# 	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>
# 
# FILE DESCRIPTION
# 
# 	This is the bin directory make file.
# 
# CHANGE LOG
# 
# 	25jun01	drj	File generation.
# 
# ******************************************************************************


# *************************************************************************** #
# Macro Definitions                                                           #
# *************************************************************************** #

BINS	= libcsc-config


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

default:
	@echo "Nothing to do for default target."
	@echo "Try \"make install\""

install:
	@for file in ${BINS}; do					\
		if [ -r $${file} -a -n "${INSTALLEXE}" ]; then		\
			${INSTALL} -m 755 $${file} ${INSTALLEXE};	\
		else							\
			echo "CANNOT ***** (displayed on next line)";	\
			echo "${INSTALL} -m 755 $${file} ${INSTALLEXE}";\
		fi							\
	done

clean:


# end of Makefile
