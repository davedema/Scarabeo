#ifndef COSTANTS_H
#define COSTANTS_H
#include <iostream>
const size_t board_size = 17;
const char board_blueprint[board_size][board_size]=
         //L stand for 3L,
         //l stands for 2L,
         // W stands for 3W,
         // wstands for 2W,
         // s standsfor scarabeo,
 {{'W',' ',' ',' ','l',' ',' ',' ','W',' ',' ',' ','l',' ',' ',' ','W'},
  {' ','w',' ',' ',' ',' ','L',' ',' ',' ','L',' ',' ',' ',' ','w',' '},
  {' ',' ','w',' ',' ',' ',' ','l',' ','l',' ',' ',' ',' ','w',' ',' '},
  {' ',' ',' ','w',' ',' ',' ',' ','l',' ',' ',' ',' ','w',' ',' ',' '},
  {'l',' ',' ',' ','w',' ',' ',' ',' ',' ',' ',' ','w',' ',' ',' ','l'},
  {' ',' ',' ',' ',' ','w',' ',' ',' ',' ',' ','w',' ',' ',' ',' ',' '},
  {' ','L',' ',' ',' ',' ','L',' ',' ',' ','L',' ',' ',' ',' ','L',' '},
  {' ',' ','l',' ',' ',' ',' ','l',' ','l',' ',' ',' ',' ','l',' ',' '},
  {'W',' ',' ','l',' ',' ',' ',' ','s',' ',' ',' ',' ','l',' ',' ','W'},
  {' ',' ','l',' ',' ',' ',' ','l',' ','l',' ',' ',' ',' ','l',' ',' '},
  {' ','L',' ',' ',' ',' ','L',' ',' ',' ','L',' ',' ',' ',' ','L',' '},
  {' ',' ',' ',' ',' ','w',' ',' ',' ',' ',' ','w',' ',' ',' ',' ',' '},
  {'l',' ',' ',' ','w',' ',' ',' ',' ',' ',' ',' ','w',' ',' ',' ','l'},
  {' ',' ',' ','w',' ',' ',' ',' ','l',' ',' ',' ',' ','w',' ',' ',' '},
  {' ',' ','w',' ',' ',' ',' ','l',' ','l',' ',' ',' ',' ','w',' ',' '},
  {' ','w',' ',' ',' ',' ','L',' ',' ',' ','L',' ',' ',' ',' ','w',' '},
  {'W',' ',' ',' ','l',' ',' ',' ','W',' ',' ',' ','l',' ',' ',' ','W'},
 };


const int image_size=30;
const int tiles_size=25;
const int boardPixelSize=board_size*image_size;

unsigned int const alphabeth_size=22; // il 22esimo carattere è '\n' '\r'
unsigned int const handMaxSize=8;


size_t const numA = 12;
size_t const numB = 4;
size_t const numC = 7;
size_t const numD = 4;
size_t const numE = 12;
size_t const numF = 4;
size_t const numG = 4;
size_t const numH = 2;
size_t const numI = 12;
size_t const numL = 6;
size_t const numM = 6;
size_t const numN = 6;
size_t const numO = 12;
size_t const numP = 4;
size_t const numQ = 2;
size_t const numR = 7;
size_t const numS = 7;
size_t const numT = 7;
size_t const numU = 4;
size_t const numV = 4;
size_t const numZ = 2;
size_t const numJolly = 2;


const size_t maxtile=numA+numB+numC+numD+numE+numF+numG+numH+numI+numL+numM+numN+numO+numP+numQ+numR+numS+numT+numU+numV+numZ+numJolly;


//valore in punti delle tessere   --da scrivere dati corretti
unsigned int const pointA = 1;
unsigned int const pointB = 4;
unsigned int const pointC = 1;
unsigned int const pointD = 4;
unsigned int const pointE = 1;
unsigned int const pointF = 4;
unsigned int const pointG = 4;
unsigned int const pointH = 8;
unsigned int const pointI = 1;
unsigned int const pointL = 2;
unsigned int const pointM = 2;
unsigned int const pointN = 2;
unsigned int const pointO = 1;
unsigned int const pointP = 3;
unsigned int const pointQ = 10;
unsigned int const pointR = 1;
unsigned int const pointS = 1;
unsigned int const pointT = 1;
unsigned int const pointU = 4;
unsigned int const pointV = 4;
unsigned int const pointZ = 8;
unsigned int const pointJolly = 0; //i punti del jolly variano in base alla lettera che sostituisce... capire come gestire


float tileCentered_Pos(unsigned long i);

void debug(int i);

char pos_to_letter(size_t pos);

#endif // COSTANTS_H
