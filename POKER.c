#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int F;
int scor[11];//Vector folosit pentru a retine cate puncte are mana fiecarui jucator 
int index[11];//Vector folosit pentru a retine numarul jucatorilor
int h[100];//Vector folosit in caz ca doi sau mai multi jucatori au aceeasi mana, in acest vector calculez in scor propriu pentru a ierarhiza manile de poker
int nivel = 0;//Folosit drept nivel al stivei cand folosesc backtracking 
int nCD, nDD;//Numar de carti community cards si dead cards
int i;
int nPlayer1, nPlayer2, nPlayer3, nPlayer4, nPlayer5, nPlayer6, nPlayer7, nPlayer8, nPlayer9, nPlayer10;//Numarul de carti din mana fiecarui jucator
nPlayer1 = -1; //Initializare
nPlayer2 = -1;
nPlayer3 = -1;
nPlayer4 = -1;
nPlayer5 = -1;
nPlayer6 = -1;
nPlayer7 = -1;
nPlayer8 = -1;
nPlayer9 = -1;
nPlayer10 = -1;

nCD = -1;
nDD = -1;
int A[100];//Acest vector este folosit in scop ajutator pentru a realiza combinatiile de carti
int st[100];//Pe acest vector il folosesc pentru a realiza combinari de n ( cate community cards am ) luate cate 5
char handCpy[100];
typedef struct
{
	int val;
	char denum[10];
	char categ[10];
}carte;

carte comunityCards[5];
carte deadCards[5];
carte playerOne[10]; carte cpyPlayerOne[10]; int maxPlayer1 = 0; char handP1[100]; int newMax = 0; //playerOne reprezinta toate cartile pe care le poate folosi jucator 1, in cpyPlayerOne se va copia cea mai buna mana, maxPlayer1 reprezinta scorul mainii de poker, iar handP1 reprezinta mana propriu-zisa
carte playerTwo[10]; carte cpyPlayerTwo[10]; int maxPlayer2 = 0; char handP2[100];
carte playerThree[10]; carte cpyPlayerThree[10]; int maxPlayer3 = 0; char handP3[100];
carte playerFour[10]; carte cpyPlayerFour[10]; int maxPlayer4 = 0; char handP4[100];
carte playerFive[10]; carte cpyPlayerFive[10]; int maxPlayer5 = 0; char handP5[100];
carte playerSix[10]; carte cpyPlayerSix[10]; int maxPlayer6 = 0; char handP6[100];
carte playerSeven[10]; carte cpyPlayerSeven[10]; int maxPlayer7 = 0; char handP7[100];
carte playerEight[10]; carte cpyPlayerEight[10]; int maxPlayer8 = 0; char handP8[100];
carte playerNine[10]; carte cpyPlayerNine[10]; int maxPlayer9 = 0; char handP9[100];
carte playerTen[10]; carte cpyPlayerTen[10]; int maxPlayer10 = 0; char handP10[100];



int valid()    //Functie valid specifica generarii combinariilor
{ 
	for (int i = 0; i < nivel; i++)
		if (st[i] >= st[nivel])
			return 0;
	return 1;
}


void bt(int nPlayer, int* maxPlayer, carte* player, carte* cpyPlayer, char hand[100]) // In functia bt se genereaza toate combinariile posibile ale cartilor
{
	nivel = 0;
	int i = 0;
	st[nivel] = A[i];
	while (nivel > -1) 
	{
		int as = 1;
		int ev = 0;
		while (as == 1 && ev == 0) 
		{
			if (i <= nPlayer)
			{
				as = 1;
				st[nivel] = A[i++];
				ev = valid();
			}
			else
			{
				as = 0;
			}
		}
		if (as)
			if (nivel == 4)
			{

				newMax = pokerHand(player, cpyPlayer, *maxPlayer);//Verific noua mana de poker 
				*maxPlayer = newMax;//In caz ca este mai buna aceasta pentru jucator
				strcpy(hand, handCpy);

			}
			else 
			{ 
				nivel++; i = -1; st[nivel] = A[i++]; 
			}
		else 
		{
			nivel--;
			int j;
			int cont = 0;
			for (j = 0; j < nPlayer; j++)//Cand se revine pe nivelul anterior trebuie gasit elementul care a fost pe acest nivel prima data, pentru a nu intra in loop infinit
			{
				if (st[nivel] == A[j])
				{
					while (st[nivel] == A[j + cont])
						cont++;
					i = j + cont;
					break;
				}
			}
		}

	}

}


