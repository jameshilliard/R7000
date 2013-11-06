# You may select DEPTHs (no indexing), COUNTs (slower) or both (more memory).
#CPPFLAGS += -DAVL_COUNT -DAVL_DEPTH

LN ?= ln
INSTALL ?= /usr/bin/install
LDCONFIG ?= /sbin/ldconfig

# Some suggestions: (-mcpu= generates i386 compatible code)
CFLAGS ?= -O2 -fomit-frame-pointer -pipe -mcpu=i686 -w
#CFLAGS = -O2 -fomit-frame-pointer -pipe -march=i586 -Wall -g
#CFLAGS = -O6 -fomit-frame-pointer -pipe -march=i586 -Wall -ansi -pedantic
#CFLAGS = -O6 -fomit-frame-pointer -pipe -march=i686 -Wall -ansi -pedantic
#CFLAGS = -O6 -march=k6 -fforce-mem -fforce-addr -pipe
#CFLAGS = -g -fomit-frame-pointer -pipe -march=i686 -Wall -ansi -pedantic
#CFLAGS = -g -pg -a -pipe -march=i686 -Wall
#LDFLAGS = -s

prefix ?= /usr/local
libdir ?= $(prefix)/lib
includedir ?= $(prefix)/include
includedir ?= /usr/include

PROGRAMS = avlsort setdiff
LIBRARY = libavl.so.1.5

all: $(LIBRARY)

test: $(PROGRAMS)

setdiff: setdiff.o avl.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

avlsort: avlsort.o avl.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(LIBRARY): avl.o
	$(CC) -nostdlib -shared -Wl,-soname,libavl.so.1 $^ -o $@ -lc

clean:
	$(RM) *.o $(PROGRAMS) libavl.*

install: all
	$(INSTALL) -d $(DESTDIR)$(libdir)
	$(INSTALL) avl.h $(DESTDIR)$(includedir)
	$(INSTALL) $(LIBRARIES) $(DESTDIR)$(libdir)
	for i in $(LIBRARIES); do\
		$(LN) -sf $$i $(DESTDIR)$(libdir)/$${i%.*};\
		$(LN) -sf $${i%.*} $(DESTDIR)$(libdir)/$${i%.*.*};\
	done
	-$(LDCONFIG)

.PHONY: clean install all
.PRECIOUS: %.h %.c
