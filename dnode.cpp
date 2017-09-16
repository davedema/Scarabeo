#include "dnode.h"

Dnode::Dnode(){
    for(size_t a=0;a<alphabeth_size;++a){
        this->node[a].exists=false;
        this->node[a].nextptr=nullptr;
    }
}

size_t Dnode::switchletter(char c){
    switch (c) {
    case 'A': case 'a': return 0;
    case 'B': case 'b': return 1;
    case 'C': case 'c': return 2;
    case 'D': case 'd': return 3;
    case 'E': case 'e': return 4;
    case 'F': case 'f': return 5;
    case 'G': case 'g': return 6;
    case 'H': case 'h': return 7;
    case 'I': case 'i': return 8;
    case 'L': case 'l': return 9;
    case 'M': case 'm': return 10;
    case 'N': case 'n': return 11;
    case 'O': case 'o': return 12;
    case 'P': case 'p': return 13;
    case 'Q': case 'q': return 14;
    case 'R': case 'r': return 15;
    case 'S': case 's': return 16;
    case 'T': case 't': return 17;
    case 'U': case 'u': return 18;
    case 'V': case 'v': return 19;
    case 'Z': case 'z': return 20;
    case '\n': case '\r': return 21;
    default: return 21;
    }

}

Dnode* Dnode::addletter_node(char c){ // aggiunge la lettera all'array e crea un nuovo nodo sotto di lui, ritorna il puntatore al nodo appena creato
    size_t temp=switchletter(c);

    if (this->node[temp].exists==false){
        this->node[temp].exists=true;
        if (c!='\n' && c!='\r') //nel caso in cui il carattere dovesse essere un carattere terminatore allora la frase sarebbe terminata, perciò non si troverà alcun altra lettera dopo di essa
            this->node[temp].nextptr=new Dnode();
    }

    return this->node[temp].nextptr; //il costruttore di Dnode imposta nextptr come nullptr, perciò nel caso dello \n questa funzione ritornerà nullptr
}

bool Dnode::is_present(char c){
    return this->node[switchletter(c)].exists;
}

Dnode::~Dnode(){
for(size_t i=0; i<alphabeth_size;++i){
    delete node[i].nextptr;
    }
}

Dnode* Dnode::next(char c){//ritorna il puntatore al prossimo dnode (relativo alla lettera scelta)
    return this->node[switchletter(c)].nextptr;
}
