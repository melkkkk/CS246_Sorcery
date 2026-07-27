import state;
import plard;
import minion;
import enchantment;
import ritual;
import game;
import board;

import <iostream>;
import <fstream>;
import <sstream>;
import <chrono>;   
import <random>;
import <string>;

using namespace std;

// counts the number of inputs in a string like "attack 1 2" -> 2 inputs
int count_inputs(string s){
    int counter = 0;
    stringstream ss{s};
    string p;
    while (ss >> p){
        ++counter;
    }
    return counter - 1;
}

int main(int argc, char *argv []){
    // setting up random seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};

    // creating player objects
    // Player p1;
    // Player p2;
    // Player *actPlayer = &p1; // going to be using these pointers for most the time i think
    // Player *nonPlayer = &p2;

    //make game object to call playcard
    // Game g = Game(actPlayer, nonPlayer);
    Game g = Game();
    
    // for testing mode
    bool testing = false;

    // for init file
    bool init = false;
    ifstream ifs{"default.init"}; //this is empty

    // set deck
    bool deck1 = false;
    bool deck2 = false;

    // parsing through command line arguments
    for (int i = 1; i < argc; ++i){
        string command(argv[i]);
        // cout << command << endl; // default.deck if no specified
        if (command == "-deck1") {
            ++i;
            ifstream infile{argv[i]};
            // p1.setDeck(infile);
            g.setDeck(1, infile);
            deck1 = true;
            // create deck for p1 from file
        } else if (command == "-deck2") {
            ++i;
            ifstream infile{argv[i]};
            // p2.setDeck(infile);
            g.setDeck(2, infile);
            deck2 = true;
            // create deck for p2 file
        } else if (command == "-init") {
            ++i;
            ifs.close();
            ifs.open(argv[i]);
            init = true;
            // read in commands from  file
        } else if (command == "-testing") {
            testing = true;
        } else if (command == "-graphics") {
            // activate graphics idk
        } else {
            cerr << "'" << command << "' is an invalid command" << endl;
            return 2;
        }
    }


    // temp fix for deck specification, can change later 
    if (!deck1) {
        ifstream infile{"default.deck"};
        // p1.setDeck(infile);
        g.setDeck(1, infile);
    } 
    if (!deck2) {
        ifstream infile{"default.deck"};
        // p2.setDeck(infile);
        g.setDeck(2, infile);
    } 

    // add more initialization stuff here
    // shuffle decks
    if (!testing) {
        // p1.shuffleDeck(rng);
        // p2.shuffleDeck(rng);
        g.shuffleDeck(1, rng);
        g.shuffleDeck(2, rng);
    }

    
    
    // get names of players
    string name;
    cout << "Input Player 1:" << endl;
    if (!init) {getline(cin, name);}
    else {getline(ifs, name);}
    // p1.setName(name);
    g.setName(1, name);

    // cout << "player name is " << p1.getName() << endl;
    cout << "player name is " << g.getName(1) << endl;
    
    cout << "Input Player 2:" << endl;
    if (!init) {getline(cin, name);}
    else {getline(ifs, name);}
    // p2.setName(name);
    g.setName(2, name);

    // cout << "player name is " << p2.getName() << endl;
    cout << "player name is " << g.getName(2) << endl;


// initialize hands of 5 cards
    int startCards = 5;
    for (int i = 0; i < startCards; ++i){
        // g.drawCard(actPlayer);
        // g.drawCard(nonPlayer);
        g.drawCard();
        g.changeTurn();
        g.drawCard();
        g.changeTurn();
    }


    // main game loop
    // bool quit = false;
    string command;

    while ((!init && getline(cin, command) && command != "\n") || (getline(ifs, command) && command != "\n")){
        stringstream ss{command};
        int inputs = count_inputs(command);
        string first, i, j, k;
        ss >> first;
        if (first == "help"){
            cout << "Commands:" << endl;
            cout << "   end -- End the current player's turn." << endl;
            cout << "   quit -- End the game." << endl;
            cout << "   attack minion other-minion -- Orders minion to attack other-minion." << endl;
            cout << "   attack minion -- Orders minion to attack the opponent." << endl;
            cout << "   play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
            cout << "   use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player. << end" << endl;
            cout << "   inspect minion -- View a minion's card and all enchantments on that minion." << endl;
            cout << "   hand -- Describe all cards in your hand." << endl;
            cout << "   board -- Describe all cards on the board." << endl;
        } else if (first == "end") {
            // if (actPlayer == &p1){
            //     cout << "PLAYER 1 TURN END" << endl;
            //     cout << "PLAYER 2 TURN START" << endl;
            // } else {
            //     cout << "PLAYER 2 TURN END" << endl;
            //     cout << "PLAYER 1 TURN START" << endl;
            // }

            //notify end of turn state

            cout << "CHANGE TURN< WE CAN ADD A GETT AND SETTER IF NEED TO PRINT LATER" << endl;
            // swap(actPlayer, nonPlayer);
            g.changeTurn();

            g.getActive()->addM(1);
            if (g.getActive()->getSizeH() < 5) g.drawCard();
            g.applyAll();

            //notify start of turn state
            
        } else if (first == "quit"){
            cout << "END GAME" << endl;
            break;
        } else if (first == "draw"){
            if (testing){

                //card drawn
                g.drawCard();

                cout << "PLAYER DRAwS CARD! ONLY AVALIABLE IN TEST MODE" << endl;
            } else {
                cout << "DRAW COMMAND ONLY AVAILABLE IN TESTING MODE" << endl;
            }
        } else if (first == "discard") {
            if (inputs >= 1) {
                ss >> i;
                if (testing){

                    g.getActive()->removeFrom(g.getActive()->getHand(), stoi(i));

                    cout << "PLAYER DISCARDS " << i << " CARD IN HAND! ONLY AVALIABLE IN TEST MODE" << endl;
                } else {
                    cout << "DISCARD COMMAND ONLY AVAILABLE IN TESTING MODE" << endl;
                }
            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "attack") {
            if (inputs >= 2) {
                ss >> i >> j;
                cout << "MINION " << i << " ATTACKS OPPOSING MINION " << j << endl;
                //

                g.attackM(stoi(i), stoi(j));

            } else if (inputs >= 1) {
                ss >> i;
                cout << "MINION " << i << " ATTACKS PLAYER" << endl;
                //

                g.attackM(stoi(i));

            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "play") {
            if (inputs >= 3) {
                ss >> i >> j >> k;
                cout << "PLAY " << i << " CARD ON PLAYER " << j << " ON THEIR " << k << " MINION" << endl;
                
                if (testing) {
                    if (stoi(j) == g.getID()) { g.playCard(stoi(i), true, g.getActive(), stoi(k)); }
                    else { g.playCard(stoi(i), true, g.getInactive(), stoi(k)); }
                } else {
                    cout << stoi(j) << " " << g.getID() << endl;
                    if (stoi(j) == g.getID()) { g.playCard(stoi(i), false, g.getActive(), stoi(k)); }
                    else { g.playCard(stoi(i), false, g.getInactive(), stoi(k)); }
                }

            } else if (inputs >= 1) {
                ss >> i;
                cout << "PLAY " << i << " CARD NO TARGET" << endl;

                if (testing) g.playCard(stoi(i), true); 
                else g.playCard(stoi(i), false);


            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "use") {
            if (inputs >= 3) {
                ss >> i >> j >> k;
                cout << "USE " << i << " ACTIVATED ABILITY ON PLAYER " << j << " ON THEIR " << k << " MINION" << endl;

                if (testing) {
                    if (stoi(j) == g.getID()) { g.use(stoi(i), true, g.getActive(), stoi(k)); }
                    else { g.use(stoi(i), true, g.getInactive(), stoi(k)); }
                } else {
                    if (stoi(j) == g.getID()) { g.use(stoi(i), false, g.getActive(), stoi(k)); }
                    else { g.use(stoi(i), false, g.getInactive(), stoi(k)); }
                }

            } else if (inputs >= 1) {
                ss >> i;
                cout << "PLAY " << i << " ACTIVATED ABILITY NO TARGET" << endl;
                
                if (testing) g.use(stoi(i), true); 
                else g.use(stoi(i), false);

            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "inspect") {
            if (inputs >= 1) {
                ss >> i;
                cout << "DESCRIBE " << i << " MINION" << endl;
            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "hand") {
            cout << "SHOWS PLAYER'S HAND" << endl;
            g.printHand();
        } else if (first == "board") {
            cout << "SHOWS BOARD" << endl;
            g.printBoard();
        } else {
            cout << command << " IS UNRECOGNIZED. PLEASE TRY AGAIN :>" << endl;
        }
    }

    return 0;
}

