#include "examplewindow.h"

////DrawingArea functions/////////

MyArea::MyArea() //: m_fix (0)
{
//  set_content_width(1200);
//  set_content_height(720);
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}
void MyArea::draw_component(char comp){

}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;
	
	cr->set_source_rgb(1, 1, 1); // seleciona cor para branco
	cr->paint(); //pinta a tela inteira de branco
	
  cr->set_line_width(5.0);

  // draw red lines out from the center of the window
  cr->set_source_rgb(0.8, 0.0, 0.0);
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);
  cr->stroke();
//  cr->move_to(xc,yc);
	//arc (double xc, double yc, double radius, double angle1, double angle2) ângulos são dados em radianos
  cr->arc(xc,yc,50,0,7);
   cr->set_source_rgb(0.8, 1.0, 0.0);
  // preenche o ultimo desenho feito antes da quebra com o stroke. Nesse caso pinta o circulo desenhado
  cr->fill(); 
  
  cr->stroke();
}



///////////APP window functions//////////////

ExampleWindow::ExampleWindow()
: m_TopBox(Gtk::Orientation::HORIZONTAL),
	m_Vbox(Gtk::Orientation::VERTICAL),
	m_Button_Close("Close")
{
  set_title("Circuit Drawer");
	set_size_request(800,600);
	
  set_child(m_TopBox); // seta a caixa topo como filho da janela principal
	
	// Show the scrollbars da área de desenho only when they are necessary:
  m_ScrollWin_DrawArea.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrollWin_DrawArea.set_expand(); // ajusta ao tamanho da área
	
  m_Vbox.append(m_Grid);
  m_Vbox.append(m_Button_Close);
  m_TopBox.append(m_Vbox);
  m_ScrollWin_DrawArea.set_child(m_Area_draw);
  m_TopBox.append(m_ScrollWin_DrawArea);
	


	/* set the spacing to 10 on x and 10 on y */
  m_Grid.set_row_spacing(2);
  m_Grid.set_column_spacing(2);


	
	  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  for(int i = 0; i < 3; i++)
  {
     for(int j = 0; j < 2; j++)
     {
        char buffer[32];
        sprintf(buffer, "botão (%d,%d)\n", i, j);
        auto pButton = Gtk::make_managed<Gtk::Button>(buffer);
        m_Grid.attach(*pButton, i, j);
     }
  }

  //Add a button to close window:
  	//m_Grid.attach(m_Button_Close, 0, 3);
  m_Button_Close.set_margin(10);
	m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clicked) );
  set_default_widget(m_Button_Close);


  // Synchonize the drawing in m_Area_Lines with the state of the toggle button.
  on_button_clicked();
}


ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
//  m_Area_draw.fix_lines(m_Button_Close.on_button_clicked());
	std::cout << "Apertei o botão\n";
}

