// File: adder.cpp

#include <cstdlib>   // atoi()
#include <cstdio>    // sprintf()
#include <gtk/gtk.h>
using namespace std;

struct widptrs {
   GtkWidget *f1;
   GtkWidget *f2;
   GtkWidget *f3;
};

static void do_calc (GtkButton *button, gpointer data)
{
  static char a_str[50], b_str[50], total_str[50];
  struct widptrs *ptrs = (struct widptrs *)data;
  GtkEntry *num1 = GTK_ENTRY(ptrs->f1);
  GtkEntry *num2 = GTK_ENTRY(ptrs->f2);
  GtkLabel *total = GTK_LABEL(ptrs->f3);

  // Convert text to integer
  int a = atoi(gtk_entry_get_text(num1));
  // Rewrite integer to entry in case garbage was entered
  sprintf(a_str,"%d",a);
  gtk_entry_set_text(num1, a_str);
  int b = atoi(gtk_entry_get_text(num2));
  sprintf(b_str,"%d",b);
  gtk_entry_set_text(num2, b_str);
  sprintf(total_str,"%d",a+b);
  gtk_label_set_text(total, total_str);
  return;
}

static int window_delete (GtkWindow *window, gpointer data)
{
   gtk_main_quit();
   return FALSE;
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    struct widptrs ptrs;
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_OBJECT(window), "delete_event",
         GTK_SIGNAL_FUNC(window_delete), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create first row
    // It has a label and a text entry box
    GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
    GtkWidget *label = gtk_label_new("Host: ");
    gtk_widget_show  (label);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(label), TRUE, TRUE, 0);
    
    GtkWidget *num1 = gtk_entry_new();
    ptrs.f1 = num1;
    gtk_entry_set_text(GTK_ENTRY(num1), "0");
    gtk_widget_show  (num1);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(num1), TRUE, TRUE, 0);

    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);

    // Create second row
    // It has a label and a text entry box
    label = gtk_label_new("Port: ");
    gtk_widget_show  (label);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(label), TRUE, TRUE, 0);
    
    GtkWidget *num2 = gtk_entry_new();
    ptrs.f2 = num2;
    gtk_entry_set_text(GTK_ENTRY(num2), "0");
    gtk_widget_show  (num2);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(num2), TRUE, TRUE, 0);

    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);

    // Create third row
    // It has two labels
    
    // Create last row
    // It has two buttons
    GtkWidget *submit_button = gtk_button_new_with_label("Connect");
    g_signal_connect(GTK_OBJECT(submit_button), "clicked",
         GTK_SIGNAL_FUNC(do_calc), &ptrs);
    gtk_widget_show  (submit_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(submit_button),
        TRUE, TRUE, 0);

    hbox = gtk_hbox_new(FALSE, 0);

    GtkWidget *rock_button = gtk_button_new_with_label("Rock");
    g_signal_connect(GTK_OBJECT(rock_button), "clicked",
         GTK_SIGNAL_FUNC(do_calc), &ptrs);
    gtk_widget_show  (rock_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(rock_button),
        TRUE, TRUE, 0);

    GtkWidget *paper_button = gtk_button_new_with_label("Paper");
    g_signal_connect(GTK_OBJECT(paper_button), "clicked",
         GTK_SIGNAL_FUNC(do_calc), &ptrs);
    gtk_widget_show  (paper_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(paper_button),
        TRUE, TRUE, 0);

    GtkWidget *scissor_button = gtk_button_new_with_label("Scissors");
    g_signal_connect(GTK_OBJECT(scissor_button), "clicked",
         GTK_SIGNAL_FUNC(do_calc), &ptrs);
    gtk_widget_show  (scissor_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(scissor_button),
        TRUE, TRUE, 0);
    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);

    hbox = gtk_hbox_new(FALSE, 0);
    label = gtk_label_new("Result: ");
    gtk_widget_show  (label);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(label), TRUE, TRUE, 0);
    
    GtkWidget *total = gtk_label_new("0");
    ptrs.f3 = total;
    gtk_widget_show  (total);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(total), TRUE, TRUE, 0);

    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);
     
    hbox = gtk_hbox_new(FALSE, 0);
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect(GTK_OBJECT(quit_button), "clicked",
         GTK_SIGNAL_FUNC(window_delete), NULL);
    gtk_widget_show  (quit_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(quit_button),
        TRUE, TRUE, 0);

    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);

    gtk_widget_show  (vbox);
    gtk_widget_show  (window);
    gtk_main ();
    
    return 0;
}
