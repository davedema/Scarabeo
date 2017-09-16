#include "tile.h"

Tile::Tile(){
    letter=' ';
    points=0;
    state=checked;
    Jolly=false;
    sprite=new sf::Sprite();        
}


Tile::Tile(char c,sf::Texture* texture){

    letter=c;

    switch(c){
    case 'A': points=pointA; break;
    case 'B': points=pointB; break;
    case 'C': points=pointC; break;
    case 'D': points=pointD; break;
    case 'E': points=pointE; break;
    case 'F': points=pointF; break;
    case 'G': points=pointG; break;
    case 'H': points=pointH; break;
    case 'I': points=pointI; break;
    case 'L': points=pointL; break;
    case 'M': points=pointM; break;
    case 'N': points=pointN; break;
    case 'O': points=pointO; break;
    case 'P': points=pointP; break;
    case 'Q': points=pointQ; break;
    case 'R': points=pointR; break;
    case 'S': points=pointS; break;
    case 'T': points=pointT; break;
    case 'U': points=pointU; break;
    case 'V': points=pointV; break;
    case 'Z': points=pointZ;  break;
    case 'J': points=pointJolly; break;
    default: points=0; break;
    }

    if(c=='J'){
        Jolly=true;
    }else{
        Jolly=false;
    }
    state=checked;

    sprite=new sf::Sprite();
    sprite->setTexture(*texture);

}

/*
void Tile::setJolly_letter_Sprite(char c){
    sf::Texture *T=new sf::Texture();
    if(Jolly==true){

        letter=c;
        setJolly_points(c);

        switch(c){
        case 'A':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/A.png");
            sprite->setTexture(*T);
            break;
        case 'B':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/B.png");
            sprite->setTexture(*T);
            break;
        case 'C':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/C.png");
            sprite->setTexture(*T);
            break;
        case 'D':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/D.png");
            sprite->setTexture(*T);
            break;
        case 'E':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/E.png");
            sprite->setTexture(*T);
            break;
        case 'F':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/F.png");
            sprite->setTexture(*T);
            break;
        case 'G':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/G.png");
            sprite->setTexture(*T);
            break;
        case 'H':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/H.png");
            sprite->setTexture(*T);
            break;
        case 'I':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/I.png");
            sprite->setTexture(*T);
            break;
        case 'L':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/L.png");
            sprite->setTexture(*T);
            break;
        case 'M':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/M.png");
            sprite->setTexture(*T);
            break;
        case 'N':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/N.png");
            sprite->setTexture(*T);
            break;
        case 'O':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/O.png");
            sprite->setTexture(*T);
            break;
        case 'P':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/P.png");
            sprite->setTexture(*T);
            break;
        case 'Q':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/Q.png");
            sprite->setTexture(*T);
            break;
        case 'R':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/R.png");
            sprite->setTexture(*T);
            break;
        case 'S':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/S.png");
            sprite->setTexture(*T);
            break;
        case 'T':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/T.png");
            sprite->setTexture(*T);
            break;
        case 'U':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/U.png");
            sprite->setTexture(*T);
            break;
        case 'V':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/V.png");
            sprite->setTexture(*T);
            break;
        case 'Z':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/Z.png");
            sprite->setTexture(*T);
            break;
        case 'J':
            delete sprite->getTexture();
            T->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png");
            sprite->setTexture(*T);
            break;
        default:
            delete T;
            break;
        }

    }

}

*/
void Tile::setJolly_letter(char c){
    if(Jolly==true){
        letter=c;
        setJolly_points(c);
    }
}

void Tile::setJolly_points(char c){
    if(Jolly==true){
        switch(c){
        case 'A': points=pointA; break;
        case 'B': points=pointB; break;
        case 'C': points=pointC; break;
        case 'D': points=pointD; break;
        case 'E': points=pointE; break;
        case 'F': points=pointF; break;
        case 'G': points=pointG; break;
        case 'H': points=pointH; break;
        case 'I': points=pointI; break;
        case 'L': points=pointL; break;
        case 'M': points=pointM; break;
        case 'N': points=pointN; break;
        case 'O': points=pointO; break;
        case 'P': points=pointP; break;
        case 'Q': points=pointQ; break;
        case 'R': points=pointR; break;
        case 'S': points=pointS; break;
        case 'T': points=pointT; break;
        case 'U': points=pointU; break;
        case 'V': points=pointV; break;
        case 'Z': points=pointZ;  break;
        default: points=0; break;
        }
    }

}

sf::Sprite* Tile::getSprite(){
    return sprite;
}

void Tile::setPosition(float x, float y){
    sprite->setPosition(x,y);
}

Tile::~Tile(){
    delete sprite;
}

char Tile::getLetter() const{
    return letter;
}
