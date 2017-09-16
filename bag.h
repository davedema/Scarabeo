//CLASSE BAG
//GENERA TUTTI I TASSELLI (LETTERE) NECESSARIE ALLA PARTITA E LE AGGIUNGE ALLA PROPRIA LISTA DI TASSELLI
//GESTISCE LE TEXTURE UTILIZZATE PER LE SPRITES DEI TASSELLI
//PERMETTE DI ESTRARRE DEI TASSELLI CASUALMENTE, FUNZIONE DA UTILIZZARE PER L'ESTAZIONE DI NUOVI TASSELLI A FINE TURNO

#ifndef BAG_H
#define BAG_H
#include "tilelist.h"

class Bag{
    TileList* tilelist;
    std::size_t size;                         //numero di lettere rimanenti (ho preferito avere una variabile in più per evitare di dover chiamare troppo volte la funzione size() di TileList
public:
    Bag();                                    //costruttore
    size_t getSize(){ return size;}           //restituisce il valore della variabile size
    TileList* extract(unsigned int quantity); //estrae il numero richiesto di tiles e restituisce il puntatore alla testa della lista contenente i tiles estratti
    Tile* extractTile(char letter);           //restituisce il puntatore ad un tile di lettera "letter", provvedendo ad estrarlo dalla lista
    void addTiles(TileList *hand);            //permette di aggiungere tasselli al sacchetto (funzione usata per il cambio mano del giocatore)
    ~Bag(){delete tilelist;}
};

#endif // BAG_H
