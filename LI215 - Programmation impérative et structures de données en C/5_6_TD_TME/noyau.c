#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>

#define TMP_STR_SIZE 128

noyau_t *creer_noyau(unsigned int dim)
	{
	noyau_t *pn;

	pn = (noyau_t *) malloc(sizeof(noyau_t));

	pn->dim = dim;
	pn->coeffs = (int *) malloc(dim * dim * sizeof(int));

	return pn;
	}

void detruire_noyau(noyau_t *pn)
	{
	if (pn)
		{
		free(pn->coeffs);
		free(pn);
		}
	}

void afficher_noyau(noyau_t *pn)
	{
	int i,j;
	printf("dim=%d\n", pn->dim);

	for(i=0;i<pn->dim;i++)
		{
		for(j=0;j<pn->dim;j++)
			printf("%d ", pn->coeffs[i*pn->dim+j]);
		putchar('\n');
		}
	}

noyau_t *charger_noyau(char *nom_fichier)
	{
	FILE *f;
	noyau_t *pn;
	unsigned int dim;
	int i;
	int *pi;
	char tmp_str[TMP_STR_SIZE];

	f=fopen(nom_fichier, "r");

	if (!f)
		{
		fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
		return NULL;
		}

	fgets(tmp_str, TMP_STR_SIZE, f);

	if (sscanf(tmp_str, "%d", &dim) != 1)
		{
		fprintf(stderr, "format fichier ne contenant pas la dim du noyau\n");
		return NULL;
		}

	if (!(pn = creer_noyau(dim)))
		return NULL;

	pi = pn->coeffs;
	for(i=0; i<dim; i++)
		{
		int j;char *cur = tmp_str; char *next;
		fgets(tmp_str, TMP_STR_SIZE, f);

		for(j=0;j<dim;j++)
			{
			*pi++=strtol(cur, &next, 0);
			if (next == cur)
				{
				fprintf(stderr, "Erreur format coefs noyau\n");
				detruire_noyau(pn);

				return NULL;
				}
			cur = next;
			}

		}
	fclose(f);
	return pn;
	}
