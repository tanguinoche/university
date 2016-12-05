#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "noyau.h"


image_t *negatif(image_t *src)
	{
	image_t *dst;
	int i;

	if (src == NULL)
		return NULL;

	dst = creer_image();
	*dst = *src;
	dst->path = strdup(src->path);
	dst->buff = (unsigned char*) malloc(src->w * src->h);

	for(i=0; i< (src->w * src->h); i++)
		dst->buff[i] = 255 - src->buff[i];
	
	return dst;
	}

image_t *rotation_droite(image_t *src, int angle)
	{
	image_t *dst;
	int i,j;

	if (src == NULL)
		return NULL;

	if (angle % 90)
		return NULL;

	angle = angle % 360;

	dst = creer_image();
	dst->path = strdup(src->path);
	dst->buff = (unsigned char*) malloc(src->w * src->h);


	if (angle == 90)
		{
		dst->w = src->h;
		dst->h = src->w;

		for(j=0; j<dst->h; j++)
			for(i=0; i<dst->w; i++)
				VAL(dst,i,j) = VAL(src, src->w -j -1, i);
		return dst;
		}
	
	if (angle == 180)
		{
		dst->w = src->w;
		dst->h = src->h;

		for(j=0; j<dst->h; j++)
			for(i=0; i<dst->w; i++)
				VAL(dst,i,j) = VAL(src, src->w -i -1, src->h -j -1);
		return dst;
		}
	
	if (angle == 270)
		{
		dst->w = src->h;
		dst->h = src->w;

		for(j=0; j<dst->h; j++)
			for(i=0; i<dst->w; i++)
				VAL(dst,i,j) = VAL(src, j, src->h -i -1);
		return dst;
		}

	dst->w = src->w;
	dst->h = src->h;
	memcpy(dst->buff, src->buff, src->w * dst->h);
	return dst;
	}

image_t *modifier_lumin(image_t *src, int pourcent)
	{
	image_t *dst;
	int i;
	int tmp_val;

	if(!src)
		return NULL;

	if (pourcent < 0)
		return NULL;

	dst = copier_image(src);

	for(i=0; i< (dst->w * dst->h); i++)
		{
		tmp_val = (src->buff[i] *  pourcent) /100;
		if (tmp_val > 255)
			tmp_val = 255;
		dst->buff[i] = tmp_val;
		}
	return dst;
	}

image_t *bruiter_image(image_t *src, int pourcent)
	{
	image_t *dst;
	int i;
	unsigned int val;

	if (src == NULL)
		return NULL;

	dst = copier_image(src);
	for(i=0; i< (dst->w * dst->h); i++)
		{
		val = rand()%100;
		if (val < pourcent)
			dst->buff[i] = rand() % 256;
		}
	return dst;
	}

int compare(const void *a, const void *b)
	{
	return (int) *(unsigned char *)a - *(unsigned char *)b;
	}
	
image_t *filtrer_median(image_t *src)
	{
	image_t *dst;
	char voisinage[]={	0,1,1,1,0,
						1,1,1,1,1,
						1,1,1,1,1,
						1,1,1,1,1,
						0,1,1,1,0};
	int dim = 5;

	unsigned char tab_val[21];
	int i,j,k,l,cote1,cote2;

	if(!src)
		return NULL;

	dst = copier_image(src);

	for(j=0;j<src->h;j++)
		for(i=0;i<src->w;i++)
			{
			int i_tab_val = 0;
			for(l=0;l<dim;l++)
				for(k=0;k<dim;k++)
					{
				
					cote1= i + k - (dim>>1);
					if (cote1 <0)
						cote1 = 0;
					if (cote1 >= src->w)
						cote1 = src->w-1;
					cote2 = j + l - (dim>>1);
					if (cote2 <0)
						cote2= 0;
					if (cote2>= src->h)
						cote2 = src->h-1;

					if (voisinage[l*dim + k])
					tab_val[i_tab_val++] = VAL(src, cote1, cote2);
					}
			qsort(tab_val, 21, 1, compare);
			VAL(dst,i,j) = tab_val[10];
			}
	return dst;
	}

image_t *convoluer(image_t *src, noyau_t *pn)
	{
	image_t *dst;
	int i,j,k,l,cote1,cote2;
	int coef_norm=0;
	unsigned int dim;

	if(!pn)
		return NULL;

	if(!src)
		return NULL;

	for(i=0;i<(pn->dim * pn->dim);i++)
		coef_norm += pn->coeffs[i];
	dim = pn->dim;

	dst = copier_image(src);

	for(j=0;j<src->h;j++)
		for(i=0;i<src->w;i++)
			{
			int somp=0;
			for(l=0;l<dim;l++)
				for(k=0;k<dim;k++)
					{
					cote1 = i + k - (dim>>1);
					if (cote1 <0)
						cote1= 0;
					if (cote1>= src->w)
						cote1 = src->w-1;
					cote2 = j + l - (dim>>1);
					if (cote2 <0)
						cote2 = 0;
					if (cote2 >= src->h)
						cote2 = src->h-1;

					somp += pn->coeffs[l*pn->dim + k] * VAL(src, cote1, cote2);
					}
			if (coef_norm)
				VAL(dst, i, j) = (unsigned char) (somp / coef_norm);
			else
				VAL(dst, i, j) = (unsigned char) abs(somp);
			}
	return dst;
	}
