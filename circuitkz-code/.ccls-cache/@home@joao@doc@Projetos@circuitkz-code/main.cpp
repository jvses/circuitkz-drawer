/* 
 * Código que pretende converter circuitos do qucs para latex no circuitikz
 */
#include <iostream>
#include <fstream> // responsável pela leitura e escrita de arquivos
#include <sstream>
#include <cstring> 
#include <cmath>


#define COMP_TYPE 2
#define COMP_ID 3
#define COMP_X 5
#define COMP_Y 6
#define COMP_MirrorX 9
#define COPM_ROTATE 10
#define COMP3_TYPE 11

using std::cout;
using std::string;
using std::stoi;

bool componentes=false;
bool wires=false;
string comp_type;
int comp3_num = {0}; // contador de componentes de nó inicia em zero
int k = {0};//cria contador auxiliar e já reseta ele para próximo loop


void str_handler(string str[],  int contador);
void comp_handler(string str[]);
void wire_handler(string str[]);
void prepare_latex_line2p(string str[]);
void prepare_latex_line3p(string str[]);
void gnd(string str[]);

struct Struc_comp3{
  float LG[2], LD[2], LS[2];
  string nome;
  bool espelhado;
  int rotacao;
  string tipo_comp;
};

struct Struc_comp3 array_comp3[100];


int main(int argc, char **argv)
{


  if(argc > 1){
    string read_file_name = argv[1]; // pega o nome do argumento 1 e coloca na string 
    string sch_file_line;
    string word_readed;
    std::ifstream arquivo_lido(read_file_name); // abre arquivo para leitura
    if(arquivo_lido.is_open()){
      // getline(arquivo_lido, linha) -> pega linha por linha de um arquivo
      //getline(string, token, delimiter); -> pega palavra por palavra de uma string dependendo do delimitador
      
      while(getline(arquivo_lido, sch_file_line)){ // Lê linha por linha e põe na string sch_file_line 
        string string_vector[500];// vetor de strings que vai receber palavra por palavra para mandar pro string_handler
                                  //
        std::stringstream line_readed(sch_file_line);// prepara string para leitura de palavra por palavra na linha
        while(getline(line_readed, word_readed, ' ' )){ // loop de leitura de palavra por palavra
          string_vector[k] = word_readed;//acrescenta string nova no array de strings
          //cout << word_readed << '\n';
          k++;//aumenta o contador
        }
        str_handler(string_vector, k);

       //cout << k <<'\n';
      k=0;//resetando contador auxiliar;
      }
      arquivo_lido.close();
    }else{
      cout << "Não foi possível abrir o arquivo" << '\n';
    }

  }else{
    cout << "Uso: ./convert_circuit [file]" << '\n';
  }


  return 0;
}



void comp_handler(string str[]){
  string tipo = str[COMP_TYPE];
  if( !tipo.compare("<R")){
    comp_type = ") to[R=";
    prepare_latex_line2p(str);
  }else if(!tipo.compare("<C")){
    comp_type = ") to[C=";
    prepare_latex_line2p(str);
  }else if(!tipo.compare("<L")){
    comp_type = ") to[L=";
    prepare_latex_line2p(str);
  }else if(!tipo.compare("<Diode")){
    comp_type = ") to[D=";
    prepare_latex_line2p(str);
  }else if (!tipo.compare("<_MOSFET")){
    if(!str[COMP3_TYPE].compare( "\"nfet\"" )){
      comp_type = "nmos";
    }else if(!str[COMP3_TYPE].compare( "\"pfet\"" )){
      comp_type = "pmos";
    }
    prepare_latex_line3p(str); // função que lida com compoentes de 3 pernas entendidos como nós
  }else if(!tipo.compare("<_BJT")){
    if(!str[COMP3_TYPE].compare( "\"npn\"" )){
      comp_type = "npn";
    }else if(!str[COMP3_TYPE].compare( "\"pnp\"" )){
      comp_type = "pnp";
    }
    prepare_latex_line3p(str); // função que lida com compoentes de 3 pernas entendidos como nós
  }
  else if(!tipo.compare("<GND")){
    gnd(str);
  }
}

