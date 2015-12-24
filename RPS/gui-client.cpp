//Austin Willis
//CS375
//Final Project
#include <iostream>
#include <gtk/gtk.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

using namespace std;
int SocketD;
char results[100];
char go[3];

struct widptrs {
   GtkWidget *f1;
   GtkWidget *f2;
   GtkWidget *f3;
   GtkWidget *f4;
   GtkWidget *f5;
   GtkWidget *f6;
};

static int window_delete (GtkWindow *window, gpointer data)
{
   struct widptrs *ptrs = (struct widptrs *) data;
   send(SocketD, "Q\0", sizeof("R\0"), 0);
   recv(SocketD, results, sizeof(results), 0);
   recv(SocketD, results, sizeof(results), 0);
   gtk_message_dialog_set_markup ((GtkMessageDialog*)data, results);
   gtk_dialog_run (GTK_DIALOG (data));
   gtk_widget_destroy (GTK_WIDGET(data));
}


static void server_connect (GtkButton *button, gpointer data)
{
   struct widptrs *ptrs = (struct widptrs *) data;
   GtkEntry *num1 = GTK_ENTRY(ptrs->f1);
   GtkEntry *num2 = GTK_ENTRY(ptrs->f2);
   GtkLabel *total = GTK_LABEL(ptrs->f3);
   GtkWidget *rock_button = GTK_WIDGET(ptrs->f4);
   GtkWidget *paper_button = GTK_WIDGET(ptrs->f5);
   GtkWidget *scissor_button = GTK_WIDGET(ptrs->f6);
    gtk_label_set_text(total, "Waiting for another player to join");	
   
   char* hostname = (char *)gtk_entry_get_text(num1);
   int port = atoi(gtk_entry_get_text(num2));

    SocketD = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host;
    host = gethostbyname(hostname);
    sockaddr_in SockAddr;
    SockAddr.sin_port=htons(port);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	cout << host << endl;
	cout << port << endl;

    if (!connect(SocketD, (sockaddr*)&SockAddr, sizeof(SockAddr))) {
    send(SocketD, "READY\0", sizeof("READY\0"), 0);
    recv(SocketD, go, sizeof(go), 0);
    go[2] = '\0';
    if (strcmp(go, "GO") == 0) {
    gtk_label_set_text(total, "Connected to another player. Click Rock, Paper, or Scissors");	
    gtk_widget_set_sensitive(rock_button, TRUE);
    gtk_widget_set_sensitive(paper_button, TRUE);
    gtk_widget_set_sensitive(scissor_button, TRUE);
    }
    } else {
    gtk_label_set_text(total, "Unable to connect. Try again later");	
    }
}

static void rock(GtkButton *button, gpointer data) {
   struct widptrs *ptrs = (struct widptrs *) data;
   GtkWidget *rock_button = GTK_WIDGET(ptrs->f4);
   GtkWidget *paper_button = GTK_WIDGET(ptrs->f5);
   GtkWidget *scissor_button = GTK_WIDGET(ptrs->f6);
    gtk_widget_set_sensitive(rock_button, FALSE);
    gtk_widget_set_sensitive(paper_button, FALSE);
    gtk_widget_set_sensitive(scissor_button, FALSE);
    send(SocketD, "R\0", sizeof("R\0"), 0);
    recv(SocketD, results, sizeof(results), 0);
    recv(SocketD, results, sizeof(results), 0);
    GtkLabel *total = GTK_LABEL(ptrs->f3); 
    gtk_label_set_text(total, results);	
    send(SocketD, "READY\0", sizeof("READY\0"), 0);
    recv(SocketD, go, sizeof(go), 0);
    go[2] = '\0';
    if (strcmp(go, "GO") == 0) {
    gtk_widget_set_sensitive(rock_button, TRUE);
    gtk_widget_set_sensitive(paper_button, TRUE);
    gtk_widget_set_sensitive(scissor_button, TRUE);
    }
}

