#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "schema_callback.h"
#include "geom.h"

#define ZOOMMIN 8
#define ZOOMINI 16
#define BORD 4
#define DIM 50
#define TPOINTS 4
#define TCARRE 3

// du vecteur au pixel
#define TOX(x) (((x) - xcda) * zoomfact + (wda/2))
#define TOY(y) (hda/2 - ((y)  - ycda) * zoomfact)

// du pixel au vecteur
#define FROMX(X) ((X) < wda/2) ? xcda - (wda/2 - (X) + zoomfact/2)/ zoomfact : xcda + ((X) - wda/2 + zoomfact/2)/ zoomfact

#define FROMY(Y) ((Y) < wda/2) ? ycda + (wda/2 - (Y) + zoomfact/2)/ zoomfact : ycda - ((Y) - wda/2 + zoomfact/2)/ zoomfact

// La fenetre principale
extern GtkWidget *pWindow;
extern GtkWidget *pDA;
extern GtkWidget *pLabel;

// Dimensions de la zone de trace en pixels
static int wda = 0;
static int hda = 0;

// Coordonnees origine (vecteur) en pixels
//static int y0da, x0da;

// Coordonnes (vecteur) du centre DA
static int ycda, xcda;

// Facteur de zoom 1 unite (vecteur) correspond a zoomfact pixels
static int zoomfact;

// Les limites du dessin en unitees (vecteurs)
int xmin, xmax, ymin, ymax;


Un_dessin *dessin = NULL;
Une_forme *new_forme = NULL;
Une_couleur couleur = {0, 0, 255};
Un_elem *redolist = NULL;

Outil tool = TOUCH;

void ResetData()
	{
	if (dessin) DetruireDessin(dessin);
	dessin = NULL;
	}

void MajAff()
	{
	gtk_widget_queue_draw(pDA);
	}

void LimDA()
	{
	ymax = ycda + ((hda - 2*BORD) / (2 * zoomfact));
	ymin = ycda - ((hda - 2*BORD) / (2 * zoomfact));
	xmax = xcda + ((wda - 2*BORD) / (2 * zoomfact));
	xmin = xcda - ((wda - 2*BORD) / (2 * zoomfact));
	}

// divers callback

void OnColor(GtkWidget *button, gpointer data)
{
	GtkWidget *dialog;
	GtkColorSelection *colorsel;
	gint response;
	GdkColor color = {0, couleur.r << 8, couleur.v << 8, couleur.b << 8};

	dialog = gtk_color_selection_dialog_new ("Changer de couleur");

	gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(pWindow));

	colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (dialog)->colorsel);

	gtk_color_selection_set_previous_color (colorsel, &color);
	gtk_color_selection_set_current_color (colorsel, &color);
	gtk_color_selection_set_has_palette (colorsel, TRUE);

	response = gtk_dialog_run (GTK_DIALOG (dialog));

	if (response == GTK_RESPONSE_OK)
		{
		gtk_color_selection_get_current_color (colorsel, &color);
		couleur.r = color.red >> 8;
		couleur.v = color.green >> 8;
		couleur.b = color.blue >> 8;
		}

	gtk_widget_destroy (dialog);
}

void OnOuvrir(GtkWidget* widget, gpointer data)
	{
	GtkWidget *dialog;
	GtkFileFilter *sch_filter;

	sch_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( sch_filter, "*.sch");
	gtk_file_filter_add_pattern (sch_filter, "*.sch");

	dialog = gtk_file_chooser_dialog_new ("Ouvrir Fichier",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), sch_filter);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
 		{
		char *nom_fichier;
		int xzoomfact, yzoomfact;

		nom_fichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

		// effacer historique
		ResetData();

		//abr = NULL;
		dessin = OuvrirDessin(nom_fichier);
		if (dessin == NULL)
			{
			fprintf(stderr, "Erreur ouverture fichier : %s", nom_fichier);
			ResetData();
			return;
			}
		g_free (nom_fichier);
		gtk_widget_destroy (dialog);

			
		// Calcul des limites
		LimitesDessin(dessin, &xmin, &xmax, &ymin, &ymax);

		// Calcul du centre
		xcda = (xmax + xmin) / 2;
		ycda = (ymax + ymin) / 2;

		// calcul du zoomfact
		xzoomfact = (wda - (2*BORD)) / (xmax - xmin);
		yzoomfact = (hda - (2*BORD)) / (ymax - ymin);
		zoomfact = (xzoomfact < yzoomfact) ? xzoomfact : yzoomfact;
		if (zoomfact < 1) zoomfact = 1;
		LimDA();
   
		//Mise a jour formes visibles
		//dessin->formes = ListeFormes(dessin->points);

		MajAff();
  		}
	}