void adaugare(carte* mg, int* a)//adauga o carte in mana jucatorului
{
	(*a)++;
	printf("Carte: ");
	scanf("%s", (mg + *a)->denum);
	printf("Categorie: ");
	scanf("%s", (mg + *a)->categ);
	if (strcmp((mg + *a)->denum, "2") == 0)(mg + *a)->val = 2;
	if (strcmp((mg + *a)->denum, "3") == 0)(mg + *a)->val = 3;
	if (strcmp((mg + *a)->denum, "4") == 0)(mg + *a)->val = 4;
	if (strcmp((mg + *a)->denum, "5") == 0)(mg + *a)->val = 5;
	if (strcmp((mg + *a)->denum, "6") == 0)(mg + *a)->val = 6;
	if (strcmp((mg + *a)->denum, "7") == 0)(mg + *a)->val = 7;
	if (strcmp((mg + *a)->denum, "8") == 0)(mg + *a)->val = 8;
	if (strcmp((mg + *a)->denum, "9") == 0)(mg + *a)->val = 9;
	if (strcmp((mg + *a)->denum, "10") == 0)(mg + *a)->val = 10;
	if (strcmp((mg + *a)->denum, "J") == 0)(mg + *a)->val = 11;
	if (strcmp((mg + *a)->denum, "Q") == 0)(mg + *a)->val = 12;
	if (strcmp((mg + *a)->denum, "K") == 0)(mg + *a)->val = 13;
	if (strcmp((mg + *a)->denum, "A") == 0)(mg + *a)->val = 14;
}




void afisareCarte(carte* mg, int a)
{
	printf("%s - %s ", (mg + a)->denum, (mg + a)->categ);
}

void inserare(carte* mg, carte* as, int* n, int i)//Subprogram folosit pentru a adauga cartile community cards in mana unui jucator
{
	(*n)++;
	strcpy((mg + *n)->denum, (as + i)->denum);
	strcpy((mg + *n)->categ, (as + i)->categ);
	(mg + *n)->val = (as + i)->val;
}

void swap(carte* a, carte* b)//Subprogram folosit pentru sortare
{
	carte* aux; 
	aux = (carte*)malloc(sizeof(carte));
	strcpy(aux->denum, a->denum);
	strcpy(aux->categ, a->categ);
	aux->val = a->val;

	strcpy(a->denum, b->denum);
	strcpy(a->categ, b->categ);
	a->val = b->val;

	strcpy(b->denum, aux->denum);
	strcpy(b->categ, aux->categ);
	b->val = aux->val;
}


void sortare(carte* V, int a)//Subprogram folosit pentru a sorta cartile crescator, pentru a usura aflarea celei mai bune maini
{
	int ok = 1;
	int i;
	while (ok)
	{
		ok = 0;
		for (i = 0; i < a; i++)
		{
			if ((V + i)->val > (V + i + 1)->val)
			{
				ok = 1;
				swap((V + i), (V + i + 1));
			}
		}
	}
}

void init(int a)//Initializeaza vectorul A
{
	int i;
	for (i = 0; i <= a; i++)
		A[i] = i;
}

int highcard(carte* playera, carte* playerb)//Folosit pentru a afla castigatorul intr-un caz special cand sunt 2 jucatori cu aceeasi mana 
{
	int i = 4;
	while (i >= 0)
	{
		if ((playera + i)->val < (playerb + i)->val)
			return -1;
		else if ((playera + i)->val > (playerb + i)->val)
			return 1;
		i--;
	}
	return 0;
}


