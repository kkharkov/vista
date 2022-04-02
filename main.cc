// main.cc
#include <iostream>
#include "webview.h"

gboolean manager_launch_keypress (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Control_L &&  GDK_KEY_Control_R && GDK_KEY_Alt_L && GDK_KEY_Alt_L){
        printf("Manager Launched");
        gtk_widget_show(widget);
        return TRUE;
    }
    return FALSE;
}


static void 
launch_wallpaper(GtkApplication *app) {
  webview::webview w(false, nullptr);
  w.hide_header();
  w.keep_below(TRUE);
  w.set_size(1000, 1000, WEBVIEW_HINT_FIXED);
  w.set_max();
  // w.set_size(screen.width, screen.height, WEBVIEW_HINT_MAX);
  w.set_title("TUX");
  // w.navigate("https://en.m.wikipedia.org/wiki/Main_Page");
  
  // extern variable to trigger reload?
  w.navigate("file:///home/kk/Documents/Personal/vista/assets/ChonkerAlpha/index.html");
  w.run();
}

static void
launch_chooser() {
  g_print("Hello World\n");
}

static void
launch_wp_manager(GtkApplication *app) {
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Manager");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  g_signal_connect (G_OBJECT (window), "key_press_event",
        G_CALLBACK (manager_launch_keypress), NULL);
  gtk_widget_show(window);
  
}

int main(int argc, char* argv[]) {
  auto app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  //g_signal_connect(app, "launch_wallpaper", G_CALLBACK (activate), NULL);
  launch_wallpaper(GTK_APPLICATION(app));
  return 0;
}