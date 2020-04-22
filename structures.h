#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "utils.h"

#ifndef __STRUCTURES__
#define __STRUCTURES__

/* definire structuri utilizate */

// pagina web

typedef struct web_page
{
	char *url;
	int num_res;
	Resource *resources;
}web_page, *T_webpage;

// celula de lista generica

typedef struct celulag
{
	struct celulag *urm; // adresa urmatoarei celule
	void *info; //adresa informatiei
}TCelulaG, *TLG;

// stiva

typedef struct stiva
{
	size_t dime; // dimensiune element
	TLG vf; // adresa celulei din varf
}TStiva, *ASt;

// tab

typedef struct tab
{
	web_page *current_page;
	void *back_stack;
	void *forward_stack;	
}*t_tab, T_tab;




/* definire functii utilizate */

//void menu(char line[256], TLG first, int bandwidth, FILE *file_out);
TLG newtab(size_t d);
void print_open_tabs(TLG first_tab);
web_page *CreatePage(char *url);
void go_to(TLG *current_tab, char *name_url);

#endif