void OnEnregistrer(GtkWidget* widget, gpointer data)
	{
	if (dessin)
		EnregDessin(dessin, dessin->path);
	}

void OnEnregSous(GtkWidget* widget, gpointer data)
	{
	GtkWidget *dialog;
	GtkFileFilter *sch_filter;

	if (dessin == NULL)
		return;
	sch_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( sch_filter, "*.sch");
	gtk_file_filter_add_pattern (sch_filter, "*.sch");
	dialog = gtk_file_chooser_dialog_new ("Enregistrer Sous",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "SansNom");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), sch_filter);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		{
		char *nom_fichier;
		nom_fichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		if (dessin)
			EnregDessin(dessin, nom_fichier);

		g_free (nom_fichier);
		}
	gtk_widget_destroy (dialog);
	}

void InitDim()
	{
	xcda = 0;
	ycda = 0;

	xmin = -(DIM /2); 
	xmax = (DIM /2); 
	ymin = -(DIM /2); 
	ymax = (DIM /2); 

	zoomfact = ZOOMINI;

	wda = DIM*zoomfact + 2 * BORD;
	hda = wda;

	/*
	x0da = wda / 2;
	y0da = x0da;
	*/

	gtk_widget_set_size_request (pDA, wda, hda);
	}

void OnNouveau(GtkWidget* widget, gpointer data)
	{
	ResetData();
	dessin = CreerDessin("SansNom");
	InitDim();
	gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);
	}

void OnQuitter(GtkWidget* widget, gpointer data)
{
	GtkWidget *pQuestion;

	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_YES_NO,
		"Voulez vous vraiment\n"
		"quitter le programme?");

	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
		case GTK_RESPONSE_YES:
			gtk_main_quit();
			break;
		case GTK_RESPONSE_NONE:
		case GTK_RESPONSE_NO:
			gtk_widget_destroy(pQuestion);
			break;
	}
}

/*Fonctions Edition*/
/*
void OnCouper(GtkWidget* widget, gpointer data)
	{
	}
void OnCopier(GtkWidget* widget, gpointer data)
	{
	}
void OnColler(GtkWidget* widget, gpointer data)
	{
	}
*/

/*Fonctions Zoom*/
void OnZoomIn(GtkWidget* widget, gpointer data)
	{
	zoomfact *= 2;
	if (zoomfact < 1) zoomfact = 1;
	LimDA();

	MajAff();
	}

void OnZoomOut(GtkWidget* widget, gpointer data)
	{
	zoomfact /= 2;
	if (zoomfact < 1) zoomfact = 1;
	LimDA();

	MajAff();
	}

void OnZoomFit(GtkWidget* widget, gpointer data)
	{
	int xzoomfact, yzoomfact;
	LimitesDessin(dessin, &xmin, &xmax, &ymin, &ymax);

	// calcul du zoomfact
	xzoomfact = (wda - (2*BORD)) / (xmax - xmin);
	yzoomfact = (hda - (2*BORD)) / (ymax - ymin);
	zoomfact = (xzoomfact < yzoomfact) ? xzoomfact : yzoomfact;
	if (zoomfact < 1) zoomfact = 1;
	LimDA();
   
	MajAff();
	}

/*Fonctions Undo/Redo*/
void OnUndo(GtkWidget* widget, gpointer data)
	{
	if (dessin->formes)
		{
		Une_forme *f = dessin->formes->forme;
		int nb_points = NbPForme(f);
		int i;

		for (i = 0; i < nb_points; i++)
			f->tabp[i]->lf = ExtraireForme(f->tabp[i]->lf, f);
		dessin->formes = ExtraireForme(dessin->formes, f);

		redolist = AjouterForme(redolist, f);
		MajAff();
		}
	}

