###########################################################################
# Makefile for BPALogin v2.0
##


#
#	Foxconn Add : Steve Hsieh : 2005-10-14 (bpa porting)
#

# include $(TOP)/.config

##
# Install locations as determined by configure
#
# steve: reference the install operation in httpd:
# 	 these MACRO can be removed 
 
#prefix=@prefix@
#exec_prefix=@exec_prefix@
#SBINPATH=@sbindir@
#ETCPATH=@sysconfdir@

##
# Locations of system utilities as determined by configure
#
##

#CC=gcc              #use mipsel-cc
#CHKCONFIG=
#INSTALL=
SED=sed

##
# Flag : reference to httpd
#

#CFLAGS= -Wall 
#LIBS=
#LDFLAGS=

CFLAGS  += -I. -I$(TOP)/shared -I$(SRCBASE)/include -Wall
#CFLAGS += -g -DDEBUG
CFLAGS  += -s -O2
LDFLAGS += -L$(ROUTERDIR)/nvram -L$(INSTALLDIR)/nvram/usr/lib -lnvram

#
#	obj list
#
OBJS = bpalogin.o protocol.o transaction.o gen_md5.o unixmain.o


#
#	rule
#
bpalogin: $(OBJS) 
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $<

#clean:
#	rm -fr *.o
clean:
	rm -f *.o bpalogin


#distclean: clean
#	rm -f bpalogin config.log config.cache config.status Makefile bpalogin.h

#bpalogin.h: bpalogin.h.in
#	$(SED) 's#@@BPALOGIN_CONF@@#$(ETCPATH)/bpalogin.conf#' < bpalogin.h.in > bpalogin.h

$(OBJS): bpalogin.h

install: bpalogin
	install -D bpalogin $(TARGETDIR)/usr/sbin/bpalogin
	$(STRIP) $(TARGETDIR)/usr/sbin/bpalogin

#install: bpalogin bpalogin.init bpalogin.bsd
#	case `uname -s` in \
#	  Linux*) \
#	    mkdir -p $(RPM_BUILD_ROOT)$(ETCPATH)/rc.d/init.d ; \
#	    $(INSTALL) -m 755 bpalogin.init \
#	               $(RPM_BUILD_ROOT)$(ETCPATH)/rc.d/init.d/bpalogin ; \
#	    \
#	    if [ -z "$(RPM_BUILD_ROOT)" -a -x "$(CHKCONFIG)" ]; then \
#	      $(CHKCONFIG) --add bpalogin ; \
#	    fi ; \
#	    ;; \
#	  \
#	  FreeBSD*) \
#	    mkdir -p $(ETCPATH)/rc.d ; \
#	    $(INSTALL) -m 755 bpalogin.bsd $(ETCPATH)/rc.d/bpalogin.sh ; \
#	    ;; \
#	    \
#	  *) \
#	    echo "###" ; \
#	    echo "# You will need to add BPALogin to your startup scripts." ; \
#	    echo "###" ; \
#	    ;; \
#	esac ; \
#	
#	mkdir -p $(RPM_BUILD_ROOT)$(SBINPATH)
#	mkdir -p $(RPM_BUILD_ROOT)$(ETCPATH)
#	$(INSTALL) -m 755 bpalogin $(RPM_BUILD_ROOT)$(SBINPATH)
#	$(INSTALL) -m 600 bpalogin.conf $(RPM_BUILD_ROOT)$(ETCPATH)
