#include "board.h"


// COSTRUTTORE
Board::Board(){

    for(size_t i=0;i<board_size;++i){// inizialmente non sono presenti lettere sul tabellone, perciò assegno a tutte le caselle della matrice contenente i puntatori alle lettere nullptr
        for(size_t j=0;j<board_size;++j){
            tBoard[i][j]=nullptr;
        }
    }

    //dichiaro le textures necessarie per disegnare il tabellone di gioco
    sf::Texture *l2=new sf::Texture(),*p2=new sf::Texture(),*l3=new sf::Texture(),*p3=new sf::Texture(),
            *backcolor1=new sf::Texture(),*backcolor2=new sf::Texture(),*scarabeo=new sf::Texture();

    //carico le immagini necessarie nelle rispettive textures
    l2->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/2L.png");
    p2->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/2P.png");
    l3->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/3L.png");
    p3->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/3P.png");
    backcolor1->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/LightBrown.png");
    backcolor2->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/Brown-red.png");
    scarabeo->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/scarabeo.png");

    //in questi 2 cicli vengono assegnate le texture e le posizioni alle rispettive sprites
    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){

            sBoard[0][i*board_size+j].setPosition(j*image_size,i*image_size); // setto la posizione della sprite

            switch (board_blueprint[i][j]) { //in base alla lettera presente nel "progetto" del tabellone (vedi board_blueprint in constants.h) assegno una texture differente ala sprite
            case 'W':sBoard[0][i*board_size+j].setTexture(*p3);break;
            case 'w':sBoard[0][i*board_size+j].setTexture(*p2);break;
            case 'L':sBoard[0][i*board_size+j].setTexture(*l3);break;
            case 'l':sBoard[0][i*board_size+j].setTexture(*l2);break;
            case 's':sBoard[0][i*board_size+j].setTexture(*scarabeo);break;
            default: // di default se la casella è in una posizione pari sul tabellone (contando le celle di memoria dalla prima a quella presa in considerazione) allora assegno una texture di un colore, altrimenti una texture di un altro
                if((i*board_size+j)%2==0){
                    sBoard[0][i*board_size+j].setTexture(*backcolor1);
                }else{
                    sBoard[0][i*board_size+j].setTexture(*backcolor2);
                }
                break;
            }
        }
    }

    for(size_t i=0;i<board_size*board_size;++i){ //assegno alle sprites delle tiles una posizione negativa
        sBoard[1][i].setPosition(-100,-100); //per convenzione mia,serve nel main in modo tale da capire quando queste sprites non hanno ancora assunto valori validi
    }

}

unsigned int Board::wordPoints(bool jollyUsed){

    wordtype dir=WordDirection();
    bool firstLetter=true;
    bool spaceFound=false;
    int c=0;    
    std::string word;    
    unsigned int points=0;
    unsigned int tempPoints=0;
    unsigned int letterMultiplier=1;
    unsigned int wordMultiplier=1;
    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){

            if(firstLetter){
                if(tBoard[i][j]!=nullptr){
                    if(tBoard[i][j]->getStatus()==checking){

                        firstLetter=false;
                        if(dir==vertical){ //se è verticale controllo le lettere presenti sopra la prima delle lettere inserite
                            while(i-c>0 && !spaceFound){
                                c++;
                                if(tBoard[i-c][j]==nullptr || i-c==0){ //se trovo una casella vuota comincio il calcolo del punteggio della parola principale
                                    spaceFound=true; //assegno true alla variabile spacefound per poter uscire dal ciclo ala fine di questa operazione
                                        int k=1; // se ho incontrato un nullptr allora devo cominciare a contare dalla lettera successiva
                                        if(tBoard[i-c][j]!=nullptr){ //se sono giunto alla fine del tabellone devo cominciare a contare da questa cassella
                                            k=0;
                                        }
                                        while(i-c+k<board_size && tBoard[i-c+k][j]!=nullptr){
                                            word.push_back(tBoard[i-c+k][j]->getLetter()); //salvo la parola in modo da poter controllare se è candidabile all'assegnamento di punteggi speciali

                                            letterMultiplier=1;
                                            if(tBoard[i-c+k][j]->getStatus()==checking){ //nel caso in cui la lettera sia stata giocata in questo turno allora tengo conto dei moltiplicatori
                                                switch (board_blueprint[i-c+k][j]){ //in base al "progetto" del tabellone controllo i moltiplicatori di parola e di lettera
                                                case 'L': letterMultiplier=3; break;
                                                case 'l': letterMultiplier=2; break;
                                                case 'W': letterMultiplier=1; wordMultiplier*=3; break;
                                                case 'w': letterMultiplier=1; wordMultiplier*=2; break;
                                                default: letterMultiplier=1; break;
                                                }
                                            }

                                            tempPoints+=tBoard[i-c+k][j]->getPoints()*letterMultiplier;
                                            k++;
                                        }                                        

                                }                               
                            }                            
                            points+=tempPoints*wordMultiplier; //motiplico il punteggio per il moltiplicatore di parola
                        }

                        letterMultiplier=1;
                        wordMultiplier=1;
                        tempPoints=0;

                        if(dir==horizontal){
                            spaceFound=false;
                            c=0;
                            while(j-c>0 && !spaceFound){
                                c++;
                                if(tBoard[i][j-c]==nullptr || j-c==0){
                                    spaceFound=true;
                                        int k=1; // se è nullptr comincio dalla prossima casella
                                        if(tBoard[i][j-c]!=nullptr){ //se invece mi sono fermato a causa del limite della board allora comincio a calcolare dal limite
                                            k=0;
                                        }
                                        while(j-c+k<board_size && tBoard[i][j-c+k]!=nullptr){
                                            word.push_back(tBoard[i][j-c+k]->getLetter());
                                            letterMultiplier=1;

                                            if(tBoard[i][j-c+k]->getStatus()==checking){
                                                switch (board_blueprint[i][j-c+k]){ //in base al "progetto" del tabellone controllo i moltiplicatori di parola e di lettera
                                                case 'L': letterMultiplier=3; break;
                                                case 'l': letterMultiplier=2; break;
                                                case 'W': letterMultiplier=1; wordMultiplier*=3; break;
                                                case 'w': letterMultiplier=1; wordMultiplier*=2; break;
                                                default: letterMultiplier=1; break;
                                                }
                                            }

                                            tempPoints+=tBoard[i][j-c+k]->getPoints() * letterMultiplier;
                                            k++;
                                        }                                         
                                }                             
                            }                            
                            points+=tempPoints*wordMultiplier;
                        }
                    }
                }
            }
        }
    }


    if(word=="SCARABEO" || word=="SCARABEI"){
        points+=100;
    }

    word.clear();

    //fino a qua ho controllato il punteggio della "parola principale formata

    //adesso aggiungo i punti dovuti alla formazione di più di una parola


    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr){
                tempPoints=0;
                letterMultiplier=1;
                wordMultiplier=1;
                if(tBoard[i][j]->getStatus()==checking){ //cerco lettere checking

                    switch (board_blueprint[i][j]){ //in base al "progetto" del tabellone controllo i moltiplicatori di parola e di lettera
                    case 'L': letterMultiplier=3; break;
                    case 'l': letterMultiplier=2; break;
                    case 'W': letterMultiplier=1; wordMultiplier*=3; break;
                    case 'w': letterMultiplier=1; wordMultiplier*=2; break;
                    default: letterMultiplier=1; break;
                    }                    
                    spaceFound=0;
                    c=0;

                    if(dir==vertical || dir==singleTile){ //se è verticale controllo gli incroci orizzontali... ma anche se si tratta di un tile giocato singolarmente
                        while(j-c>=0 && !spaceFound){
                            if(tBoard[i][j-c]==nullptr || j-c==0){
                                spaceFound=true;
                                    word.clear();

                                    int k=1; // se è nullptr devo partire dalla casella successiva.. quindi k=1
                                    if(j-c==0){ //se invece mi sono fermato a causa del bordo della amtrice allora parto da questa posizione
                                        k=0;
                                    }

                                    while(j-c+k<board_size && tBoard[i][j-c+k]!=nullptr){       //in modo da partire dalla prima lettera
                                        word.push_back(tBoard[i][j-c+k]->getLetter());
                                        if(j-c+k!=j){ // il punteggio della lettera checking lo aggiungo successivamente
                                            tempPoints+=tBoard[i][j-c+k]->getPoints();
                                        }
                                        k++;
                                    }

                                    if(word=="SCARABEO" || word=="SCARABEI"){
                                        points+=100;
                                    }
                            }
                            c++;
                        }


                        if(tempPoints!=0){ //altrienti rischierei di somare due volte il punteggio della parola senza che ce ne sia effettivamente il bisogno
                            tempPoints+=tBoard[i][j]->getPoints()*letterMultiplier;
                        }
                        points+=tempPoints*wordMultiplier;
                    }


                    if(dir==horizontal || dir==singleTile){ //se è orizzontale controllo gli incroci verticali... ma anche se si tratta di un tile giocato singolarmente
                        spaceFound=0;
                        tempPoints=0;
                        c=0;
                        while(i-c>=0 && !spaceFound){
                            if(tBoard[i-c][j]==nullptr || i-c==0){
                                spaceFound=true;

                                    int k=1; // se è nullptr devo partire dalla casella successiva.. quindi k=1
                                    if(i-c==0){ //se invece mi sono fermato a causa del bordo della amtrice allora parto da questa posizione, quindi k=0
                                        k=0;
                                    }

                                    word.clear();
                                    while(i-c+k<board_size && tBoard[i-c+k][j]!=nullptr){       //in modo da partire dalla prima lettera
                                        word.push_back(tBoard[i-c+k][j]->getLetter());
                                        if(i-c+k!=i){ // il punteggio della lettera checking lo aggiungo successivamente
                                            tempPoints+=tBoard[i-c+k][j]->getPoints();
                                        }
                                        k++;
                                    }
                                    if(word=="SCARABEO" || word=="SCARABEI"){
                                        points+=100;
                                    }
                            }
                            c++;
                        }
                        if(tempPoints!=0 || (dir==singleTile && is_empty())){       //permette alle parole di lunghezza 1 di ottenere punteggio alla prima giocata
                            tempPoints+=tBoard[i][j]->getPoints()*letterMultiplier;
                        }
                        points+=tempPoints*wordMultiplier;
                    }


                }
            }

        }
    }






    int counter=0;

    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr && tBoard[i][j]->getStatus()==checking){
                counter++;
            }
        }
    }

        points+=specialPoints(counter,jollyUsed);

    return points;
}



