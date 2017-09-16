#ifndef BOARD_H
#define BOARD_H
#include "player.h"
#include "dictionary.h"
#include <list>

enum wordtype{vertical,horizontal,unknown,singleTile};

class Board{

    Tile* tBoard[board_size][board_size]; //matrice di puntatori a TILE contenente i tasselli già controllati presenti sul tabellone
    sf::Sprite sBoard[2][board_size*board_size]; //nella prima riga sono salvate le sprites del tabellone, nella seconda riga quelle dei tiles


    bool checkString(Dictionary* dictionary,std::string stringedBoard);    //controlla la validità delle varie  parole presenti nella stringa passata in ingresso (le parole sono separate da almeno uno spazio
    bool isWordSeg(wordtype direction);                                    //funzione che permette se la parola appena giocata è "segmentata", che corrisponde a verificare che non siano state inserite più parole nello stesso turno
    bool wordCrossed(wordtype dir);
    std::string columnToString(bool columns[]);     //converte una riga del tabellone in stringa
    std::string rowToString(bool rows[]);           //converte una colonna del tabellone in stringa
    void setChecked();                              //imposta ogni tassello come "checked", controllato
    unsigned int wordPoints(bool jollyUsed);           //restituisce il punteggio base della parola appena formata, cioè senza tener conto degli "specialPoints"
    void removeTiles(Player* player);               //rimuove dal tabellone le lettere appena giocate (da usare nel caso in cui queste non formino parole di senso compiuto)
    wordtype WordDirection();                       //restituisce la direzione della parola appena inserita,restituisce "unknown" se sono state inserite lettere in modo sparso, senza una direzione specifica, restituisce singletile se invece è stata aggiunta solo una lettera
    int addTile(size_t counter, TileList *hand, Dictionary *dict, size_t posx, size_t posy, wordtype dir,std::string &word, Dnode *dnode, bool jollyUsed);  //funzione ricorsiva usata per il suggerimento, data una direzione, la posizoone attuale sul tabellone e un dNode(nodo del dizionario)
    int hintPoints(Dictionary* dictionary, wordtype dir,bool jollyUsed);   //funzione che restituisce il punteggio ottenuto da una parola (specifico per il suggerimento)
    unsigned int specialPoints(int num, bool jollyUsed);    //funzione che permette ritorna eventuali punteggi speciali da assegnare per la formazione di parole di un certo tipo
    void refreshSprites();                                  //reimposta le sprites
    void changeJollyTexture(Tile* tile,char letter);        //cambia la texture della sprite del jolly
public:   
    Board();    
    sf::Sprite* getSprites(){return sBoard[0];}    
    bool updateBoards(Dictionary* dictionary,Bag* bag,Player* player);    // controllo validità tabellone, chiamato ad ogni inserimento di parola
    bool is_empty();                                                      //restituisce true se il tabellone è vuoto
    bool isPos_free(sf::Vector2f pos);                                    //restituisce true se la posizione passata come parametro è libera
    Tile* pickJolly(sf::Vector2f pos,Tile *droppedTile);                  //permette di riprendere un jolly dal tabellone
    bool onJolly(sf::Vector2f pos,Tile *droppedTile);                     //resstituisce true se nella posizione corrente si trova un jolly
    void loadFromFile(Bag* bag,std::string path);                         //carica da file un tabellone
    bool help(Player *player, Dictionary *dictionary,Bag *myBag);         //suggerimenti
    ~Board();
};

#endif // BOARD_H
