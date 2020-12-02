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

void posiziona_navi(int matrice[][8])
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
			
			getchar(); // remove the \n character after the first scanf
			
			// scegliere il verso della nave
			
			printf("Scegli il verso della nave (su' = w, giu' = s, sinistra = a, destra = d) w/a/s/d?: ");
			scanf("%c",
			      &direzione);
			
			// trasformare lettera riga e numero colonna nei rispettivi indici della matrice
			
			riga = lettera_riga - 'a';
			colonna = numero_colonna - 1;
			
			// inserire nella matrice le caselle appartenenti alla nava, identificate attraverso la lunghezza della nave
			
			int conteggio2 = navi[i].dimensione;
			while(conteggio2 > 0)
			{
				matrice[riga][colonna] = navi[i].dimensione;
				if(direzione == 'w')
				{
					riga--;
				}
				else if(direzione == 's')
				{
					riga++;
				}
				else if(direzione == 'a')
				{
					colonna--;
				}
				else if(direzione == 'd')
				{
					colonna++;
				}
				conteggio2--;
			}
			stampa_matrice(matrice);
			
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
	int tabella[8][8];
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			tabella[i][j] = 0;
		}
	}
	/*{
		{0, 4, 4, 4, 4, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 0, 0, 0, 2, 0},
		{0, 3, 0, 0, 0, 0, 2, 0},
		{0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};*/
	stampa_matrice(tabella);
	posiziona_navi(tabella);
	return (0);
}