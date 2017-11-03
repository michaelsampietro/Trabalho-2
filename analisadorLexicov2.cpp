// Trabalho 1 de Compiladores: Analisador Léxico
// 
// Alunos: Michael Alexandre da Silva Sampietro (132583)
//         Renan Fernandes Silva (132591)

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <queue>

#define RE -1

using namespace std;

typedef struct entrada {
  string token;
  string lexema;
  string tipo;
} entrada;

int linha = 1, coluna = 1;
char c;
string buffer = "";
ifstream file;
int estado = 0;
char aux;

std::map<int, string> estadosFinais;

std::map<string, entrada> simbolos;

queue<string> filaSimbolos;


int tabelaTransicoes[20][28] = {
  /*      0,  1,  2,  3,   4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27*/
  /*      D,  ",  L,  {, EOF,  >,  <, <=, >=, <>,  =, <-,  +,  -,  *,  /,  (,  ),  ;, \t, \n,  ., \.,  E,  _,  }, " ",Resto*/
  /*0*/ { 1,  7, 10, 11,  13, 14, 14, 14, 14, 14, 14, 15, 16, 16, 16, 16, 17, 18, 19,  0,  0, RE, RE, RE, RE, RE,  0, RE},
  /*1*/ { 1, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE,  2,  4, RE, RE, RE, RE},
  /*2*/ { 3, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*3*/ { 3, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE,  4, RE, RE, RE, RE},
  /*4*/ { 5, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE,  6,  6, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*5*/ { 5, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*6*/ { 5, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*7*/ { 8,  9,  8,  8,  RE,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8},
  /*8*/ { 8,  9,  8,  8,  RE,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8},
  /*9*/ {RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*10*/{10, RE, 10, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, 10, RE, RE, RE},
  /*11*/{11, 11, 11, 11,  RE, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 11, 11},
  /*12*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*13*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*14*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*15*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*16*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*17*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*18*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
  /*19*/{RE, RE, RE, RE,  RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE},
};

void abrirArquivo(ifstream &arquivo) {
  arquivo.open("texto.alg", ifstream::in);
}

char lerArquivo(ifstream &arquivo) {
  char letra = RE;

  // Retorna verdadeiro se ele não for EOF, erro logico ou erro de I/O
  if(arquivo.good())
    letra = arquivo.get();

  return letra;
}

void fecharArquivo(ifstream &arquivo) {
  arquivo.close();
}

// Insere na hash da tabela de símbolos
void adicionarSimbolo(std::map<string, entrada> &simbolos, string token, string lexema, string tipo) {
  entrada auxiliar;

  auxiliar.token = token;
  auxiliar.lexema = lexema;
  auxiliar.tipo = tipo;

  // Usa lexema para chave da struct auxiliar 
  simbolos.insert (std::pair<string, entrada> (lexema, auxiliar));
}


void imprimirLexema(std::map<string, entrada> &simbolos, std::map<int, string> &estadosFinais, int estado, string buffer) {
  // Se o lexema está na tabela de símbolos, imprime
  if(simbolos.find(buffer)->second.lexema == buffer && buffer != "") {
    cout << "Token: " << simbolos.find(buffer)->second.token << "\tLexema: " << simbolos.find(buffer)->second.lexema << "\tTipo: " << simbolos.find(buffer)->second.tipo << endl;
    filaSimbolos.push(simbolos.find(buffer)->second.token); 
  } else if (buffer != "") {
    // Se o estado atual do lexema é um estado final, adiciona à tabela de símbolos (apenas id por enquanto) e imprime
    if (estadosFinais.find(estado)->first == estado) {
      if(estado == 10) {
        // Adiciona na tabela de simbolos
        adicionarSimbolo(simbolos, estadosFinais.find(estado)->second, buffer, "");
        std::cout << "\nAdicionou:\t\n";
      }

      cout << "Token: " << estadosFinais.find(estado)->second << "\tLexema: " << buffer;
      filaSimbolos.push(estadosFinais.find(estado)->second); 
      
      if(estado == 1) {
        cout << "\tTipo: inteiro" << "\n";
      }
      else if(estado == 3 || estado == 5) {
        cout << "\tTipo: real" << "\n";
      }
      else if(estado == 9) {
        cout << "\tTipo: string" << "\n";        
      }
      else {
        cout << "\tTipo: " << "\n";
      }
    } else { // Se estado atual não é estado final, imprime erro.
      std::cout << "Erro! Linha: " << linha << "\tColuna: " << coluna << '\n';
      fecharArquivo(file);
      exit(1);

    }
  } else if (buffer == "" && estado == 13) { // Verifica se é EOF e imprime.
    std::cout << "Token: " << estadosFinais.find(estado)->second << "\tLexema: \tTipo: \n";
  }
}

// Função que analisa, char por char, até encontrar um lexema.
void analisadorLexico (char c) {
  // Se for número, adiciona ao buffer e muda o estado
  if(isdigit(c)) {
      estado = tabelaTransicoes[estado][0];
      buffer = buffer + c;
    } // Se o numero estiver em notação cientifica, modifique estado e acrescente ao buffer. 
    else if (c == 'E' && tabelaTransicoes[estado][23] == 4) { 
      estado = tabelaTransicoes[estado][23];
      buffer = buffer + c;
    } // Se for letra, adiciona ao buffer e muda estado 
    else if (isalpha(c)) {
      estado = tabelaTransicoes[estado][2];
      buffer = buffer + c;
    } // Quebras de linha 
    else if (c == '\n') {
      linha += 1; // acrescenta a linha
      coluna = 1; // reseta a coluna

      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][20] == 8 || tabelaTransicoes[estado][20] == 11) {
        estado = tabelaTransicoes[estado][20];
        buffer = buffer + c;
      } else { // Imprime lexema, reseta buffer e estado.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == ' ') {
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][26] == 8 || tabelaTransicoes[estado][26] == 11) {
        estado = tabelaTransicoes[estado][26];
        buffer = buffer + c;
      } else { // Imprime lexema, reseta buffer e estado.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == '\t') {
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][19] == 8 || tabelaTransicoes[estado][19] == 11) {
        estado = tabelaTransicoes[estado][19];
        buffer = buffer + c;
      } else { // Imprime lexema, reseta buffer e estado.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == ';') {
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][18] == 8 || tabelaTransicoes[estado][18] == 11) {
        estado = tabelaTransicoes[estado][18];
        buffer = buffer + c;
      } else {
        // Imprime lexema
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = ";"; 
        estado = tabelaTransicoes[0][18];

        // imprime ; e reseta buffer e estado.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == '(') {
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][16] == 8 || tabelaTransicoes[estado][16] == 11) { // se estiver dentro de comentário/string
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][16];
      } else {
        // Imprime lexema
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "(";
        estado = tabelaTransicoes[0][16];

        // imprime (, reseta buffer e estado
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == ')') {
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][17] == 8 || tabelaTransicoes[estado][17] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][17];
      } else {
        // Imprime lexema
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = ")";
        estado = tabelaTransicoes[0][17];

        // imprime (, reseta buffer e estado
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == '\"') {
      // Verifica se é fecha aspas
      if (tabelaTransicoes[estado][1] == 9) { 
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][1];

        // Imprime toda a string + ". Zera estado e buffer.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        estado = 0;
        buffer = "";
      } else if (tabelaTransicoes[estado][1] == 7) { // Verifica se é abre aspas
        // Imprime lexema anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta o buffer como abre aspas e muda o estado.
        buffer = "\"";
        estado = tabelaTransicoes[estado][1];
      } else if (tabelaTransicoes[estado][1] == 11) { // Verifica se está dentro de comentário.
        // Se estiver, apenas acrescenta ao buffer e muda estado. 
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][1];
      } else { // se não for nem abre aspas, fecha aspas ou estiver em um comentario, é RE
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        estado = tabelaTransicoes[0][1];
        buffer = "\"";
      }
    } else if (c == '<') {
      // Verifica se esta em comentario ou string
      if (tabelaTransicoes[estado][6] == 8 || tabelaTransicoes[estado][6] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][6];
      } else { // Senão, verifica o próximo caractere. (Pode ser <=, etc..)
        aux = lerArquivo(file);
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Se o proximo caractere apos o < for um -, então o buffer vira <- e muda de estados. 
        // Os outros casos seguem o mesmo padrão.
        if (aux == '-'){ 
          buffer = "<-";
          estado = tabelaTransicoes[0][11];
        } else if (aux == '=') {
          buffer = "<=";
          estado = tabelaTransicoes[0][7];
        } else if (aux == '>') {
          buffer = "<>";
          estado = tabelaTransicoes[0][9];
        } else { // Se o próximo caractere não for nenhum dos anteriores, seta o buffer como <, 
                 // volta o estado e retorna o caractere lido ao arquivo
          buffer = "<";
          estado = tabelaTransicoes[0][6];

          file.unget();
        }
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == '>') {
      // Verifica se esta em string ou comentario.
      if (tabelaTransicoes[estado][5] == 8 || tabelaTransicoes[estado][5] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][5];
      } else {
        aux = lerArquivo(file);
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Se o proximo caractere apos o > for um =, então o buffer vira >= e muda de estados. 
        if (aux == '=') {
          buffer = ">=";
          estado = tabelaTransicoes[0][8];
        } else {// Se o próximo caractere não for =, seta o buffer como >, 
                 // volta o estado e retorna o caractere lido ao arquivo
          buffer = ">";
          estado = tabelaTransicoes[0][5];

          file.unget();
        }
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      }
    } else if (c == '=') {
      // Verifica se esta dentro de comentario ou string
      if (tabelaTransicoes[estado][10] == 8 || tabelaTransicoes[estado][10] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][10];
      } else {
        // Imprime lexema anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como igual e imprime.
        buffer = "="; 
        estado = tabelaTransicoes[0][10];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        buffer = "";
        estado = 0;
      }
    } else if (c == '+') {
      // Verifica se é comentario, string ou se está lendo um numeral (E+...)
      if (tabelaTransicoes[estado][12] == 8 || tabelaTransicoes[estado][12] == 11 || tabelaTransicoes[estado][12] == 6) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][12];
      } else {
        // Imprime anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como + e imprime
        buffer = "+";
        estado = tabelaTransicoes[0][12];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        buffer = "";
        estado = 0;
      }
    } else if (c == '-') {
      // Verifica se é comentario, string ou se está lendo um numeral (E-...)
      if (tabelaTransicoes[estado][13] == 8 || tabelaTransicoes[estado][13] == 11 || tabelaTransicoes[estado][13] == 6) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][13];
      } else {
        // Imprime anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como - e imprime
        buffer = "-";
        estado = tabelaTransicoes[0][13];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        estado = 0;
      }
    } else if (c == '*') {
      // Verifica se é comentario, string
      if (tabelaTransicoes[estado][14] == 8 || tabelaTransicoes[estado][14] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][14];
      } else {
        // Imprime anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como * e imprime
        buffer = "*";
        estado = tabelaTransicoes[0][14];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        buffer = "";
        estado = 0;
      }
    } else if (c == '/') {
      // Verifica se é comentario, string
      if (tabelaTransicoes[estado][15] == 8 || tabelaTransicoes[estado][15] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][15];
      } else {
        // Imprime anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como / e imprime
        buffer = "/";
        estado = tabelaTransicoes[0][15];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        buffer = "";
        estado = 0;
      }
    } else if (c == '{') {
      // Verifica se está dentro de uma string ou comentário
      if (tabelaTransicoes[estado][3] == 8 || tabelaTransicoes[estado][3] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][3];
      } else { // Se não for comentário nem string, imprime o anterior.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Modifica estado e seta o buffer como abre chaves.
        estado = tabelaTransicoes[0][3];
        buffer = "{";
      }
    } else if (c == '}') {
      // Verifica se está dentro de uma string.
      if (tabelaTransicoes[estado][25] == 8) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][25];
      } else if (tabelaTransicoes[estado][25] == 12) { // Se estiver fechando um comentário
        buffer = buffer + c; // acrescenta fecha chaves ao buffer
        estado = tabelaTransicoes[estado][25]; // muda o estado

        // Imprime o comentário completo.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        buffer = "";
        estado = 0;
      } else {
        cout << "ERRO: Símbolo entrado incorretamente.\nLinha: " << linha << " Coluna: " << coluna << endl;
      }
    } else if (c == '.') {
      // Verifica se não está dentro de um comentário ou string.
      if (tabelaTransicoes[estado][21] == 8 || tabelaTransicoes[estado][21] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][21];
      } else { 
        // Imprime lexema anterior.
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como ., modifica o estado e imprime.
        buffer = ".";
        estado = tabelaTransicoes[0][21];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado
        buffer = "";
        estado = 0;
      }
    } else if (c == '\\') {
      // Devemos ler o próximo caractere, pois pode ser \.
      aux = lerArquivo(file);
      if (aux == '.') { // Se o próximo for um ponto
        // Verifica se está dentro de uma string, comentário ou numeral.
        if (tabelaTransicoes[estado][22] == 8 || tabelaTransicoes[estado][22] == 11 || tabelaTransicoes[estado][22] == 2) {
          buffer = buffer + '.'; // Adiciona . ao buffer
          estado = tabelaTransicoes[estado][22];
        } else {
          // Imprime anterior
          imprimirLexema(simbolos, estadosFinais, estado, buffer);

          // Seta buffer como ., muda estado e imprime . 
          buffer = ".";
          estado = tabelaTransicoes[0][22];

          imprimirLexema(simbolos, estadosFinais, estado, buffer);

          // Reseta buffer e estado
          buffer = "";
          estado = 0;
        }
      } else if (aux == 'n') {
        // Verifica se não está dentro de um comentário ou string.
        if (tabelaTransicoes[estado][20] == 8 || tabelaTransicoes[estado][20] == 11) {
          buffer = buffer + '\n';
          estado = tabelaTransicoes[estado][20];
        } else {
          imprimirLexema(simbolos, estadosFinais, estado, buffer);
          
          buffer = "";
          estado = 0;
        }
      } else if (aux == 't') {
        // Verifica se não está dentro de um comentário ou string.
        if (tabelaTransicoes[estado][19] == 8 || tabelaTransicoes[estado][19] == 11) {
          buffer = buffer + '\t';
          estado = tabelaTransicoes[estado][19];
        } else {
          imprimirLexema(simbolos, estadosFinais, estado, buffer);
          
          buffer = "";
          estado = 0;
        }
      } else { // Se o próximo caractere não for um .
        // Retorna caracter ao arquivo
        file.unget();

        // Imprime o buffer 
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta estado e buffer
        buffer = "";
        estado = 0;
      }
    } else if (c == '_') {
      // Verifica se está em string, comentário ou identificador.
      if (tabelaTransicoes[estado][24] == 8 || tabelaTransicoes[estado][24] == 11 || tabelaTransicoes[estado][24] == 10) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][24];
      } else { 
        // Imprime anterior
        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Seta buffer como _, muda o estado e imprime _ 
        buffer = "_";
        estado = tabelaTransicoes[0][24];

        imprimirLexema(simbolos, estadosFinais, estado, buffer);

        // Reseta buffer e estado.
        buffer = "";
        estado = 0;
      }
    } else if (c == EOF) { // Verifica se atingiu o final do arquivo
      // Imprime anterior
      imprimirLexema(simbolos, estadosFinais, estado, buffer);

      // Reseta buffer, muda o estado, imprime o lexema.
      buffer = "";
      estado = tabelaTransicoes[0][4];

      imprimirLexema(simbolos, estadosFinais, estado, buffer);

      // Fecha o arquivo, pois atingiu o fim.
      fecharArquivo(file);
    } else { // Verifica se inseriu um caractere não permitido
      // Verifica se está em string ou comentário
      if (tabelaTransicoes[estado][27] == 8 || tabelaTransicoes[estado][27] == 11) {
        buffer = buffer + c;
        estado = tabelaTransicoes[estado][27];
      } else { // Senão, imprime erro.
        cout << "Erro: Caracter Invalido! \nLinha: " << linha << " Coluna: " << coluna << endl;
      }
    }
}