void OnRedo(GtkWidget* widget, gpointer data)
	{
	if (redolist)
		{
		Une_forme *f = redolist->forme;
		int nb_points = NbPForme(f);
		int i;

		redolist = ExtraireForme(redolist, f);
		for (i = 0; i < nb_points; i++)
			f->tabp[i]->lf = AjouterForme(f->tabp[i]->lf, f);

		dessin->formes = AjouterForme(dessin->formes, f);
		MajAff();
		}
	}

/*Fonctions Outils*/
void OnTouch(GtkWidget* widget, gpointer data)
	{
	tool = TOUCH;
	if (new_forme)
		{
		DetruireForme(new_forme);
		new_forme = NULL;
		}
	gtk_label_set_text(GTK_LABEL(pLabel), "Glisser pour déplacer");
	}
void OnSelectLine(GtkWidget* widget, gpointer data)
	{
	tool = LINE;
	if (new_forme)
		{
		DetruireForme(new_forme);
		new_forme = NULL;
		}
	gtk_label_set_text(GTK_LABEL(pLabel), "Ligne premier point");
	}
void OnSelectCurve(GtkWidget* widget, gpointer data)
	{
	tool = CURVE;
	if (new_forme)
		{
		DetruireForme(new_forme);
		new_forme = NULL;
		}
	gtk_label_set_text(GTK_LABEL(pLabel), "Courbe premier point");
	}

int startx, starty;
int curx, cury;
int startxc, startyc;

void OnBtPress (GtkWidget *widget, GdkEventButton *event, gpointer data)
	{
	Un_point *p;
	// Seulement bouton de gauche
	if (event->button != 1 ) return;

	startx = event->x;
	starty = event->y;

	switch (tool)
		{
		case TOUCH :
			//Memoriser la psition initiale
			startxc = xcda;
			startyc = ycda;
			break;

		case LINE :
			p = ChercherPointABRX(dessin, FROMX(startx), FROMY(starty));
			if (p == NULL)
				{
				p = CreerPoint(VMax(dessin->points) + 1, FROMX(startx), FROMY(starty));
				dessin->points = AjouterPoint(dessin->points, p);
				dessin->abrx = AjouterPointABRX(dessin->abrx, p);
				}

			if (new_forme == NULL) // premier point
				{
				new_forme = CreerForme(SEG, couleur, 2);
				new_forme->etat = DEB;
				new_forme->tabp[0] = p;
				gtk_label_set_text(GTK_LABEL(pLabel), "Ligne second point");
				break;
				}

			// second point
			new_forme->etat = OK;
			new_forme->tabp[1] = p;
			new_forme->tabp[0]->lf = AjouterForme(new_forme->tabp[0]->lf, new_forme);
			new_forme->tabp[1]->lf = AjouterForme(new_forme->tabp[1]->lf, new_forme);
			dessin->formes = AjouterForme(dessin->formes, new_forme);
			new_forme = NULL;
			gtk_label_set_text(GTK_LABEL(pLabel), "Ligne premier point");
			MajAff();
			break;

		case CURVE :
			p = ChercherPointABRX(dessin, FROMX(startx), FROMY(starty));
			if (p == NULL)
				{
				p = CreerPoint(VMax(dessin->points) + 1, FROMX(startx), FROMY(starty));
				dessin->points = AjouterPoint(dessin->points, p);
				dessin->abrx = AjouterPointABRX(dessin->abrx, p);
				}

			if (new_forme == NULL) // premier point
				{
				new_forme = CreerForme(COURB, couleur, 4);
				new_forme->etat = DEB;
				new_forme->tabp[0] = p;
				gtk_label_set_text(GTK_LABEL(pLabel), "Courbe premier point de controle");
				break;
				}

			switch(new_forme->etat)
				{
				case DEB :
					new_forme->etat = CTL1;
					new_forme->tabp[1] = p;
					gtk_label_set_text(GTK_LABEL(pLabel), "Courbe second point");
					break;
					
				case CTL1 :
					new_forme->etat = FIN;
					new_forme->tabp[3] = p;
					gtk_label_set_text(GTK_LABEL(pLabel), "Courbe second point de controle");
					break;
					
				case FIN :
					new_forme->etat = OK;
					new_forme->tabp[2] = p;
					new_forme->tabp[0]->lf = AjouterForme(new_forme->tabp[0]->lf, new_forme);
					new_forme->tabp[1]->lf = AjouterForme(new_forme->tabp[1]->lf, new_forme);
					new_forme->tabp[2]->lf = AjouterForme(new_forme->tabp[2]->lf, new_forme);
					new_forme->tabp[3]->lf = AjouterForme(new_forme->tabp[3]->lf, new_forme);
					dessin->formes = AjouterForme(dessin->formes, new_forme);
					new_forme = NULL;
					gtk_label_set_text(GTK_LABEL(pLabel), "Courbe premier point");
					break;

				default :
					break;
				}
			MajAff();
			break;
		}


	}

