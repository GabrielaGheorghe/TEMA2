#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"
#include "structures.h"


int main(int args, char* arg[])

{

	FILE *file_in, *file_out;
	file_in = fopen(arg[1], "rt");
	file_out = fopen(arg[2], "wt");
	char line[256];
	int bandwidth;
	bandwidth = 1024;
	int index_tab = 0;
	int index_resource = 0;
	int i;
	TLG L = NULL;
	int number_resources;
	TLG first;
	char *command;
	TLG p;
	int nr_entries;
	web_page* old_current_page = malloc(sizeof(web_page));
	web_page* new_current_page = malloc(sizeof(web_page));
	
	TLG current_tab = NULL;
	void* queue = NULL;
	queue = InitQ(30);
	void* priorities_queue = NULL;
	priorities_queue = InitQ(sizeof(Resource));
	TCoada *coada = (TCoada*)priorities_queue;
	
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux)
		return 0;

	aux->info = malloc(sizeof(T_tab));
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	T_tab *info_tab = (T_tab*)(aux->info);
	info_tab->current_page = malloc(sizeof(web_page));
	if(!info_tab->current_page)
	{
		free(info_tab);
		free(aux);
		return 0;
	}
	info_tab->current_page = NULL;
	info_tab->back_stack = NULL;
	info_tab->forward_stack = NULL;
	aux->urm = NULL;
	aux->info = info_tab;
	first = aux;
	int nr;
	p = first;
	current_tab = p;
	int number_seconds;
	int long number_bytes;
	int long remaining_bytes;
	TLG auxiliar;

	if(file_in == NULL)
		printf("Fisierul de intrare nu a putut fi deschis\n");
	if(file_out == NULL)
		printf("Fisierul de iesire nu a putut fi deschis\n");
	if(file_in != NULL)
	{
		while(fgets(line, 256, file_in) != NULL)
		{
			//printf("%s", line);
			char *rest = line;
			command = strtok_r(rest, "\n", &rest);
			char *first_word = strtok_r(command, " ", &command);
			if(strcmp(first_word, "newtab") == 0)
			{
				for(p = first; p->urm != NULL; p = p->urm);// parcurg lista pana ajung pe ultima celula diferita de null,adica p->urm == null
				p->urm = newtab(sizeof(T_tab));// adaug celula noua la sfarsit
				current_tab = p->urm;
			}
			else if(strcmp(first_word, "set_band") == 0)
			{
				bandwidth = atoi(command);
			}
			else if(strcmp(first_word, "print_open_tabs") == 0)
			{
				print_open_tabs(first, file_out);
			}
			else if(strcmp(first_word, "change_tab") == 0)
			{
			index_tab = atoi(command);
			i = 0;
			for(p = first; p != NULL; p = p->urm)
			{
				if(index_tab == i)
				{
					current_tab = p;
				}
				i++;
			}	
			}
			else if(strcmp(first_word, "deltab") == 0)
			{

				TLG ant = NULL;
				for(p = first, ant = NULL; p->urm != NULL; ant = p, p = p -> urm);
	
				if(p == current_tab)
				{

					DelTab(p->info);		
					free(p);
					ant->urm = NULL;
					current_tab = ant;
					}
				else
					{		
					DelTab(p->info);
					free(p);
					ant->urm = NULL;
					}
									
			}
			else if(strcmp(first_word, "goto") == 0)
			{
				number_bytes = bandwidth;
				remaining_bytes = 0;
				TLG q = coada->ic;
				void *el = malloc(sizeof(Resource));
				TLG last_downloaded = NULL;

				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->current_page == NULL)
				{
							
				  info_tab->current_page = CreatePage(command);
				  InsQ(queue, info_tab->current_page->url);
				}

				else
				{
		
				if(info_tab->back_stack == NULL) // daca este prima pagina accesata din acel tab
				{	
					info_tab->back_stack = InitS(sizeof(web_page)); // creeaza stiva de back
					Push(info_tab->back_stack, info_tab->current_page); // adauga pagina curenta in stiva de back
					info_tab->current_page = CreatePage(command); // incarca o noua pagina in tab-ul curent
					InsQ(queue, info_tab->current_page->url);
				}
				else
				{
					Push(info_tab-> back_stack, info_tab->current_page); // adauga pagina curenta in stiva de back
					info_tab->current_page = CreatePage(command); // incarca o noua pagina in tab-ul curent	
					InsQ(queue, info_tab->current_page->url);
				}
				}


				for(q = coada->ic; q != NULL; ) // se incepe descarcarea resurselor
				{
					
					remaining_bytes = ((Resource*)q->info)->dimension - ((Resource*)q->info)->currently_downloaded;
					if(number_bytes >= remaining_bytes)
					{
						number_bytes = number_bytes - remaining_bytes;
						if(L == NULL)
						{
							auxiliar = AlocaCelula((Resource*)(q->info));
							if(!auxiliar)
								return 0;
							L = auxiliar;
							last_downloaded = auxiliar;
							if(coada->ic == coada->sc)
							{
								ExtrLastQ(coada, el);
							
							}
							else
							{
								ExtrQ(coada, el);
								
							}
						}

						else if(L != NULL)
						{
							auxiliar = AlocaCelula((Resource*)(q->info));
							if(!auxiliar)
								return 0;
							last_downloaded->urm = auxiliar;
							last_downloaded = auxiliar;
							printf("%s\n", ((Resource*)last_downloaded->info)->name);
							if(coada->ic == coada->sc)
							{
								ExtrLastQ(coada, el);
							}
							else
							{
								ExtrQ(coada, el);
							}
						}
					}
					else if(number_bytes < remaining_bytes)
					{
						remaining_bytes = remaining_bytes - number_bytes;
						((Resource*)(q->info))->currently_downloaded += number_bytes;
						number_bytes = 0;
					}

				if(number_bytes == 0)
					break;
				q = coada->ic;
				}
				//info_tab->forward_stack = InitS(sizeof(web_page));
				//golirea stivei de forward
		
				web_page *elem;
				if(info_tab->forward_stack)
				 {
					
				while(((TStiva*)info_tab->forward_stack)->vf)
				{
				 	elem  = malloc(sizeof(web_page));
				 	if(!elem)
				 		return 0;
				 	Pop(info_tab->forward_stack, elem);
				 	free(elem);
				}
				 free(((TStiva*)info_tab->forward_stack)->vf);
				}
			}
			else if(strcmp(first_word, "back") == 0)
			{
				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->back_stack != NULL)
				{
					 old_current_page = info_tab->current_page;
					 if(!old_current_page)
					 	return 0;
					if(info_tab->forward_stack == NULL)
					{
						info_tab->forward_stack = InitS(sizeof(web_page));
						Push(info_tab->forward_stack, old_current_page);
						Pop(info_tab->back_stack, info_tab->current_page);
					}
					else
					{
						Push(info_tab->forward_stack, old_current_page);
						Pop(info_tab->back_stack, info_tab->current_page);
					}
				}
				else
					printf("can't go back, no pages in stack.\n");
				
			}
			else if(strcmp(first_word, "forward") == 0)
			{
				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->forward_stack != NULL)
				{
					new_current_page = info_tab->current_page;
					if(!new_current_page)
						return 0;
					Pop(info_tab->forward_stack, info_tab->current_page);
					Push(info_tab->back_stack, new_current_page);
					
				}
					
				else
					printf("can't go forward, no pages in stack.\n");
			}
			else if(strcmp(first_word, "history") == 0)
			{
				TCoada *coada = (TCoada*)queue;
				TLG q = coada->ic;
				for(q = coada->ic; q != NULL; q = q->urm)
				{
				char *info = (char*)(q->info);
				fprintf(file_out, "%s\n", info);
				printf("history %s ",info);
				}
				printf("\n");
			}
			else if(strcmp(first_word, "del_history") == 0)
			{

				nr_entries = atoi(command);
				TCoada *history = (TCoada*)queue;
				if(!history->ic)
					return 0;
				TLG cap_lista = history->ic;
				nr = 0;
				int i;
				for(cap_lista = history->ic; cap_lista != NULL; cap_lista = cap_lista->urm)
					nr++; // nr de elemente din coada de istoric global
				if((nr_entries > 0) && (nr_entries < nr))
				{

					for(i = nr_entries; i > 0; i--)
					
					{
						void *el = malloc(30);
						ExtrQ(history, el);
						free(el);
					}

				}
				else if(nr_entries > nr)
				{

					void *last_elem = malloc(30);
					for(i = nr - 1; i > 0; i--)
					{
						void *el = malloc(30);
						ExtrQ(history, el);
						free(el);
					}
					ExtrLastQ(history, last_elem);
					free(last_elem);

				}
				 else
				{

					void *last_elem = malloc(30);
					for(i = nr_entries-1; i > 0; i--)
					
					{
						void *el = malloc(30);
						ExtrQ(history, el);
					
					}
				ExtrLastQ(history, last_elem);
			
				}
			
			}
			else if(strcmp(first_word, "list_dl") == 0)
			{
				int contor = 0;
				if(current_tab == NULL)
					return 0;
				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->current_page == NULL)
					return 0;
				web_page *one_page = info_tab->current_page;
				number_resources = one_page->num_res;
				for(contor = 0; contor < number_resources; contor++)
				{
					if(!one_page->resources)
						return 0;
					Resource *vector_resources =  one_page->resources;
					unsigned long size = vector_resources[contor].dimension;
					fprintf(file_out, "[%d - \"%s\" : %ld]\n", contor, vector_resources[contor].name, size);
				}
			}
			else if(strcmp(first_word, "download") == 0)
			{

				if(current_tab == NULL)
					return 0;
				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->current_page == NULL)
					return 0;
				web_page *one_page = info_tab->current_page;
				index_resource = atoi(command);
				number_resources = one_page->num_res;
				Resource* current_resource;
				current_resource = malloc(sizeof(Resource));
				if(!current_resource)
					return 0;
				memcpy(current_resource, &one_page->resources[index_resource], sizeof(Resource));
				int current_remaining_dimension = one_page->resources[index_resource].dimension - one_page->resources[index_resource].currently_downloaded;
				TCoada *priorities_queue_dowloads = (TCoada*)priorities_queue;

				if(priorities_queue_dowloads->ic == NULL) // inserare primul element din coada
				{
					InsQVida(priorities_queue_dowloads, current_resource);									
				}
				else if(((Resource*)(priorities_queue_dowloads->sc->info))->dimension - 
	   				   ((Resource*)(priorities_queue_dowloads->sc->info))->currently_downloaded <= current_remaining_dimension)
				{
					InsQNevida(priorities_queue_dowloads, current_resource);				
				}
				else if(((Resource*)(priorities_queue_dowloads->ic->info))->dimension -
				       ((Resource*)(priorities_queue_dowloads->ic->info))->currently_downloaded >= current_remaining_dimension)
				{
					InsQNevidaInc(priorities_queue_dowloads, current_resource);
				}
				else
				{
					for(p = priorities_queue_dowloads->ic; p != NULL; p = p->urm)
					{
						if((current_remaining_dimension > ((Resource*)(p->info))->dimension - ((Resource*)(p->info))->currently_downloaded)
						&& (current_remaining_dimension < ((Resource*)(p->urm->info))->dimension - ((Resource*)(p->urm->info))->currently_downloaded))
						{
							TLG aux = (TLG)malloc(sizeof(TCelulaG));
							if(!aux)
							return 0;
							aux->info = malloc((priorities_queue_dowloads)->dime);
							if(!aux->info)
							{
							free(aux);
							return 0;
							}							
							memcpy(aux->info, current_resource, priorities_queue_dowloads->dime);
							aux->urm = p->urm;
							p->urm = aux;
								
						}
					}
				}
				
			}
			else if(strcmp(first_word, "downloads") == 0)
			{
				if(current_tab == NULL)
					return 0;
				TCoada *coada = (TCoada*)priorities_queue;
				TLG q = coada->ic;
				for(q = coada->ic; q != NULL; q = q->urm)
				{
				fprintf(file_out, "[\"%s\" : %ld/%ld]\n", ((Resource*)q->info)->name, ((Resource*)q->info)->dimension - 
	           		                        ((Resource*)q->info)->currently_downloaded, ((Resource*)q->info)->dimension);
				}
				for( ; L != NULL; L = L->urm)
				{
					fprintf(file_out, "[\"%s\" : completed]\n", ((Resource*)L->info)->name);
				}
			}
			else if(strcmp(first_word, "wait") == 0)
			{
				number_seconds = atoi(command);
				number_bytes = number_seconds*bandwidth;
				remaining_bytes = 0;
				TLG q = coada->ic;
				void *el = malloc(sizeof(Resource));
				TLG last_downloaded = NULL;
				if(coada->ic == NULL)
					return 0;
				for(q = coada->ic; q != NULL; )
				{
					
					remaining_bytes = ((Resource*)q->info)->dimension - ((Resource*)q->info)->currently_downloaded;
					if(number_bytes >= remaining_bytes)
					{

						number_bytes = number_bytes - remaining_bytes;
						if(L == NULL)
						{
							auxiliar = AlocaCelula((Resource*)(q->info));
							if(!auxiliar)
								return 0;
							L = auxiliar;
							last_downloaded = auxiliar;
							if(coada->ic == coada->sc)
							{
								ExtrLastQ(coada, el);
								free(el);
							}
							else
							{
								ExtrQ(coada, el);
								free(el);
							}
						}

						else if(L != NULL)
						{
							auxiliar = AlocaCelula((Resource*)(q->info));
							if(!auxiliar)
								return 0;
							last_downloaded->urm = auxiliar;
							last_downloaded = auxiliar;
							if(coada->ic == coada->sc)
							{
								ExtrLastQ(coada, el);
							}
							else
							{
								ExtrQ(coada, el);
							}
						}
					}
					else if(number_bytes < remaining_bytes)
					{
						remaining_bytes = remaining_bytes - number_bytes;
						((Resource*)(q->info))->currently_downloaded += number_bytes;
						number_bytes = 0;
					}

				if(number_bytes == 0)
					break;
				q = coada->ic;
				}
			}
		}

	fclose(file_in);
	}
	
fclose(file_out);

return 0;
}