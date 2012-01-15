#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "decider.h"

static struct monitor *r0, *r1, *r2, *c0, *c1, *c2, *d1, *d2;


void init_monitor(struct monitor *m) {
	m->count = 0;
	m->valid = 1;
	m->value = '\0';
}


/*
 * Initializes game by setting up monitors to
 * determine winners
 */
void game_init(){
	//extern void init_monitor(struct monitor*);	

	struct monitor g;
	init_monitor(&g);

	//Set up monitors for each row, column and diagonals
	r0 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(r0);
	
	r1 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(r1);
	
	r2 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(r2);
	
	c0 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(c0);

	c1 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(c1);	

	c2 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(c2);	

	d1 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(d1);	

	d2 = (struct monitor*)malloc(sizeof(struct monitor));
	init_monitor(d2);
}


/*
 * Determines winner
 */
int check_winner(int x, int y, char c){
	struct monitor *row, *col, *diag1, *diag2;
	int da = 0, db = 0;
	
	//get row, column or diagonal	
	if (x == 0) {
		row = r0;
		if (y == 0) {
			diag1 = d1;
			da = 1;
		}
	}
	else if (x == 1) {
		row = r1;
		if (y == 1) {
			diag1 = d1;
			da = 1;
		}
	}
	else {
		row = r2;
		if (y == 2) {
			diag1 = d1;
			da = 1;
		}
	}
	if (y == 0) {
		col = c0;
		if (x == 2) {
			diag2 = d2;
			db = 1;
		}
	}
	else if (y == 1) {
		col = c1;
		if (x == 1) {
			diag2 = d2;
			db = 1;
		}
	}
	else {
		col = c2;
		if (x == 0) {
			diag2 = d2;
 			db = 1;
		}
	}
	
	//validate
	if (row->valid == 0 && col->valid == 0) {
		if (da == 1) 
			if (diag1->valid == 0)
				if (db == 1)
					if (diag2->valid == 0)
						return 0;
	}
	//possibility of finding winner, update rows, columns and diags
	if (row->value == '\0') {
		row->value = c;
		row->count++;
	}
	else {
		if (row->value == c) {
			if (row->count++ == 2)
				return 1;
		}
		else
			row->valid = 0;
	}
	if (col->value == '\0') {
		col->value = c;
		col->count++;
	}
	else {
		if (col->value == c) {
			if (col->count++ == 2)
				return 1;
		}
		else
			col->valid = 0;
	}
	
	if (da == 1) {
		if (diag1->value == '\0') {
			diag1->value = c;
			diag1->count++;
	}
	else {
		if (diag1->value == c) {
			if (diag1->count++ == 2)
				return 1;
		}
		else
			diag1->valid = 0;
		}
	}

	if (db == 1) {
		if (diag2->value == '\0') {
			diag2->value = c;
			diag2->count++;
	}
	else {
		if (diag2->value == c) {
			if (diag2->count++ == 2)
				return 1;
		}
		else
			diag2->valid = 0;
		}
	}
	return 0;
}
