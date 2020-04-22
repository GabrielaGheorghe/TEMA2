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

// void menu(char line[256], TLG first, int bandwidth, FILE *file_out)

// {
// 	int len;
// 	len = strlen(line);
// 	char *command;
// 	int i;
// 	int index_tab;
// 	char *rest = line;
// 	TLG p, current_tab;
// 	int nr = 0;

	// command = strtok_r(rest, " ", &rest);
	// if ( line[len - 1] == '\n') {  //eliminare '\n' de la sfarsitul liniei citite 
	// 	line[len - 1] = '\0';
	// 	len --;
	// }
	// if(strcmp(command, "newtab") == 0)
	// {
	// 	newtab(&first, sizeof(T_tab));
	// 	for(p = first; p != NULL; p=p->urm){
	// 		if(p->urm == NULL)
	// 		{
	// 			current_tab = p;
	// 		}
	// 	}

		
	// 	//fputs(command, file_out);
	//  }
	
	// else if(strcmp(command, "set_band") == 0)
	// {
	// 	bandwidth = atoi(rest);
	// }
	// else if(strcmp(command, "print_open_tabs") == 0)
	// {
	// 	print_open_tabs(&first);
	// }
	// else if(strcmp(command, "change_tab") == 0)
	// {
	// 		for(p = first; p != current_tab; p=p->urm)
	// 		nr++;
		
	// 	printf("%d\n", nr);

	// 	index_tab = atoi(rest);
	// 	for(p = first, i = 0; p != NULL; p = p->urm, i++)
	// 	{
	// 		if(index_tab == i)
	// 		{
	// 			current_tab = p;
	// 		}
	// 	}
		
	// }

	// else if(strcmp(command,"goto") == 0)
	// {
	// 	for(p = first; p != current_tab; p=p->urm)
	// 		nr++;
	// 	printf("%d\n", nr);
	// }

//}
	// T_tab *info_tab =(T_tab*)current_tab->info;
	// printf("aici\n");
	// info_tab->current_page = CreatePage(rest);
	// 	for(p = first; p != current_tab; p=p->urm)
	// 		nr++;
	// 	printf("%d\n", nr);
	// }
//}


int main(int args, char* arg[])

{

	FILE *file_in, *file_out;
	file_in = fopen(arg[1], "r");
	file_out = fopen(arg[2], "w");
	char line[256];
	int bandwidth = 1024;
	TLG first;
	int len;
	len = strlen(line);
	char *command;
	//int i;
	//int index_tab = 0;
	TLG p;
	//TLG current_tab = NULL;
	int nr = 0;

	//newtab(&first, sizeof(T_tab));

	//TLG p = *first;
	//TLG ultim = NULL;
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
	p = first;

	if(file_in == NULL)
		printf("Fisierul de intrare nu a putut fi deschis\n");
	if(file_out == NULL)
		printf("Fisierul de iesire nu a putut fi deschis\n");
	if(file_in != NULL)
	{
		while(fgets(line, 256, file_in) != NULL)
		{
			
			//fputs(line[0], file_out);
			char *rest = line;
			command = strtok_r(rest, " ", &rest);
			if ( line[len - 1] == '\n') {  //eliminare '\n' de la sfarsitul liniei citite 
				line[len - 1] = '\0';
				len --;
			}
		//	printf("%s\n", command);
			if(strcmp(command, "newtab") == 0)
			{
			
				for(p = first; p != NULL; p = p->urm);
					p->urm = newtab(sizeof(T_tab));
				
				for(p = first; p != NULL; p=p->urm)
					nr++;
				printf("%d\n", nr);
			}

				// for(p = first; p != NULL; p=p->urm)
				// 	nr++;
				// printf("%d\n", nr);
		
		//fputs(command, file_out);
		 
			// else if(strcmp(command, "set_band") == 0)
			// {
			// 	bandwidth = atoi(rest);
			// }
			// else if(strcmp(command, "print_open_tabs") == 0)
			// {
			// 	print_open_tabs(first);
			// }
			// else if(strcmp(command, "change_tab") == 0)
			// {
			// 	// for(p = first; p != current_tab; p=p->urm)
			// 	// nr++;
		
			// 	// printf("%d\n", nr);

			// index_tab = atoi(rest);
			// for(p = first, i = 0; p != NULL; p = p->urm, i++)
			// {
			// 	if(index_tab == i)
			// 	{
			// 		current_tab = p;
			// 	}
			// }
		
			// }
		}

	fclose(file_in);
	}
	
fclose(file_out);

return 0;
}

