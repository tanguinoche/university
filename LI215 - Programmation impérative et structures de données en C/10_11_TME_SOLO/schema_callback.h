#ifndef SCHEMA_CALLBACK
#define SCHEMA_CALLBACK
typedef enum outil_ {TOUCH, LINE, CURVE} Outil;

void OnExpose(GtkWidget* widget, gpointer data);
void OnOuvrir(GtkWidget* widget, gpointer data);
void OnEnregistrer(GtkWidget* widget, gpointer data);
void OnEnregSous(GtkWidget* widget, gpointer data);
void OnNouveau(GtkWidget* widget, gpointer data);
void OnQuitter(GtkWidget* widget, gpointer data);

/*
void OnCouper(GtkWidget* widget, gpointer data);
void OnCopier(GtkWidget* widget, gpointer data);
void OnColler(GtkWidget* widget, gpointer data);
*/

void OnUndo(GtkWidget* widget, gpointer data);
void OnRedo(GtkWidget* widget, gpointer data);

void OnZoomIn(GtkWidget* widget, gpointer data);
void OnZoomOut(GtkWidget* widget, gpointer data);
void OnZoomFit(GtkWidget* widget, gpointer data);

void OnColor(GtkWidget *button, gpointer data);

void OnTouch(GtkWidget* widget, gpointer data);
void OnSelectLine(GtkWidget* widget, gpointer data);
void OnSelectCurve(GtkWidget* widget, gpointer data);

void OnExpose(GtkWidget* widget, gpointer data);
void OnAbout(GtkWidget* widget, gpointer data);
void OnBtPress (GtkWidget *widget, GdkEventButton *event, gpointer data);
void OnMouseMove (GtkWidget *widget, GdkEventMotion *event, gpointer data);

void ResetData();
void InitDim();

#endif
