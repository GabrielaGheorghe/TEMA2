#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "utils.h"
#include "structures.h"

void delay(int number_of_seconds) 

{ 
	int mili_sec;
	clock_t timp_incepere;
    // Conversie in mili-secunde
    mili_sec = 1000 * number_of_seconds; 
  
    // Storing start time 
    timp_incepere = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < timp_incepere + mili_sec) 
        ; 
} 

int main(int args, char* arg[])

{

	FILE *file_in, *file_out;
	file_in = fopen(arg[1], "rt");
	file_out = fopen(arg[2], "wt");
	char line[256];
	int bandwidth;
	bandwidth = 1024;
	int index_tab = 0;
	int i;
	TLG first;
	char *command;
	TLG p;
	TLG current_tab = NULL;
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
	first = aux;
	int nr;
	p = first;

	if(file_in == NULL)
		printf("Fisierul de intrare nu a putut fi deschis\n");
	if(file_out == NULL)
		printf("Fisierul de iesire nu a putut fi deschis\n");
	if(file_in != NULL)
	{
		while(fgets(line, 256, file_in) != NULL)
		{
			char *rest = line;
			command = strtok_r(rest, "\n", &rest);
			char *first_word = strtok_r(command, " ", &command);
			if(strcmp(first_word, "newtab") == 0)
			{
				for(p = first; p->urm != NULL; p = p->urm);//parcurg lista pana ajung pe ultima celula diferita de null,adica p->urm == null
				p->urm = newtab(sizeof(T_tab));//adaug celula noua la sfarsit
				current_tab = p->urm;
			}
			else if(strcmp(first_word, "set_band") == 0)
			{
				bandwidth = atoi(command);
			}
			else if(strcmp(first_word, "print_open_tabs") == 0)
			{
				print_open_tabs(first);
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
			else if(strcmp(first_word, "goto") == 0)
			{

				delay(1); // intarziere cu o secunda
				T_tab *info_tab = (T_tab*)(current_tab->info);
				if(info_tab->current_page != NULL)
				{
				
					if(info_tab->back_stack == NULL) // daca este prima pagina accesata din acel tab
					{

						info_tab->back_stack = InitS(sizeof(web_page)); // creeaza stiva de back
						Push(info_tab->back_stack, info_tab->current_page); // adauga pagina curenta in stiva de back
						info_tab->current_page = CreatePage(command); // incarca o noua pagina in tab-ul curent
					}

					else
					{
						Push(info_tab->back_stack, info_tab->current_page); // adauga pagina curenta in stiva de back
						info_tab->current_page = CreatePage(command); // incarca o noua pagina in tab-ul curent	
					}
				}
				
				if(info_tab->current_page == NULL)
					info_tab->current_page = CreatePage(command);
			 // TStiva* s = (TStiva*)(info_tab->back_stack);
			 // nr = 0;
			 // TLG g;
			 // if(s->vf)
			 // 	nr++;
			 // printf("%d\n", nr);

			}
				
			
		}

	fclose(file_in);
	}
	
fclose(file_out);

return 0;
}
