#include <iostream>
#include <sstream>
//#include <vector>
#include <cstring>
#include <fstream>


using std::cout;
using std::string;


int main(int argc, char **argv)
{
/*
  string linha;
  std::stringstream ss(linha);
  string teste = "ola";
  string string_auxiliar;
  string vetor_de_strings[500];
  int i={0};
  while(getline(ss,string_auxiliar, ' ')){
    vetor_de_strings[i]=string_auxiliar;
    i++;
  }
  cout << "A primeira string foi: " << vetor_de_strings[0] << '\n';
  /*
  for(int k ={0}; k < i; k++){
    cout << vetor_de_strings[k] << '\n';
  }*/
  string palavra = "ola";

  cout << "a comparação falsa é: " << palavra.compare("oi") << "|| a comparação verdadeira é " << palavra.compare("ola") << '\n';
/*  auto var = teste.compare("ola");
  cout << var << '\n';
  
  if(!teste.compare("ola")){
    cout << "Elas saõ iguais, o strncmp deu zero" << '\n';
  }else{
    cout << "algo deu errao, ela deu diferente" << '\n';
  } */

  return 0;
}

