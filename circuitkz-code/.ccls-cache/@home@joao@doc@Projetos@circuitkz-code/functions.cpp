#include "functions.h"


void comp_handler(string str[]){
  string tipo = str[COMP_TYPE];
  if( !tipo.compare("<R")){
    comp_type = ") to[R=";
  }else if(!tipo.compare("<C")){
    comp_type = ") to[C=";
  }else if(!tipo.compare("<L")){
    comp_type = ") to[L=";
  }else if(!tipo.compare("<Diode")){
    comp_type = ") to[D=";
  }
  prepare_latex_line(str);


}

void prepare_latex_line(string str[]){
  int iaux_x, iaxu_y, oaux_x, oaux_y;
  switch(stoi(str[COPM_ROTATE])){
    case 0:
    case 2:
      iaxu_y = oaux_y = -((stoi(str[COMP_Y])/20)*2/3 ) ;// o eixo Y é o mesmo mas com sinal trocado em ambos os pontos
      iaux_x = (((stoi(str[COMP_X]) - 30 )/20) *2/3);
      oaux_x = (((stoi(str[COMP_X]) + 30 )/20) *2/3);
      break;
    case 1:
    case 3: 
      iaxu_y = -(((stoi(str[COMP_Y]) - 30 )/20)*2/3);
      oaux_y = -(((stoi(str[COMP_Y]) + 30 )/20) *2/3);
      iaux_x = oaux_x = ((stoi(str[COMP_X])/20) *2/3);// o eixo X é o mesmo, sem troca de sinal
      break;
    default:
      cout << "% Holve algo de errado na introdução das informações \n";
      break;
  }
  
  cout << "\\draw (" << iaux_x << "," << iaxu_y << comp_type << str[COMP_ID] << "] (" << oaux_x << "," << oaux_y << ");" << '\n';

}


void wire_handler(string str[]){
  cout << "ainda não tenho suporte para as linha kkkk" << '\n';

}


void str_handler(string str[], int contador){
  if(contador == 1 ){
    if(str[0] == "<Components>"){
      componentes = true;
    }
    else if(str[0]== "</Components>"){
      componentes = false;
    }
    else if(str[0] == "<Wires>"){
      wires = true;
    }
    else if(str[0] == "</Wires>"){
      wires = false;
    }
  }
  
  if(componentes){
    comp_handler(str);
  }
  if(wires){
    wire_handler(str);
  }

}