void gnd(string str[]){
  cout << "\\draw (" << round((stoi(str[COMP_X])) *1/3 )/10 << "," << -round((stoi(str[COMP_Y])) *1/3 ) / 10 << ") node[ground] {};" << '\n';

}


void prepare_latex_line2p(string str[]){
  float iaux_x, iaux_y, oaux_x, oaux_y;
  int rotate_aux = stoi(str[COPM_ROTATE]);

  //cout << " A var de rotate é: "<< rotate_aux << " e a string é: " << str[COPM_ROTATE] << '\n';
  switch(rotate_aux){
    case 0:
    case 2:
      iaux_y = oaux_y = -round( (stoi(str[COMP_Y])) *1/3 ) / 10;// o eixo Y é o mesmo mas com sinal trocado em ambos os pontos
      iaux_x = round( (stoi(str[COMP_X]) - 30 ) *1/3 ) / 10;
      oaux_x = round( (stoi(str[COMP_X]) + 30 ) *1/3 ) / 10;
      break;
    case 1:
    case 3:
      iaux_y = -round( (stoi(str[COMP_Y]) - 30 ) *1/3 ) / 10;
      oaux_y = -round( (stoi(str[COMP_Y]) + 30 ) *1/3 ) / 10;
      iaux_x = oaux_x = round( (stoi(str[COMP_X])) *1/3 ) / 10;// o eixo X é o mesmo, sem troca de sinal
      break;
    default:
      cout << "% Holve algo de errado na introdução das informações \n";
      break;
  }

  cout << "\\draw (" << iaux_x << "," << iaux_y << comp_type << str[COMP_ID] << "] (" << oaux_x << "," << oaux_y << ");" << '\n';

}

