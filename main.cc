// main.cc
#include <iostream>
#include "webview.h"

gboolean show_manager (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Home){
        std::cout << "SHOW MANAGER" << std::endl;
        gtk_widget_show(widget);
        return TRUE;
    }
    return FALSE;
}


static void
launch_wallpaper(std::string filepath) {
  webview::webview w(true, nullptr);
  w.hide_header();
  w.keep_below(TRUE);
  w.set_size(1000, 1000, WEBVIEW_HINT_FIXED);
  w.set_max(); // needs more robust solution
  w.set_title("TUX");
  // w.navigate("https://en.m.wikipedia.org/wiki/Main_Page");
  if(filepath.empty()) {
    filepath = "/home/kk/Documents/Personal/vista/assets/ChonkerAlpha/index.html"; // either launch the chooser or figure out local paths
  }
  std::string path = "file://" + filepath;
  w.navigate(path);
  w.run();
}

static void
launch_wp_chooser(GtkApplication *app, GtkWindow *parent_window) {
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  std::string filename;

  dialog = gtk_file_chooser_dialog_new ("Open File", parent_window, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
  gtk_widget_show_all(GTK_WIDGET(dialog));

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    g_print(filename.c_str());
    std::cout << filename << std::endl; //debug
  }
  gtk_widget_destroy (dialog);
  launch_wallpaper(filename);
}

static void
activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *wp_choose_button;
  GtkWidget *button_box;

  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

  window = gtk_application_window_new(app);
  wp_choose_button = gtk_button_new_with_label("Choose Wallpaper");

  gtk_window_set_title(GTK_WINDOW(window), "Manager");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

  button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER(window), button_box);
  gtk_container_add(GTK_CONTAINER(button_box), wp_choose_button);

  g_signal_connect (window, "key_press_event",
        G_CALLBACK (show_manager), GTK_WIDGET(window));
  g_signal_connect (wp_choose_button, "clicked",
        G_CALLBACK (launch_wp_chooser), GTK_WINDOW(window));

  gtk_widget_show_all(window);
}

int main(int argc, char* argv[]) {
  auto app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  int status;
  gpointer user_data;
  
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}