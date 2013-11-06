# -*- Makefile -*-

top_builddir := ..
builddir     := .
top_srcdir  := ..
srcdir      := .
ksourcedir  := /disk2/antony/R7000/GPL/V1.0.1.22/V1.0.1.22_1.0.15/components/opensource/linux/linux-2.6.36
prefix      := /disk2/antony/R7000/GPL/V1.0.1.22/V1.0.1.22_1.0.15/src/router/iptables-1.4.12/src/install
exec_prefix := ${prefix}
libdir      := ${exec_prefix}/lib
libexecdir  := ${exec_prefix}/libexec
xtlibdir    := ${exec_prefix}/lib/xtables

CC             := arm-brcm-linux-uclibcgnueabi-gcc
CCLD           := ${CC}
CFLAGS         := -Os -O2 -DBCMNVRAM -DBCMWPA2 -DRESTART_ALL_PROCESSES -D__CONFIG_USBAP__ -DBCMQOS -DBCMWPS -D__CONFIG_EMF__ -DTRAFFIC_MGMT_RSSI_POLICY -DPHYMON -DSUPPORT_REMOTE_HTTPS -DINCLUDE_WPS_V20 -DINCLUDE_5G_AUTO_CHANNEL -DOPENDNS_PARENTAL_CONTROL -DINCLUDE_ACCESSCONTROL -DINCLUDE_UCP -DU12H270 -DR7000 -DMULTIPLE_SSID -DENABLE_ML -DOPEN_SOURCE_SUPPORT -DBCM53125 -DBCM5301X -DCONFIG_RUSSIA_IPTV -DVIDEO_STREAMING_QOS -DDLNA -DHTTP_ACCESS_USB -DMAX_USB_ACCESS -DSAMBA_ENABLE -DUSB_NEW_SPEC -DINCLUDE_WIFI_BUTTON -DINCLUDE_USB_LED -DINCLUDE_DUAL_BAND -DSINGLE_FIRMWARE -DINCLUDE_GET_ST_CHKSUM -DUNIFIED_STR_TBL -DFIRST_MTD_ROTATION -DWIFI_ON_OFF_SCHE -DAUTO_CONN_24HR -DIGMP_PROXY -DAP_MODE -D__CONFIG_IGMP_SNOOPING__ -DLINUX26 -DINCLUDE_IPV6 -DPRESET_WL_SECURITY -DNEW_BCM_WPS_IPC -DSUPPORT_AC_MODE -DSTA_MODE -DPPP_RU_DESIGN -DEXT_ACS -DBCM_DCS -DEXT_ACS
CPPFLAGS       := 
LDFLAGS        := 
regular_CFLAGS := -Wall -Waggregate-return -Wmissing-declarations 	-Wmissing-prototypes -Wredundant-decls -Wshadow -Wstrict-prototypes 	-Winline -pipe
regular_CPPFLAGS := -D_LARGEFILE_SOURCE=1 -D_LARGE_FILES -D_FILE_OFFSET_BITS=64 -D_REENTRANT 	-DXTABLES_LIBDIR=\"${xtlibdir}\" -DXTABLES_INTERNAL
kinclude_CPPFLAGS :=  -I/disk2/antony/R7000/GPL/V1.0.1.22/V1.0.1.22_1.0.15/components/opensource/linux/linux-2.6.36/include -I/disk2/antony/R7000/GPL/V1.0.1.22/V1.0.1.22_1.0.15/components/opensource/linux/linux-2.6.36/include

AM_CFLAGS      := ${regular_CFLAGS}
AM_CPPFLAGS     = ${regular_CPPFLAGS} -I${top_builddir}/include -I${top_builddir} -I${top_srcdir}/include ${kinclude_CPPFLAGS}
AM_DEPFLAGS     = -Wp,-MMD,$(@D)/.$(@F).d,-MT,$@

ifeq (${V},)
AM_LIBTOOL_SILENT = --silent
AM_VERBOSE_CC     = @echo "  CC      " $@;
AM_VERBOSE_CCLD   = @echo "  CCLD    " $@;
AM_VERBOSE_CXX    = @echo "  CXX     " $@;
AM_VERBOSE_CXXLD  = @echo "  CXXLD   " $@;
AM_VERBOSE_AR     = @echo "  AR      " $@;
AM_VERBOSE_GEN    = @echo "  GEN     " $@;
endif