void prepare_latex_line3p(string str[]){ // função ajusta as orientações dos componentes de 3 pernas como nós e armazena os dados no array de struct pra checagem de conexão nas wires mais tarde;
  float aux_x = stoi(str[ COMP_X ]) , aux_y = stoi(str[COMP_Y]);
  //cout << "Os valores respectivos de aux x e y são: " << aux_x << " e " << aux_y << '\n';
  //size_t size_aux = sizeof(float) * 2;
  int rotate_aux = stoi(str[COPM_ROTATE]), mirrorx= stoi(str[COMP_MirrorX]);
  if(mirrorx){//caso tenha espelhamento (ainda não terminei de ajustar as coisas)
    array_comp3[comp3_num].espelhado = true;
switch(rotate_aux){
      case 2:
        array_comp3[comp3_num].LG[0] = aux_x + 30;
        array_comp3[comp3_num].LG[1] = aux_y;
        array_comp3[comp3_num].LS[0] = aux_x;
        array_comp3[comp3_num].LD[0] = aux_x;
        //cout << "////////" << comp_type << "////////" << !comp_type.compare("pmos") << "///" << (!comp_type.compare("npn") || !comp_type.compare("nmos"))<< "///" <<( !comp_type.compare("pnp") || !comp_type.compare("pmos") )<< '\n';
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LD[1] = aux_y - 30;
          array_comp3[comp3_num].LS[1] = aux_y + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LD[1] = aux_y + 30;
          array_comp3[comp3_num].LS[1] = aux_y - 30;
        }
        comp_type.append(", rotate=180");
        break;
      case 3:
        array_comp3[comp3_num].LG[0] = aux_x;
        array_comp3[comp3_num].LG[1] = aux_y - 30;
        array_comp3[comp3_num].LD[1] = aux_y;
        array_comp3[comp3_num].LS[1] = aux_y;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LD[0] = aux_x - 30;
          array_comp3[comp3_num].LS[0] = aux_x + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LD[0] = aux_x + 30;
          array_comp3[comp3_num].LS[0] = aux_x - 30;
        }

        comp_type.append(", rotate=90");
        /*
        array_comp3[comp3_num].LG[] = {aux_x , aux_y - 30};
        array_comp3[comp3_num].LD[] = {aux_x - 30, aux_y};
        array_comp3[comp3_num].LS[] = {aux_x + 30, aux_y};*/
        break;
      case 0:
        array_comp3[comp3_num].LG[0] = aux_x - 30;
        array_comp3[comp3_num].LG[1] = aux_y;
        array_comp3[comp3_num].LD[0] = aux_x;
        array_comp3[comp3_num].LS[0] = aux_x ;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LS[1] = aux_y - 30;
          array_comp3[comp3_num].LD[1] = aux_y + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LS[1] = aux_y + 30;
          array_comp3[comp3_num].LD[1] = aux_y - 30;
        }
        comp_type.append(", rotate=0");
        /*
        array_comp3[comp3_num].LG[] = {aux_x - 30 , aux_y};
        array_comp3[comp3_num].LD[] = {aux_x , aux_y + 30};
        array_comp3[comp3_num].LS[] = {aux_x , aux_y - 30};*/
        break;
      case 1:
        array_comp3[comp3_num].LG[0] = aux_x;
        array_comp3[comp3_num].LG[1] = aux_y + 30;
        array_comp3[comp3_num].LD[1] = aux_y;
        array_comp3[comp3_num].LS[1] = aux_y ;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LS[0] = aux_x - 30;
          array_comp3[comp3_num].LD[0] = aux_x + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LS[0] = aux_x + 30;
          array_comp3[comp3_num].LD[0] = aux_x - 30;
        }

        comp_type.append(", rotate=-90");
        /*
        array_comp3[comp3_num].LG[] = {aux_x , aux_y + 30};
        array_comp3[comp3_num].LD[] = {aux_x + 30, aux_y};
        array_comp3[comp3_num].LS[] = {aux_x - 30, aux_y};*/
        break;
      default:
        cout << "% Holve algo de errado na introdução das informações \n";
        break;
      }
    comp_type.append(", yscale=-1 ");// apesar do qucs dizer que tá espelhado em X a inversão tá em Y.
  }else{// caso não haja espelhamento
    array_comp3[comp3_num].espelhado = false;
    switch(rotate_aux){
      case 0:
        array_comp3[comp3_num].LG[0] = aux_x - 30;
        array_comp3[comp3_num].LG[1] = aux_y;
        array_comp3[comp3_num].LD[0] = aux_x;
        array_comp3[comp3_num].LS[0] = aux_x ;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LD[1] = aux_y - 30;
          array_comp3[comp3_num].LS[1] = aux_y + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){

          array_comp3[comp3_num].LD[1] = aux_y + 30;
          array_comp3[comp3_num].LS[1] = aux_y - 30;
        }

        comp_type.append(", rotate=0");
        /*
        array_comp3[comp3_num].LG[] = {aux_x - 30 , aux_y};
        array_comp3[comp3_num].LD[] = {aux_x , aux_y - 30};
        array_comp3[comp3_num].LS[] = {aux_x , aux_y + 30};*/
        break;
      case 1:
        array_comp3[comp3_num].LG[0] = aux_x;
        array_comp3[comp3_num].LG[1] = aux_y + 30;
        array_comp3[comp3_num].LD[1] = aux_y;
        array_comp3[comp3_num].LS[1] = aux_y;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LS[0] = aux_x + 30;
          array_comp3[comp3_num].LD[0] = aux_x - 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LS[0] = aux_x - 30;
          array_comp3[comp3_num].LD[0] = aux_x + 30;
        }

        comp_type.append(", rotate=90");
        /*
        array_comp3[comp3_num].LG[] = {aux_x , aux_y + 30};
        array_comp3[comp3_num].LD[] = {aux_x - 30, aux_y};
        array_comp3[comp3_num].LS[] = {aux_x + 30, aux_y};*/
        break;
      case 2:
        array_comp3[comp3_num].LG[0] = aux_x + 30;
        array_comp3[comp3_num].LG[1] = aux_y;
        array_comp3[comp3_num].LD[0] = aux_x;
        array_comp3[comp3_num].LS[0] = aux_x ;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LS[1] = aux_y - 30;
          array_comp3[comp3_num].LD[1] = aux_y + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){
          array_comp3[comp3_num].LS[1] = aux_y + 30;
          array_comp3[comp3_num].LD[1] = aux_y - 30;
        }

        comp_type.append(", rotate=180");
        /*
        array_comp3[comp3_num].LG[] = {aux_x + 30 , aux_y};
        array_comp3[comp3_num].LD[] = {aux_x , aux_y + 30};
        array_comp3[comp3_num].LS[] = {aux_x , aux_y - 30};*/
        break;
      case 3:
        array_comp3[comp3_num].LG[0] = aux_x;
        array_comp3[comp3_num].LG[1] = aux_y - 30;
        array_comp3[comp3_num].LD[1] = aux_y;
        array_comp3[comp3_num].LS[1] = aux_y;
        if(!comp_type.compare("npn") || !comp_type.compare("nmos")){
          array_comp3[comp3_num].LS[0] = aux_x - 30;
          array_comp3[comp3_num].LD[0] = aux_x + 30;
        }else if( !comp_type.compare("pnp") || !comp_type.compare("pmos") ){

          array_comp3[comp3_num].LS[0] = aux_x + 30;
          array_comp3[comp3_num].LD[0] = aux_x - 30;
        }

        comp_type.append(", rotate=-90");
        /*
        array_comp3[comp3_num].LG[] = {aux_x , aux_y - 30};
        array_comp3[comp3_num].LD[] = {aux_x + 30, aux_y};
        array_comp3[comp3_num].LS[] = {aux_x - 30, aux_y};*/
        break;
      default:
        cout << "% Holve algo de errado na introdução das informações \n";
        break;
    }
  }



 /* //array_comp3[comp3_num].tipo_comp = comp_type;
  for (int i=0; i < k; i++){
  cout << str[i] << " ";
  }
  cout << '\n';
*/  
//  cout << "Este componente é: " << str[COMP_ID] << " com os valores respectivos LG,LD e LS: ";
//  cout << array_comp3[comp3_num].LG[0] << " " << array_comp3[comp3_num].LG[1] << " "<< array_comp3[comp3_num].LD[0] << " "<<  array_comp3[comp3_num].LD[1] << " "<< array_comp3[comp3_num].LS[0] << " "<< array_comp3[comp3_num].LS[1] << '\n';
  array_comp3[comp3_num].rotacao = rotate_aux;
  array_comp3[comp3_num].nome = str[COMP_ID];
  aux_x = round( (aux_x) *1/3) / 10;
  aux_y = -round( (aux_y) *1/3 ) / 10 ;
  cout << "\\draw (" << aux_x << "," << aux_y << ") node[" << comp_type << "] (" << array_comp3[comp3_num].nome << ") {" << array_comp3[comp3_num].nome << "};" << '\n'; 
    //  cout << "detectado componente do tipo node" << '\n';
  comp3_num++;
}


