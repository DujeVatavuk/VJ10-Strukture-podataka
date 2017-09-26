/*
Napisati program kojim se
a.Sluèajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u binarno stablo pretraživanja. Zatim ispišemo to stablo u preorder naèinu ispisa.
b.Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u proizvoljno definiranoj datoteci.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stablo *node;
typedef struct stablo
{
	int el;
	node left;
	node right;
}stablo;

node unosUStablo(int, node);
int randomBroj(int, int[]);//generirat cemo 100 RAZLICITIH brojeva
void printPreorder(node);
node citanjeIzDatoteke(node);//u njoj se poziva brisi
node brisi(int, node);//identican onome kojeg nam je crnjac napisa
node nadjiMin(node);

int main()
{
	srand(time(NULL));
	node root = NULL;
	int rbr[100];

	for (int i = 0; i < 100; i++)
	{
		rbr[i] = randomBroj(i, rbr);
		root = unosUStablo(rbr[i], root);
	}
	printPreorder(root);
	printf("\n\n");
	root = citanjeIzDatoteke(root);//odma i brise sve sta treba jel se "brisi" poziva unutar funkcije
	printPreorder(root);
	printf("\n\n");

	return 0;
}

int randomBroj(int brojac, int rbr[])
{
	int check = 0, R;
	do
	{
		R = rand() % 400 + 300;
		check = 0;
		for (int i = 0; i < brojac; i++)
		{
			if (R == rbr[i])
			{
				check = 1;
				break;
			}
		}
	} while (check == 1);
	return R;
}

node unosUStablo(int x, node S)
{
	if (NULL == S)
	{
		S = (node)malloc(sizeof(stablo));
		S->left = NULL;
		S->right = NULL;
		S->el = x;
	}
	else if (x > S->el)
	{
		S->right = unosUStablo(x, S->right);
	}
	else if (x < S->el)
	{
		S->left = unosUStablo(x, S->left);
	}
	return S;
}

void printPreorder(node S)
{
	if (NULL != S)
	{
		printf("\n\t%d", S->el);
		printPreorder(S->left);
		printPreorder(S->right);
	}
}

node citanjeIzDatoteke(node S)
{
	FILE *dat;
	dat = fopen("Brojevi.txt", "r");
	int brojIzDat;
	while (!feof(dat))
	{
		fscanf(dat, "%d", &brojIzDat);
		S = brisi(brojIzDat, S);//ovaj brisi u sebi ima i find
	}
	fclose(dat);
	return S;
}

node brisi(int x, node T)
{
	node temp;

	if (NULL == T)
	{
		return T;
	}
	else if (x < T->el)
	{
		T->left = brisi(x, T->left);
	}
	else if (x > T->el)
	{
		T->right = brisi(x, T->right);
	}
	else
	{
		if (T->left && T->right)//ako ima oba diteta
		{
			temp = nadjiMin(T->right);
			T->el = temp->el;
			T->right = brisi(T->el, T->right);
		}
		else
		{
			temp = T;
			if (NULL == T->left)
			{
				T = T->right;
			}
			else if (NULL == T->right)
			{
				T = T->left;
			}
			free(temp);
		}
	}
	return T;
}

node nadjiMin(node S)
{
	while (NULL != S->left)
	{
		S = S->left;
	}
	return S;
}
