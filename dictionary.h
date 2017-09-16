#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <fstream>
#include <dnode.h>

const std::string filename="/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Dizionario.txt";

class Dictionary{

    Dnode* node;    

    bool recursive_search(std::string word,size_t pos,size_t lastpos,Dnode* tempnode);

public:
    Dictionary();    
    bool search(std::string word);            
    Dnode *getDnode(){return node;}
    ~Dictionary();
};

#endif // DICTIONARY_H