void wire_handler(string str[]){
  float iaux_x, iaux_y, oaux_x, oaux_y;// variaveis que vão aramazenar os valores dos endereços para o circuitikz
  string wire_tikz1, wire_tikz2;
  str[2].erase(0, 1);
  float ad1x,ad1y,ad2x,ad2y;//valores para comparação com os addrs das structs. Antes de converter para o plano X-Y do circuitikz
   ad1x = stoi(str[2]);
   ad1y = stoi(str[3]);
   ad2x = stoi(str[4]);
   ad2y = stoi(str[5]);
   
  iaux_x = round((stoi(str[2])) *1/3 ) / 10;// valores convertidos para o plano do circuitikz
  iaux_y = -round((stoi(str[3])) *1/3 ) / 10;
  oaux_x = round((stoi(str[4])) *1/3 ) / 10;
  oaux_y = -round((stoi(str[5])) *1/3 ) / 10;
  
  bool ja_pegou_um = false, ja_pegou_outro = false;
  string conexao;
  for(int i=0; i<comp3_num; i++){
    //checagem dos pontos de partida
    if( ad1x == array_comp3[i].LG[0] && ad1y == array_comp3[i].LG[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz1 = wire_tikz1 + " (" + array_comp3[i].nome + ".G) " ;
      ja_pegou_um = true;
      break;
    }else if( ad1x == array_comp3[i].LD[0] && ad1y == array_comp3[i].LD[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz1 = wire_tikz1 + " (" + array_comp3[i].nome + ".D)" ;
      ja_pegou_um = true;
      break;
    }else if( ad1x == array_comp3[i].LS[0] && ad1y == array_comp3[i].LS[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz1 = wire_tikz1 + " (" + array_comp3[i].nome + ".S)" ;
      //cout << "passei por i S\n";
      ja_pegou_um = true;
      break;
    }
  }
    string istrx,istry,ostrx,ostry;
    istrx = std::to_string(iaux_x);
    istry = std::to_string(iaux_y);
    ostrx = std::to_string(oaux_x);
    ostry = std::to_string(oaux_y);

    int ipx,ipy,opx,opy;
    ipx = istrx.find(".");
    ipy = istry.find(".");
    opx = ostrx.find(".");
    opy = ostry.find(".");
    
    istrx.erase(ipx+2, ipx+5);
    istry.erase(ipy+2, ipy+5);
    ostrx.erase(opx+2, opx+5);
    ostry.erase(opy+2, opy+5);

    
    if(!ja_pegou_um){
      wire_tikz1 = wire_tikz1 + " (" + istrx + "," + istry +  ")";
    }

  for(int i=0; i<comp3_num; i++){
    //checagem dos pontos de chegada
    if( ad2x == array_comp3[i].LG[0] && ad2y == array_comp3[i].LG[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz2 = wire_tikz2 + " (" + array_comp3[i].nome + ".G);";
      ja_pegou_outro = true;
      //cout << 
      break;
    }else if( ad2x == array_comp3[i].LD[0] && ad2y == array_comp3[i].LD[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz2 = wire_tikz2 + " (" + array_comp3[i].nome + ".D);" ;
      ja_pegou_outro = true;
      break;
    }else if( ad2x == array_comp3[i].LS[0] && ad2y == array_comp3[i].LS[1] ){// se alinha começa no LG de algum componente com nó
      wire_tikz2 = wire_tikz2 + " (" + array_comp3[i].nome + ".S);" ;
      ja_pegou_outro = true;
      //cout << "passei por i S\n";
      break;
    }
  }

  if(ja_pegou_um || ja_pegou_outro){
    if(ad1x == ad2x){
      conexao = " |- ";
    }else if(ad1y == ad2y){
      conexao = " -| ";
    }else{
      conexao = " to[short] ";  
    }
  }


  if(ja_pegou_um && !ja_pegou_outro){
    wire_tikz2 = wire_tikz2 + "(" + ostrx + "," + ostry +  ");";
   }
  
  if(!ja_pegou_um && !ja_pegou_outro){
    conexao = " to[short] ";
    wire_tikz2 = wire_tikz2 + "(" + ostrx + "," + ostry +  ");";
  }
  

  cout << "\\draw " << wire_tikz1 << conexao << wire_tikz2 << '\n'; // comando que printa a linha

}


void str_handler(string str[] , int contador){
  if(contador == 1 ){// só vai fazer a troca da true/false se a linha tiver um componente só
    if(str[0] == "<Components>"){
      componentes = true;
      cout << "\%Há comandos que podem te auxiliar na exibição do seu circuito\n" << 
"%\\ctikzset{tripoles/mos style=arrows} \% este coloca as pontas nos transistores\n" << 
"%\\ctikzset{transistors/arrow pos=end}\n" <<
"%\\ctikzflipxy{NAME} \% Esse espelha o nome do componente que foi jirado nos eixos x e y\n" <<
"%\\ctikzflipx{NAME} \% Esse espelha os nome só no eixo x\n" << 
  "%\\ctikzflipy{NAME} \% e esse só no eixo y\n";
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
  } else{// se o contador for diferente de 1 aí ele chama as outras funções
       if(componentes){
          comp_handler(str);
        }
        if(wires){
        wire_handler(str);
       // cout << comp3_num << '\n';
        }
  }
}

