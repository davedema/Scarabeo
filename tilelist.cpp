#include "tilelist.h"

//**********************************************da sistemare decisamente*************************//
/*
void TileList::recursiveDelete(TileList *tilelist){
    if(this->nextptr!=nullptr)
        return recursiveDelete(this->nextptr);
    if(this->nextptr==nullptr){
        delete tile;        //**************************************ripassa le slides sulle classi, non sono sicuro che sia corretto agire in questo modo*************************************
        delete this;
    }
}*/
//**************************************************************************************************



TileList::TileList():tile(nullptr),nextptr(nullptr){}

TileList::TileList(Tile* t):tile(t),nextptr(nullptr){}

TileList::TileList(TileList *t){
    TileList *tCursor=t;
    size_t i=0;
    while (tCursor!=nullptr){
        this->push_back(new TileList(t->getTile(i)));
        tCursor=tCursor->next();
        i++;
    }
}


void TileList::push_back(Tile *t){ //scorre la lista con un while fino a trovare nextptr==nullptr, a quel punto vi aggancia una nuova tilelist costruita passando il Tile* t ricevuto in input
        TileList*temp=this;
        while(temp->nextptr!=nullptr){
            temp=temp->nextptr;
        }
        temp->nextptr=new TileList(t);
}

void TileList::push_back(TileList* tilelist){ //scorre la lista con un while fino a trovare nextptr==nullptr, a quel punto vi aggancia la tilelist passata come parametro
    TileList *temp=this;

    while(temp->nextptr!=nullptr){
        temp=temp->nextptr;
    }    
    temp->nextptr=tilelist;
}


TileList *TileList::operator[](size_t pos){
    size_t i=0;
    TileList* Pcurrent=this;
    while(Pcurrent->next()!=nullptr && i<pos){    // scorro finchè la lista non finisce e finchè non abbiamo ancora raggiunto la posizione stabilita
        ++i;
        Pcurrent=Pcurrent->next();
    }
    if (i==pos)
        return Pcurrent;
}

TileList *TileList::extract(size_t pos){ //ritorna il puntatore al nodo della lista di tilelist in posizione ps
    size_t i=0;
    TileList* Pcurrent=this;            //mi servono due puntatori, uno che punti alla posizionie precedente a quella che ritornerò
    TileList* Pnext=this->nextptr;     // e una che punti al nodo che effettivamente ritornerò
    while(Pnext!=nullptr && i<pos){    // scorro finchè la lista non finisce e finchè non abbiamo ancora raggiunto la posizione stabilita
        ++i;
        Pcurrent=Pnext;
        Pnext=Pnext->nextptr;
    }
    //dopo il ciclo ci troviamo nella situazione in cui o Pnext è nullptr, o i==pos o (Pnext==nullptr  e i==pos)
    if (Pnext!=nullptr && i==pos){  //controllo di essere effettivamente giunto al nodo da ritornare e controllo che quel nodo non sia nullo
        Pcurrent->nextptr=Pnext->nextptr; //aggancio il nodo precedente a quello da ritornare con il nodo successivo al nodo da ritornare
        Pnext->nextptr=nullptr; //Per pulizia assegno al nextptr del Pnext da ritornare, nullptr        
        return Pnext; //ritorno il nodo cercato
    }
    //in caso contrario, cioè nel caso in cui la posizione data in input non sia associata ad un nodo nella lista, ritorno nullptr
    return nullptr;


}

Tile *TileList::extractTile(size_t pos){
    size_t i=0;
    TileList* Pcurrent=this;            //mi servono due puntatori, uno che punti alla posizionie precedente a quella che ritornerò
    TileList* Pnext=this->nextptr;     // e una che punti al nodo che effettivamente ritornerò
    Tile *temp;
    while(Pnext!=nullptr && i<pos){    // scorro finchè la lista non finisce e finchè non abbiamo ancora raggiunto la posizione stabilita
        ++i;
        Pcurrent=Pnext;
        Pnext=Pnext->nextptr;
    }
    //dopo il ciclo ci troviamo nella situazione in cui o Pnext è nullptr, o i==pos o (Pnext==nullptr  e i==pos)
    if (Pnext!=nullptr && i==pos){  //controllo di essere effettivamente giunto al nodo da ritornare e controllo che quel nodo non sia nullo
        Pcurrent->nextptr=Pnext->nextptr; //aggancio il nodo precedente a quello da ritornare con il nodo successivo al nodo da ritornare
        Pnext->nextptr=nullptr; //Per pulizia assegno al nextptr del Pnext da ritornare, nullptr
        temp=Pnext->tile;
        Pnext->tile=nullptr;
        delete Pnext;
        return temp; //ritorno il nodo cercato
    }
    //in caso contrario, cioè nel caso in cui la posizione data in input non sia associata ad un nodo nella lista, ritorno nullptr
    return nullptr;
}

Tile* TileList::getTile(size_t pos){ //ritorna un puntatore alla tile nella posizione passata come parametro
    //if (this!=nullptr){
    TileList* temp=this->nextptr; // al massimo può essere nullptr
    size_t i=0;
    while (temp!=nullptr && i<pos){//evito di accedere a zone di memoria non definite con temp!= nullprt
        temp=temp->nextptr;
        ++i;
    }
    if(temp!=nullptr&&temp->tile!=nullptr && i==pos)
        return temp->tile;

    return nullptr;
}


size_t TileList::size(){
    TileList* temp = this->nextptr; //this rappresenta per noi la testa, che punta alla lista effettiva, non fa parte del calcolo della lunghezza della lista
    size_t i=0;
    while(temp!=nullptr){
        i++;
        temp=temp->nextptr;
    }

    if(i<=130)
        return i;
    return 0;
}

TileList* TileList::next(){
    return nextptr;
}

/*
std::__cxx11::string TileList::toString(){
    std::string temp;
    TileList *tempPointer=this->next();
    size_t i=0;
    while (tempPointer!=nullptr){
        temp.push_back(tempPointer->getTile(i)->getLetter());
        i++;
    }
    return temp;
}
*/

void TileList::cutHead(){
    if(this->tile==nullptr)
        this->nextptr=nullptr;
}

unsigned int TileList::listPoints(){
    unsigned int temp=0;
    for(size_t i=0;i<size();++i){
        temp+=getTile(i)->getPoints();
    }
    return temp;
}


TileList::~TileList(){    
    delete tile;
    delete nextptr;
}


