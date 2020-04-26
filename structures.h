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

// coada

typedef struct coada
{
	size_t dime;
	TLG ic, sc;
}TCoada, *AQ;

// tab

typedef struct tab
{
	web_page *current_page;
	void *back_stack;
	void *forward_stack;	
}*t_tab, T_tab;




/* definire functii utilizate */

void *InitS(size_t d);
void *InitQ(size_t d);
int InsQ(void *Q, void *element);
int InsQVida(void *Q, void *element);
int InsQNevida(void *Q, void *element);
int InsQNevidaInc(void *Q, void *element);
int Push(void *S, void *element);
int ExtrQ(void *Q, void *el);
int ExtrLastQ(void *Q, void *el);
int Pop(void *S, void *element);
TLG newtab(size_t d);
void print_open_tabs(TLG first_tab, FILE *out);
web_page *CreatePage(char *url);
TLG AlocaCelula(void *x);
//void ElibereazaStructPage(void *p);
void DelTab(void* x);
// void DistrugeLG(TLG *L, void(*ELimEL)(void*));
// void ResetS(TStiva *s);

#endif