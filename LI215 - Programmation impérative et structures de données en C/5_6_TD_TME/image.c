#include<stdlib.h>
#include<string.h>
#include "image.h"

image_t *creer_image()
	{
	image_t *p;

	p = (image_t *) malloc(sizeof(image_t));

	p->w=0;
	p->h=0;
	p->path=NULL;
	p->buff=NULL;

	return p;
	}

image_t *copier_image(image_t *src)
	{
	image_t *dst;

	dst = creer_image();
	dst->w = src->w;
	dst->h = src->h;
	dst->path = strdup(src->path);
	dst->buff = (unsigned char *) malloc(src->w * src->h *sizeof (unsigned char));
	memcpy(dst->buff, src->buff, src->w * src->h * sizeof (unsigned char));
	return dst;
	}

void detruire_image(image_t *p)
	{
	if (p == NULL) return;
	free(p->buff);
	free(p->path);
	free(p);
	}
