#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMERO_NAVI 4

struct nave
{
	char *nome_plurale;
	char *nome_singolare;
	int dimensione;
	int numero;
};

struct nave navi[] =
{
	{
		"portaerei",
		"portaerei",
		4,
		1
	},
	{
		"corazzata",
		"corazzate",
		3,
		2
	},
	{
		"incrociatore",
		"incrociatori",
		2,
		3
	},
	{
		"sommergibile",
		"sommergibili",
		1,
		2
	}
};

void stampa_matrice(int matrice[][8])
{
	printf("\n       ---------------------------------\n");
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 0)
				printf("       ");
			if(matrice[i][j] > 0)
				printf("| %d ", 
					   matrice[i][j]);
			else
				printf("|   ");
			
			if(j == 7)
				printf("|");
		}
		printf("\n       ---------------------------------\n");
	}
}

void posizione_navi(int matrice[][8])
{
	for(int i = 0; i < NUMERO_NAVI; i++)
	{
		int conteggio = navi[i].numero;
		char posizione[20]; 
		char lettera_riga;   
		int  numero_colonna;
		int  riga = -1;		 
		int  colonna = -1;     
		char direzione;
		
		while(conteggio > 0)
		{
			// scegliere la casella di partenza della nave
			
			printf("Posiziona %d %s: ",
				   conteggio,
				   conteggio == 1 ? navi[i].nome_plurale : navi[i].nome_singolare);
			scanf("%s", 
				  posizione);
			lettera_riga = posizione[0];
			numero_colonna = atoi(&posizione[1]);
			
			// scegliere il verso della nave
			
			printf("Scegli il verso della nave (sù = w, giù = s, sinistra = a, destra = d) w/a/s/d?: ");
			scanf("%c",
			      &direzione);
			
			// trasformare lettera riga e numero colonna nei rispettivi indici della matrice
			
			riga = lettera_riga - 'a';
			colonna = numero_colonna - 1;
			
			// inserire ogni casella appartenente alla nave nella matrice
			
			int conteggio2 = navi[i].numero;
			int i = riga;
			int j = colonna;
			while(conteggio2 > 0)
			{
				matrice[i][j] = navi[i].numero;
				if(direzione == 'w')
				{
					i--;
				}
				else if(direzione == 's')
				{
					i++;
				}
				else if(direzione == 'a')
				{
					j--;
				}
				else if(direzione == 'd')
				{
					j++;
				}
				conteggio2--;
			}
			
			conteggio--;
		}
	}
}


/*
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 4, 4, 4, 4, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
*/
int main(void)
{
	int tabella[8][8] = 
	{
		{0, 4, 4, 4, 4, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 0, 0, 0, 2, 0},
		{0, 3, 0, 0, 0, 0, 2, 0},
		{0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};
	stampa_matrice(tabella);
	posizione_navi(tabella);
	return (0);
}