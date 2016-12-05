#ifndef IMAGE_
#define IMAGE_

#define VAL(img,i,j) (img)->buff[(j)*(img)->w+(i)]

typedef struct
	{
	unsigned long w;
	unsigned long h;
	char *path;
	unsigned char *buff;
	} image_t;

image_t *creer_image();

image_t *copier_image(image_t *src);

void detruire_image(image_t *p);
#endif
