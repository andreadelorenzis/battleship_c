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

void stampa_disp_iniziale(int matrice[][8])
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

void stampa_tabella(char matrice[][8])
{
	printf("\n       ---------------------------------\n");
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 0)
				printf("       ");
			if(matrice[i][j] == 'c')
				printf("| X ");
			else if(matrice[i][j] == 'n')
				printf("| o ");
			else
				printf("|   ");
			
			if(j == 7)
				printf("|");
		}
		printf("\n       ---------------------------------\n");
	}
}

void prendi_posizione(int *riga, int *colonna)
{
	char posizione[20];
	char lettera_riga;   
	int  numero_colonna;
	
		scanf("%s", 
			  posizione);
		lettera_riga = posizione[0];
		numero_colonna = atoi(&posizione[1]);
		
		// trasformare lettera riga e numero colonna nei rispettivi indici della matrice
		
		*riga = lettera_riga - 'a';
		*colonna = numero_colonna - 1;
}

void posiziona_navi(int matrice[][8], int giocatore)
{
	for(int i = 0; i < NUMERO_NAVI; i++)
	{
		int  riga;		 
		int  colonna;     
		char direzione;
		int conteggio = navi[i].numero;	
	
		while(conteggio > 0)
		{
			// scegliere la casella di partenza della nave
			printf("Player %d posiziona %d %s: ",
					giocatore,
					conteggio,
					conteggio == 1 ? navi[i].nome_plurale : navi[i].nome_singolare);
			prendi_posizione(&riga, &colonna);
			getchar(); // remove the \n character after the first scanf
			
			// scegliere il verso della nave
			
			printf("Player %d scegli il verso della nave (su' = w, giu' = s, sinistra = a, destra = d) w/a/s/d?: ",
				   giocatore);
			scanf("%c",
			      &direzione);
			
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
			stampa_disp_iniziale(matrice);
			
			conteggio--;
		}
	}
}

void spara_colpo(int disp_iniziale[][8], char tabella[][8], int giocatore)
{
	int riga,
		colonna;
	printf("Player %d scegli la casella dove sparare il colpo: ",
		   giocatore);
	prendi_posizione(&riga, &colonna);
	if(disp_iniziale[riga][colonna] > 0)
		tabella[riga][colonna] = 'c';     // casella nave colpita
	else 
		tabella[riga][colonna] = 'n';	  // casella vuota colpita
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
	int disp_iniziale_p1[8][8];
	int disp_iniziale_p2[8][8];
	char tabella_p1[8][8];
	char tabella_p2[8][8];
	int giocatore_corrente = 1;
	
	int vittoria = 0;
	
	// inizializzare tabella di zeri
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			disp_iniziale_p1[i][j] = 0;
			disp_iniziale_p2[i][j] = 0;
		}
	}
	stampa_disp_iniziale(disp_iniziale_p1);
	posiziona_navi(disp_iniziale_p1, 1);
	stampa_disp_iniziale(disp_iniziale_p2);
	posiziona_navi(disp_iniziale_p2, 2);
	
	while(!vittoria)
	{
		if(giocatore_corrente == 1)
		{
			spara_colpo(disp_iniziale_p2, tabella_p1, giocatore_corrente);
			stampa_tabella(tabella_p1);
			giocatore_corrente = 2;
		}
		else
		{
			spara_colpo(disp_iniziale_p1, tabella_p2, giocatore_corrente);
			stampa_tabella(tabella_p2);
			giocatore_corrente = 1;
		}
	}
	return (0);
}