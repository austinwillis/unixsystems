// File: dialog.cpp

#include <gtk/gtk.h>

void callback( GtkWidget *widget,
               gpointer   data )
{
    gtk_dialog_run (GTK_DIALOG (data));
    gtk_widget_destroy (GTK_WIDGET(data));
}

// another callback 
gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

void destroy( GtkWidget *widget, gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
   GtkWidget *window,
      *dialog,
      *vbox,
      *button;

    gtk_init (&argc, &argv);

    // Create main window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Dialog Demo");
    gtk_window_set_default_size (GTK_WINDOW (window), (gint) 200, (gint) 200);
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",
		      G_CALLBACK (destroy), NULL);
    
    // Create dialog object
    dialog = gtk_message_dialog_new (GTK_WINDOW(window),
                    GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_INFO,
                    GTK_BUTTONS_CLOSE,
                    "You have clicked the quit button" );

    // Create layout box
    vbox = gtk_vbox_new (FALSE, 0);

    // Create quit button
    button = gtk_button_new_with_label ("Quit");
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (callback), (gpointer) dialog);
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy),
                              G_OBJECT (window));

    // Pack button into box
    gtk_box_pack_start (GTK_BOX(vbox), button, FALSE, FALSE, 10);
    gtk_widget_show (button);

    // Put the box into the main window. 
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
    gtk_widget_show (window);

    // main program is still running after dialog box is destroyed
    gtk_main ();
    
    return 0;
}
