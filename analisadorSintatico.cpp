// Trabalho 2 de Compiladores: Analisador Léxico
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
#include <stack>
#include "analisadorLexicov2.cpp"

using namespace std;

#define BRANCO -1000
#define Acc 1000
#define $ 500

/* Shift define */
#define S2 2
#define S4 4
#define S9 9
#define S10 10
#define S11 11
#define S12 12
#define S14 14
#define S17 17
#define S18 18
#define S22 22
#define S24 24
#define S25 25
#define S26 26
#define S27 27
#define S32 32
#define S33 33
#define S35 35
#define S37 37
#define S38 38
#define S39 39
#define S40 40
#define S42 42
#define S45 45
#define S46 46
#define S49 49
#define S50 50
#define S51 51
#define S54 54
#define S55 55
#define S57 57
#define S58 58

/* Reduce define */
#define R2 -2
#define R3 -3
#define R4 -4
#define R5 -5
#define R6 -6
#define R7 -7
#define R8 -8
#define R9 -9
#define R10 -10
#define R11 -11
#define R12 -12
#define R13 -13
#define R14 -14
#define R15 -15
#define R16 -16
#define R17 -17
#define R18 -18
#define R19 -19
#define R20 -20
#define R21 -21
#define R22 -22
#define R23 -23
#define R24 -24
#define R25 -25
#define R26 -26
#define R27 -27
#define R28 -28
#define R29 -29
#define R30 -30

/* Error define */
#define E0 100
#define E1 101
#define E2 102
#define E3 103
#define E4 104
#define E6 106
#define E7 107
#define E8 108
#define E10 110
#define E11 111
#define E12 112
#define E13 113
#define E14 114
#define E16 116
#define E17 117
#define E18 118
#define E22 122
#define E23 123
#define E23 123
#define E27 127
#define E29 129
#define E30 130
#define E31 131
#define E33 133
#define E36 136
#define E43 143
#define E44 144
#define E47 147
#define E48 148
#define E51 151
#define E54 154
#define E55 155


// Comentei o hashzin p/ roda de buenas
// Hash com todos os possíveis erros:
// map<int, string> erros;

// erros.insert (pair<int, string> (E0, "Programa iniciado com palavra inválida. Utilize 'inicio'"));
// erros.insert (pair<int, string> (E1, "Símbolo não permitido")); // Só aceita Acc lá, pensar em uma frase melhor.
// erros.insert (pair<int, string> (E2, "Inicie o bloco de variáveis utilizando 'varinicio'"));
// erros.insert (pair<int, string> (E3, "--")); // Melhorar string
// erros.insert (pair<int, string> (E4, "Identificador inválido"));
// erros.insert (pair<int, string> (E6, "Expressão inválida"));
// erros.insert (pair<int, string> (E7, "Expressão inválida"));