// Inicia estados finais
void iniciaEstadosFinais () {
  // Insere os estados finais no map "estadosFinais"
  estadosFinais.insert (std::pair<int, string> (1, "Num"));
  estadosFinais.insert (std::pair<int, string> (3, "Num"));
  estadosFinais.insert (std::pair<int, string> (5, "Num"));
  estadosFinais.insert (std::pair<int, string> (9, "Literal"));
  estadosFinais.insert (std::pair<int, string> (10, "id"));
  estadosFinais.insert (std::pair<int, string> (12, "Comentario"));
  estadosFinais.insert (std::pair<int, string> (13, "EOF"));
  estadosFinais.insert (std::pair<int, string> (14, "OPR"));
  estadosFinais.insert (std::pair<int, string> (15, "RCB"));
  estadosFinais.insert (std::pair<int, string> (16, "OPM"));
  estadosFinais.insert (std::pair<int, string> (17, "AB_P"));
  estadosFinais.insert (std::pair<int, string> (18, "FC_P"));
  estadosFinais.insert (std::pair<int, string> (19, "PT_V"));
}

void iniciaTabelaSimbolos () {
  // Vetor que armazena todas as palavras chave da linguagem
  string stringToken[] = {"inicio", "varinicio", "varfim", "escreva", "leia", "se", "entao", "fimse", "fim", "inteiro", "literal", "real"};
  
    // Struct auxiliar
    entrada palavrasChave;
    std::map<string, entrada>::iterator simbolos_it;
  
    // Insere todas as palavras chaves da linguagem na hash de simbolos
    for (int i = 0; i < 12; i++) {
      palavrasChave.token = stringToken[i];
      palavrasChave.lexema = stringToken[i];
      palavrasChave.tipo = "";
  
      simbolos.insert (std::pair<string, entrada> (stringToken[i], palavrasChave));
    }
}


// Função auxiliar pra main
void auxiliarMain () {
  abrirArquivo(file);

  iniciaEstadosFinais();
  iniciaTabelaSimbolos();
  
    // Imprime toda a hash de símbolos.
    // 
    // for (simbolos_it = simbolos.begin(); simbolos_it != simbolos.end();  ++simbolos_it) {
    //   cout << "Token: " << simbolos_it->second.token << " Lexema: " << simbolos_it->second.lexema << " Tipo: " << simbolos_it->second.tipo << endl;
    // }
    // 
    // Imprime todas as palavras chave da linguagem.
    // 
    // for (int i = 0; i < 12; i++) {
    //   std::cout << simbolos.find(stringToken[i])->second.lexema << '\n';
    // }
  
    // Enquanto o arquivo estiver aberto
    while (file.is_open()) {
      c = lerArquivo(file); // Leia um caractere
      coluna += 1; // Acrescenta a coluna
  
      // Analisa o caracter lido
      analisadorLexico(c);
    }
}


// int main() {

//   auxiliarMain();

//   return 0;
// }
