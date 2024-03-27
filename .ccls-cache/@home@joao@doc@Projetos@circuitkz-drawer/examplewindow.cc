#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_HBox(Gtk::Orientation::HORIZONTAL),
	m_Button_Close("Close")
{
  set_title("Circuit Drawer");
	set_size_request(300,300);
	
  set_child(m_HBox);

  m_HBox.append(m_Grid);
  m_HBox.append(m_Area_draw);
	


	/* set the spacing to 10 on x and 10 on y */
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);


	
	  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  for(int i = 0; i < 1; i++)
  {
     for(int j = 0; j < 2; j++)
     {
        char buffer[32];
        sprintf(buffer, "botão (%d,%d)\n", i, j);
        auto pButton = Gtk::make_managed<Gtk::ToggleButton>(buffer);
        m_Grid.attach(*pButton, i, j, 1, 1);
     }
  }

  //Add a button to close window:
  m_Grid.attach(m_Button_Close, 2, 0);
  m_Button_Close.set_margin(20);
	m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_toggled) );
  set_default_widget(m_Button_Close);


  // Synchonize the drawing in m_Area_Lines with the state of the toggle button.
  on_button_toggled();
}


ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_toggled()
{
  m_Area_draw.fix_lines(m_Button_Close.on_clicked());
}