#
#	Wildcard module list
#
pfx_build_mod := $(patsubst ${srcdir}/libxt_%.c,%,$(sort $(wildcard ${srcdir}/libxt_*.c)))
 pf4_build_mod := $(patsubst ${srcdir}/libipt_%.c,%,$(sort $(wildcard ${srcdir}/libipt_*.c)))
 pf6_build_mod := $(patsubst ${srcdir}/libip6t_%.c,%,$(sort $(wildcard ${srcdir}/libip6t_*.c)))
pfx_build_mod := $(filter-out ,${pfx_build_mod})
pf4_build_mod := $(filter-out ,${pf4_build_mod})
pf6_build_mod := $(filter-out ,${pf6_build_mod})
pfx_objs      := $(patsubst %,libxt_%.o,${pfx_build_mod})
pf4_objs      := $(patsubst %,libipt_%.o,${pf4_build_mod})
pf6_objs      := $(patsubst %,libip6t_%.o,${pf6_build_mod})
pfx_solibs    := $(patsubst %,libxt_%.so,${pfx_build_mod})
pf4_solibs    := $(patsubst %,libipt_%.so,${pf4_build_mod})
pf6_solibs    := $(patsubst %,libip6t_%.so,${pf6_build_mod})


#
# Building blocks
#
targets := libext.a libext4.a libext6.a \
           matches4.man matches6.man \
           targets4.man targets6.man
targets_install :=
# libext_objs := ${pfx_objs}
# libext4_objs := ${pf4_objs}
# libext6_objs := ${pf6_objs}
 targets += ${pfx_solibs} ${pf4_solibs} ${pf6_solibs}
 targets_install += ${pfx_solibs} ${pf4_solibs} ${pf6_solibs}

.SECONDARY:

.PHONY: all install clean distclean FORCE

#all: ${targets} check
all: ${targets}

check: ${targets}
	@echo "  CHECK    unknown symbols in .so files"; \
	. ../libxtables/libxtables.la; \
	for i in lib*.so; do \
		[ "$$i" = "lib*.so" ] && continue; \
		LD_PRELOAD="$$dlname" LD_LIBRARY_PATH=../libxtables/.libs \
			ldd -r $$i 2>&1 >/dev/null; \
	done;

install: ${targets_install}
	@mkdir -p "${DESTDIR}${xtlibdir}";
	if test -n "${targets_install}"; then install -pm0755 $^ "${DESTDIR}${xtlibdir}/"; fi;

clean:
	rm -f *.o *.oo *.so *.a {matches,targets}[46].man initext.c initext4.c initext6.c;

distclean: clean
	rm -f .*.d .*.dd;

init%.o: init%.c
	${AM_VERBOSE_CC} ${CC} ${AM_CPPFLAGS} ${AM_DEPFLAGS} ${AM_CFLAGS} -D_INIT=$*_init ${CFLAGS} -o $@ -c $<;

-include .*.d


#
#	Shared libraries
#
lib%.so: lib%.oo
	${AM_VERBOSE_CCLD} ${CCLD} ${AM_LDFLAGS} -shared ${LDFLAGS} -o $@ $< ${$*_LIBADD};

lib%.oo: ${srcdir}/lib%.c
	${AM_VERBOSE_CC} ${CC} ${AM_CPPFLAGS} ${AM_DEPFLAGS} ${AM_CFLAGS} -D_INIT=lib$*_init -DPIC -fPIC ${CFLAGS} -o $@ -c $<;

# Need the LIBADDs in iptables/Makefile.am too for libxtables_la_LIBADD
xt_RATEEST_LIBADD   = -lm
xt_statistic_LIBADD = -lm


#
#	Static bits
#
#	If static building is disabled, libext*.a will still be generated,
#	but will be empty. This is good since we can do with less case
#	handling code in the Makefiles.
#
lib%.o: ${srcdir}/lib%.c
	${AM_VERBOSE_CC} ${CC} ${AM_CPPFLAGS} ${AM_DEPFLAGS} ${AM_CFLAGS} -DNO_SHARED_LIBS=1 -D_INIT=lib$*_init ${CFLAGS} -o $@ -c $<;

libext.a: initext.o ${libext_objs}
	${AM_VERBOSE_AR} ${AR} crs $@ $^;

libext4.a: initext4.o ${libext4_objs}
	${AM_VERBOSE_AR} ${AR} crs $@ $^;

libext6.a: initext6.o ${libext6_objs}
	${AM_VERBOSE_AR} ${AR} crs $@ $^;

