#ifndef CONVERT_FUNCTIONS
#define CONVERT_FUNCTIONS

#include <iostream>
#include <fstream> // responsável pela leitura e escrita de arquivos
#include <sstream>

#define COMP_TYPE 0
#define COMP_ID 1
#define COMP_X 3
#define COMP_Y 4
#define COMP_MirrorX 7
#define COPM_ROTATE 8

using std::cout;
using std::string;
using std::stoi;



bool componentes=false;
bool wires=false;
string comp_type;

void str_handler(string str[], int contador);
void comp_handler(string str[]);
void wire_handler(string str[]);
void prepare_latex_line(string str[]);


#endif 
