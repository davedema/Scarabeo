#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <bag.h>




class Player
{
    std::string name;                   //nome del giocatore
    unsigned int currentPoints;         //punteggio corrente del giocatore
    TileList* hand;                     //mano del giocatore

public:
    Player(std::string newname):name(newname),currentPoints(0),hand(new TileList()){} //costruttore
    Player():name(""),currentPoints(0),hand(new TileList()){}   //costruttore senza parametri in ingresso
    void refill_hand(Bag* mybag);           //funzione che permette di pescare le lettera mancanti dalla mano del giocatore (richiamata una volta alla fine di ogni turno)
    void changeHand(Bag *myBag);            //funzione che permette di sostituire completamente la propia mano con lettere presenti nel sacchetto
    bool firstMove();                       //funzione che permette di capire se il tassello appena giocato è il primo tassello ad essere stato giocato durante questo turno    
    bool isPos_free(sf::Vector2f pos);      //funzione per controllare che il giocatore non giochi due lettere sovrapposte (il controllo viene effettuato tra le tessere presenti nella mano del giocatore)
    void addPoints(unsigned int points){currentPoints+=points;} //funzione che permette di aggiungere punti al punteggio totale del giocatore
    unsigned int handPoints(){return hand->listPoints();}       //funzione che restituisce la somma dei punti delle lettere presenti nella mano del giocatore
    unsigned int getPoints(){return currentPoints;}             //funzione che restituisce il punteggio attuale del giocatore
    std::string getName(){return name;}                         //funzione che restituisce il nome del giocatore
    TileList* showHand(){return hand;}                          //funzione che restituisce il puntatore alla testa della TileList "hand" del giocatore
    sf::Sprite* getSprites(size_t pos);                         //funzione che restituisce il puntatore alla sprite della lettera in posizione pos all'interno della mano del giocatore
    ~Player();
};

#endif // PLAYER_H
