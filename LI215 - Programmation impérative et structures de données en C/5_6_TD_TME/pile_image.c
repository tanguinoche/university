#include <gtk/gtk.h>
#include "image.h"

#define TPILE 5

extern GtkWidget *pLabel_Nomf;
extern GtkWidget *pLabel_Res;
extern GtkWidget *pDA;

// Version ellaboree de la pile
static image_t *pile[TPILE];
static unsigned int itop=0, ibot=0, icur=0;

image_t *cur_image;

void pile_new_image(image_t *new_image)
	{
	char str_res[32];
	static int first_call = TRUE;

	if (first_call)
		{
		first_call = FALSE;
		}
	else
		{
		icur = (icur + 1) % TPILE;
		if (icur == ibot)
			ibot = (ibot + TPILE - 1) % TPILE;
		}

	if(pile[icur])
		detruire_image(pile[icur]);
	pile[icur] = new_image;
	cur_image = new_image;
	// mise a jours des labels
	gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
	snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
	gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
	// forcer le dessin de la fenetre
	gtk_widget_queue_draw_area(pDA, 0, 0, cur_image->w, cur_image->h);
	itop = icur;
	}

void pile_free_images()
	{
	int i;
	static int first_call = TRUE;

	if (first_call)
		{
		for(i=0; i<TPILE; i++)
			pile[i] = NULL;
		first_call = FALSE;
		}
	else
		{
		for(i=0; i<TPILE; i++)
			detruire_image(pile[i]);
		}
	gtk_label_set_text (GTK_LABEL (pLabel_Nomf), "Pas d image chargee");
	gtk_label_set_text (GTK_LABEL (pLabel_Res), "Resolution Image");
	cur_image = NULL;
	gtk_widget_queue_draw_area(pDA, 0, 0, 0, 0);
	}

void pile_undo()
	{
	if (icur == ibot)
		return;

	icur = (icur + TPILE - 1) % TPILE;
	cur_image = pile[icur];
	gtk_widget_queue_draw_area(pDA, 0, 0, cur_image->w, cur_image->h);
	}

void pile_redo()
	{
	if (icur == itop)
		return;

	icur = (icur + 1) % TPILE;
	cur_image = pile[icur];
	gtk_widget_queue_draw_area(pDA, 0, 0, cur_image->w, cur_image->h);
	}
