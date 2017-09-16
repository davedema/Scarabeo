#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "costants.h"


//numero di tessere in base alla lettera


//status......
enum status {checking,checked};


class Tile{

        char letter;                //lettera del tassello
        unsigned int points;        //punti legati alla lettera
        status state;               //stato del tassello, può essere "checking", cioè in fase di "controllo" o checked, cioè controllata
        bool Jolly;                 //utilizzato per distinguere un tassello jolly da un altro        
        sf::Sprite* sprite;         //sprite usata per rappresentare il tassello graficamente

    void setJolly_points(char c);
public:
    Tile();         //costruttore.. pretty straightforward
    Tile(char letter,sf::Texture* texture);    //costruttore con parametri in ingresso
    status getStatus() const {return state;}          //funzione che restituisce il valore della variabile "status"
    unsigned int getPoints() const {return points;}   //funzione che restituisce il valore della variabile "points"
    void setJolly_letter(char c);              //funzione che modifica la variabile "letter" e la variabile "points" di una tile se è jolly
    //void setJolly_letter_Sprite(char c);
    bool isJolly(){return Jolly;}               //funzione che restituisce il valore della variabile "Jolly"
    void setStatus(status s){state=s;}          //funzione che permette di modificate il valore della funzione "status"
    char getLetter() const;                     //funzione che restituisce il valore della variabile "letter"   
    sf::Sprite* getSprite();                                //funzione che restituisce un puntatore alla variabile "sprite"
    void setPosition(float x,float y);                      //funzione che modifica la posizione della sprite del tassello
    ~Tile();

};

#endif // TILE_H
