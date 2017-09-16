
//----------------------------------------------------NODO DELL'ALBERO CONTENENTE IL DIZIONARIO------------------------------

#ifndef DNODE_H
#define DNODE_H
#include <iostream>
#include "costants.h"


class Dnode; // serve per avvertire il compilatore che Dnode è una classe , visto che viene usata in Dnode_cell prima della sua effettiva dichiarazione
//chiedere se la cosa appena fatta va effettivamente bene

struct Dnode_cell{
    bool exists; // inizialmente avevo utilizzato un char, ma grazie alla funzione switchletter mi basta semplicemente utilizzare un bool
                 //i miei array sono pensati per rappresentare in ordine tutte le lettere dell'alfabeto più il carattere di terminazione
                 //trovando un true per esempio in seconda posizione sta ad indicare che la b esiste
                 // perchè questo metodo? in modo tale da poter formare delle parole in "verticale"
                 // se nell'array è presente /n vuol dire che la parola formata dai nodi presenti sul percorso per arrivare  fino a lei è stata appena terminata
                 // se nell'array, nella casella in cui abbiamo appena controllato è stato trovato false vuol dire che nessuna parola formata dalle lettere prima scelte ammette successivamente quella determinata lettera appena cercata

    Dnode* nextptr;
};


class Dnode{   //dictionary node

    Dnode_cell node[alphabeth_size]; //array contenente Dnode_cell i quali contengono una bool ed un puntatore ad un altro array di Dnode_cell, cioè ad un Dnode

    //functions
    size_t switchletter(char c);
public:
    Dnode();
    Dnode* addletter_node(char c);
    Dnode* next(char c);
    bool is_present(char c); //essenzialmente ritorna il valore del nodo nella cella(dell'array) corrispondente alla lettera cercata
    ~Dnode();
};

#endif // DNODE_H