void OnMouseMove (GtkWidget *widget, GdkEventMotion *event, gpointer data)
	{
	int x,y;

	x = curx = event->x;
	y = cury = event->y;

	x += zoomfact/2;
	y -= zoomfact/2;
	if ((tool == TOUCH) && (event->state & GDK_BUTTON1_MASK))
		{
		int dx = x - startx;
		int dy = y - starty;
		int modif = 0;
   
		if (abs(dx) >= zoomfact)
			{
			xcda = startxc - (dx / zoomfact);
			modif = 1;
			}
   
		if (abs(dy) >= zoomfact)
			{
			ycda = startyc + (dy / zoomfact);
			modif = 1;
			}
   
		if (modif)
			{
			LimDA();
			}
		}
	MajAff();
	}

void OnAbout(GtkWidget* widget, gpointer data)
{
	GtkWidget *pAbout;

	pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		"Li215 mini projet schema\n"
		"Universite Pierre et Marie Curie");

	gtk_dialog_run(GTK_DIALOG(pAbout));

	gtk_widget_destroy(pAbout);
}


void TraceGrille(cairo_t *cr)
	{
	double y, x;
	if (zoomfact > ZOOMMIN)
		{
		cairo_set_line_width (cr, 1);
		cairo_set_source_rgb( cr, 0.0, 0.0, 0.0);
   
		for (y = TOY(ymax); y < hda; y += zoomfact)
			for (x = TOX(xmin); x < wda; x += zoomfact)
				cairo_rectangle (cr, x, y, 1, 1);
		cairo_stroke (cr);
		}
	}

void trace_dessin(cairo_t *cr, Un_dessin *d)
	{
	Un_elem *el;

	if (d == NULL) return;

	// Affichage des formes
	for(el = d->formes ;el ;el = el->suiv)
		{
		Une_forme *f = el->forme;
		cairo_set_source_rgb( cr, f->coul.r / 255.0, f->coul.v / 255.0, f->coul.b / 255.0);
		switch (f->type)
			{
			case SEG :
				cairo_move_to (cr, TOX(f->tabp[0]->x), TOY(f->tabp[0]->y));
				cairo_line_to (cr, TOX(f->tabp[1]->x), TOY(f->tabp[1]->y));
				break;
			case COURB :
				cairo_move_to (cr, TOX(f->tabp[0]->x), TOY(f->tabp[0]->y));
				cairo_curve_to(cr,
									TOX(f->tabp[1]->x), TOY(f->tabp[1]->y),
									TOX(f->tabp[2]->x), TOY(f->tabp[2]->y),
									TOX(f->tabp[3]->x), TOY(f->tabp[3]->y));
				break;
			default :
				fprintf(stderr, "Code forme inconnu : %d\n", f->type);
			}
		cairo_stroke (cr);
		}
	}

void trace_point(cairo_t *cr, int x, int y)
	{
	cairo_set_source_rgb( cr, 0.0, 1.0, 0.0);
	cairo_move_to (cr, x-TCARRE, y-TCARRE);
	cairo_line_to (cr, x+TCARRE, y-TCARRE);
	cairo_line_to (cr, x+TCARRE, y+TCARRE);
	cairo_line_to (cr, x-TCARRE, y+TCARRE);
	cairo_line_to (cr, x-TCARRE, y-TCARRE);
	cairo_stroke (cr);
	}

