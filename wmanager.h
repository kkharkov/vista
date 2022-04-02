#include <gtkmm.h>

class WpManagerWindow : public Gtk::Window
{
public:
  WpManagerWindow();
};

WpManagerWindow::WpManagerWindow()
{
  set_title("Basic application");
  set_default_size(200, 200);
}
