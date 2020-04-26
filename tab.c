#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "utils.h"
#include "structures.h"


// initializare stiva

void *InitS(size_t d)
{
	ASt S;
	S = (ASt)malloc(sizeof(TStiva));
	if(!S)
		return NULL;
	S->dime = d;
	S->vf = NULL;
	return (void*)S;
}

// initializare coada

void *InitQ(size_t d)
{
	AQ Q;
	Q = (AQ)malloc(sizeof(TCoada));
	if(!Q)
		return NULL;
	Q->dime = d;
	Q->sc = NULL;
	Q->ic = NULL;
	return (void*)Q;
}

// inserare in coada vida

int InsQVida(void *Q, void *element)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = malloc(((TCoada*)Q)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, element, ((TCoada*)Q)->dime);
	aux->urm = NULL;
	((TCoada*)Q)->ic = aux;
	((TCoada*)Q)->sc = aux;
	return 1;
}

// inserare in coada nevida la final

int InsQNevida(void *Q, void *element)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = malloc(((TCoada*)Q)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	//aux->info = element;
	memcpy(aux->info, element, ((TCoada*)Q)->dime);
	aux->urm = NULL;
	((TCoada*)Q)->sc->urm = aux;
	((TCoada*)Q)->sc = aux;
	return 1;

}

// inserare in coada nevida la inceput

int InsQNevidaInc(void *Q, void *element)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = malloc(((TCoada*)Q)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, element, ((TCoada*)Q)->dime);
	aux->urm = ((TCoada*)Q)->ic;
	((TCoada*)Q)->ic = aux;
	return 1;
}

// inserarea in coada cu subcazuri de coada vida/nevida

int InsQ(void *Q, void *element)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = malloc(((TCoada*)Q)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, element, ((TCoada*)Q)->dime);
	aux->urm = NULL;
	if(((TCoada*)Q)->ic == NULL)
	{
		((TCoada*)Q)->ic = aux;
		((TCoada*)Q)->sc = aux;
	}
	else
	{
		((TCoada*)Q)->sc->urm = aux;
		((TCoada*)Q)->sc = aux;
	}
	return 1;
}

// extragere element din stiva

int ExtrQ(void *Q, void *el)
{
	TLG aux;
	aux = ((TCoada*)Q)->ic;
	((TCoada*)Q)->ic = aux->urm;
	memcpy(el, aux->info, ((TCoada*)Q)->dime);
	free(aux->info);
	free(aux);
	return 1;
}

// elimina toate elementele din coada

int ExtrLastQ(void *Q, void *el)
{
	TLG aux;
	aux = ((TCoada*)Q)->ic;
	((TCoada*)Q)->ic = aux->urm;
	memcpy(el, aux->info, ((TCoada*)Q)->dime);
	free(aux->info);
	free(aux);
	((TCoada*)Q)->ic = NULL;
	((TCoada*)Q)->sc = NULL;
	return 1;	
}

// adaugare element in stiva

int Push(void *S, void *element)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;
	aux->info = malloc(((TStiva*)S)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, element, ((TStiva*)S)->dime);
	aux->urm = ((TStiva*)S)->vf;
	((TStiva*)S)->vf = aux;
	return 1;
}

// extragere element din stiva

int Pop(void *S, void *element)
{
	memcpy(element, ((TStiva*)S)->vf->info, ((TStiva*)S)->dime);
	TLG aux = ((TStiva*)S)->vf;
	((TStiva*)S)->vf = aux -> urm;
	free(aux->info);
	free(aux);
	return 1;
}


// deschidere tab nou

TLG newtab(size_t d)
{

	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return NULL;
	aux->info = malloc(d);
	if(!aux->info)
	{
		free(aux);
		return NULL;
	}
	T_tab *info_tab = (T_tab*)(aux->info);
	info_tab->current_page = malloc(sizeof(web_page));
	if(!info_tab->current_page)
	{
		free(info_tab);
		free(aux);
		return NULL;
	}
	info_tab->current_page = NULL;
	info_tab->back_stack = NULL;
	info_tab->forward_stack = NULL;
	aux->urm = NULL;

return aux;
}

// printare tab-uri exiatente

void print_open_tabs(TLG first_tab, FILE *out)
{
	TLG p;
	int i = 0;
	for(p = first_tab, i = 0; p != NULL; p = p->urm, i++)
	{
		T_tab *info_tab = (T_tab*)(p->info);
		if(info_tab->current_page == NULL)
		{
			fprintf(out, "(%d: empty)\n", i);	
		}
		else
		{
			fprintf(out, "(%d: %s)\n", i, info_tab->current_page->url);
		}
	}
}

//creare pagina web

web_page *CreatePage(char *url)
{
	web_page *one_page = (T_webpage)malloc(sizeof(web_page));
	if(!one_page)
		return NULL;
	one_page->url = malloc(sizeof(100));
	if(!one_page->url)
	{
		free(one_page);
		return NULL;
	}
	strcpy(one_page->url, url);
	one_page->resources = get_page_resources(url, &one_page->num_res);
	return one_page;
}

// alocare celula de lista

TLG AlocaCelula(void *x)
{
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return NULL;
	aux->info = malloc(sizeof(Resource));
	if(!aux->info)
	{
		free(aux);
		return NULL;
	}
	memcpy(aux->info, x, sizeof(Resource));
	aux->urm = NULL;
	return aux;
}

// void ElibereazaStructPage(void *p)
// {
// 	web_page *page = (web_page*)p;
// 	free(page->url);
// 	free(page->resources);
// }

// void DistrugeLG(TLG *L, void(*ELimEL)(void*))
// {
// 	TLG p = *L;
// 	TLG aux;
// 	while(p != NULL)
// 	{
// 		aux = p;
// 		p = p->urm;
// 		ELimEL(aux->info);
// 		free(aux);
// 	}
// 	*L = NULL;
// }

// void ResetS(TStiva *s)
// {
// 	TLG l;
// 	l = s->vf;
// 	DistrugeLG(&l, ElibereazaStructPage);
// 	s->vf = NULL;
// }

void DelTab(void* x)
{

	T_tab* tab = (T_tab*)x;
	void *elem;
	elem  = malloc(sizeof(web_page));
	if(!elem)
		return;
	// if(!tab->current_page)
	// 	return;
	if(tab->current_page != NULL)
	{
	free(tab->current_page->url);
	free(tab->current_page->resources);
	free(tab->current_page);
	}

	if(tab->back_stack)
	{

		while(((TStiva*)tab->back_stack)->vf->urm)
		{
			elem  = malloc(sizeof(web_page));
			if(!elem)
				return;
		Pop(tab->back_stack, elem);
		free(elem);
		}
	free(((TStiva*)tab->back_stack)->vf);
	}

	if(tab->forward_stack)
	{
		while(((TStiva*)tab->forward_stack)->vf->urm)
		{
			elem  = malloc(sizeof(web_page));
			if(!elem)
				return;
		Pop(tab->forward_stack, elem);
		free(elem);
		}
	free(((TStiva*)tab->forward_stack)->vf);
	}
	free(tab->back_stack);
	free(tab->forward_stack);
}