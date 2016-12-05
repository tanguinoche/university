#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "schema_callback.h"
#include "geom.h"
#include "mesicones.h"

GtkWidget *pDA;
GtkWidget *pLabel;
GtkWidget *pWindow;


int main(int argc, char **argv)
{
	GtkWidget *pVBox;
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pSeparator;
	GtkWidget *pToolBar;
	GtkToolItem *pButton;
	GtkWidget *pHBox;
	//GtkWidget *pScroll;


	gtk_init(&argc, &argv);

	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "schema");
	//gtk_window_set_default_size(GTK_WINDOW(pWindow), -1, -1);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 600, 500);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


	/* Creation de la GtkVBox */
	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/**** Creation du menu ****/

	/* ETAPE 1 */
	pMenuBar = gtk_menu_bar_new();
	/** Premier sous-menu **/

	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Ouvrir");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnOuvrir), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Enregistrer");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnEnregistrer), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Enregistrer _Sous");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnEnregSous), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Nouveau");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnNouveau), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pSeparator = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pSeparator);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Quitter");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Fichier");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Sous-menu Edition**/
	pMenu = gtk_menu_new();
	/* ETAPE 3 */

	pMenuItem = gtk_menu_item_new_with_mnemonic("Annuler");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnUndo), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Retablir");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRedo), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

/*
	pMenuItem = gtk_menu_item_new_with_mnemonic("Couper");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnCouper), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Copier");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnCopier), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Coller");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnColler), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	*/

	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Edition");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Sous-menu Affichage**/

	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("A_juster");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnZoomFit), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Agrandir");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnZoomIn), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Reduire");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnZoomOut), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Affichage");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Troisieme sous-menu **/
	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("A propos de schema");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_label("?");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/* Ajout du menu a la fenetre */
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);

	/* Bare d outil std*/
	pToolBar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(pToolBar), GTK_TOOLBAR_ICONS);

	/*zone Fichiers*/
	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnNouveau), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Nouveau");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnOuvrir), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Ouvrir");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnEnregistrer), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Enregistrer");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_SAVE_AS);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnEnregSous), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Enregistrer Sous");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), gtk_separator_tool_item_new(), -1);

	/*zone Edition*/
	/*
	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnCouper), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Couper");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnCopier), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Copier");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnColler), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Coller");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), gtk_separator_tool_item_new(), -1);
	*/

	/*zone Zoom*/
	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_ZOOM_FIT);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnZoomFit), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Optimal");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_ZOOM_IN);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnZoomIn), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Agrandir");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_ZOOM_OUT);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnZoomOut), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Reduire");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), gtk_separator_tool_item_new(), -1);

	/*zone Undo*/
	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_REDO);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnRedo), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Retablir");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_UNDO);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnUndo), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Annuler");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), gtk_separator_tool_item_new(), -1);

	/*zone Selecteur de Couleur*/

	pButton = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_COLOR);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnColor), NULL);
	gtk_tool_item_set_tooltip_text(pButton, "Couleur");
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_box_pack_start(GTK_BOX(pVBox), pToolBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), gtk_hseparator_new(), FALSE, FALSE, 0);



	/* Creation de la GtkVBox */
	pHBox = gtk_hbox_new(FALSE, 0);

	/* Bare d outil Formes*/
	pToolBar = gtk_toolbar_new();
	gtk_orientable_set_orientation(GTK_ORIENTABLE(pToolBar), GTK_ORIENTATION_VERTICAL);
	gtk_toolbar_set_style(GTK_TOOLBAR(pToolBar), GTK_TOOLBAR_ICONS);

	/*Boutons formes*/
	GdkPixbuf *pPixbuf;
	GtkWidget *pIcon;

	/*Bouton Selection */

	pPixbuf = gdk_pixbuf_new_from_inline(-1, arrow_icon, FALSE, NULL);
   pIcon = gtk_image_new_from_pixbuf(pPixbuf);
	pButton = gtk_radio_tool_button_new (NULL);
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(pButton), pIcon);
	gtk_tool_item_set_tooltip_text(pButton, "Selectionner");
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnTouch), NULL);
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pPixbuf = gdk_pixbuf_new_from_inline(-1, line_icon, FALSE, NULL);
   pIcon = gtk_image_new_from_pixbuf(pPixbuf);
	pButton = gtk_radio_tool_button_new_from_widget(GTK_RADIO_TOOL_BUTTON(pButton));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(pButton), pIcon);
	gtk_tool_item_set_tooltip_text(pButton, "Segment");
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnSelectLine), NULL);
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	pPixbuf = gdk_pixbuf_new_from_inline(-1, bezierline_icon, FALSE, NULL);
   pIcon = gtk_image_new_from_pixbuf(pPixbuf);
	pButton = gtk_radio_tool_button_new_from_widget(GTK_RADIO_TOOL_BUTTON(pButton));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(pButton), pIcon);
	gtk_tool_item_set_tooltip_text(pButton, "Courbe");
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(OnSelectCurve), NULL);
	gtk_toolbar_insert (GTK_TOOLBAR(pToolBar), pButton, -1);

	gtk_box_pack_start(GTK_BOX(pHBox), pToolBar, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pHBox), gtk_vseparator_new(), FALSE, FALSE, 0);

	// une DrawingArea
	pDA = gtk_drawing_area_new ();

	// Gestion des click sur la DA
	// Autorisation des evenements
	gtk_widget_set_events (pDA, gtk_widget_get_events (pDA)
									| GDK_BUTTON_PRESS_MASK
									| GDK_POINTER_MOTION_MASK
									| GDK_POINTER_MOTION_HINT_MASK
									| GDK_BUTTON_RELEASE_MASK);
	// connexion de callbacks
	g_signal_connect (pDA, "expose-event", G_CALLBACK (OnExpose), (GtkWidget*) pDA);
	g_signal_connect (pDA, "button-press-event", G_CALLBACK (OnBtPress), (GtkWidget*) pDA);
	g_signal_connect (pDA, "motion-notify-event", G_CALLBACK (OnMouseMove), (GtkWidget*) pDA);


	// dimensionnement minimal par defaut

	// Ajout barres de defilement

	/*
	pScroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScroll), pDA);
	*/

	//gtk_box_pack_start(GTK_BOX(pHBox), pScroll, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pHBox), pDA, TRUE, TRUE, 0);
	//gtk_box_pack_start(GTK_BOX(pVBox), pDA, TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), gtk_hseparator_new(), FALSE, FALSE, 0);

	//Une zone de notification
	pLabel = gtk_label_new ("Bonjour");
	gtk_misc_set_alignment(GTK_MISC (pLabel),0,1);
	gtk_box_pack_start (GTK_BOX (pVBox), pLabel, FALSE, TRUE, 0);

	InitDim();
	OnNouveau(NULL, NULL);

	gtk_widget_show_all(pWindow);

	// Boucle GTK
	gtk_main();

	// destruction listes et arbres
	ResetData();

	return EXIT_SUCCESS;
}