void trace_nlle_forme(cairo_t *cr)
	{
	double pointille[] = {4.0, 4.0};
	if (new_forme == NULL) return;

	trace_point(cr, TOX(new_forme->tabp[0]->x), TOY(new_forme->tabp[0]->y));
	cairo_move_to (cr, TOX(new_forme->tabp[0]->x), TOY(new_forme->tabp[0]->y));
	switch (new_forme->type)
		{
		case SEG :
			cairo_set_dash(cr, pointille, 2, 0.0); 
			cairo_line_to (cr, curx, cury);
			cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
			cairo_stroke (cr);
			cairo_set_dash(cr, NULL, 0, 0.0); 
			break;

		case COURB :
			switch(new_forme->etat)
				{
				case DEB :
				cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
				cairo_set_dash(cr, pointille, 2, 0.0); 
				cairo_line_to (cr, curx, cury);
				cairo_stroke (cr);
				cairo_set_dash(cr, NULL, 0, 0.0); 
				break;
					
				case CTL1 :
				cairo_set_dash(cr, pointille, 2, 0.0); 
				cairo_line_to (cr, TOX(new_forme->tabp[1]->x), TOY(new_forme->tabp[1]->y));
				cairo_set_source_rgb(cr, new_forme->coul.r/255.0, new_forme->coul.v/255.0, new_forme->coul.b/255.0);
				cairo_stroke (cr);
				cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
				cairo_move_to (cr, TOX(new_forme->tabp[0]->x), TOY(new_forme->tabp[0]->y));
				cairo_curve_to(cr, TOX(new_forme->tabp[1]->x), TOY(new_forme->tabp[1]->y),
									TOX(new_forme->tabp[1]->x), TOY(new_forme->tabp[1]->y), curx, cury);
				cairo_stroke (cr);
				cairo_set_dash(cr, NULL, 0, 0.0); 
				break;

				case FIN :
				cairo_set_dash(cr, pointille, 2, 0.0); 
				cairo_line_to (cr, TOX(new_forme->tabp[1]->x), TOY(new_forme->tabp[1]->y));
				cairo_set_source_rgb(cr, new_forme->coul.r/255.0, new_forme->coul.v/255.0, new_forme->coul.b/255.0);
				cairo_stroke (cr);

				cairo_move_to (cr, TOX(new_forme->tabp[0]->x), TOY(new_forme->tabp[0]->y));
				cairo_curve_to(cr, TOX(new_forme->tabp[1]->x), TOY(new_forme->tabp[1]->y), curx, cury,
									TOX(new_forme->tabp[3]->x), TOY(new_forme->tabp[3]->y));
				cairo_set_source_rgb(cr, new_forme->coul.r/255.0, new_forme->coul.v/255.0, new_forme->coul.b/255.0);
				cairo_stroke (cr);
				trace_point(cr, TOX(new_forme->tabp[3]->x), TOY(new_forme->tabp[3]->y));

				cairo_move_to (cr, TOX(new_forme->tabp[3]->x), TOY(new_forme->tabp[3]->y));
				cairo_line_to (cr, curx, cury);
				cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
				cairo_stroke (cr);
				cairo_set_dash(cr, NULL, 0, 0.0); 
				break;

				default :
					break;
				}
			break;
		}
	cairo_stroke (cr);
	}

// affichage de l image drawing_area
void OnExpose(GtkWidget* widget, gpointer data)
	{
	cairo_t *cr;
	int nwda = pDA->allocation.width;
	int nhda = pDA->allocation.height;

	// detection du redimensionnent
	if ( nwda != wda)
		{
		wda = nwda;
		LimDA();
		}
	if ( nhda != hda)
		{
		hda = nhda;
		LimDA();
		}

	// Dessin de la fenetre
	cr = gdk_cairo_create (pDA->window);

	// peinture du fond
	cairo_set_source_rgb( cr, 1.0, 1.0, 1.0);
	cairo_paint(cr);
	
	// trace grille
	TraceGrille(cr);

	// trace du dessin
	trace_dessin(cr, dessin);

	// trace Nouvelle Forme
	trace_nlle_forme(cr);

	cairo_destroy(cr);
	}
