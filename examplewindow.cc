#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_HBox(Gtk::Orientation::HORIZONTAL),
  m_Button_FixLines("Fix lines")
{
  set_title("Thin lines example");

  m_HBox.append(m_Area_Lines);
  m_HBox.append(m_Button_FixLines);

  set_child(m_HBox);

  m_Button_FixLines.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_toggled));

  // Synchonize the drawing in m_Area_Lines with the state of the toggle button.
  on_button_toggled();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_toggled()
{
  m_Area_Lines.fix_lines(m_Button_FixLines.get_active());
}
