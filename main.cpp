#include "bag.h"
#include "board.h"
#include "player.h"
#include "dictionary.h"




bool isPosValid(Player* player,Board* board,sf::Vector2f pos){
    if(player->isPos_free(pos) && board->isPos_free(pos)){ //grazie alla regola del cortocircuito nel caso in cui la posizione sia occupata da un tassello appena giocato allora non controllo nemmeno i tasselli giocati nei turni precedenti
        return true;
    }
    return false;
}

bool jollyLetterChoosen(sf::Sprite *sLetters,Player *player,sf::Vector2i const &pos,size_t n){
    for(size_t i=0;i<alphabeth_size-1;++i){
        if(sLetters[i].getGlobalBounds().contains(pos.x,pos.y)){
            char c;
            c=pos_to_letter(i);
            Tile* temp=player->showHand()->getTile(n);
            temp->setJolly_letter(c); // imposta le nuova lettera al jolly e il rispettivo punteggio
            return true;
        }
    }
    return false;
}

void nextTurn(size_t &turn,size_t numPlayers){
    ++turn;
    if(turn>=numPlayers){
        turn=0;
    }
}



int main(){

    Board* board=new Board();
    Bag* bag=new Bag();



    size_t numPlayers;
    bool buttonPressed=0;
    bool justAI=false;
    bool loadExamples=0;

    //------------------------------intro---------------------------------------

    sf::Texture introBackground;
    sf::Texture button2P;
    sf::Texture button3P;
    sf::Texture button4P;
    sf::Texture buttonAI;
    sf::Texture loadEx;

    introBackground.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/woodBackIntro.jpg");
    button2P.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/Pulsante2GiocatoriSmall.png");
    button3P.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/Pulsante3GiocatoriSmall.png");
    button4P.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/Pulsante4GiocatoriSmall.png");
    buttonAI.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteAIVSAISmall.png");
    loadEx.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteLOADSmall.png");

    sf::Sprite sIntroBackground(introBackground);
    sf::Sprite sButton2P(button2P);
    sf::Sprite sButton3P(button3P);
    sf::Sprite sButton4P(button4P);
    sf::Sprite sButtonAI(buttonAI);
    sf::Sprite sLoadEx(loadEx);

    sButton2P.setPosition(300,5);
    sButton3P.setPosition(300,155);
    sButton4P.setPosition(300,305);
    sButtonAI.setPosition(300,455);
    sLoadEx.setPosition(600,455);


    sf::RenderWindow introWindow(sf::VideoMode(850,600),"Scarabeo",sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i pos=sf::Mouse::getPosition(introWindow);
    sf::Event e;
    while(introWindow.isOpen() && !buttonPressed){
        pos=sf::Mouse::getPosition(introWindow);        
        while(introWindow.pollEvent(e)){
            if(e.type==sf::Event::Closed)
                introWindow.close();

            if(e.type == sf::Event::MouseButtonPressed){
                if(sButton2P.getGlobalBounds().contains(pos.x,pos.y)){
                    numPlayers=2;
                    buttonPressed=true;
                }

                if(sButton3P.getGlobalBounds().contains(pos.x,pos.y)){
                    numPlayers=3;
                    buttonPressed=true;
                }

                if(sButton4P.getGlobalBounds().contains(pos.x,pos.y)){
                    numPlayers=4;
                    buttonPressed=true;
                }

                if(sButtonAI.getGlobalBounds().contains(pos.x,pos.y)){
                    numPlayers=2;
                    buttonPressed=true;
                    justAI=true;
                    std::cout<<"In modalita' AI vs AI premi all'interno della finestra di gioco\nper vedere la prossima mossa dei giocatori\n\n";
                }

                if(sLoadEx.getGlobalBounds().contains(pos.x,pos.y)){
                    numPlayers=2;
                    buttonPressed=true;
                    loadExamples=true; //in questo caso faccio che si apre un altra finestra in cui puoi scegliere quale esempio caricare...
                }

            }

        }
        introWindow.clear();               
        introWindow.draw(sIntroBackground);

        introWindow.draw(sButton2P);
        introWindow.draw(sButton3P);
        introWindow.draw(sButton4P);
        introWindow.draw(sButtonAI);
        introWindow.draw(sLoadEx);
        introWindow.display();        
    }    

    //------------------------------fine intro---------------------------------------


    if(loadExamples){
        std::string path;
        introWindow.setTitle("Caricamento Esempi");
        buttonPressed=false;

        sf::Texture file1;
        sf::Texture file2;
        sf::Texture file3;
        sf::Texture file4;

        file1.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteLOADSmall1.png");
        file2.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteLOADSmall2.png");
        file3.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteLOADSmall3.png");
        file4.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/PulsanteLOADSmall4.png");

        sButton2P.setTexture(file1);
        sButton3P.setTexture(file2);
        sButton4P.setTexture(file3);
        sButtonAI.setTexture(file4);

        while(introWindow.isOpen() && !buttonPressed){
            pos=sf::Mouse::getPosition(introWindow);
            while(introWindow.pollEvent(e)){
                if(e.type==sf::Event::Closed)
                    introWindow.close();

                if(e.type == sf::Event::MouseButtonPressed){
                    if(sButton2P.getGlobalBounds().contains(pos.x,pos.y)){
                        path="/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/SFML/ScarabeoSFML/Load1.txt";
                        buttonPressed=true;
                    }

                    if(sButton3P.getGlobalBounds().contains(pos.x,pos.y)){
                        path="/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/SFML/ScarabeoSFML/Load4.txt";
                        buttonPressed=true;
                    }

                    if(sButton4P.getGlobalBounds().contains(pos.x,pos.y)){
                        path="/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/SFML/ScarabeoSFML/Load5.txt";
                        buttonPressed=true;
                    }

                    if(sButtonAI.getGlobalBounds().contains(pos.x,pos.y)){
                        path="/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/SFML/ScarabeoSFML/Load6.txt";
                        buttonPressed=true;
                    }

                }

            }
            introWindow.clear();
            introWindow.draw(sIntroBackground);

            introWindow.draw(sButton2P);
            introWindow.draw(sButton3P);
            introWindow.draw(sButton4P);
            introWindow.draw(sButtonAI);            
            introWindow.display();
        }

     board->loadFromFile(bag,path);

    }

    introWindow.close();

    //definizioni e inizializzazioni

    std::vector <Player *> player;
    std::string name;
    //Player* player[4] = {new Player("Dave"),new Player("Evi"),new Player("Lollo"),new Player("lui")};


    for(size_t i=0;i<numPlayers;++i){        
        if(!justAI && !loadExamples){
            std::cout<<"inserire il nome del giocatore numero "<<i+1<<" :";
            std::cin>>name;
        }else{
            name="Player "+std::to_string(i+1);
        }
        Player *temp= new Player(name);
        name.clear();
        player.push_back(temp);
        temp->refill_hand(bag);
    }        

    Dictionary* dictionary = new Dictionary();


    sf::RenderWindow window(sf::VideoMode(boardPixelSize+image_size*6,boardPixelSize+image_size*4),"Scarabeo",sf::Style::Titlebar | sf::Style::Close);

    //-----------------------------------------testi-----------------------------------
    sf::Font font;
    font.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/fonts/comics book/ComickBook_Simple.ttf");

    sf::Text playersName(player[0]->getName(),font);
    playersName.setPosition(boardPixelSize+image_size*2,5);    
    playersName.setCharacterSize(20);

    sf::Text playersPoints("Punti : "+ std::to_string(player[0]->getPoints()),font);
    playersPoints.setPosition(boardPixelSize+image_size*4/3,40);    
    playersPoints.setCharacterSize(20);

    sf::Text tilesLeft("Lettere rimaste : " + std::to_string(bag->getSize()),font);
    tilesLeft.setPosition(boardPixelSize+image_size,310);
    tilesLeft.setCharacterSize(12);

    std::vector <sf::Text *> testiPunti;

    for(size_t i=0;i<numPlayers;++i){
        sf::Text *tempText=new sf::Text(player[i]->getName() +" : 0 punti",font);
        tempText->setPosition(boardPixelSize+image_size,350+i*20);
        tempText->setCharacterSize(12);
        testiPunti.push_back(tempText);
    }

    //---------------------------------------------------------------------------------

    bool jollyPlayed=false;

//-------------------------------------------------textures------------------------------------------------------------------
    sf::Texture tLetters[alphabeth_size-1];
    tLetters[0].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/A.png");
    tLetters[1].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/B.png");
    tLetters[2].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/C.png");
    tLetters[3].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/D.png");
    tLetters[4].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/E.png");
    tLetters[5].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/F.png");
    tLetters[6].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/G.png");
    tLetters[7].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/H.png");
    tLetters[8].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/I.png");
    tLetters[9].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/L.png");
    tLetters[10].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/M.png");
    tLetters[11].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/N.png");
    tLetters[12].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/O.png");
    tLetters[13].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/P.png");
    tLetters[14].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Q.png");
    tLetters[15].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/R.png");
    tLetters[16].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/S.png");
    tLetters[17].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/T.png");
    tLetters[18].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/U.png");
    tLetters[19].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/V.png");
    tLetters[20].loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tiles/Z.png");

    sf::Texture backgrnd;
    backgrnd.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/wooback1.jpg");
    sf::Texture carpet;
    carpet.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/tm176_23nu_s.jpg");

    //*************************************PULSANTI*********************************
    sf::Texture confirm;
    confirm.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/ConfermaParolaSMALL.png");
    sf::Texture panicButton;
    panicButton.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/CancellaParolaSMALL.png");
    sf::Texture helpButton;
    helpButton.loadFromFile("/home/davedema/Documents/Poli/Ingegneria Informatica/Fondamenti di informatica/Elaborato Definitivo/New Folder/Scarabeo/Image/aiutoSMALL.png");
    //------------------------------------------------------------------------------------------------------------------------------



    //----------------------------------------SPRITES-----------------------------------------------------
    sf::Sprite* sBackground=board->getSprites();
    sf::Sprite* sPlayerHand[handMaxSize];
    sf::Sprite sBackgrnd(backgrnd);
    sf::Sprite sCarpet(carpet);
    sCarpet.setPosition(image_size*3,boardPixelSize+image_size/3);
    sCarpet.setScale(0.3,0.1);
    sf::Sprite sConfirm(confirm);
    sConfirm.setPosition(boardPixelSize+image_size*4/3,70+80+5);
    sf::Sprite sPanicButton(panicButton);
    sPanicButton.setPosition(boardPixelSize+image_size*4/3,80);
    sf::Sprite sHelpButton(helpButton);
    sHelpButton.setPosition(boardPixelSize+image_size*4/3,70*2 +80+5*2);
    sf::Sprite sLetters[alphabeth_size-1];
    //---------------------------------------------------------------------------------



    //-----------------------------------vettori2-------------------------------------
    sf::Vector2f startingPos[handMaxSize];
    sf::Vector2f lastPos;
    sf::Vector2f newPos;
    //--------------------------------------------------------------------------------

    for(size_t i=0;i<player[0]->showHand()->size();++i){//assegno le sprites delle lettere dei giocatori e le loro rispettive posizioni di partenza
        sPlayerHand[i]=player[0]->getSprites(i);
        startingPos[i]=sPlayerHand[i]->getPosition();
    }

    size_t n=0;
    size_t turn=0;
    float dx,dy;
    bool Move=false;
    bool GameOver=0;
    int hintFailed=0;
    int playersTested=0;


  //FINE DICHIARAZIONI DI VARIABILI, INIZIO CODICE EFFETTIVO

    //ciclo finchè la finestra nn viene chiusa
    while(window.isOpen() && !GameOver){


        if(hintFailed==3){ //se sono già stati falliti 3 tentativi cambio giocatore
            nextTurn(turn,numPlayers);
            playersName.setString(player[turn]->getName());
            for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                sPlayerHand[i]=player[turn]->getSprites(i);
            }
            playersPoints.setString("Punti : " + std::to_string(player[turn]->getPoints()));
            playersTested++;
            hintFailed=0;
            if(playersTested==numPlayers){ //se sono stati testati tutti i giocatori e nessuno è stato in grado di formare una parola, allora la partita si conclude in stallo
                GameOver=true;
            }else{
                std::cout<<"A causa dell'impossibilità nel formare nuove parole il turno è passato al giocatore successivo"<<std::endl;
            }
        }

        pos=sf::Mouse::getPosition(window);

        while(window.pollEvent(e)){ //cercare cos'è pollEvent

            if(e.type==sf::Event::Closed)
                window.close();

            //*********************Drag && Drop**********************************
            if(e.type == sf::Event::MouseButtonPressed){

                if(jollyPlayed && !justAI){//nel caso in cui sia stato giocato il jolly allora scorri le sprites relative alla scelta della lettera jolly e controlla se ho premuto su quelle

                    if(jollyLetterChoosen(sLetters,player[turn],pos,n)){ //funzione che dice se è stata scelta la lettera del jolly
                        jollyPlayed=false;
                    }
                //nel momento della scelta della lettera del jolly non voglio sia possibile spostare altre lettere
                }else{ //controlla se il mouse è stato premuto sopra ad una lettera della mano del giocatore
                    if(!justAI){
                    for(size_t i=0;i<player[turn]->showHand()->size();++i){//scorro la mano
                        if(sPlayerHand[i]->getGlobalBounds().contains(pos.x,pos.y)){//controllo che la posizione del puntatore del mouse sia interna alla lettera presa in considerazione
                            n=i;//salvo la posizione della lettera utilizzata
                            Move=true; //avendo premuto su una lettera allora è possibile spostarla, move=true
                            lastPos=sf::Vector2f(sPlayerHand[n]->getPosition().x,sPlayerHand[n]->getPosition().y); //salvo la posizione della lettera in modo da poterla tuilizzare nel caso in cui la lettera venga posizionata in una posizione non valida
                            dx= pos.x - sPlayerHand[n]->getPosition().x;//offset dal puntatore del mouse alla posizione della lettera assex
                            dy= pos.y - sPlayerHand[n]->getPosition().y;//offset dal puntatore del mouse alla posizione della lettera assey
                        }
                    }
                    }


                    //pulsante help
                    if(sHelpButton.getGlobalBounds().contains(pos.x,pos.y) || justAI){
                        int pointsPreHelp=player[turn]->getPoints();

                        if(board->help(player[turn],dictionary,bag)==false){
                            std::cout<<"Non è stato possibile formare alcuna parola, le lettere della mano sono state sostituite"<<std::endl;
                            hintFailed++;
                        }else{
                            hintFailed=0;
                            playersTested=0;
                        }

                        player[turn]->refill_hand(bag);

                        for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                            sPlayerHand[i]=player[turn]->getSprites(i);
                            sPlayerHand[i]->setPosition(startingPos[i]);
                        }

                        if(player[turn]->getPoints()!=pointsPreHelp){
                            nextTurn(turn,numPlayers);
                            playersName.setString(player[turn]->getName());
                            for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                                sPlayerHand[i]=player[turn]->getSprites(i);
                            }
                        }

                        playersPoints.setString("Punti : " + std::to_string(player[turn]->getPoints()));
                        tilesLeft.setString("Lettere rimaste : " + std::to_string(bag->getSize()));                        
                        for(size_t i=0;i<numPlayers;++i){
                            testiPunti[i]->setString(player[i]->getName()+ " :" + std::to_string(player[i]->getPoints()) +" punti");
                        }

                    }


                    //pulsante per riprendere in mano le lettere (cancella parola)
                    if(sPanicButton.getGlobalBounds().contains(pos.x,pos.y) && !justAI){
                        for(size_t i=0;i<player[turn]->showHand()->size();++i){
                            sPlayerHand[i]->setPosition(startingPos[i]);
                        }
                    }
                    //-------------------------------------------------------------



                    //pulsante conferma inserimento------------------------------------------------------------------------
                    if(sConfirm.getGlobalBounds().contains(pos.x,pos.y) && !justAI){
                        bool board_isgood=board->updateBoards(dictionary,bag,player[turn]);

                        for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                            sPlayerHand[i]=player[turn]->getSprites(i);
                            sPlayerHand[i]->setPosition(startingPos[i]);
                        }
                        if(board_isgood){ //se la parola inserita è corretta allora cambio turno e quindi reimposto gli elementi della finestra
                            nextTurn(turn,numPlayers);

                            hintFailed=0; //la board è cambiata, perciò adesso potrebbero essere disponibili altre parole
                            playersTested=0;

                            //cambio il testo delle varie label
                            playersName.setString(player[turn]->getName());
                            playersPoints.setString("Punti : " + std::to_string(player[turn]->getPoints()));
                            tilesLeft.setString("Lettere rimaste : " + std::to_string(bag->getSize()));
                            for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                                sPlayerHand[i]=player[turn]->getSprites(i);
                            }

                            for(size_t i=0;i<numPlayers;++i){
                                testiPunti[i]->setString(player[i]->getName()+ " :" + std::to_string(player[i]->getPoints()) +" punti");
                            }
                        }
                    }
                    //---------------------------------------------------------------------------------------------------



                }

            }
            if (Move && !justAI){ //se il mouse si sta muovendo( dopo aver scelto un tile) allora sposto il tile selezionato
                if((window.getSize().x> (int) pos.x) && (window.getSize().y> (int) pos.y) && ((int) pos.x-dx>0) && ( (int) pos.y-dy>0))  //condizione per evitare di uscire dalla finestra
                    sPlayerHand[n]->setPosition(pos.x - dx,pos.y - dy); //campio posizione del tile
            }
            //*********************************Rilascio Mouse***************************************************
            if(e.type == sf::Event::MouseButtonReleased && !justAI){
                if(Move){
                    if(pos.x<boardPixelSize && pos.y<boardPixelSize){
                        //la nuova posizione,è centrata rispetto alle caselle del tabellone
                        newPos=sf::Vector2f(image_size*int(pos.x/image_size) + float(image_size-tiles_size)/2,image_size*int(pos.y/image_size) + float(image_size-tiles_size)/2); //nuova posizione per la lettera, sistemata in modo tale da centrare la casella graficamente
                        //******************controllo che la posizione sia valida*****************
                        if(isPosValid(player[turn],board,newPos)){


                            //********************************SCELTA LETTERA DEL JOLLY************************************************
                            if(player[turn]->showHand()->getTile(n)->isJolly()){
                                jollyPlayed=true;
                                for(size_t i=0;i<alphabeth_size-1;++i){
                                    sLetters[i].setTexture(tLetters[i]);
                                    if(i<7){
                                        sLetters[i].setPosition(boardPixelSize + i*tiles_size,boardPixelSize+4);
                                    }else{
                                        if(i<14){
                                            sLetters[i].setPosition(boardPixelSize + (i-7)*tiles_size,tiles_size+boardPixelSize+4);
                                        }else{
                                            sLetters[i].setPosition(boardPixelSize + (i-7*2)*tiles_size,tiles_size*2+boardPixelSize+4);
                                        }
                                    }

                                    }

                                }

                            sPlayerHand[n]->setPosition(newPos);
                        }else{                            
                            if(board->onJolly(newPos,player[turn]->showHand()->getTile(n))){ // controllo se la tile è stata lasciata sopra ad un jolly già presente sul tabellone
                                Tile* tempTile=player[turn]->showHand()->extractTile(n);    //in questo caso controllo che la lettera scelta per il jolly sia uguale alla lettera appena giocata
                                tempTile->getSprite()->setPosition(newPos);                               
                                player[turn]->showHand()->push_back(board->pickJolly(newPos,tempTile));

                                for(size_t i=0;i<player[turn]->showHand()->size();++i){ //riassegno sPlayerHand in base alla nuova mano
                                    sPlayerHand[i]=player[turn]->getSprites(i);
                                    sPlayerHand[i]->setPosition(startingPos[i]);
                                }
                            }else{
                                sPlayerHand[n]->setPosition(lastPos);
                            }
                        }
                    }else{
                        sPlayerHand[n]->setPosition(startingPos[n]);
                    }
                    Move=false;
                }
            }            
        }

        if(bag->getSize()==0){
            for(size_t i=0;i<numPlayers;++i){
                if(player[i]->showHand()->size()==0)
                    GameOver=true;
            }
        }        







            //////////// draw ///////////
            window.clear();
            window.draw(sBackgrnd);
            window.draw(sCarpet);

            for(size_t i=0;i<board_size*board_size*2;++i)
                window.draw(sBackground[i]);

            if(jollyPlayed){
                for(size_t i=0;i<alphabeth_size-1;++i){
                    window.draw(sLetters[i]);
                }
            }


            window.draw(playersName);
            window.draw(playersPoints);
            window.draw(tilesLeft);

            for(size_t i=0;i<numPlayers;++i){
                window.draw(*(testiPunti[i]));
            }

            window.draw(sConfirm);
            window.draw(sHelpButton);
            window.draw(sPanicButton);
            for(size_t i=0;i<player[turn]->showHand()->size();++i)
                window.draw(*sPlayerHand[i]);
            window.display();

        }

    window.close();


    std::string winner;
    unsigned int topPoints=0;

if(playersTested==numPlayers){
 std::cout<<"Stallo, nessuna nuova parola puù essere formata"<<std::endl;
}else{
    if(turn==0){    //per selezionare il giocatore che ha giocato l'ultima parola e potergli aggiungere i punteggi dei tile degli altri giocatori
        turn=numPlayers-1;
    }else{
        turn-=1;
    }

    for(size_t i=0;i<numPlayers;++i){
        player[turn]->addPoints(player[i]->handPoints());
    }
}
    for(size_t i=0;i<numPlayers;++i){
        if(player[i]->getPoints()>topPoints){
            winner=player[i]->getName();
            topPoints=player[i]->getPoints();
        }
    }

    if(topPoints>0){
        std::cout<<"complimenti "+winner+" hai vinto la partita!"<<std::endl;
        std::cout<<"il tuo punteggio e' di "<<topPoints<<" punti"<<std::endl;
    }
        return 0;
    }