void Board::setChecked(){
    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr){                
                if(tBoard[i][j]->getStatus()!=checked){
                    tBoard[i][j]->setStatus(checked);
                }
            }
        }
    }
}

void Board::removeTiles(Player *player){
    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr && tBoard[i][j]->getStatus()!=checked){
                tBoard[i][j]->setStatus(checked);
                player->showHand()->push_back(tBoard[i][j]);
                tBoard[i][j]=nullptr;
            }
        }
    }

}


bool Board::updateBoards(Dictionary* dictionary,Bag* bag,Player* player){
    TileList* hand=player->showHand();                          // per evitare ogni volta la chiamata di funzione
    float posx=0,posy=0;                                        //usato per salvare la posizione delle sprite nella finestra di gioco
    bool rows[board_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //array di bool necessario per salvare in quali righe della matrice sono state aggiunte nuove lettere
    bool columns[board_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //array di bool necessario per salvare in quali colonne della matrice sono state aggiunte nuove lettere
    size_t x=0,y=0;                 //usati per salvare la posizione all'interno della matrice corrispondente alla posizione sul tabellone di gioco
    size_t counter=0;
    size_t size=hand->size();
    bool jollyUsed=false;
    Tile* temp;

    for(size_t i=0;i<size;++i){ //scorro tutti i tiles presenti nella mano del giocatore e controllo la loro posizione
        temp=hand->getTile(i-counter); //    ->getTile(i-counter);
        posx=temp->getSprite()->getPosition().x; //salvo le posizioni della sprite
        posy=temp->getSprite()->getPosition().y;
        if(temp->isJolly()){
            jollyUsed=true;
        }
        if(posx<boardPixelSize && posy<boardPixelSize){ // controllo che la sprite sia presente all'interno dell'area del tabellone di gioco
            x=int(posx/image_size);//segno la posizione sulla matrice della lettera inserita
            y=int(posy/image_size);
            columns[x]=true; //salvo le righe e le colonne necessarie per il controllo della parola
            rows[y]=true;
            temp->setStatus(checking); //cambio lo status a checking
            tBoard[y][x]=temp; //per ora lo inserisco nella matrice, nel caso in cui dovesse essere ritenuto idoneo allora dovrei provvedere a staccare il tilelist dalla hand del player
            temp=hand->extractTile(i-counter); //rimuove il nodo di tilelist da cui è stato estratto il tile
            ++counter; //conto quante lettere ho tolto dalla mano in modo tale da non sbordare quando cerco di accedere agli elementi della mano (riga 66)
            //-temporaneo

        }
    }

    //se le varie parole formate sono valide nel dizionario e le lettere sono state inserite in modo valido allora accetto le tile giocate,assegno i punti al giocatore e riempo la sua mano
    if(!isWordSeg(WordDirection()) && wordCrossed(WordDirection()) && checkString(dictionary,rowToString(rows)) && checkString(dictionary,columnToString(columns))){

        player->refill_hand(bag);//riempo la mano del giocatore        
        player->addPoints(wordPoints(jollyUsed)); //aggiungo i punti ottenuti dalle parole formate

        for(size_t i=0;i<board_size;++i){
            for(size_t j=0; j<board_size;++j){
                if(tBoard[i][j]!=nullptr && tBoard[i][j]->getStatus()==checking && tBoard[i][j]->isJolly()){
                    changeJollyTexture(tBoard[i][j],tBoard[i][j]->getLetter());
                }
            }
        }

        refreshSprites();
        setChecked(); //setto tutte le lettere come controllate
        return true;
    }else{ // se le parole formate sul tabellone non sono valide allora tutte le lettere appena giocate (quindi checking) tornano in mano al giocatore
        removeTiles(player);
        return false;
    }

}


wordtype Board::WordDirection(){ //controllo che la parola sia stata inserita in una sola riga/colonna e ritorno la direzione della parola
    size_t posx=-1,posy=-1;
    wordtype direction=unknown;
    size_t counter=0;
    for(size_t i=0;i<board_size;++i){ //scorro la matrice delle tiles
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr){ //evita di controllare le caselle contenenti nullptr
                if(tBoard[i][j]->getStatus()==checking){ //se la tile è stata giocata in questo turno(quindi è in fase di approvazione)
                    if(counter==0){//se è la prima tile trovata
                        posx=j; // mi segno la sua posizione
                        posy=i;            //sulle x e sulle y
                    }else{
                        if(counter==1){ //se è la seconda lettera trovata allora posso definire un verso per la parola
                            if(i==posy){//orizzontale
                                direction=horizontal;
                            }else{
                                if(j==posx){//verticale
                                    direction=vertical;
                                }else{ //altrimenti la lattera è stata inserita in una posizione non valida
                                    return unknown;
                                }
                            }
                        }else{ //dopo il controllo del secondo tile sappiamo già la direzione della parola
                            if(direction==vertical && j!=posx){ // se la parola è inserita in verticale e la lettera appena inserita non si trova sulla stessa colonna allora ret false
                                return unknown;
                            }else{
                                if(direction==horizontal && i!=posy) // se la parola è inserita in orizzont e la lettera appena inserita non si trova sulla stessa riga allora ret false
                                    return unknown;
                            }
                        }
                    }
                    if(counter<2)
                        counter++;
                }
            }
        }
    }
    if (counter==1) //se è stata trovata solo una lettera
        return singleTile;
    return direction;
}


