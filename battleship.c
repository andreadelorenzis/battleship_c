#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMERO_NAVI 1

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
		2
	}/*,
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
	}*/
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
	printf("\n");
}

void stampa_tabella(char matrice[][8], int giocatore)
{
	printf("       -------------Player%d-------------\n",
		   giocatore);
	printf("       ---------------------------------\n");
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
	printf("\n");
}

void prendi_posizione(int *riga, int *colonna)
{
	char posizione[20];
	char lettera_riga;   
	int  numero_colonna;
	
	do
	{	
		scanf("%s", 
			  posizione);
		lettera_riga = posizione[0];
		numero_colonna = atoi(&posizione[1]);
		
		if(strlen(posizione) > 2                     ||
		   (lettera_riga < 97 || lettera_riga > 104) ||
		   (numero_colonna < 1 || numero_colonna > 8))
		{
			printf("Posizione non valida. Riprova: ");
		}
		else 
		{
			
			// trasformare lettera riga e numero colonna nei rispettivi indici della matrice
			
			*riga = lettera_riga - 'a';
			*colonna = numero_colonna - 1;	
		}
		//while(getchar() != '\n');
	}
	while((strlen(posizione) != 2)                  ||
		  (lettera_riga < 97 || lettera_riga > 104) ||
		  (numero_colonna < 1 || numero_colonna > 8));
}

void posiziona_navi(int matrice[][8], int giocatore)
{
	char risposta_continuazione = 's';
	
	for(int i = 0; i < NUMERO_NAVI; i++)
	{
		int  riga;		 
		int  colonna;     
		char direzione;
		int conteggio = navi[i].numero;	
		
		system("cls");
		stampa_disp_iniziale(matrice);
	
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
			getchar();
			
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
			system("cls");
			stampa_disp_iniziale(matrice);
			conteggio--;
		}
	}
				do{
				printf("Continuare? s/n?: ");
				scanf("%c", 
					  &risposta_continuazione);	
				if(risposta_continuazione != 's' && risposta_continuazione != 'n')
					printf("Valore non valido.\n");	
				while(getchar() != '\n');
			}
			while(risposta_continuazione != 's' && risposta_continuazione != 'n');
			if(risposta_continuazione == 'n')
			{
				// riazzerare tabella
				
				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						matrice[i][j] = 0;
					}
				}
				posiziona_navi(matrice, giocatore);
			}
			else 
				system("cls");
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

// controlla se il numero delle caselle colpite nella tabella colpi del player e uguale al numero delle caselle nave disposte. Se e' così, tutte le navi sono state affondate
// e restituisce 1, altrimenti 0.

int controlla_vittoria(char tabella[][8], int giocatore)
{
	// conto caselle nave dell'avversario colpite dal giocatore
	int caselle_nave_colpite = 0;
	int caselle_nave_totali = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(tabella[i][j] == 'c')
				caselle_nave_colpite++;
		}
	}
	// conto tutte le caselle appartententi ad una nave
	for(int i = 0; i < NUMERO_NAVI; i++)
	{
		caselle_nave_totali += navi[i].numero * navi[i].dimensione;
	}
	// comparo i 2 numeri
	if(caselle_nave_colpite == caselle_nave_totali)
	{
		system("cls");
		stampa_tabella(tabella, giocatore);
		printf("Partita finita! Player %d ha distrutto tutte le navi dell'avversario!\n",
			   giocatore);
		return 1;
	}
	return 0;
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
			tabella_p1[i][j] = 0;
			tabella_p2[i][j] = 0;
		}
	}

	posiziona_navi(disp_iniziale_p1, 1);
	posiziona_navi(disp_iniziale_p2, 2);
	
	while(!vittoria)
	{
		if(giocatore_corrente == 1)
		{
			stampa_tabella(tabella_p1, giocatore_corrente);
			spara_colpo(disp_iniziale_p2, tabella_p1, giocatore_corrente);
			stampa_tabella(tabella_p1, giocatore_corrente);
			vittoria = controlla_vittoria(tabella_p1, giocatore_corrente);
			printf("\n\n\n\n\n");
			giocatore_corrente = 2;
		}
		else
		{
			stampa_tabella(tabella_p2, giocatore_corrente);
			spara_colpo(disp_iniziale_p1, tabella_p2, giocatore_corrente);
			stampa_tabella(tabella_p2, giocatore_corrente);
			vittoria = controlla_vittoria(tabella_p2, giocatore_corrente);
			printf("\n\n\n\n\n");
			giocatore_corrente = 1;
		}
	}
	return (0);
}