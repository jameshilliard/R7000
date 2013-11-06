.c.o:
	@echo "Compile $<:"
	@gcc -g -c -I../include -I- $<

.PHONEY:	default clean

default:	ihash thash tlist tmem tnotify turand

clean:
	rm -f ihash ihash.o
	rm -f thash thash.o
	rm -f tlist tlist.o
	rm -f tmem tmem.o
	rm -f tnotify tnotify.o
	rm -f turand turand.o

hasher:	hasher.o ../lib/libcsc.a
	gcc -g -o hasher hasher.o -L../lib -lcsc

hasher2:	hasher2.o ../lib/libcsc.a
	gcc -g -o hasher2 hasher2.o -L../lib -lcsc

ihash:	ihash.o ../lib/libcsc.a
	gcc -g -o ihash ihash.o -L../lib -lcsc

thash:	thash.o ../lib/libcsc.a
	gcc -g -o thash thash.o -L../lib -lcsc

tlist:	tlist.o ../lib/libcsc.a
	gcc -g -o tlist tlist.o -L../lib -lcsc

tmem:	tmem.o ../lib/libcsc.a
	gcc -g -o tmem tmem.o -L../lib -lcsc

tnotify:	tnotify.o ../lib/libcsc.a
	gcc -g -o tnotify tnotify.o -L../lib -lcsc

turand:	turand.o ../lib/libcsc.a
	gcc -g -o turand turand.o -L../lib -lcsc -lm
