# Solaris specific defines, passed to subdirectories.
# To use Sun CC, uncomment the CC and KFLAGS variables.
#
# $Id: Makefile.in,v 1.6 2009-11-25 14:58:26 franklahm Exp $
# This Makefile.in is not automake generated
# copy and paste from automake Makefile.in
srcdir = .
top_srcdir = ../..

# end copy and paste

CC	= mipsel-linux-uclibc-gcc
# LD hardcoded to sun ld, GNU ld has been reported to cause some trouble with 64 bit
LD	= /usr/ccs/bin/ld

INSTALL = /usr/bin/install -c
GREP=/bin/grep


# -D_ISOC9X_SOURCE is handled by OSVERSION. basically, it's not needed
# with 2.5.1.
DEFS=	-D__svr4__ -DSOLARIS -I../../sys/generic \
	-I.. -DHAVE_CONFIG_H

# Variables
KCFLAGS=
KLDFLAGS=
COMPILE_KERNEL_GCC=
SPARC64=
SOLARIS_MODULE_FALSE=
SOLARIS_MODULE_TRUE=#
USE_SOLARIS_TRUE=#
USE_SOLARIS_FALSE=

OPTOPTS=

# Local build stuff.

SRC= linkage.c tpi.c dlpi.c ioc.c if.c aarp.c ddp.c sock.c rt.c
OBJ= linkage.o tpi.o dlpi.o ioc.o if.o aarp.o ddp.o sock.o rt.o
HEADERS= if.h ioc.h rt.h sock.h
EXTRA_DIST= ddp.conf Makefile.in $(SRC) $(HEADERS)
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

INCPATH=	-I../../include -I../netatalk -I../..
CFLAGS=	${DEFS} ${OPTOPTS} ${INCPATH} ${KCFLAGS}

# Not building on Solaris
all:

# No Solaris kernel module build
#all:
#	@echo
#	@echo "Solaris kernel module cannot be build"
install:

uninstall:

# Build Solaris kernel module
#all :	kernel

#kernel: ddp 

#FRC: 

#ddp :	${OBJ}
#	${LD} ${KLDFLAGS} -r -o ddp ${OBJ}

#linkage.o : linkage.c
#	${CC} ${CFLAGS} -DVERSION=\"`cat ../../VERSION`\" -c linkage.c

#kuninstall : FRC
#	@if [ x"${SPARC64}" = x"yes" ] ; then \
#		${RM} /usr/kernel/drv/sparcv9/ddp; \
#		${RM} /usr/kernel/strmod/sparcv9/ddp; \
#	else \
#		${RM} /usr/kernel/drv/ddp; \
#		${RM} /usr/kernel/strmod/ddp; \
#	fi
#	${RM} /usr/kernel/drv/ddp.conf
#	-rem_drv ddp
#	sync;sync;sync

#kinstall : kernel kuninstall
#	@if [ x"${SPARC64}" = x"yes" ]; then \
#		${INSTALL} -o root -g sys -c ddp /usr/kernel/drv/sparcv9/ddp; \
#		ln /usr/kernel/drv/sparcv9/ddp /usr/kernel/strmod/sparcv9/ddp; \
#	else \
#		${INSTALL} -o root -g sys -c ddp /usr/kernel/drv/ddp; \
#		ln /usr/kernel/drv/ddp /usr/kernel/strmod/ddp; \
#	fi
#	${INSTALL} -o root -g sys -c ddp.conf /usr/kernel/drv/ddp.conf
#	add_drv -m '* 0666 root sys' ddp
#	sync;sync;sync
#	@if ${GREP} 'ddp' /etc/netconfig; then \
#            echo "netconfig already contains a ddp module, skipping"; \
#        else \
#            echo "adding ddp module to netconfig"; \
#            echo "ddp        tpi_clts      -    appletalk ddp   /dev/ddp        -" >> /etc/netconfig; \
#	fi
#	@echo "Installed Solaris kernel module"


#install:
#	@echo
#	@echo "To install the Solaris kernel module type 'make kinstall' as root user"

#uninstall:
#	@echo
#	@echo "To uninstall the Solaris kernel module type 'make kuninstall' as root user"

# copy and paste from automake Makefile.in
distdir : $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's|.|.|g'`; \
	list='$(DISTFILES)'; for file in $$list; do \
	  case $$file in \
	    $(srcdir)/*) file=`echo "$$file" | sed "s|^$$srcdirstrip/||"`;; \
	    $(top_srcdir)/*) file=`echo "$$file" | sed "s|^$$topsrcdirstrip/|$(top_builddir)/|"`;; \
	  esac; \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkdir_p) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
# end copy and paste

clean : sysclean

klean sysclean :
	rm -f a.out core* *.o *.bak *[Ee]rrs tags
	rm -f ddp

distclean: clean
	 -rm -f Makefile

maintainer-clean: distclean

depend :

check:

tags:

dvi:

installcheck:

install-exec:

# DO NOT DELETE THIS LINE

