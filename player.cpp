#include "player.h"

void Player::refill_hand(Bag* bag){ //aggiunge alla mano il numero di tessere mancanti
    unsigned int tilesleft= handMaxSize-hand->size();
    hand->push_back(bag->extract(tilesleft));
    float sPosx=(boardPixelSize)/2 - image_size*hand->size()/2; // in modo che la mano sia sempre centrata
    float sPosy=boardPixelSize + image_size;
    Tile* temp;
    for(size_t i=0;i<hand->size();++i){
            temp=hand->getTile(i);
            if(temp!=nullptr)
                temp->setPosition(sPosx+image_size*i,sPosy);
      }

}

bool Player::firstMove(){
int counter=0;
for(size_t i=0;i<hand->size();++i){
    if(hand->getTile(i)->getSprite()->getPosition().x<boardPixelSize && hand->getTile(i)->getSprite()->getPosition().y<boardPixelSize)
        ++counter;
}
if(counter==1)
return true;

return false;
}

bool Player::isPos_free(sf::Vector2f pos){
    sf::Vector2f sPos;
    int counter=0;
    for(size_t i=0;i<hand->size();++i){
        sPos= sf::Vector2f(hand->getTile(i)->getSprite()->getPosition());
        if(sPos==pos)
            ++counter;
    }
    if(counter==0)
        return true;
    return false;
}


sf::Sprite *Player::getSprites(size_t pos){
    if(pos<hand->size()){
       return hand->getTile(pos)->getSprite();
    }
    return nullptr;
}

Player::~Player(){
    delete hand;
}

void Player::changeHand(Bag *myBag){

    TileList *tempList;
    tempList=hand->next();
    hand->cutHead();
    myBag->addTiles(tempList);        
    refill_hand(myBag);
    //parte grafica
    float sPosx=(boardPixelSize)/2 - image_size*hand->size()/2; // in modo che la mano sia sempre centrata
    float sPosy=boardPixelSize + image_size;
    Tile *temp;
    for(size_t i=0;i<hand->size();++i){
        temp=hand->getTile(i);
        if(temp!=nullptr)
            temp->setPosition(sPosx+image_size*i,sPosy);
    }
}
