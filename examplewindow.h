#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <iostream>
//#include "myarea.h"

//////////////////DrawingArea//////////////////

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

  //void fix_lines(bool fix = true);

protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

/*private:*/
/*  double m_fix;*/
};

////////////////APP Window//////////////////////

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_clicked();

private:
  Gtk::Box m_TopBox,m_Vbox; // caixas do topo e lateral com os botões
	Gtk::Grid m_Grid;
	Gtk::Button m_Button_Close;
  MyArea m_Area_draw;
  //Gtk::CheckButton m_Button_FixLines;
};

#endif //GTKMM_EXAMPLEWINDOW_H
