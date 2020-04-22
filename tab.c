#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"
#include "structures.h"


// initializare stiva

// void *InitS(size_t d)
// {
// 	ASt S;
// 	S = (ASt)malloc(sizeof(TStiva));
// 	if(!S)
// 		return NULL;
// 	S->dime = d;
// 	S->vf = NULL;
// 	return (void*)S;
// }

// deschidere tab nou

TLG newtab(size_t d)
{

	//TLG p = *first;
	//TLG ultim = NULL;
	
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


	// if(p == NULL)
	// {
	// 	*first = aux;
	// }
	// if(p != NULL)
	// 	{

		// 	for(p = *first; p != NULL; p = p->urm)
		// 	{
		// 		if(p->urm == NULL)
		// 		{
					
		// 			ultim = p;
		// 		}
				
		// 	}
		// ultim->urm = aux;
		//}
return aux;
}

void print_open_tabs(TLG first_tab)
{
	TLG p;
	int i = 0;
	for(p = first_tab, i = 0; p != NULL; p = p->urm, i++)
	{
		T_tab *info_tab = (T_tab*)(p->info);
		if(info_tab->current_page == NULL)
		{
			printf("(%d: empty)\n", i);	
		}
		else
		{
			printf("(%d: %s)\n", i, info_tab->current_page->url);
		}

	}
}


// web_page *CreatePage(char *url)

// {
// 	web_page *one_page = (T_webpage)malloc(sizeof(web_page));
// 	if(!one_page)
// 		return NULL;
// 	one_page->url = malloc(sizeof(30));
// 	if(!one_page->url)
// 	{
// 		free(one_page);
// 		return NULL;
// 	}
// 	strcpy(one_page->url, url);
// 	one_page->resources = get_page_resources(url, &one_page->num_res);
// 	return one_page;
// }

// T_tab *Aloca_tab()
// {
// 	 T_tab *info_tab = malloc(sizeof(T_tab));
// 	if(!info_tab)
// 		return;
// 	info_tab->current_page = malloc(sizeof(web_page));
// 	if(!info_tab)
// 	{
// 		free(info_tab);
// 		return NULL;
// 	}

// }

// void go_to(TLG *current_tab, char *name_url)
// {
// 	T_tab *info_tab = malloc(sizeof(T_tab));
// 	if(!info_tab)
// 		return;
// 	info_tab = (T_tab*)((*current_tab)->info);
// 	//printf("aici\n");
// 	info_tab->current_page = malloc(sizeof(web_page));
// 	if(!info_tab->current_page)
// 		return;
// 	info_tab->current_page = CreatePage(name_url);
// }