initext_func  := $(addprefix xt_,${pfx_build_mod})
initext4_func := $(addprefix ipt_,${pf4_build_mod})
initext6_func := $(addprefix ip6t_,${pf6_build_mod})

.initext.dd: FORCE
	@echo "${initext_func}" >$@.tmp; \
	cmp -s $@ $@.tmp || mv $@.tmp $@; \
	rm -f $@.tmp;

.initext4.dd: FORCE
	@echo "${initext4_func}" >$@.tmp; \
	cmp -s $@ $@.tmp || mv $@.tmp $@; \
	rm -f $@.tmp;

.initext6.dd: FORCE
	@echo "${initext6_func}" >$@.tmp; \
	cmp -s $@ $@.tmp || mv $@.tmp $@; \
	rm -f $@.tmp;

initext.c: .initext.dd
	${AM_VERBOSE_GEN}
	@( \
	echo "" >$@; \
	for i in ${initext_func}; do \
		echo "extern void lib$${i}_init(void);" >>$@; \
	done; \
	echo "void init_extensions(void);" >>$@; \
	echo "void init_extensions(void)" >>$@; \
	echo "{" >>$@; \
	for i in ${initext_func}; do \
		echo  " ""lib$${i}_init();" >>$@; \
	done; \
	echo "}" >>$@; \
	);

initext4.c: .initext4.dd
	${AM_VERBOSE_GEN}
	@( \
	echo "" >$@; \
	for i in ${initext4_func}; do \
		echo "extern void lib$${i}_init(void);" >>$@; \
	done; \
	echo "void init_extensions4(void);" >>$@; \
	echo "void init_extensions4(void)" >>$@; \
	echo "{" >>$@; \
	for i in ${initext4_func}; do \
		echo  " ""lib$${i}_init();" >>$@; \
	done; \
	echo "}" >>$@; \
	);

initext6.c: .initext6.dd
	${AM_VERBOSE_GEN}
	@( \
	echo "" >$@; \
	for i in ${initext6_func}; do \
		echo "extern void lib$${i}_init(void);" >>$@; \
	done; \
	echo "void init_extensions6(void);" >>$@; \
	echo "void init_extensions6(void)" >>$@; \
	echo "{" >>$@; \
	for i in ${initext6_func}; do \
		echo " ""lib$${i}_init();" >>$@; \
	done; \
	echo "}" >>$@; \
	);

#
#	Manual pages
#
ex_matches = $(shell echo ${1} | LC_ALL=POSIX grep -Eo '\b[[:lower:][:digit:]_]+\b')
ex_targets = $(shell echo ${1} | LC_ALL=POSIX grep -Eo '\b[[:upper:][:digit:]_]+\b')
man_run    = \
	${AM_VERBOSE_GEN} \
	for ext in $(sort ${1}); do \
		f="${srcdir}/libxt_$$ext.man"; \
		cf="${srcdir}/libxt_$$ext.c"; \
		if [ -f "$$f" ] && grep -Eq "$(3)|NFPROTO_UNSPEC" "$$cf"; then \
			echo -e "\t+ $$f" >&2; \
			echo ".SS $$ext"; \
			cat "$$f" || exit $$?; \
			continue; \
		fi; \
		f="${srcdir}/lib$(2)t_$$ext.man"; \
		if [ -f "$$f" ]; then \
			echo -e "\t+ $$f" >&2; \
			echo ".SS $$ext"; \
			cat "$$f" || exit $$?; \
			continue; \
		fi; \
	done >$@;

matches4.man: .initext.dd .initext4.dd $(wildcard ${srcdir}/lib*.man)
	$(call man_run,$(call ex_matches,${pfx_build_mod} ${pf4_build_mod}),ip,NFPROTO_IPV4)

matches6.man: .initext.dd .initext6.dd $(wildcard ${srcdir}/lib*.man)
	$(call man_run,$(call ex_matches,${pfx_build_mod} ${pf6_build_mod}),ip6,NFPROTO_IPV6)

targets4.man: .initext.dd .initext4.dd $(wildcard ${srcdir}/lib*.man)
	$(call man_run,$(call ex_targets,${pfx_build_mod} ${pf4_build_mod}),ip,NFPROTO_IPV4)

targets6.man: .initext.dd .initext6.dd $(wildcard ${srcdir}/lib*.man)
	$(call man_run,$(call ex_targets,${pfx_build_mod} ${pf6_build_mod}),ip6,NFPROTO_IPV6)
