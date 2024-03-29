#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

  void fix_lines(bool fix = true);

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

private:
  double m_fix;
};

#endif // GTKMM_EXAMPLE_MYAREA_H