//------------------------------------IS WORD SEGMENTED--------------------------
bool Board::isWordSeg(wordtype direction){ //ritorna vero se la parola è segmentata e quindi non valida (cioè se non è continua nella stessa riga)    
    if (direction==unknown)
        return true;
    size_t startingPosx=0,startingPosy=0;
    bool flag=0;
    bool spaceFound=0;
    size_t i=0,j=0;

    //per trovare la lettera iniziale della parola
    while(i<board_size && flag==false){
        while(j<board_size && flag==false){
            if(tBoard[i][j]!=nullptr){
                if(tBoard[i][j]->getStatus()==checking){
                    startingPosx=j;
                    startingPosy=i;
                    flag=true;
                }
            }
            j++;
        }
        j=0;
        i++;
    }

    if (direction==vertical){
        for(size_t y=startingPosy;y<board_size;++y){
            if(tBoard[y][startingPosx]!=nullptr){                                //se è stato trovato uno spazio nella parola ma dopo
                if(spaceFound && tBoard[y][startingPosx]->getStatus()==checking) //è stata trovata una altra tile checking allora la giocata non è valida                    
                        return true; //true.. la parola è "segmentata"
            }else{
                spaceFound=true;
            }
        }
    }else{
        if (direction==horizontal){
            for(size_t x=startingPosx;x<board_size;++x){
                if(tBoard[startingPosy][x]!=nullptr){                                //se è stato trovato uno spazio nella parola ma dopo
                    if(spaceFound && tBoard[startingPosy][x]->getStatus()==checking) //è stata trovata una altra tile checking allora la giocata non è valida                        
                        return true;
                }else{
                    spaceFound=true;
                }
            }
        }
    }

    if(wordCrossed(direction)){
    return false;
    }else{
        return true;
    }
}

