#include "bag.h"

Bag::Bag(){

    srand(time(0)); //necessario per il random successivo;

    //dichiaro un puntatore a texture per ogni tipo di tile presente nel gioco

    sf::Texture *A=new sf::Texture();
    sf::Texture *B=new sf::Texture();
    sf::Texture *C=new sf::Texture();
    sf::Texture *D=new sf::Texture();
    sf::Texture *E=new sf::Texture();
    sf::Texture *F=new sf::Texture();
    sf::Texture *G=new sf::Texture();
    sf::Texture *H=new sf::Texture();
    sf::Texture *I=new sf::Texture();
    sf::Texture *L=new sf::Texture();
    sf::Texture *M=new sf::Texture();
    sf::Texture *N=new sf::Texture();
    sf::Texture *O=new sf::Texture();
    sf::Texture *P=new sf::Texture();
    sf::Texture *Q=new sf::Texture();
    sf::Texture *R=new sf::Texture();
    sf::Texture *S=new sf::Texture();
    sf::Texture *T=new sf::Texture();
    sf::Texture *U=new sf::Texture();
    sf::Texture *V=new sf::Texture();
    sf::Texture *Z=new sf::Texture();

    std::vector<sf::Texture*> jollyTexture;

    for (size_t k=0; k<numJolly; ++k){
        jollyTexture.push_back(new sf::Texture());
    }

    //carico le immagini relative alle rispettive texture
    A->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/A.png");
    B->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/B.png");
    C->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/C.png");
    D->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/D.png");
    E->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/E.png");
    F->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/F.png");
    G->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/G.png");
    H->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/H.png");
    I->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/I.png");
    L->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/L.png");
    M->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/M.png");
    N->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/N.png");
    O->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/O.png");
    P->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/P.png");
    Q->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Q.png");
    R->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/R.png");
    S->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/S.png");
    T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/T.png");
    U->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/U.png");
    V->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/V.png");
    Z->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Z.png");

    for (size_t k=0; k<numJolly; ++k){
        jollyTexture[k]->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png");
    }
    //J1->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png");
  //  J2->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png");

     //questo procedimento è necessario per permettere di costruire le tiles con le giuste sprites


         tilelist=new TileList(); //Creo la testa della lista

         for (size_t k=0; k<numA; ++k){
             tilelist->push_back(new Tile('A',A));             
         }
         for (size_t k=0; k<numB; ++k){
             tilelist->push_back(new Tile('B',B));
         }
         for (size_t k=0; k<numC; ++k){
             tilelist->push_back(new Tile('C',C));
         }
         for (size_t k=0; k<numD; ++k){
             tilelist->push_back(new Tile('D',D));
         }
         for (size_t k=0; k<numE; ++k){
             tilelist->push_back(new Tile('E',E));
         }
         for (size_t k=0; k<numF; ++k){
             tilelist->push_back(new Tile('F',F));
         }
         for (size_t k=0; k<numG; ++k){
             tilelist->push_back(new Tile('G',G));
         }
         for (size_t k=0; k<numH; ++k){
             tilelist->push_back(new Tile('H',H));
         }
         for (size_t k=0; k<numI; ++k){
             tilelist->push_back(new Tile('I',I));
         }
         for (size_t k=0; k<numL; ++k){
             tilelist->push_back(new Tile('L',L));
         }
         for (size_t k=0; k<numM; ++k){
             tilelist->push_back(new Tile('M',M));
         }
         for (size_t k=0; k<numN; ++k){
             tilelist->push_back(new Tile('N',N));
         }
         for (size_t k=0; k<numO; ++k){
             tilelist->push_back(new Tile('O',O));
         }
         for (size_t k=0; k<numP; ++k){
             tilelist->push_back(new Tile('P',P));
         }
         for (size_t k=0; k<numQ; ++k){
             tilelist->push_back(new Tile('Q',Q));
         }
         for (size_t k=0; k<numR; ++k){
             tilelist->push_back(new Tile('R',R));
         }
         for (size_t k=0; k<numS; ++k){
             tilelist->push_back(new Tile('S',S));
         }
         for (size_t k=0; k<numT; ++k){
             tilelist->push_back(new Tile('T',T));
         }
         for (size_t k=0; k<numU; ++k){
             tilelist->push_back(new Tile('U',U));
         }
         for (size_t k=0; k<numV; ++k){
             tilelist->push_back(new Tile('V',V));
         }
         for (size_t k=0; k<numZ; ++k){
             tilelist->push_back(new Tile('Z',Z));
         }
         for (size_t k=0; k<numJolly; ++k){
             tilelist->push_back(new Tile('J',jollyTexture[k]));
         }

         size=maxtile;
}

TileList *Bag::extract(unsigned int quantity){
    //se estraggo il primo elemento allora devo cambiare head, altrimenti devo sostituire il nextptr del nodo precedente a quello estratto con il nextptr del nodo estratto e ritornare l'indirizzo del nodo estratto
    //la gestione dell'head dovrebbe essere già fatta dall'extract_node()
    size_t temp=tilelist->size();
    size_t temp1=size;

    if (quantity>size){
        quantity=size;
    }

    TileList* templist=new TileList(); //puntatore a lista temporaneo che utilizzo per il return. la testa è da eliminare prima del return in modo da passare solamente nodi effettivamente utilizzati
    std::size_t position=0;
    for(size_t i=0;i<quantity;++i){ //gira esattamente quantity volte
        position=0;
        position=rand()%size;
        --size;
        templist->push_back((*tilelist).extract(position)); //aggiungo il nodo appena estratto da bag list alla lista temporanea
    }
    return templist->next(); //puntatore temporaneo a lista utilizzato per distruggere la memoria nello heap leagata a templist. inoltre permette di eliminare la testa della lista che andremo a passare

}

Tile *Bag::extractTile(char letter){
    size_t pos=0;
    TileList *temp=tilelist;
    while(temp!=nullptr && pos<size){
        if(temp->getTile(pos)!=nullptr){
            if(temp->getTile(pos)->getLetter()==letter){
                size--;             
                return tilelist->extractTile(pos);
            }
        }
        pos++;
    }    
    return nullptr;

}
void Bag::addTiles(TileList *hand){
    size+=hand->size()+1;   // +1 in quanto gli ho passato la mano senza la testa, e il size parte a contare tenendo conto della testa
    tilelist->push_back(hand);
}