int pokerHand(carte* player, carte* cpyPlayer, int maxPlayer)//Subprogram folosit pentru a identifica o mana de poker
{
	if (//Verific daca e ROYAL FLUSH
		strcmp((player + st[0])->denum, "10") == 0 &&
		strcmp((player + st[1])->denum, "J") == 0 &&
		strcmp((player + st[2])->denum, "Q") == 0 &&
		strcmp((player + st[3])->denum, "K") == 0 &&
		strcmp((player + st[4])->denum, "A") == 0 &&
		strcmp((player + st[0])->categ, (player + st[1])->categ) == 0 &&
		strcmp((player + st[2])->categ, (player + st[3])->categ) == 0 &&
		strcmp((player + st[4])->categ, (player + st[0])->categ) == 0
		)
	{
		(maxPlayer) = 10;
		strcpy(handCpy, "ROYAL FLUSH");
		strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
		strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
		(cpyPlayer + 0)->val = (player + st[0])->val;

		strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
		strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
		(cpyPlayer + 1)->val = (player + st[1])->val;

		strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
		strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
		(cpyPlayer + 2)->val = (player + st[2])->val;

		strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
		strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
		(cpyPlayer + 3)->val = (player + st[3])->val;

		strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
		strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
		(cpyPlayer + 4)->val = (player + st[4])->val;
		return maxPlayer;
	}

	if (//Verific daca e STRAIGHT FLUSH
		((player + st[0])->val == (player + st[1])->val - 1 &&
			(player + st[1])->val == (player + st[2])->val - 1 &&
			(player + st[2])->val == (player + st[3])->val - 1 &&
			(player + st[3])->val == (player + st[4])->val - 1 &&
			strcmp((player + st[0])->categ, (player + st[1])->categ) == 0 &&
			strcmp((player + st[1])->categ, (player + st[2])->categ) == 0 &&
			strcmp((player + st[2])->categ, (player + st[3])->categ) == 0 &&
			strcmp((player + st[3])->categ, (player + st[4])->categ) == 0) ||
		((player + st[0])->val == 14 && (player + st[1])->val == 2 &&
			(player + st[2])->val == 3 && (player + st[3])->val == 4 &&
			(player + st[4])->val == 5 &&
			strcmp((player + st[0])->categ, (player + st[1])->categ) == 0 &&
			strcmp((player + st[1])->categ, (player + st[2])->categ) == 0 &&
			strcmp((player + st[2])->categ, (player + st[3])->categ) == 0 &&
			strcmp((player + st[3])->categ, (player + st[4])->categ) == 0
			))
	{
		if ((maxPlayer) < 9 || (maxPlayer == 9))//Daca gasesc o mana mai buna sau identica ( pentru ca se genereaza crescator deci urmatoare mana de acelasi tip este mai buna decat precedenta) ii ia locul celei din urma
		{
			(maxPlayer) = 9;
			strcpy(handCpy, "STRAIGHT FLUSH");
			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}

	if (
		(player + st[0])->val == (player + st[1])->val &&
		(player + st[1])->val == (player + st[2])->val &&
		(player + st[2])->val == (player + st[3])->val
		)
	{
		if ((maxPlayer) < 8 || (maxPlayer == 8))//Daca gasesc o mana mai buna sau de acelasi tip, noua mana ii ia locul celei din urma
		{
			(maxPlayer) = 8;
			strcpy(handCpy, "FOUR OF A KIND");
			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if
		(
			(player + st[1])->val == (player + st[2])->val &&
			(player + st[2])->val == (player + st[3])->val &&
			(player + st[3])->val == (player + st[4])->val
			)
	{
		if ((maxPlayer) < 8 || (maxPlayer == 8))
		{
			(maxPlayer) = 8;
			strcpy(handCpy, "FOUR OF A KIND");
			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		((player + st[0])->val == (player + st[1])->val &&
			(player + st[1])->val == (player + st[2])->val &&
			(player + st[3])->val == (player + st[4])->val) ||
		((player + st[0])->val == (player + st[1])->val &&
			(player + st[2])->val == (player + st[3])->val &&
			(player + st[3])->val == (player + st[4])->val))
	{
		if ((maxPlayer) < 7 || (maxPlayer == 7))
		{
			(maxPlayer) = 7;
			strcpy(handCpy, "FULL HOUSE");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		strcmp((player + st[0])->categ, (player + st[1])->categ) == 0 &&
		strcmp((player + st[1])->categ, (player + st[2])->categ) == 0 &&
		strcmp((player + st[2])->categ, (player + st[3])->categ) == 0 &&
		strcmp((player + st[3])->categ, (player + st[4])->categ) == 0
		)
	{
		if ((maxPlayer) < 6 || (maxPlayer == 6))
		{
			(maxPlayer) = 6;
			strcpy(handCpy, "FLUSH");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		(player + st[0])->val == (player + st[1])->val - 1 &&
		(player + st[1])->val == (player + st[2])->val - 1 &&
		(player + st[2])->val == (player + st[3])->val - 1 &&
		(player + st[3])->val == (player + st[4])->val - 1 ||
		((player + st[0])->val == 2 && (player + st[1])->val == 3 &&
			(player + st[2])->val == 4 && (player + st[3])->val == 5 &&
			(player + st[4])->val == 14))
	{
		if ((maxPlayer) < 5 || (maxPlayer == 5))
		{
			(maxPlayer) = 5;
			strcpy(handCpy, "STRAIGHT");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		(player + st[0])->val == (player + st[1])->val &&
		(player + st[1])->val == (player + st[2])->val ||
		(player + st[1])->val == (player + st[2])->val &&
		(player + st[2])->val == (player + st[3])->val ||
		(player + st[2])->val == (player + st[3])->val &&
		(player + st[3])->val == (player + st[4])->val
		)
	{
		if ((maxPlayer) < 4 || (maxPlayer == 4))
		{
			(maxPlayer) = 4;
			strcpy(handCpy, "THREE OF A KIND");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		(player + st[0])->val == (player + st[1])->val &&
		(player + st[2])->val == (player + st[3])->val ||
		(player + st[0])->val == (player + st[1])->val &&
		(player + st[3])->val == (player + st[4])->val ||
		(player + st[1])->val == (player + st[2])->val &&
		(player + st[3])->val == (player + st[4])->val
		)
	{
		if ((maxPlayer) < 3 || (maxPlayer == 3))
		{
			(maxPlayer) = 3;
			strcpy(handCpy, "TWO PAIR");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (
		(player + st[0])->val == (player + st[1])->val ||
		(player + st[1])->val == (player + st[2])->val ||
		(player + st[2])->val == (player + st[3])->val ||
		(player + st[3])->val == (player + st[4])->val
		)
	{
		if ((maxPlayer) < 2 || (maxPlayer == 2))
		{
			(maxPlayer) = 2;
			strcpy(handCpy, "ONE PAIR");

			strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
			strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
			(cpyPlayer + 0)->val = (player + st[0])->val;

			strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
			strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
			(cpyPlayer + 1)->val = (player + st[1])->val;

			strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
			strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
			(cpyPlayer + 2)->val = (player + st[2])->val;

			strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
			strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
			(cpyPlayer + 3)->val = (player + st[3])->val;

			strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
			strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
			(cpyPlayer + 4)->val = (player + st[4])->val;

			return maxPlayer;
		}
	}
	if (maxPlayer <= 1)
	{
		(maxPlayer) = 1;
		strcpy(handCpy, "HIGH CARD");

		strcpy((cpyPlayer + 0)->denum, (player + st[0])->denum);
		strcpy((cpyPlayer + 0)->categ, (player + st[0])->categ);
		(cpyPlayer + 0)->val = (player + st[0])->val;

		strcpy((cpyPlayer + 1)->denum, (player + st[1])->denum);
		strcpy((cpyPlayer + 1)->categ, (player + st[1])->categ);
		(cpyPlayer + 1)->val = (player + st[1])->val;

		strcpy((cpyPlayer + 2)->denum, (player + st[2])->denum);
		strcpy((cpyPlayer + 2)->categ, (player + st[2])->categ);
		(cpyPlayer + 2)->val = (player + st[2])->val;

		strcpy((cpyPlayer + 3)->denum, (player + st[3])->denum);
		strcpy((cpyPlayer + 3)->categ, (player + st[3])->categ);
		(cpyPlayer + 3)->val = (player + st[3])->val;

		strcpy((cpyPlayer + 4)->denum, (player + st[4])->denum);
		strcpy((cpyPlayer + 4)->categ, (player + st[4])->categ);
		(cpyPlayer + 4)->val = (player + st[4])->val;
	}
	return maxPlayer;
}


void winner(int nrJucatori)//Subprogram folosit pentru a realiza clasamentul jucatorilor in vectorul index
{
	if (nrJucatori == 1)
		index[0] = 1;
	else if (nrJucatori == 2)
	{
		if (maxPlayer1 < maxPlayer2)
		{
			index[0] = 2;
			index[1] = 1;
		}
		else if (maxPlayer1 > maxPlayer2)
		{
			index[0] = 1;
			index[1] = 2;
		}
		else if (highcard(playerOne, playerTwo) < 0)
		{
			index[0] = 2;
			index[1] = 1;
		}
		else
		{
			index[0] = 1;
			index[1] = 2;
		}
	}
	else if (nrJucatori == 3)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);

		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 2; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 4)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 3; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 5)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 4; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 6)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		scor[5] = maxPlayer6;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		index[5] = 6;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		h[5] = bestCard(cpyPlayerSix, maxPlayer6);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 5; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 7)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		scor[5] = maxPlayer6;
		scor[6] = maxPlayer7;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		index[5] = 6;
		index[6] = 7;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		h[5] = bestCard(cpyPlayerSix, maxPlayer6);
		h[6] = bestCard(cpyPlayerSeven, maxPlayer7);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 6; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 8)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		scor[5] = maxPlayer6;
		scor[6] = maxPlayer7;
		scor[7] = maxPlayer8;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		index[5] = 6;
		index[6] = 7;
		index[7] = 8;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		h[5] = bestCard(cpyPlayerSix, maxPlayer6);
		h[6] = bestCard(cpyPlayerSeven, maxPlayer7);
		h[7] = bestCard(cpyPlayerEight, maxPlayer8);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 7; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 9)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		scor[5] = maxPlayer6;
		scor[6] = maxPlayer7;
		scor[7] = maxPlayer8;
		scor[8] = maxPlayer9;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		index[5] = 6;
		index[6] = 7;
		index[7] = 8;
		index[8] = 9;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		h[5] = bestCard(cpyPlayerSix, maxPlayer6);
		h[6] = bestCard(cpyPlayerSeven, maxPlayer7);
		h[7] = bestCard(cpyPlayerEight, maxPlayer8);
		h[8] = bestCard(cpyPlayerNine, maxPlayer9);
		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 8; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
	else if (nrJucatori == 10)
	{
		scor[0] = maxPlayer1;
		scor[1] = maxPlayer2;
		scor[2] = maxPlayer3;
		scor[3] = maxPlayer4;
		scor[4] = maxPlayer5;
		scor[5] = maxPlayer6;
		scor[6] = maxPlayer7;
		scor[7] = maxPlayer8;
		scor[8] = maxPlayer9;
		scor[9] = maxPlayer10;
		index[0] = 1;
		index[1] = 2;
		index[2] = 3;
		index[3] = 4;
		index[4] = 5;
		index[5] = 6;
		index[6] = 7;
		index[7] = 8;
		index[8] = 9;
		index[9] = 10;
		h[0] = bestCard(cpyPlayerOne, maxPlayer1);
		h[1] = bestCard(cpyPlayerTwo, maxPlayer2);
		h[2] = bestCard(cpyPlayerThree, maxPlayer3);
		h[3] = bestCard(cpyPlayerFour, maxPlayer4);
		h[4] = bestCard(cpyPlayerFive, maxPlayer5);
		h[5] = bestCard(cpyPlayerSix, maxPlayer6);
		h[6] = bestCard(cpyPlayerSeven, maxPlayer7);
		h[7] = bestCard(cpyPlayerEight, maxPlayer8);
		h[8] = bestCard(cpyPlayerNine, maxPlayer9);
		h[9] = bestCard(cpyPlayerTen, maxPlayer10);

		int ok = 0;
		int i;
		int aux;
		while (!ok)
		{
			ok = 1;
			for (i = 0; i < 9; i++)
			{
				if (scor[i] < scor[i + 1])
				{
					aux = scor[i];
					scor[i] = scor[i + 1];
					scor[i + 1] = aux;

					aux = index[i];
					index[i] = index[i + 1];
					index[i + 1] = aux;

					aux = h[i];
					h[i] = h[i + 1];
					h[i + 1] = aux;

					ok = 0;
				}
				else if (scor[i] == scor[i + 1])
				{
					if (h[i] < h[i + 1])
					{
						aux = scor[i];
						scor[i] = scor[i + 1];
						scor[i + 1] = aux;

						aux = index[i];
						index[i] = index[i + 1];
						index[i + 1] = aux;

						aux = h[i];
						h[i] = h[i + 1];
						h[i + 1] = aux;

						ok = 0;
					}
				}
			}
		}
	}
}

int bestCard(carte* player, int c)//Subprogram folosit pentru a identifica cea mai buna mana din doua de acelasi tip
{
	if (c == 1)
	{
		return (player + 4)->val * 100000 + (player + 3)->val * 10000 + (player + 2)->val * 1000 + (player + 1)->val * 10 + (player + 0)->val;//Pentru highcard doar formez un numar dupa cele mai semnificative carti
	}
	if (c == 2)//Pentru ONE PAIR se formeaza un numar dupa cele doua carti care sunt identice urmate de urmatoarele cele mai semnificative carti
	{
		if ((player + 0)->val == (player + 1)->val)
			return (player + 1)->val * 10000 + (player + 4)->val * 100 + (player + 3)->val * 10 + (player + 2)->val;
		if ((player + 1)->val == (player + 2)->val)
			return (player + 1)->val * 10000 + (player + 4)->val * 100 + (player + 3)->val * 10 + (player + 0)->val;
		if ((player + 2)->val == (player + 3)->val)
			return (player + 2)->val * 10000 + (player + 4)->val * 100 + (player + 1)->val * 10 + (player + 0)->val;
		if ((player + 3)->val == (player + 4)->val)
			return (player + 4)->val * 10000 + (player + 2)->val * 100 + (player + 1)->val * 10 + (player + 0)->val;
	}
	if (c == 3)//Pentru TWO PAIR se formeaza numarul dupa cele 2 perechi de carti identice urmate de ultima carte
	{
		if ((player + 0)->val == (player + 1)->val && (player + 2)->val == (player + 3)->val)
			return (player + 3)->val * 10000 + (player + 0)->val * 100 + (player + 4)->val * 10;
		if ((player + 0)->val == (player + 1)->val && (player + 3)->val == (player + 4)->val)
			return (player + 3)->val * 10000 + (player + 0)->val * 100 + (player + 2)->val * 10;
		if ((player + 1)->val == (player + 2)->val && (player + 3)->val == (player + 4)->val)
			return (player + 3)->val * 10000 + (player + 1)->val * 100 + (player + 0)->val * 10;
	}
	if (c == 4)//Pentru THREE OF A KIND returnez doar carte care este 3 ori, stiind ca oriunde s-ar afla cele 3 carti, una este mereu la mijloc
	{
		return (player + 2)->val;
	}
	if (c == 5 || c == 6)//Pentru FLUSH si STRAIGHT doar returnez ultima carte, fiind cea mai semnificativa
	{
		return (player + 4)->val;
	}
	if (c == 7 || c == 8)//Pentru FULL HOUSE si FOUR OF A KIND returnez cartea din mijloc, fiind cea mai semnificativa
	{
		return (player + 2)->val;
	}
	if (c == 9)//Pentru STRAIGHT FLUSH doar returnez ultima carte, fiind cea mai semnificativa
	{
		return (player + 4)->val;
	}
	return 1;
}



int main()
{
	int k;
	int nJucatori, nComCards;//Numar jucatori si numar community cards
	printf("Exemplu:\nCarte -> 2,3,4,5...J,Q,K,A\nCategorie -> ROMB,TREFLA,IROSIE,INEAGRA\n\n\n");
	printf("Introduceti numarul de jucatori:");
	scanf("%d", &nJucatori);
	switch (nJucatori)
	{
	case 1: 
		printf("Numarul de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)//Citesc community cards
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)//Afisez community cards
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);//Citesc carti jucator 1
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);//Afisez carti jucator 1
			if (i < 1)
				printf("; ");
		}

		printf("\n");
		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);//Adaug community cards in mana jucatorului
		}
		sortare(playerOne, nPlayer1);//Sortez crescator dupa valoare cartile jucatorului
		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);//Determin combiantiile 
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);//Afisez cea mai buna mana 
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		break;//Acelasi lucru pentru urmatoarele doar ca se introduc mai multi jucatori
	case 2:
		printf("Numarul de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		printf("\nMana jucatorului 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucatorului 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		winner(2);//Apelez functia pentru 2 jucatori
		printf("\nCASTIGATOR: Jucator %d\n", index[0]);
		printf("Clasament:");//Afisez clasamentul 
		for (i = 0; i < 2; i++)
		{
			printf("Jucator %d ", index[i]);
			if (i < 1)
				printf("; ");
		}
		printf("\n");

		break;
	case 3:
		printf("Numar de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Cartile jucatorului 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");



		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		printf("\nMana jucatorului 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucatorului 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucatorului 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");

		winner(3);
		printf("\nCASTIGATOR: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 3; i++)
		{
			printf("Jucator %d ", index[i]);
			if (i < 2)
				printf("; ");
		}
		printf("\n");

		break;
	case 4: 
		printf("Numarul de comunity cards (minim 3, maxim 5):");
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Cartile jucatorului 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Cartile jucatorului 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");


		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);

		printf("\nMana jucatorului 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucatorului 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucatorului 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucatorului 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");

		winner(4); 
		printf("\nCastigator: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 4; i++)
		{
			printf("Jucator %d ", index[i]);
			if (i < 3)
				printf("; ");
		}
		printf("\n");

		break;
	case 5: 
		printf("Numar de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Cartile jucatorului 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Cartile jucatorului 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Cartile jucatorului 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");



		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);

		printf("\nMana jucatorului 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucatorului 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucatorului 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucatorului 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucatorului 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");

		winner(5); 
		printf("\nCASTIGATOR: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 5; i++) {
			printf("Jucator %d ", index[i]);
			if (i < 4)
				printf("; ");
		}
		printf("\n");
		break;
	case 6:
		printf("Numar de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards); 
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Carti jucator 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Carti jucator 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Carti jucator 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Carti jucator 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Carti jucator 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 6 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSix, &nPlayer6);
		}

		printf("Carti jucator 6 sunt:");
		for (i = 0; i <= nPlayer6; i++)
		{
			afisareCarte(playerSix, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");


		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);
			inserare(playerSix, comunityCards, &nPlayer6, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);
		sortare(playerSix, nPlayer6);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);
		bt(nPlayer6, &maxPlayer6, playerSix, cpyPlayerSix, handP6);

		printf("\nMana jucator 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucator 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucator 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucator 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucator 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");
		printf("\nMana jucator 6: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSix, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP6);
		printf("\n");

		winner(6);
		printf("\nCASTIGATOR: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 6; i++) {
			printf("Jucator %d ", index[i]);
			if (i < 5)
				printf("; ");
		}
		printf("\n");
		break;
	case 7: 
		printf("Numar de comunity cards (minim 3, maxim 5):");
		scanf("%d", &nComCards);
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Carti jucator 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Carti jucator 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Carti jucator 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Carti jucator 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Carti jucator 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 6 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSix, &nPlayer6);
		}

		printf("Carti jucator 6 sunt:");
		for (i = 0; i <= nPlayer6; i++)
		{
			afisareCarte(playerSix, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 7 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSeven, &nPlayer7);
		}

		printf("Carti jucator 7 sunt:");
		for (i = 0; i <= nPlayer7; i++)
		{
			afisareCarte(playerSeven, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");

		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);
			inserare(playerSix, comunityCards, &nPlayer6, k);
			inserare(playerSeven, comunityCards, &nPlayer7, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);
		sortare(playerSix, nPlayer6);
		sortare(playerSeven, nPlayer7);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);
		bt(nPlayer6, &maxPlayer6, playerSix, cpyPlayerSix, handP6);
		bt(nPlayer7, &maxPlayer7, playerSeven, cpyPlayerSeven, handP7);

		printf("\nMana jucator 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucator 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucator 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucator 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucator 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");
		printf("\nMana jucator 6: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSix, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP6);
		printf("\n");
		printf("\nMana jucator 7: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSeven, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP7);
		printf("\n");

		winner(7); 
		printf("\nCastigator: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 7; i++) {
			printf("Jucator %d ", index[i]);
			if (i < 6)
				printf("; ");
		}
		printf("\n");
		break;
	case 8: 
		printf("Numar de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards);
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Carti jucator 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCarti jucator 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Carti jucator 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Carti jucator 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Carti jucator 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Carti jucator 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 6 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSix, &nPlayer6);
		}

		printf("Carti jucator 6 sunt:");
		for (i = 0; i <= nPlayer6; i++)
		{
			afisareCarte(playerSix, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 7 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSeven, &nPlayer7);
		}

		printf("Carti jucator 7 sunt:");
		for (i = 0; i <= nPlayer7; i++)
		{
			afisareCarte(playerSeven, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 8 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerEight, &nPlayer8);
		}

		printf("Carti jucator 8 sunt:");
		for (i = 0; i <= nPlayer8; i++)
		{
			afisareCarte(playerEight, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);
			inserare(playerSix, comunityCards, &nPlayer6, k);
			inserare(playerSeven, comunityCards, &nPlayer7, k);
			inserare(playerEight, comunityCards, &nPlayer8, k);
		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);
		sortare(playerSix, nPlayer6);
		sortare(playerSeven, nPlayer7);
		sortare(playerEight, nPlayer8);
		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);
		bt(nPlayer6, &maxPlayer6, playerSix, cpyPlayerSix, handP6);
		bt(nPlayer7, &maxPlayer7, playerSeven, cpyPlayerSeven, handP7);
		bt(nPlayer8, &maxPlayer8, playerEight, cpyPlayerEight, handP8);

		printf("\nMana jucator 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucator 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucator 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucator 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucator 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");
		printf("\nMana jucator 6: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSix, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP6);
		printf("\n");
		printf("\nMana jucator 7: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSeven, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP7);
		printf("\n");
		printf("\nMana jucator 8: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerEight, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP8);
		printf("\n");
		winner(8); 
		printf("\nCastigator: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 8; i++) 
		{
			printf("Jucator %d ", index[i]);
			if (i < 7)
				printf("; ");
		}
		printf("\n");
		break;
	case 9: 
		printf("Numar de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards);
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Cartile jucatorului 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Carti jucator 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Cartile jucatorului 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 6 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSix, &nPlayer6);
		}

		printf("Cartile jucatorului 6 sunt:");
		for (i = 0; i <= nPlayer6; i++)
		{
			afisareCarte(playerSix, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 7 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSeven, &nPlayer7);
		}

		printf("Cartile jucatorului 7 sunt:");
		for (i = 0; i <= nPlayer7; i++)
		{
			afisareCarte(playerSeven, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCarti jucator 8 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerEight, &nPlayer8);
		}

		printf("Cartile jucatorului 8 sunt:");
		for (i = 0; i <= nPlayer8; i++)
		{
			afisareCarte(playerEight, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 9 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerNine, &nPlayer9);
		}

		printf("Cartile jucatorului 9 sunt:");
		for (i = 0; i <= nPlayer9; i++)
		{
			afisareCarte(playerNine, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);
			inserare(playerSix, comunityCards, &nPlayer6, k);
			inserare(playerSeven, comunityCards, &nPlayer7, k);
			inserare(playerEight, comunityCards, &nPlayer8, k);
			inserare(playerNine, comunityCards, &nPlayer9, k);

		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);
		sortare(playerSix, nPlayer6);
		sortare(playerSeven, nPlayer7);
		sortare(playerEight, nPlayer8);
		sortare(playerNine, nPlayer9);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);
		bt(nPlayer6, &maxPlayer6, playerSix, cpyPlayerSix, handP6);
		bt(nPlayer7, &maxPlayer7, playerSeven, cpyPlayerSeven, handP7);
		bt(nPlayer8, &maxPlayer8, playerEight, cpyPlayerEight, handP8);
		bt(nPlayer9, &maxPlayer9, playerNine, cpyPlayerNine, handP9);

		printf("\nMana jucator 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucator 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucator 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucator 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucator 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");
		printf("\nMana jucator 6: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSix, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP6);
		printf("\n");
		printf("\nMana jucator 7: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSeven, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP7);
		printf("\n");
		printf("\nMana jucator 8: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerEight, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP8);
		printf("\n");
		printf("\nMana jucator 9: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerNine, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP9);
		printf("\n");
		winner(9); 
		printf("\nCASTIGATOR: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 9; i++) 
		{
			printf("Jucator %d ", index[i]);
			if (i < 8)
				printf("; ");
		}
		printf("\n");
		break;
	case 10: 
		printf("Numarul de comunity cards (minim 3, maxim 5):"); 
		scanf("%d", &nComCards);
		if (nComCards > 5 || nComCards < 3)
			exit(0);
		printf("Comunity cards (%d):\n", nComCards);
		for (i = 0; i < nComCards; i++)
		{
			adaugare(comunityCards, &nCD);
		}
		printf("Comiunity cards sunt:");
		for (i = 0; i <= nCD; i++)
		{
			afisareCarte(comunityCards, i);
			if (i < nComCards - 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 1 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerOne, &nPlayer1);
		}
		printf("Cartile jucatorului 1 sunt:");
		for (i = 0; i <= nPlayer1; i++)
		{
			afisareCarte(playerOne, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n");
		printf("\n\n\nCartile jucatorului 2 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTwo, &nPlayer2);
		}

		printf("Cartile jucatorului 2 sunt:");
		for (i = 0; i <= nPlayer2; i++)
		{
			afisareCarte(playerTwo, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 3 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerThree, &nPlayer3);
		}

		printf("Cartile jucatorului 3 sunt:");
		for (i = 0; i <= nPlayer3; i++)
		{
			afisareCarte(playerThree, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 4 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFour, &nPlayer4);
		}

		printf("Cartile jucatorului 4 sunt:");
		for (i = 0; i <= nPlayer4; i++)
		{
			afisareCarte(playerFour, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 5 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerFive, &nPlayer5);
		}

		printf("Cartile jucatorului 5 sunt:");
		for (i = 0; i <= nPlayer5; i++)
		{
			afisareCarte(playerFive, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 6 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSix, &nPlayer6);
		}

		printf("Cartile jucatorului 6 sunt:");
		for (i = 0; i <= nPlayer6; i++)
		{
			afisareCarte(playerSix, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 7 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerSeven, &nPlayer7);
		}

		printf("Cartile jucatorului 7 sunt:");
		for (i = 0; i <= nPlayer7; i++)
		{
			afisareCarte(playerSeven, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 8 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerEight, &nPlayer8);
		}

		printf("Cartile jucatorului 8 sunt:");
		for (i = 0; i <= nPlayer8; i++)
		{
			afisareCarte(playerEight, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 9 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerNine, &nPlayer9);
		}

		printf("Cartile jucatorului 9 sunt:");
		for (i = 0; i <= nPlayer9; i++)
		{
			afisareCarte(playerNine, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		printf("\n\n\nCartile jucatorului 10 (2):\n");
		for (i = 0; i < 2; i++)
		{
			adaugare(playerTen, &nPlayer10);
		}

		printf("Cartile jucatorului 10 sunt:");
		for (i = 0; i <= nPlayer10; i++)
		{
			afisareCarte(playerTen, i);
			if (i < 1)
				printf("; ");
		}
		printf("\n\n");
		for (k = 0; k <= nCD; k++)
		{
			inserare(playerOne, comunityCards, &nPlayer1, k);
			inserare(playerTwo, comunityCards, &nPlayer2, k);
			inserare(playerThree, comunityCards, &nPlayer3, k);
			inserare(playerFour, comunityCards, &nPlayer4, k);
			inserare(playerFive, comunityCards, &nPlayer5, k);
			inserare(playerSix, comunityCards, &nPlayer6, k);
			inserare(playerSeven, comunityCards, &nPlayer7, k);
			inserare(playerEight, comunityCards, &nPlayer8, k);
			inserare(playerNine, comunityCards, &nPlayer9, k);
			inserare(playerTen, comunityCards, &nPlayer10, k);
		}
		sortare(playerOne, nPlayer1);
		sortare(playerTwo, nPlayer2);
		sortare(playerThree, nPlayer3);
		sortare(playerFour, nPlayer4);
		sortare(playerFive, nPlayer5);
		sortare(playerSix, nPlayer6);
		sortare(playerSeven, nPlayer7);
		sortare(playerEight, nPlayer8);
		sortare(playerNine, nPlayer9);
		sortare(playerTen, nPlayer10);

		init(nPlayer1);
		bt(nPlayer1, &maxPlayer1, playerOne, cpyPlayerOne, handP1);
		bt(nPlayer2, &maxPlayer2, playerTwo, cpyPlayerTwo, handP2);
		bt(nPlayer3, &maxPlayer3, playerThree, cpyPlayerThree, handP3);
		bt(nPlayer4, &maxPlayer4, playerFour, cpyPlayerFour, handP4);
		bt(nPlayer5, &maxPlayer5, playerFive, cpyPlayerFive, handP5);
		bt(nPlayer6, &maxPlayer6, playerSix, cpyPlayerSix, handP6);
		bt(nPlayer7, &maxPlayer7, playerSeven, cpyPlayerSeven, handP7);
		bt(nPlayer8, &maxPlayer8, playerEight, cpyPlayerEight, handP8);
		bt(nPlayer9, &maxPlayer9, playerNine, cpyPlayerNine, handP9);
		bt(nPlayer10, &maxPlayer10, playerTen, cpyPlayerTen, handP10);

		printf("\nMana jucator 1: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerOne, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP1);
		printf("\n");
		printf("\nMana jucator 2: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTwo, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP2);
		printf("\n");
		printf("\nMana jucator 3: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerThree, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP3);
		printf("\n");
		printf("\nMana jucator 4: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFour, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP4);
		printf("\n");
		printf("\nMana jucator 5: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerFive, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP5);
		printf("\n");
		printf("\nMana jucator 6: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSix, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP6);
		printf("\n");
		printf("\nMana jucator 7: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerSeven, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP7);
		printf("\n");
		printf("\nMana jucator 8: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerEight, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP8);
		printf("\n");
		printf("\nMana jucator 9: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerNine, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP9);
		printf("\n");
		printf("\nMana jucator 10: ");
		for (i = 0; i <= 4; i++)
		{
			afisareCarte(cpyPlayerTen, i);
			if (i < 4)
				printf("; ");
		}
		printf("\nMana poker:%s\n", handP10);
		printf("\n");
		winner(10); 
		printf("\nCastigator: Jucator %d\n", index[0]);
		printf("Clasament:");
		for (i = 0; i < 10; i++) 
		{
			printf("Jucator %d ", index[i]);
			if (i < 9)
				printf("; ");
		}
		printf("\n");

		break;
	default:printf("Numar invalid de jucatori.\n");
		break;
	}

	system("pause");
	return 0;
}