int tabelaShiftReduce[59][37] = {
//                                                                     Ações Terminais                                                    |                                Transições (NT)
//           0,        1,       2,    3,  4,  5,        6,    7,      8,      9,     10,  11,  12, 13,14,15,    16,  17,    18,  19,  20, | 21, 22,23, 24,25,   26,27, 28,  29,  30, 31,   32,   33,   34,       35,     36
// Estados,inicio, varinicio, varfim, ;, id, inteiro, real, literal, leia, escreva, num, rcb, opm, se, (, ), então, opr, fimse, fim,   $, | P',  P, V, LV, D, TIPO, A, ES, ARG, CMD, LD, OPRD, COND, CABECALHO, EXP_R, CORPO
/* 0 */  { S2,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,E0,BRANCO,1,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 1 */  { E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,E1,Acc,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 2 */  { E2,S4,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,E2,BRANCO,BRANCO,3,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 3 */  { E3,E3,E3,E3,S12,E3,E3,E3,S10,S11,E3,E3,E3,S14,E3,E3,E3,E3,E3,S9,E3,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,5,6,BRANCO,7,BRANCO,BRANCO,8,13,BRANCO,BRANCO },
/* 4 */  { E4,E4,S17,E4,S18,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,E4,BRANCO,BRANCO,BRANCO,15,16,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 5 */  { R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,R2,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 6 */  { E6,E6,E6,E6,S12,E6,E6,E6,S10,S11,E6,E6,E6,S14,E6,E6,E6,E6,E6,S9,E6,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,19,6,BRANCO,7,BRANCO,BRANCO,8,13,BRANCO,BRANCO },
/* 7 */  { E7,E7,E7,E7,S12,E7,E7,E7,S10,S11,E7,E7,E7,S14,E7,E7,E7,E7,E7,S9,E7,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,20,6,BRANCO,7,BRANCO,BRANCO,8,13,BRANCO,BRANCO },
/* 8 */  { E8,E8,E8,E8,S12,E8,E8,E8,S10,S11,E8,E8,E8,S14,E8,E8,E8,E8,E8,S9,E8,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,21,6,BRANCO,7,BRANCO,BRANCO,8,13,BRANCO,BRANCO },
/* 9 */  { R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,R30,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 10 */ { E10,E10,E10,E10,S22,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,E10,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 11 */ { E11,E11,E11,E11,S26,E11,E11,S24,E11,E11,S25,E11,E11,E11,E11,E11,E11,E11,E11,E11,E11,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,23,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 12 */ { E12,E12,E12,E12,E12,E12,E12,E12,E12,E12,E12,S27,E12,E12,E12,E12,E12,E12,E12,E12,E12,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 13 */ { E13,E13,E13,E13,S12,E13,E13,E13,S10,S11,E13,E13,E13,S14,E13,E13,E13,E13,S32,E13,E13,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,29,BRANCO,30,BRANCO,BRANCO,31,13,BRANCO,28 },
/* 14 */ { E14,E14,E14,E14,E14,E14,E14,E14,E14,E14,E14,E14,E14,E14,S33,E14,E14,E14,E14,E14,E14,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 15 */ { R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,R3,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 16 */ { E16,E16,S17,E16,S18,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,E16,BRANCO,BRANCO,BRANCO,34,16,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 17 */ { E17,E17,E17,S35,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,E17,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 18 */ { E18,E18,E18,E18,E18,S37,S38,S39,E18,E18,E18,E18,E18,E18,E18,E18,E18,E18,E18,E18,E18,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,36,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 19 */ { R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,R10,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 20 */ { R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,R16,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 21 */ { R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,R22,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 22 */ { E22,E22,E22,S42,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,E22,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 23 */ { E23,E23,E23,S40,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,E23,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 24 */ { R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,R13,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 25 */ { R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,R14,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 26 */ { R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,R15,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 27 */ { E27,E27,E27,E27,S45,E27,E27,E27,E27,E27,S46,E27,E27,E27,E27,E27,E27,E27,E27,E27,E27,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,43,44,BRANCO,BRANCO,BRANCO,BRANCO },
/* 28 */ { R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,R23,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 29 */ { E29,E29,E29,E29,S12,E29,E29,E29,S10,S11,E29,E29,E29,S14,E29,E29,E29,E29,S32,E29,E29,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,29,BRANCO,30,BRANCO,BRANCO,31,13,BRANCO,41 },
/* 30 */ { E30,E30,E30,E30,S12,E30,E30,E30,S10,S11,E30,E30,E30,S14,E30,E30,E30,E30,S32,E30,E30,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,29,BRANCO,30,BRANCO,BRANCO,31,13,BRANCO,52 },
/* 31 */ { E31,E31,E31,E31,S12,E31,E31,E31,S10,S11,E31,E31,E31,S14,E31,E31,E31,E31,S32,E31,E31,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,29,BRANCO,30,BRANCO,BRANCO,31,13,BRANCO,53 },
/* 32 */ { R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,R29,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 33 */ { E33,E33,E33,E33,S45,E33,E33,E33,E33,E33,S46,E33,E33,E33,E33,E33,E33,E33,E33,E33,E33,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,48,BRANCO,BRANCO,47,BRANCO },
/* 34 */ { R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,R4,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 35 */ { R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,R5,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 36 */ { E36,E36,E36,S49,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,E36,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 37 */ { R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,R7,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 38 */ { R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,R8,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 39 */ { R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,R9,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 40 */ { R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,R12,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 41 */ { R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,R26,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 42 */ { R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,R11,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 43 */ { E43,E43,E43,S50,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,E43,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 44 */ { E44,E44,E44,R19,E44,E44,E44,E44,E44,E44,E44,E44,S51,E44,E44,E44,E44,E44,E44,E44,E44,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 45 */ { R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,R20,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 46 */ { R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,R21,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 47 */ { E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,E47,S54,E47,E47,E47,E47,E47,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 48 */ { E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,E48,S55,E48,E48,E48,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 49 */ { R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,R6,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 50 */ { R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,R17,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 51 */ { E51,E51,E51,E51,S45,E51,E51,E51,E51,E51,S46,E51,E51,E51,E51,E51,E51,E51,E51,E51,E51,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,56,BRANCO,BRANCO,BRANCO,BRANCO },
/* 52 */ { R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,R27,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 53 */ { R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,R28,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 54 */ { E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,E54,S57,E54,E54,E54,E54,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 55 */ { E55,E55,E55,E55,S45,E55,E55,E55,E55,E55,S46,E55,E55,E55,E55,E55,S58,E55,E55,E55,E55,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,58,BRANCO,BRANCO,BRANCO,BRANCO },
/* 56 */ { R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,R18,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 57 */ { R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,R24,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO },
/* 58 */ { R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,R25,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO,BRANCO }
};

/* Estrutura para armazenar as produções da gramática */
struct producao {
    int numero;
    string lado_esquerdo;
    string lado_direito;
	int tamanho_direito;
	int coluna_GOTO;
};


void initProducoes(struct producao *producoes) {
		
	/* 1 P' -> P */
	producoes[0].numero 			= 1;
	producoes[0].lado_esquerdo 		= "P\'";
	producoes[0].lado_direito 		= "P";
	producoes[0].tamanho_direito 	= 1;
	producoes[0].coluna_GOTO 		= 21;

	/* 2 P -> inicio V A */
	producoes[1].numero 			= 2;
	producoes[1].lado_esquerdo 		= "P";
	producoes[1].lado_direito 		= "inicio V A";
	producoes[1].tamanho_direito 	= 3;
	producoes[1].coluna_GOTO 		= 22;

	/* 3 V -> varinicio LV */
	producoes[2].numero 			= 3;
	producoes[2].lado_esquerdo 		= "V";
	producoes[2].lado_direito 		= "varinicio LV";
	producoes[2].tamanho_direito 	= 2;
	producoes[2].coluna_GOTO 		= 23;

	/* 4 LV -> D LV */
	producoes[3].numero 			= 4;
	producoes[3].lado_esquerdo 		= "LV";
	producoes[3].lado_direito 		= "D LV";
	producoes[3].tamanho_direito 	= 2;
	producoes[3].coluna_GOTO 		= 24;

	/* 5 LV -> varfim; */
	producoes[4].numero 			= 5;
	producoes[4].lado_esquerdo 		= "LV";
	producoes[4].lado_direito 		= "varfim;";
	producoes[4].tamanho_direito 	= 2;
	producoes[4].coluna_GOTO 		= 24;

	/* 6 D -> id TIPO;*/
	producoes[5].numero 			= 6;
	producoes[5].lado_esquerdo 		= "D";
	producoes[5].lado_direito 		= "id TIPO;";
	producoes[5].tamanho_direito 	= 3;
	producoes[5].coluna_GOTO 		= 25;

	/* 7 TIPO -> inteiro */
	producoes[6].numero 			= 7;
	producoes[6].lado_esquerdo 		= "TIPO";
	producoes[6].lado_direito 		= "inteiro";
	producoes[6].tamanho_direito 	= 1;
	producoes[6].coluna_GOTO 		= 26;

	/* 8 TIPO -> real */
	producoes[7].numero 			= 8;
	producoes[7].lado_esquerdo 		= "TIPO";
	producoes[7].lado_direito 		= "real";
	producoes[7].tamanho_direito 	= 1;
	producoes[7].coluna_GOTO 		= 26;

	/* 9 TIPO -> literal */
	producoes[8].numero 			= 9;
	producoes[8].lado_esquerdo 		= "TIPO";
	producoes[8].lado_direito 		= "literal";
	producoes[8].tamanho_direito 	= 1;
	producoes[8].coluna_GOTO 		= 26;

	/* 10 A -> ES A */
	producoes[9].numero 			= 10;
	producoes[9].lado_esquerdo 		= "A";
	producoes[9].lado_direito 		= "ES A";
	producoes[9].tamanho_direito 	= 2;
	producoes[9].coluna_GOTO 		= 27;

	/* 11 ES -> leia id; */
	producoes[10].numero 			= 11;
	producoes[10].lado_esquerdo 	= "ES";
	producoes[10].lado_direito 		= "leia id;";
	producoes[10].tamanho_direito 	= 3;
	producoes[10].coluna_GOTO 		= 28;

	/* 12 ES -> escreva ARG; */
	producoes[11].numero 			= 12;
	producoes[11].lado_esquerdo 	= "ES";
	producoes[11].lado_direito 		= "escreva ARG;";
	producoes[11].tamanho_direito 	= 3;
	producoes[11].coluna_GOTO 		= 28;

	/* 13 ARG -> literal */
	producoes[12].numero 			= 13;
	producoes[12].lado_esquerdo 	= "ARG";
	producoes[12].lado_direito 		= "literal";
	producoes[12].tamanho_direito 	= 1;
	producoes[12].coluna_GOTO 		= 29;

	/* 14 ARG -> num */
	producoes[13].numero 			= 14;
	producoes[13].lado_esquerdo 	= "ARG";
	producoes[13].lado_direito 		= "num";
	producoes[13].tamanho_direito 	= 1;
	producoes[13].coluna_GOTO 		= 29;

	/* 15 ARG -> id */
	producoes[14].numero 			= 15;
	producoes[14].lado_esquerdo 	= "ARG";
	producoes[14].lado_direito 		= "id";
	producoes[14].tamanho_direito 	= 1;
	producoes[14].coluna_GOTO 		= 29;

	/* 16 A -> CMD A */
	producoes[15].numero 			= 16;
	producoes[15].lado_esquerdo 	= "A";
	producoes[15].lado_direito 		= "CMD A";
	producoes[15].tamanho_direito 	= 2;
	producoes[15].coluna_GOTO 		= 27;

	/* 17 CMD -> id rcb LD; */
	producoes[16].numero 			= 17;
	producoes[16].lado_esquerdo 	= "CMD";
	producoes[16].lado_direito 		= "id rcb LD;";
	producoes[16].tamanho_direito 	= 4;
	producoes[16].coluna_GOTO 		= 30;

	/* 18 LD -> OPRD opm OPRD */
	producoes[17].numero 			= 18;
	producoes[17].lado_esquerdo 	= "LD";
	producoes[17].lado_direito 		= "OPRD opm OPRD";
	producoes[17].tamanho_direito 	= 3;
	producoes[17].coluna_GOTO 		= 31;

	/* 19 LD -> OPRD */
	producoes[18].numero 			= 19;
	producoes[18].lado_esquerdo 	= "LD";
	producoes[18].lado_direito 		= "OPRD";
	producoes[18].tamanho_direito 	= 1;
	producoes[18].coluna_GOTO 		= 31;

	/* 20 OPRD -> id */
	producoes[19].numero 			= 20;
	producoes[19].lado_esquerdo 	= "OPRD";
	producoes[19].lado_direito 		= "id";
	producoes[19].tamanho_direito 	= 1;
	producoes[19].coluna_GOTO 		= 32;

	/* 21 OPRD -> num */
	producoes[20].numero 			= 21;
	producoes[20].lado_esquerdo 	= "OPRD";
	producoes[20].lado_direito 		= "num";
	producoes[20].tamanho_direito 	= 1;
	producoes[20].coluna_GOTO 		= 32;

	/* 22 A -> COND A */
	producoes[21].numero 			= 22;
	producoes[21].lado_esquerdo 	= "A";
	producoes[21].lado_direito 		= "COND A";
	producoes[21].tamanho_direito 	= 2;
	producoes[21].coluna_GOTO 		= 27;

	/* 23 COND -> CABEÇALHO CORPO */
	producoes[22].numero 			= 23;
	producoes[22].lado_esquerdo 	= "COND";
	producoes[22].lado_direito 		= "CABEÇALHO CORPO";
	producoes[22].tamanho_direito 	= 2;
	producoes[22].coluna_GOTO 		= 33;

	/* 24 CABEÇALHO -> se (EXP_R) então */
	producoes[23].numero 			= 24;
	producoes[23].lado_esquerdo 	= "CABEÇALHO";
	producoes[23].lado_direito 		= "se (EXP_R) então";
	producoes[23].tamanho_direito 	= 5;
	producoes[23].coluna_GOTO 		= 34;

	/* 25 EXP_R -> OPRD opr OPRD */
	producoes[24].numero 			= 25;
	producoes[24].lado_esquerdo 	= "EXP_R";
	producoes[24].lado_direito 		= "OPRD opr OPRD";
	producoes[24].tamanho_direito 	= 3;
	producoes[24].coluna_GOTO 		= 35;

	/* 26 CORPO -> ES CORPO */
	producoes[25].numero 			= 26;
	producoes[25].lado_esquerdo 	= "CORPO";
	producoes[25].lado_direito 		= "ES CORPO";
	producoes[25].tamanho_direito 	= 2;
	producoes[25].coluna_GOTO 		= 36;

	/* 27 CORPO -> CMD CORPO */
	producoes[26].numero 			= 27;
	producoes[26].lado_esquerdo 	= "CORPO";
	producoes[26].lado_direito 		= "CMD CORPO";
	producoes[26].tamanho_direito 	= 2;
	producoes[26].coluna_GOTO 		= 36;

	/* 28 CORPO -> COND CORPO */
	producoes[27].numero 			= 28;
	producoes[27].lado_esquerdo 	= "CORPO";
	producoes[27].lado_direito 		= "COND CORPO";
	producoes[27].tamanho_direito 	= 2;
	producoes[27].coluna_GOTO 		= 36;

	/* 29 CORPO -> fimse */
	producoes[28].numero 			= 29;
	producoes[28].lado_esquerdo 	= "CORPO";
	producoes[28].lado_direito 		= "fimse";
	producoes[28].tamanho_direito 	= 1;
	producoes[28].coluna_GOTO 		= 36;

	/* 30 A -> fim */
	producoes[29].numero 			= 30;
	producoes[29].lado_esquerdo 	= "A";
	producoes[29].lado_direito 		= "fim";
	producoes[29].tamanho_direito 	= 1;
	producoes[29].coluna_GOTO 		= 27;
}

int chamaLexico () {
	string aString = filaSimbolos.front();

	filaSimbolos.pop();

	if (aString == "inicio") {
		return 0;
	} else if (aString == "varinicio") {
		return 1;
	} else if (aString == "varfim") {
		return 2;
	} else if (aString == "PT_V") {
		return 3;
	} else if (aString == "id") {
		return 4;
	} else if (aString == "inteiro") {
		return 5;
	} else if (aString == "real") {
		return 6;
	} else if (aString == "literal" || aString == "Literal") {
		return 7;
	} else if (aString == "leia") {
		return 8;
	} else if (aString == "escreva") {
		return 9;
	} else if (aString == "num" || aString == "Num") {
		return 10;
	} else if (aString == "RCB") {
		return 11;
	} else if (aString == "OPM") {
		return 12;
	} else if (aString == "se") {
		return 13;
	} else if (aString == "AB_P") {
		return 14;
	} else if (aString == "FC_P") {
		return 15;
	} else if (aString == "entao") {
		return 16;
	} else if (aString == "OPR") {
		return 17;
	} else if (aString == "fimse") {
		return 18;
	} else if (aString == "fim") {
		return 19;
	} else if (aString == "$") {
		return 20;
	} else {
		cout << "ERRO!! - TOKEN INVALIDO!" << endl;
		exit(1);
	}
}

// 0 2 4 18
void analiseSintaticaLR () {
	struct producao producoes[30];
	initProducoes(producoes);
	stack<int> pilha;
	pilha.push(0);
	filaSimbolos.push("$");

	int a, s, aux, comprimento, t;


	a = chamaLexico();
	while (1) {
		s = pilha.top();

		if ( tabelaShiftReduce[s][a] >= 0 && tabelaShiftReduce[s][a] <= 58) {
			pilha.push(tabelaShiftReduce[s][a]);
			a = chamaLexico();
		} else if (tabelaShiftReduce[s][a] < 0 && tabelaShiftReduce[s][a] >= -30 ) {
			aux = (tabelaShiftReduce[s][a] * -1) - 1;
			comprimento = producoes[aux].tamanho_direito;
			while (comprimento > 0) {
				pilha.pop();
				comprimento--;
			}
			t = pilha.top();
			pilha.push(tabelaShiftReduce[t][producoes[aux].coluna_GOTO]);
			cout << producoes[aux].lado_esquerdo << " -> " << producoes[aux].lado_direito << endl;
		} else if (tabelaShiftReduce[s][a] == Acc) {
			cout << "\nAceitou!" << endl; 
			break; // A análise terminou!
		} else {
			// cout << "Erro:" << erros.find(tabelaShiftReduce[s][a])->second << endl;
			cout << "\nDeu Erro!" << endl; 
			exit(1);
		}
	}
}

int main(int argc, char const *argv[]) {
	auxiliarMain();

	// while (!filaSimbolos.empty()) {
	// 	cout << filaSimbolos.front() << endl;
	// 	filaSimbolos.pop();
	// }

	cout << "\n\n#####################################\n\n";
	analiseSintaticaLR();

	return 0;
}