static void paper(GtkButton *button, gpointer data) {
   struct widptrs *ptrs = (struct widptrs *) data;
   GtkWidget *rock_button = GTK_WIDGET(ptrs->f4);
   GtkWidget *paper_button = GTK_WIDGET(ptrs->f5);
   GtkWidget *scissor_button = GTK_WIDGET(ptrs->f6);
    gtk_widget_set_sensitive(rock_button, FALSE);
    gtk_widget_set_sensitive(paper_button, FALSE);
    gtk_widget_set_sensitive(scissor_button, FALSE);
    send(SocketD, "P\0", sizeof("P\0"), 0);
    recv(SocketD, results, sizeof(results), 0);
    recv(SocketD, results, sizeof(results), 0);
    GtkLabel *total = GTK_LABEL(ptrs->f3); 
    gtk_label_set_text(total, results);	
    send(SocketD, "READY\0", sizeof("READY\0"), 0);
    recv(SocketD, go, sizeof(go), 0);
    go[2] = '\0';
    if (strcmp(go, "GO") == 0) {
    gtk_widget_set_sensitive(rock_button, TRUE);
    gtk_widget_set_sensitive(paper_button, TRUE);
    gtk_widget_set_sensitive(scissor_button, TRUE);
    }
}

static void scissor(GtkButton *button, gpointer data) {
   struct widptrs *ptrs = (struct widptrs *) data;
   GtkWidget *rock_button = GTK_WIDGET(ptrs->f4);
   GtkWidget *paper_button = GTK_WIDGET(ptrs->f5);
   GtkWidget *scissor_button = GTK_WIDGET(ptrs->f6);
    gtk_widget_set_sensitive(rock_button, FALSE);
    gtk_widget_set_sensitive(paper_button, FALSE);
    gtk_widget_set_sensitive(scissor_button, FALSE);
    send(SocketD, "S\0", sizeof("S\0"), 0);
    recv(SocketD, results, sizeof(results), 0);
    recv(SocketD, results, sizeof(results), 0);
    GtkLabel *total = GTK_LABEL(ptrs->f3); 
    gtk_label_set_text(total, results);	
    send(SocketD, "READY\0", sizeof("READY\0"), 0);
    recv(SocketD, go, sizeof(go), 0);
    go[2] = '\0';
    if (strcmp(go, "GO") == 0) {
    gtk_widget_set_sensitive(rock_button, TRUE);
    gtk_widget_set_sensitive(paper_button, TRUE);
    gtk_widget_set_sensitive(scissor_button, TRUE);
    }
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
    gtk_entry_set_text(GTK_ENTRY(num1), "localhost");
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
         GTK_SIGNAL_FUNC(server_connect), &ptrs);
    gtk_widget_show  (submit_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(submit_button),
        TRUE, TRUE, 0);

    hbox = gtk_hbox_new(FALSE, 0);

    GtkWidget *rock_button = gtk_button_new_with_label("Rock");
    g_signal_connect(GTK_OBJECT(rock_button), "clicked",
         GTK_SIGNAL_FUNC(rock), &ptrs);
    gtk_widget_show  (rock_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(rock_button),
        TRUE, TRUE, 0);
    ptrs.f4 = rock_button;

    GtkWidget *paper_button = gtk_button_new_with_label("Paper");
    g_signal_connect(GTK_OBJECT(paper_button), "clicked",
         GTK_SIGNAL_FUNC(paper), &ptrs);
    gtk_widget_show  (paper_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(paper_button),
        TRUE, TRUE, 0);
    ptrs.f5 = paper_button;

    GtkWidget *scissor_button = gtk_button_new_with_label("Scissors");
    g_signal_connect(GTK_OBJECT(scissor_button), "clicked",
         GTK_SIGNAL_FUNC(scissor), &ptrs);
    gtk_widget_show  (scissor_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(scissor_button),
        TRUE, TRUE, 0);
    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);
    ptrs.f6 = scissor_button;

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
    GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(window),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_CLOSE,
					 	"%s", results);

    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(quit_button), "clicked",
         G_CALLBACK(window_delete), (gpointer) dialog);
    g_signal_connect_swapped (G_OBJECT (quit_button), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              G_OBJECT (window));

    gtk_widget_show  (quit_button);
    gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(quit_button),
        TRUE, TRUE, 0);

    gtk_widget_show  (hbox);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(hbox), FALSE, FALSE, 0);
    gtk_widget_set_sensitive(rock_button, FALSE);
    gtk_widget_set_sensitive(paper_button, FALSE);
    gtk_widget_set_sensitive(scissor_button, FALSE);

    gtk_widget_show  (vbox);
    gtk_widget_show  (window);
    gtk_main ();
    
    return 0;
}
