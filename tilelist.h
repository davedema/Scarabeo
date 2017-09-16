#ifndef TILELIST_H
#define TILELIST_H
#include "tile.h"
#include <iostream>

class TileList{
    Tile* tile;
    TileList* nextptr;

public:

    TileList();

    TileList(Tile* t);       //costruttore a partire da un tile, crea un nodo usando come tile quello in input alla funzione
    TileList(TileList *t);   //costruttore per copia
    void push_back(Tile* t);    //aggiunge alla coda della lista una nuova tilelist lunga 1 creata a parite dal tile passato come parametro
    void push_back(TileList* tilelist); //aggiunge alla coda della lista la lista la cui testa è passata come parametro (provvede a "tagliare" la testa della lista autonomamente
    TileList* operator[](size_t pos);  //restituisce il puntatore al nodo della lista in posizione "pos"
    TileList* extract(size_t pos);     //restituisce il puntatore al nodo in posizione "pos" preventivamente eliminato dalla lista in cui era contenuto precedentemente
    Tile* extractTile(size_t pos);     //restituisce il puntatore al tile presente al nodo della lista in posizione "pos" preventivamente eliminato dalla lista in cui era contenuto precedentemente
    Tile* getTile(size_t pos);         //restituisce il puntatore al tile presente al nodo della lista in posizione "pos"
    size_t size();                     //restituisce il valore della lunghezza della lista senza tener conto della testa della lista
    TileList* next();                  //ritorna il nextptr di un nodo
    void cutHead();                    //taglia la lista in posizione del nodo da cui è stata chiamata la funzione
    unsigned int listPoints();         //restituisce la somma dei punti dei tile presenti nella lista
    ~TileList();    

};

#endif // TILELIST_H
