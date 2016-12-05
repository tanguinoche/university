#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h"
#define TMP_STR_SIZE 32

image_t *charger_image_pgm(char *nom_fichier)
	{
	FILE *f;
	image_t *img;
	unsigned int nb_ng;
	char tmp_str[TMP_STR_SIZE];

	f=fopen(nom_fichier, "r");

	if (!f)
		{
		fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
		return NULL;
		}

	fgets(tmp_str, TMP_STR_SIZE, f);

	if (strcmp(tmp_str, "P5\n"))
		{
		fprintf(stderr, "format fichier non pgm (P5)\n");
		return NULL;
		}

	img = creer_image();

	fgets(tmp_str, TMP_STR_SIZE, f);

	if (sscanf(tmp_str, "%ld %ld\n", &(img->w), &(img->h)) != 2)
		{
		fprintf(stderr, "format fichier non pgm\n");
		detruire_image(img);
		return NULL;
		}

	fgets(tmp_str, TMP_STR_SIZE, f);

	if (sscanf(tmp_str, " %d ", &nb_ng) != 1)
		{
		fprintf(stderr, "format fichier non pgm\n");
		detruire_image(img);
		return NULL;
		}

	if (nb_ng != 255)
		{
		fprintf(stderr, "Nombre de ng diff de 255 erreur\n");
		detruire_image(img);
		return NULL;
		}

	img->buff = (unsigned char *) malloc(img->w * img->h * sizeof (unsigned char));

	if (fread(img->buff, img->w, img->h, f) != img->h)
		{
		fprintf(stderr, "fichier image imcomplet!\n");
		return NULL;
		}
	fclose(f);
	img->path = strdup(nom_fichier);
	return img;
	}

int sauver_image_pgm(char *nom_fichier, image_t *img)
	{
	FILE *f;

	f=fopen(nom_fichier, "w");

	if (!f)
		{
		fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
		return 0;
		}

	fprintf(f, "P5\n");
	fprintf(f, "%ld %ld\n", img->w, img->h);
	fprintf(f, "255\n");

	fwrite(img->buff, img->w, img->h, f);
	fclose(f);
	return 1;
	}
