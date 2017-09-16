#include "dictionary.h"


Dictionary::Dictionary(){

    node=new Dnode();
    std::ifstream dict(filename);
    char c=' '; //variabile temporanea in cui salverò temporaneamente i caratteri appena letti da file (uno per volta)
    Dnode* tempnode=this->node; //puntatore utilizzato per costruire l'albero senza il rischio di perdere la testa
    if(dict.is_open()){
        while(dict.good()){
            dict.get(c);
            if (c!='\n'){
                tempnode=tempnode->addletter_node(c); // addletter_node aggiunge il carattere appena trovato e crea un nuovo Dnode sotto al nodo eppena modificato. inoltre ritorna il puntatore al Dnode appena creato
                // se il carattere e' \r allora non crea un nuovo Dnode
                if (tempnode==nullptr){ //cioè nel caso in cui è appena stato trovato \r , cioè nel caso in cui una parola sia stata cmpletamente inserita
                    tempnode=this->node; //ricomincio dalla cima dell'albero
                }
            }
        }
    }else{
        std::cout<<"problem while opening "<<filename<<std::endl;
    }

    dict.close();

}

bool Dictionary::recursive_search(std::string word,size_t pos,size_t lastpos,Dnode* tempnode){   
    if(pos!=lastpos){
        if (!tempnode->is_present(word[pos])){// se il carattere della parola cercata non è presente nel nodo allora la parola non può esistere. questo comprende anche il carattere terminatore
            return false;
        }else{ //se il carattere è presente nel nodo corrente
            if(word[pos]=='\r' || word[pos]=='\n'){ // e se il carattere preso in considerazione è \r o \n -> cioè la parola è finita
                return true; //quindi ritorno true se la parola è terminata e nell'albero ho salvato in quel nodo un true nella casella di \r
                //(cioè che le lettere presenti sul percorso fatto per arrivare fino a qui formano una parola presente nel dizionario italiano)
            }
        }
        return recursive_search(word,pos+1,lastpos,tempnode->next(word[pos]));
    }
    return false;
}

bool Dictionary::search(std::string word){    
    return recursive_search(word,0,word.size(),this->node);
}

Dictionary::~Dictionary(){    
    delete node;
}