bool Board::wordCrossed(wordtype dir){ //controlla che venga effettivamente intersecata una parola e che la prima parola passi per il centro
    bool WordCrossed=0;
    bool firstLetter=1,spaceFound=0;
    size_t c=0;

    if(is_empty()){                
        if(tBoard[board_size/2][board_size/2]!=nullptr){ //se la board è vuota controllo che la parola inserita passi per il centro del tabellone
            WordCrossed=1; //se è la prima mossa non è necessario controllare che la parola inserita incroci altre parole
        }
    }else{
        for(size_t i=0;i<board_size;++i){
            for(size_t j=0;j<board_size;++j){
                if(tBoard[i][j]!=nullptr){
                    if(tBoard[i][j]->getStatus()==checking){
                        if(firstLetter){
                            firstLetter=0;
                            if(dir==vertical || dir==singleTile){
                                c=0;
                                while(i+c<board_size && !spaceFound){
                                    if(tBoard[i+c][j]==nullptr){
                                        spaceFound=true;
                                    }else{
                                        if(tBoard[i+c][j]->getStatus()==checked){
                                            WordCrossed=1;
                                        }
                                    }
                                    c++;
                                }
                                c=0;
                                spaceFound=0;
                                while(i-c>0 && !spaceFound){
                                    c++;
                                    if(tBoard[i-c][j]==nullptr){
                                        spaceFound=true;
                                    }else{
                                        if(tBoard[i-c][j]->getStatus()==checked){
                                            WordCrossed=1;
                                        }
                                    }
                                }
                            }
                            if(dir==horizontal || dir==singleTile){
                                c=0;
                                spaceFound=0;
                                while(j+c<board_size && !spaceFound){

                                    if(tBoard[i][j+c]==nullptr){
                                        spaceFound=true;
                                    }else{
                                        if(tBoard[i][j+c]->getStatus()==checked){
                                            WordCrossed=1;
                                        }
                                    }
                                    c++;
                                }
                                c=0;
                                spaceFound=0;
                                while(j-c>0 && !spaceFound){
                                    c++;
                                    if(tBoard[i][j-c]==nullptr){
                                        spaceFound=true;
                                    }else{
                                        if(tBoard[i][j-c]->getStatus()==checked){
                                            WordCrossed=1;
                                        }
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }
    if(dir==unknown){
        WordCrossed=false;
    }
    return WordCrossed;
}


//**********************************************************CHECK STRING***************************************

bool Board::checkString(Dictionary* dictionary,std::string stringedBoard){
    std::string word;
    for(auto i=stringedBoard.begin();i!=stringedBoard.end();++i){
        if(*i!=' ')
            word.push_back(*i);
        else{
            if(word.size()>3){
                word.push_back('\r');
                if(!dictionary->search(word)){
                    return false;
                }
            }
            word.clear();
        }
    }
    return true;
}


std::string Board::rowToString(bool lines[]){
    std::string stemp="";
    for(size_t i=0;i<board_size;++i){
        if(lines[i]){
            for(size_t j=0;j<board_size;++j){
                if(tBoard[i][j]==nullptr){
                    stemp.push_back(' ');
                }else{
                    stemp.push_back(tBoard[i][j]->getLetter());
                }
            }
            stemp.push_back(' '); // quando cambio riga per la lettura aggiungo uno spazio alla stringa
        }
    }
    return stemp;
}



std::string Board::columnToString(bool columns[]){
    std::string stemp;
    for(size_t j=0;j<board_size;++j){
        if(columns[j]){
            for(size_t i=0;i<board_size;++i){
                if(tBoard[i][j]==nullptr){
                    stemp.push_back(' ');
                }else{
                    stemp.push_back(tBoard[i][j]->getLetter());
                }
            }
            stemp.push_back(' '); // quando cambio riga per la lettura aggiungo uno spazio alla stringa
        }
    }

    return stemp;
}

//*************************************************IS EMPTY********************************************
bool Board::is_empty(){
    bool temp=true;
    for(size_t i=0;i<board_size*board_size;++i){
        if(sBoard[1][i].getPosition().x>0 && sBoard[1][i].getPosition().y>0)
            temp=false;
    }
    return temp;
}


//**************************************************IS POS FREE*******************************
bool Board::isPos_free(sf::Vector2f pos){//scorro l'array contenente le sprites delle lettere e controllo che la posizione in cui vorrei lasciare la lettera non sia già occupata
    for(size_t i=0;i<board_size*board_size;++i){ //parto già dalla seconda riga del vettore, cioè da dove ho immagazzinato le sprites dei tasselli
        sf::Vector2f backPos(sBoard[1][i].getPosition());
        if(backPos.x>=0 && backPos.y>=0){ //controllo che la sprite presa in considerazione sia stata modificata almeno una volta dopo la costruzione della board, e quindi che contenga effettivamente i valori di un tile
            if(backPos==pos)
                return false;
        }
    }
    return true;

}


Tile* Board::pickJolly(sf::Vector2f pos,Tile *droppedTile){
Tile* temp;
sf::Vector2f backPos;
for(size_t i=0;i<board_size*board_size;++i){ //parto già dalla seconda riga del vettore, cioè da dove ho immagazzinato le sprites dei tasselli
    backPos.x=sBoard[1][i].getPosition().x;
    backPos.y=sBoard[1][i].getPosition().y;

    size_t rows= i/board_size;


    if(backPos.x>=0 && backPos.y>=0){ //controllo che la sprite presa in considerazione sia stata modificata almeno una volta dopo la costruzione della board, e quindi che contenga effettivamente i valori di un tile

         if(tBoard[rows][i-rows*board_size]!=nullptr){
            temp=tBoard[rows][i-rows*board_size];
            temp->isJolly();
         }

        if(backPos==pos && temp->isJolly() && temp->getLetter()==droppedTile->getLetter()){

            sf::Texture *J=new sf::Texture();
            J->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png");

            temp->setStatus(checked);               //reimposto i valori iniziali del jolly
            temp->setJolly_letter('j');            
            temp->getSprite()->setTexture(*J);
            tBoard[rows][i-rows*board_size]=droppedTile;
            droppedTile->setStatus(checked);        //reimposto i valori del tile come se fosse già stato giocato e controllato            
            sBoard[1][i]=*(droppedTile->getSprite());
            return temp;
        }
    }
}
return nullptr;
}


bool Board::onJolly(sf::Vector2f pos,Tile *droppedTile){

for(size_t i=0;i<board_size*board_size;++i){ //parto già dalla seconda riga del vettore, cioè da dove ho immagazzinato le sprites dei tasselli
    sf::Vector2f backPos(sBoard[1][i].getPosition());
    size_t rows= i/board_size;;
    if(backPos.x>=0 && backPos.y>=0){ //controllo che la sprite presa in considerazione sia stata modificata almeno una volta dopo la costruzione della board, e quindi che contenga effettivamente i valori di un tile
        if(backPos==pos && tBoard[rows][i-rows*17]->isJolly() && tBoard[rows][i-rows*17]->getLetter()==droppedTile->getLetter()){
            return true;
        }
    }
}
return false;
}


//****************************************************load from file****************************************************

void Board::loadFromFile(Bag *bag, std::__cxx11::string path){
std::ifstream file(path);
char c=' '; //variabile temporanea in cui salverò temporaneamente i caratteri appena letti da file (uno per volta)
size_t i=0;
size_t j=0;
sf::Vector2f newPos;

if(file.is_open()){
    while(file.good()){
        file.get(c);
        if (c=='*'){
            j++;
        }else{
            if(c=='\n'|| c=='\r'){
                i++;
                j=0;
            }else{
                tBoard[i][j]=bag->extractTile(c);                
                tBoard[i][j]->setStatus(checked);
                if(tBoard[i][j]!=nullptr){

                    newPos=sf::Vector2f(tileCentered_Pos(j), tileCentered_Pos(i)); //posizione lettera in modo da centrare la casella graficamente
                    sBoard[1][i*17 + j]=*(tBoard[i][j]->getSprite());
                    sBoard[1][i*17 + j].setPosition(newPos);                 
                }
                j++;
            }
        }
    }
}else{
std::cout<<"problem while opening "<<path<<std::endl;
}

file.close();
}



//impostare il cambio sprite del jolly
//impostare chiamata help estremo.... (vedi add tile)
//impostare capacità di scambiare una lettera dalla mano con un jolly sul tabellone


//*****************************************************HELP***************************************************

bool Board::help(Player *player, Dictionary *dictionary,Bag *bag){
    TileList *hand=player->showHand();
    size_t size=hand->size();
    bool goodForVerticals[board_size][board_size]={0};
    bool goodForHorizontals[board_size][board_size]={0};


    if(is_empty()){ //se il tabellone è vuoto accetto solo la riga e la colonna centrale ad un massimo di 7 caselle di distanza dal centro
        for(size_t a=board_size/2 +1 -handMaxSize; a<board_size/2+handMaxSize; ++a){
                goodForHorizontals[board_size/2][a]=true;
                goodForVerticals[a][board_size/2]=true;
        }
    }else{

        for(size_t i=0;i<board_size;++i){
            for(size_t j=0;j<board_size;++j){
                if(tBoard[i][j]==nullptr){
                    if(i>0 && tBoard[i-1][j]!=nullptr) //controllo la cella precedente, in quanto potrei voler cominciare una parola con una lettera già presente sul tabellone
                        goodForVerticals[i][j]=true;

                    if(j>0 && tBoard[i][j-1]!=nullptr) //controllo la cella precedente, in quanto potrei voler cominciare una parola con una lettera già presente sul tabellone
                        goodForHorizontals[i][j]=true;

                    for(int c=0;c<size;c++){ //controllo le tot celle successive (tot =hand->size()) per una cella piena, in questo modo so he da quella posizione potrei potenzialmente creare una parola
                        if(i+c<board_size){
                            if(tBoard[i+c][j]!=nullptr){
                                goodForVerticals[i][j]=true;
                            }
                        }

                        if(j+c<board_size){
                            if(tBoard[i][j+c]!=nullptr) //controllo le tot celle successive (tot =hand->size()) per una cella piena, in questo modo so he da quella posizione potrei potenzialmente creare una parola
                                goodForHorizontals[i][j]=true;
                        }

                    }
                }
            }
        }
    }

    int tempPoints=0;
    int topPoints=0;
    size_t topPosX=0;
    size_t topPosY=0;
    std::string word;
    std::string topWord="";
    size_t k=0;
    wordtype dirTopWord;
    Tile* tempTile;
    char letter;
    size_t c=0;
    bool letterFound=0;
    sf::Vector2f newPos;
    size_t itoCall=0;
    size_t jtoCall=0;
    bool spaceFound=0;
    bool jollyUsed=false;



    //**************************************chiamata verticale********************************

    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(goodForVerticals[i][j]){
                spaceFound=0;
                itoCall=i;

                c=0;
                while(i-c>0 && !spaceFound){ //se prima della posizione di partenza ci sono altre lettere le tengo in considerazione per partire dalla prima di queste
                    c++;                     //altrimenti formerei parole di senso compiuto solo dalla posizione di partenza senza tenere conto delle lettere precedenti,quindi poi nel controllo punti mote parole andrbbero scartate
                    if(tBoard[i-c][j]!=nullptr){
                        itoCall=i-c;
                    }else{
                        spaceFound=1;
                    }
                }

                if(tBoard[itoCall][j]==nullptr){ //se la cella è vuota
                    k=0;
                    while(k<size){          //scorro le varie lettere presenti in mano cercando una prima lettera per la mia parola
                        word.clear();       //pulisco word in cui salvo le varie parole temporanee generate
                        if(hand->getTile(k)!=nullptr && (dictionary->getDnode()->is_present(hand->getTile(k)->getLetter()) || hand->getTile(k)->isJolly())){ //se nel dizionario esistono parole che cominciano con la lettera scelta

                            if(hand->getTile(k)->getStatus()!=checking){        //se la lettera scelta non si trova sul tabellone
                                tempPoints=addTile(k,hand,dictionary,itoCall,j,vertical,word,dictionary->getDnode(),jollyUsed); //chiamo la funzione ricorsiva addTile che restituirà il punteggio maggiore ottenuto emodificherà word salvando al suo interno la TOPWORD
                                if (tempPoints>topPoints){          // se il punteggio appena ottenuto dalla chiamata di funzione è superiore al punteggio massimo incontrato fin'ora
                                    topPoints=tempPoints;           //cambio il punteggio massimo
                                    topWord=word;                   //salvo la parola corrispondente
                                    topPosY=itoCall;
                                    topPosX=j;
                                    dirTopWord=vertical;
                                }
                            }
                        }
                        k++;
                    }
                }else{
                    k=0;
                    word.clear();
                    if(dictionary->getDnode()->is_present(tBoard[itoCall][j]->getLetter())){
                            tempPoints=addTile(k,hand,dictionary,itoCall,j,vertical,word,dictionary->getDnode(),false); //i jolly presenti sul tabellone non vanno presi in considerazione per quanto riguarda gli special points, perciò chiamo la funzione con jollyused=false
                            if (tempPoints>topPoints){
                                topPoints=tempPoints;
                                topWord=word;
                                topPosY=itoCall;
                                topPosX=j;
                                dirTopWord=vertical;                           
                        }
                    }

                }
            }
        }
    }



    //*************************************chiamata orizzontale***********************

    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(goodForHorizontals[i][j]){
                spaceFound=0;
                jtoCall=j;

                c=0;
                while(j-c>0 && !spaceFound){    //se prima della posizione di partenza ci sono altre lettere le tengo in considerazione per partire dalla prima di queste
                    c++;                        //altrimenti formerei parole di senso compiuto solo dalla posizione di partenza senza tenere conto delle lettere precedenti,quindi poi nel controllo punti mote parole andrbbero scartate
                    if(tBoard[i][j-c]!=nullptr){
                        jtoCall=j-c;
                    }else{
                        spaceFound=1;
                    }
                }

                if(tBoard[i][jtoCall]==nullptr){
                    k=0;
                    while(k<size){
                        word.clear();
                        if(hand->getTile(k)!=nullptr && (dictionary->getDnode()->is_present(hand->getTile(k)->getLetter()) || hand->getTile(k)->isJolly())){
                            if(hand->getTile(k)->getStatus()!=checking){   //se la lettera scelta non si trova sul tabellone

                                if(hand->getTile(k)->isJolly()){ // se è stato usato un jolly imposto jollyused a true in modo da poter chiamare correttamente la funzione addtile
                                    jollyUsed=true;
                                }else{
                                    jollyUsed=false;
                                }

                                tempPoints=addTile(k,hand,dictionary,i,jtoCall,horizontal,word,dictionary->getDnode(),jollyUsed);

                                if (tempPoints>topPoints){
                                    topPoints=tempPoints;
                                    topWord=word;                                    
                                    topPosY=i;
                                    topPosX=jtoCall;
                                    dirTopWord=horizontal;
                                }
                            }
                        }
                        k++;
                    }
                }else{
                    k=0;
                    word.clear();
                    if(dictionary->getDnode()->is_present(tBoard[i][jtoCall]->getLetter())){
                            tempPoints=addTile(k,hand,dictionary,i,jtoCall,horizontal,word,dictionary->getDnode(),false);

                            if (tempPoints>topPoints){
                                topPoints=tempPoints;
                                topWord=word;                                
                                topPosY=i;
                                topPosX=jtoCall;
                                dirTopWord=horizontal;                            
                        }
                    }

                }
            }
        }
    }


    for(size_t i=0;i<hand->size();++i){
        if(hand->getTile(i)->isJolly()){
            hand->getTile(i)->setJolly_letter('J');   //imposto la lettera di ogni jolly a j, questo permette nel passaggio successivo di cambiare texture al jolly
        }
    }

    //parte grafica

    for(size_t i=0;i<topWord.size();++i){ //scorro la parola formata e scelgo dalla mano le lettere da usare per formarla sul tabellone
        letter=topWord[i];
        c=0;
        letterFound=false;

        if(dirTopWord==vertical){
            if(sBoard[1][(topPosY+i)*board_size + topPosX].getPosition().x<0 && sBoard[1][(topPosY+i)*board_size + topPosX].getPosition().y<0){
                while(c<hand->size() && !letterFound){
                    tempTile=hand->getTile(c);
                    if(tempTile!=nullptr && tempTile->getLetter()==letter){
                        tempTile=hand->extractTile(c);
                        tBoard[topPosY+i][topPosX]=tempTile;
                        newPos=sf::Vector2f(tileCentered_Pos(topPosX), tileCentered_Pos(topPosY+i)); //posizione lettera in modo da centrare la casella graficamente
                        tempTile->setPosition(newPos.x,newPos.y);
                        sBoard[1][(topPosY+i)*board_size + topPosX]= *(tempTile->getSprite());
                        sBoard[1][(topPosY+i)*board_size + topPosX].setPosition(newPos.x,newPos.y);
                        letterFound=true;
                    }
                    c++;
                }
                if(!letterFound){
                    c=0;
                    while(c<hand->size() && !letterFound){
                        tempTile=hand->getTile(c);
                        if(tempTile!=nullptr && tempTile->isJolly()){
                            tempTile=hand->extractTile(c);                            
                            tempTile->setJolly_letter(letter);

                            changeJollyTexture(tempTile,letter);

                            tBoard[topPosY+i][topPosX]=tempTile;                            
                            newPos=sf::Vector2f(tileCentered_Pos(topPosX),tileCentered_Pos(topPosY+i)); //posizione lettera in modo da centrare la casella graficamente
                            tempTile->setPosition(newPos.x,newPos.y);
                            sBoard[1][(topPosY+i)*board_size + topPosX]= *(tempTile->getSprite());
                            sBoard[1][(topPosY+i)*board_size + topPosX].setPosition(newPos.x,newPos.y);                            
                            letterFound=true;
                        }
                        c++;
                    }
                }
            }
        }else{
            if(dirTopWord==horizontal){
                if(sBoard[1][topPosY*board_size + topPosX+i].getPosition().x<0 && sBoard[1][topPosY*board_size + topPosX+i].getPosition().y<0){
                    while(c<hand->size() && !letterFound){
                        tempTile=hand->getTile(c);
                        if(tempTile!=nullptr && tempTile->getLetter()==letter){
                            tempTile=hand->extractTile(c);
                            tBoard[topPosY][topPosX+i]=tempTile;
                            newPos=sf::Vector2f(tileCentered_Pos(topPosX+i), tileCentered_Pos(topPosY)); //posizione lettera in modo da centrare la casella graficamente
                            tempTile->setPosition(newPos.x,newPos.y);
                            sBoard[1][topPosY*board_size + topPosX+i]=*(tempTile->getSprite());
                            sBoard[1][topPosY*board_size + topPosX+i].setPosition(newPos.x,newPos.y);                            
                            letterFound=true;
                        }
                        c++;
                    }
                    if(!letterFound){
                        c=0;
                        while(c<hand->size() && !letterFound){
                            tempTile=hand->getTile(c);
                            if(tempTile!=nullptr && tempTile->isJolly()){
                                tempTile=hand->extractTile(c);
                                tempTile->setJolly_letter(letter);

                                changeJollyTexture(tempTile,letter);

                                tBoard[topPosY][topPosX+i]=tempTile;
                                newPos=sf::Vector2f(tileCentered_Pos(topPosX+i), tileCentered_Pos(topPosY)); //posizione lettera in modo da centrare la casella graficamente
                                tempTile->setPosition(newPos.x,newPos.y);
                                sBoard[1][topPosY*board_size + topPosX+i]=*(tempTile->getSprite());
                                sBoard[1][topPosY*board_size + topPosX+i].setPosition(newPos.x,newPos.y);                                
                                letterFound=true;
                            }
                            c++;
                        }
                    }
                }
            }
        }
    }   

   // player->addPoints(topPoints+specialPoints(topWord,jollyUsed));
player->addPoints(topPoints);

if(topPoints>0){
    return true;
}

   //se non sono stati totalizzati punti allora cambio la mano del giocatore
        if(bag->getSize()!=0){
            player->changeHand(bag);
        }    

    return false;

}





//le parole formate da 3 lettere o meno non è necessario che siano disposte in modo da poter formare una parola di senso compiuto.......
//probabilmente ti conviene creare un nuovo help più "disperato" da usare solo nel caso in cui non siano state generate parole dall'help normale


//*****************************************************ADDTILE*******************************************************

int Board::addTile(size_t counter, TileList *hand, Dictionary *dict,
                   size_t posy, size_t posx, wordtype dir,std::string &word, Dnode *dnode, bool jollyUsed){


    bool fromHand=0;                                //per ricordare se la lettera scelta è stata pescata dalla mano del giocatore o meno

    size_t i=0;                                     //contatore per il ciclo interno
    size_t nextPosX=posx;                           //prossime posizioni che utilizzerò
    size_t nextPosY=posy;

    Tile *currentTile=nullptr;                      //puntatore al tile scelto in questa chiamata di funzione
    Tile* tempTile=nullptr;                         //puntatore al prossimo potenziale tile da utilizzare
    bool endReached=0;                              //indica se è sato raggiunto il bordo del tabellone
    std::string currentWord;                        //utilizzata per salvare la parola corrente
    std::string topWord;                            //utilizzata per salvare la parola migliore trovata

    int tempPoints=0,topPoints=0;

    char topJollyLetter='J';

    // questo controllo è da fare anche prima della chiamata ricorsiva, alrimenti sprec una delle lettere presenti sulla mano per poi sceglierne una presente sul tabellone
    if(this->tBoard[posy][posx]!=nullptr){          //se la casella presa in considerazione è occupata allora uso la lettera già presente
        currentTile=tBoard[posy][posx];             //salvo la lettera presente sul tabellone
        fromHand=0;                                 //specifico che non è stata usata alcuna lettera dalla mia mano
    }else{                                          //se la casella corrente è vuota allora uso una lettera dalla mia mano
        fromHand=1;                                 //specifico che sto giocando una lettera dalla mano
        currentTile=hand->getTile(counter);         //salvo la lettera corrente estraendo l'elemento numero "counter" dalla mia mano
        if (currentTile!=nullptr){                  //per sicurezza controllo che l'elemento non sia nullptr
            currentTile->setStatus(checking);   //imposto lo status della lettera appena presa a checking, il controllo per vedere se la lettera presa in considerazione è già stata utilizzata viene fatto prima della chiamata ricorsiva
            tBoard[posy][posx]=currentTile;     //"gioco la lettera sul tabellone" (la lettera rimane comunque nella mano)
        }else{                                      //giusto per sicurezza se la lettera presa in considerazione è nullptr
            return hintPoints(dict,dir,jollyUsed);            //controllo la parola così com'è
        }
    }
if(!currentTile->isJolly()){     //se invece è un jolly gestisco la cosa più avanti
    word.push_back(currentTile->getLetter());       //appendo alla mia stringa la lettera appena scelta (sia che sia stata presa dal tabellone che dalla mano)
}
    currentWord=word;                               //salvo la parola in un stringa che serve per tenere da parte la stringa così com'è fino a questa chiamata della funzione

    switch (dir){                                   //controllo per verificare in base alla direzione, se siamo giunti al limite del tabellone
    case vertical:                                  //se il verso di inserimento è verticale allora la prossima posizione sarà posx+1
        if(posy<board_size-1){                        //controllo di non trovarmi sul bordo esterno della tabella
            nextPosY=posy+1;                             //imposto la prossima posizione
        }else{
                                                    //se stiamo puntando al bordo della matrice allora
            endReached=true;
        }
        break;
    case horizontal:                                //stesso ragionamento del vertical ma in questo caso andremo a modificare nextPosY
        if(posx<board_size-1){
            nextPosX=posx+1;
        }else{
            endReached=true;
        }
        break;

    default:                                        //di default controllo la parola così com'è
        endReached=true;
        break;
    }


 if(currentTile->isJolly() && fromHand && currentTile->getStatus()==checking){

     jollyUsed=true;

     for(size_t k=0;k<alphabeth_size-1;++k){       //essendo un jolly uso un ciclo per testare ogni lettera possibile
         switch (k){
             case 0: currentTile->setJolly_letter('A'); break;
             case 1: currentTile->setJolly_letter('B'); break;
             case 2: currentTile->setJolly_letter('C'); break;
             case 3: currentTile->setJolly_letter('D'); break;
             case 4: currentTile->setJolly_letter('E'); break;
             case 5: currentTile->setJolly_letter('F'); break;
             case 6: currentTile->setJolly_letter('G'); break;
             case 7: currentTile->setJolly_letter('H'); break;
             case 8: currentTile->setJolly_letter('I'); break;
             case 9: currentTile->setJolly_letter('L'); break;
             case 10: currentTile->setJolly_letter('M'); break;
             case 11: currentTile->setJolly_letter('N'); break;
             case 12: currentTile->setJolly_letter('O'); break;
             case 13: currentTile->setJolly_letter('P'); break;
             case 14: currentTile->setJolly_letter('Q'); break;
             case 15: currentTile->setJolly_letter('R'); break;
             case 16: currentTile->setJolly_letter('S'); break;
             case 17: currentTile->setJolly_letter('T'); break;
             case 18: currentTile->setJolly_letter('U'); break;
             case 19: currentTile->setJolly_letter('V'); break;
             case 20: currentTile->setJolly_letter('Z'); break;
         default:
             break;
         }
         word.push_back(currentTile->getLetter());      //appendo a word la lettera appena scelta
         currentWord.push_back(currentTile->getLetter());         //modifico currentWord


         if(endReached){        //se ho raggiunto il bordo esterno del tabellone allora testo la parola formata fino a questo punto
             tempPoints = hintPoints(dict,dir,jollyUsed);            //restituisco il punteggio generato dalla parola formata fin'ora
             if (tempPoints>topPoints){
                 topPoints=tempPoints;
                 topJollyLetter=currentTile->getLetter();             //salvo la scelta migliore per il jolly
                 topWord=currentWord;
             }
         }else{

             if(dnode->next(currentTile->getLetter())!=nullptr){                 //controllo che con le lettere scelte fino ad ora sia possibile effettivamente continuare a creare una parola di senso compiuto


                 if(tBoard[nextPosY][nextPosX]==nullptr){        //se la prossima casella è vuota allora ciclo sulle lettere della mano altrimenti uso una lettera a caso che tanto non verrà presa in considerazione in quanto verrà usata la lettera presente sul tabellone
                     //in questo modo almeno evito 7 chiamate identiche inutili
                     while(i<hand->size()){                          //ciclo che permette di controllare tutte le lettere presenti in mano e                         
                                                                    //nel caso in cui sia possibile richiama la funzione ricorsiva per quella lettera

                         tempTile=hand->getTile(i);                  //salvo il puntatore alla prossima potenziale tile, cioè la tile in posizione i sulla mano
                         if(tempTile!=nullptr && tempTile->getStatus()!=checking){               //controllo che questo non sia nullo o che la tile sia già stata scelta
                             if(dnode->next(currentTile->getLetter())->is_present(tempTile->getLetter())){   //condizione controllo se la prossima lettera può effettivamente generare una parola di senso compiuto
                                 tempPoints=addTile(i, hand, dict, nextPosY, nextPosX, dir,word,dnode->next(currentTile->getLetter()),jollyUsed); //richiamo la funzione ricorsiva per la prossima lettera scelta, cioè quella in posizione i dalla mano del giocatore
                                 if (tempPoints>topPoints){     //se il punteggio appena restituito dalla funzione ricorsiva è maggiore del punteggio massimo
                                     topPoints=tempPoints;      //allora cambia il punteggio massimo
                                     topJollyLetter=currentTile->getLetter();                                     
                                     topWord=word;
                                 }
                                 word=currentWord;
                             }

                         }
                         i++;
                     }
                 }else{

                     if(dnode->next(currentTile->getLetter())->is_present(tBoard[nextPosY][nextPosX]->getLetter())){   //condizione controllo se la prossima lettera può effettivamente generare una parola di senso compiuto

                         tempPoints=addTile(0, hand, dict, nextPosY, nextPosX, dir,word,dnode->next(currentTile->getLetter()),jollyUsed); //richiamo la funzione ricorsiva per una lettera a caso (la prima) sapendo che comunque non verrà utilizzata in quanto la prossima casella è già occupata

                         if (tempPoints>topPoints){
                             topPoints=tempPoints;
                             topJollyLetter=currentTile->getLetter();                             
                             topWord=word;
                         }
                     }
                 }
                 tempPoints=hintPoints(dict,dir,jollyUsed); //dopo aver controllato tutte le lettere che posso agganciare alla fine della parola controllo la parola stessa

                 if (tempPoints>topPoints){
                     topPoints=tempPoints;
                     topJollyLetter=currentTile->getLetter();
                     topWord=currentWord;

                 }
             }
         }
         currentWord.pop_back(); //ad ogni ciclo aggiungo una delle 21 lettere e la tolgo alla fine del ciclo, più avanti aggiungerò la topJollyletter
         word=currentWord;
     }

     currentTile->setJolly_letter(topJollyLetter);
 }else{ //se non è stato giocato un jolly non si ha bisogno di ciclare tutte le lettere dell'alfabeto ma si utilizza direttamente la lettera "pescata"

     if(endReached){    //se è stata raggiunta la fine
         tempPoints = hintPoints(dict,dir,jollyUsed);            //restituisco il punteggio generato dalla parola formata fin'ora
         if (tempPoints>topPoints){
             topPoints=tempPoints;
             topWord=currentWord;             
         }
     }else{

         if(dnode->next(currentTile->getLetter())!=nullptr){                 //controllo che con le lettere scelte fino ad ora sia possibile effettivamente continuare a creare una parola di senso compiuto
             if(tBoard[nextPosY][nextPosX]==nullptr){        //se la prossima casella è vuota allora ciclo sulle lettere della mano altrimenti uso una lettera a caso che tanto non verrà presa in considerazione in quanto verrà usata la lettera presente sul tabellone
                 //in questo modo almeno evito 7 chiamate identiche inutili

                 while(i<hand->size()){                          //ciclo che permette di controllare tutte le lettere presenti in mano e
                     //nel caso in cui sia possibile richiama la funzione ricorsiva per quella lettera
                     tempTile=hand->getTile(i);                  //salvo il puntatore alla prossima potenziale tile, cioè la tile in posizione i sulla mano
                     if(tempTile!=nullptr && tempTile->getStatus()!=checking){               //controllo che questo non sia nullo o che la tile sia già stata scelta
                         if(dnode->next(currentTile->getLetter())->is_present(tempTile->getLetter())){   //condizione controllo se la prossima lettera può effettivamente generare una parola di senso compiuto
                             tempPoints=addTile(i, hand, dict, nextPosY, nextPosX, dir,word,dnode->next(currentTile->getLetter()),jollyUsed); //richiamo la funzione ricorsiva per la prossima lettera scelta, cioè quella in posizione i dalla mano del giocatore
                             if (tempPoints>topPoints){     //se il punteggio appena restituito dalla funzione ricorsiva è maggiore del punteggio massimo
                                 topPoints=tempPoints;      //allora cambia il punteggio massimo
                                 topWord=word;
                             }
                             word=currentWord;
                         }

                     }
                     i++;
                 }
             }else{ //se la prossima casella è già occupata allora utilizzo la lettera presente sul tabellone come prossima lettera
                 if(dnode->next(currentTile->getLetter())->is_present(tBoard[nextPosY][nextPosX]->getLetter())){   //condizione controllo se la prossima lettera può effettivamente generare una parola di senso compiuto

                     tempPoints=addTile(0, hand, dict, nextPosY, nextPosX, dir,word,dnode->next(currentTile->getLetter()),jollyUsed); //richiamo la funzione ricorsiva per una lettera a caso (la prima) sapendo che comunque non verrà utilizzata in quanto la prossima casella è già occupata

                     if (tempPoints>topPoints){
                         topPoints=tempPoints;
                         topWord=word;
                     }
                 }
             }

             tempPoints=hintPoints(dict,dir,jollyUsed); //dopo aver controllato tutte le lettere che posso agganciare alla fine della parola controllo la parola stessa

             if (tempPoints>topPoints){
                 topPoints=tempPoints;
                 topWord=currentWord;
             }


         }
     }


 }


 if(currentTile->isJolly() && fromHand){ //se è stato appena usato un jolly allora provvedo ad accodarlo
  word.push_back(topJollyLetter);
  currentTile->setJolly_letter(topJollyLetter);
 }
    if(fromHand){                                           //se la lettera è stata scelta dalla mano
        currentTile->setStatus(checked);                    //segno la tile corrente come già controllata e quindi non in uso
        tBoard[posy][posx]=nullptr;                         //e la elimino dal tabellone
    }

    if(topPoints>0){                        //se il punteggio è maggiore di zero allora restituisco quel punteggio... controllo abbastanza inutile visto che topPoints è inizializzato a 0
        word=topWord;
        return topPoints;
    }   


    return -1000;   //altrimenti ritorno un punteggio negativo in modo da essere sicuro di non accettare parole insensate
}


//***********************************************hintpoints*******************************************
int Board::hintPoints(Dictionary* dictionary,wordtype dir,bool jollyUsed){
    bool rows[board_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //array di bool necessario per salvare in quali righe della matrice sono state aggiunte nuove lettere
    bool columns[board_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //array di bool necessario per salvare in quali colonne della matrice sono state aggiunte nuove lettere           

    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr){
                if(tBoard[i][j]->getStatus()==checking){                  
                    rows[i]=true;
                    columns[j]=true;

                }
            }

        }
    }

    if(wordCrossed(dir)){
        //se le varie parole formate sono valide nel dizionario e le lettere sono state inserite in modo valido allora accetto le tile giocate,assegno i punti al giocatore e riempo la sua mano
        if(!isWordSeg(WordDirection()) && wordCrossed(WordDirection()) && checkString(dictionary,rowToString(rows)) && checkString(dictionary,columnToString(columns))){
            return wordPoints(jollyUsed); //aggiungo i punti ottenuti dalle parole formate, passo come parametri true e true in modo tale che non vengano aggiunti punteggi speciali. i punteggi speciali per l'aiuto verranno aggiunti dalla funzione help alla fine delle chiamate ricorsive
        }
    }
    return -1000;

}

unsigned int Board::specialPoints(int num,bool jollyUsed){
    unsigned int points=0;
    if(num==6){
        points+=10;
    }

    if(num==7){
        points+=30;
    }

    if(num==8){
        points+=50;
    }

    if(!jollyUsed && num>0){
        points+=10;
    }

    return points;
}

void Board::refreshSprites(){
    for(size_t i=0;i<board_size;++i){
        for(size_t j=0;j<board_size;++j){
            if(tBoard[i][j]!=nullptr){
                if(tBoard[i][j]->getStatus()==checking){
                    sBoard[1][j+i*board_size]=*(tBoard[i][j]->getSprite()); //salvo la sua sprite nelle sprite del tabellone di gioco
                }
            }
        }
    }

}

void Board::changeJollyTexture(Tile *tile, char letter){

sf::Texture *t=new sf::Texture();

switch (letter) {
case 'A': case 'a': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/A.png"); break;
case 'B': case 'b': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/B.png"); break;
case 'C': case 'c': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/C.png"); break;
case 'D': case 'd': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/D.png"); break;
case 'E': case 'e': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/E.png"); break;
case 'F': case 'f': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/F.png"); break;
case 'G': case 'g': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/G.png"); break;
case 'H': case 'h': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/H.png"); break;
case 'I': case 'i': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/I.png"); break;
case 'L': case 'l': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/L.png"); break;
case 'M': case 'm': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/M.png"); break;
case 'N': case 'n': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/N.png"); break;
case 'O': case 'o': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/O.png"); break;
case 'P': case 'p': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/P.png"); break;
case 'Q': case 'q': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/Q.png"); break;
case 'R': case 'r': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/R.png"); break;
case 'S': case 's': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/S.png"); break;
case 'T': case 't': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/T.png"); break;
case 'U': case 'u': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/U.png"); break;
case 'V': case 'v': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/V.png"); break;
case 'Z': case 'z': t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Shiny/Z.png"); break;
default: t->loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Jolly.png"); break;
}

delete tile->getSprite()->getTexture();
tile->getSprite()->setTexture(*t);

}


Board::~Board(){
for(size_t i=0;i<board_size;++i){
    for(size_t j=0;j<board_size;++j){
        delete tBoard[i][j];
    }
}
}
