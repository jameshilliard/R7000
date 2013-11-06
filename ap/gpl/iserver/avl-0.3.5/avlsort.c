/*****************************************************************************

    avlsort.c - Example program for the AVL-tree library.

    Copyright (C) 1998  Michael H. Buselli <cosine@cosine.org>
    Copyright (C) 2000-2002  Wessel Dankers <wsl@nl.linux.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA

*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "avl.h"

void avl_insert_always(avl_tree_t *avltree, void *item) {
	avl_node_t *newnode, *node;

	newnode = avl_init_node(malloc(sizeof(avl_node_t)), item);
	if(newnode) {
		switch(avl_search_closest(avltree, newnode->item, &node)) {
			case -1:
				avl_insert_before(avltree, node, newnode);
				return;
			case 0:
			case 1:
				avl_insert_after(avltree, node, newnode);
		}

	}
}

int main(int argc, char **argv) {
	avl_tree_t *t;
	avl_node_t *c;
	char *s, *n;
	char *ob, *bb, *eb;
	int r, bs;
	int l, u;
	struct stat st;
	int mmapped = 0;

	t = avl_alloc_tree((avl_compare_t)strcmp, NULL);

	u = 0;
	if(!fstat(STDIN_FILENO, &st) && S_ISREG(st.st_mode)) {
		bs = st.st_size;
		bb = eb = mmap(NULL, bs+1, PROT_READ|PROT_WRITE, MAP_PRIVATE, STDIN_FILENO, 0);
		if(bb) {
			mmapped = 1;
			eb = bb+bs;
		} else {
			bb = eb = malloc(bs+1);
			if(!bb) {
				perror("malloc()");
				exit(2);
			}
			while(bs > 0) {
				r = read(STDIN_FILENO, eb, bs);
				if(r <= 0) {
					perror("moo");
					exit(2);
				}
				eb += r;
				bs -= r;
			}
		}
	} else {
		bs = 65536; r = 0;
		bb = eb = ob = malloc(bs);
		if(!bb) {
			perror("malloc()");
			exit(2);
		}
		for(;;) {
			eb += r;
			r = read(STDIN_FILENO, eb, 65536);
			if(r < 0) {
				perror("moo");
				exit(2);
			}
			if(r == 0)
				break;
			bb = realloc(ob = bb, bs += r);
			if(!bb) {
				fprintf(stderr, "realloc() to %d bytes failed.\n", bs);
				exit(2);
			}
			if(bb != ob) {
				eb += bb - ob;
				u++;
			}
		}
	}

	if(*(eb-1) != '\n')
		*eb++ = '\n';
	bs = eb - bb;
	bb = s = mmapped?(ob=bb):realloc(ob = bb, bs);
	if(bb != ob)
		u++;
	eb = bb + bs;
	if(mmapped)
		fprintf(stderr, "Finished reading input (mmap()ed)\n");
	else
		fprintf(stderr, "Finished reading input (%d relocations)\n", u);

	l = 0;
	for(n = s = bb; s<eb; s = n) {
		n = strchr(n, '\n');
		*n++ = '\0';
		avl_insert_always(t, s);
		l++;
	}
	fprintf(stderr, "Inserted %d lines\n", l);

	l = 0;
	for(c = t->head; c; c = c->next) {
		puts(c->item);
		l++;
	}
	fprintf(stderr, "Wrote %d lines, depth %d\n", l, t->top?t->top->depth:0);

	for(; l; l--)
		avl_delete_node(t, t->top);
	if(!t->top) fprintf(stderr, "Deleted all lines\n");

	avl_free_nodes(t);

	return 0;
}
