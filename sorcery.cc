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

    //make main game object
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


    // deck specification
    if (!deck1) {
        ifstream infile{"default.deck"};
        g.setDeck(1, infile);
    } 
    if (!deck2) {
        ifstream infile{"default.deck"};
        g.setDeck(2, infile);
    } 

    // add more initialization stuff here
    // shuffle decks
    if (!testing) {
        g.shuffleDeck(1, rng);
        g.shuffleDeck(2, rng);
    }

    
    // get names of players
    string name;
    cout << "Input Player 1:" << endl;
    if (!init) {getline(cin, name);}
    else {getline(ifs, name);}
    g.setName(1, name);
    
    cout << "Input Player 2:" << endl;
    if (!init) {getline(cin, name);}
    else {getline(ifs, name);}
    g.setName(2, name);

    // initialize hands of 5 cards
    int startCards = 5;
    for (int i = 0; i < startCards; ++i){
        g.drawCard();
        g.changeTurn();
        g.drawCard();
        g.changeTurn();
    }

    // main game loop
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
            cout << "   testing -- switches testing mode on or off" << endl;
            cout << "   who -- indicates who's turn it is" << endl;
        } else if (first == "end") {
            g.applyAll(); // applies all changes of current turn to active player before notify
            g.notifyBoard(EventType::EndOfTurn);
            g.changeTurn();
            g.applyAll();  // applies all changes of just past turn before notify
            g.notifyBoard(EventType::StartOfTurn);
            g.getActive()->addM(1);
            if (g.getActive()->getSizeH() < 5) g.drawCard();            
        } else if (first == "quit"){
            break;
        } else if (first == "who"){
            cout << "It is player " << g.getID() << "'s turn" << endl;
        } else if (first == "testing"){
            if (testing){
                cout << "Testing mode OFF" << endl;
            } else {
                cout << "Testing mode ON" << endl;
            }
            testing = !testing;
        } else if (first == "draw"){
            if (testing){
                if (g.getActive()->getSizeH() < 5) g.drawCard();
                cout << "Card drawn!" << endl;
            } else {
                cout << "Draw command only available in testing mode" << endl;
            }
        } else if (first == "discard") {
            if (inputs >= 1) {
                ss >> i;
                if (testing){
                    try {
                        int m = stoi(i);
                        if (g.getActive()->getSizeH() > m - 1 && m - 1 >= 0) g.getActive()->removeFrom(g.getActive()->getHand(), m - 1);
                    } catch (...) {
                        cout << "Error with arguments" << endl;
                    }
                } else {
                    cout << "Discard command only available in testing mode" << endl;
                }
            } else cout << "Incorrect number of arguments" << endl;
        } else if (first == "attack") {
            if (inputs >= 2) {
                ss >> i >> j;
                try {
                    int m = stoi(i);
                    int n = stoi(j);
                    g.attackM(m, n);
                    g.removeDeadMinions();
                    g.notifyBoard(EventType::MinionDied);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else if (inputs >= 1) {
                ss >> i;
                try {
                    int m = stoi(i);
                    g.attackM(m);
                    if (g.playerWin()) {break;}
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else cout << "NOT CORRECT NUMBER OF ARGS" << endl;
        } else if (first == "play") {
            if (inputs >= 3) {
                ss >> i >> j >> k;   
                try {
                    int m = stoi(i);
                    int n = stoi(j);
                    int o;
                    if (k == "r") {
                        o = 0;
                    } else {o = stoi(k);}           
                    if (testing) {
                        if (n == g.getID()) { g.playCard(m - 1, true, g.getActive(), o); }
                        else { g.playCard(m - 1, true, g.getInactive(), o); }
                    } else {
                        if (n == g.getID()) { g.playCard(m - 1, false, g.getActive(), o); }
                        else { g.playCard(m - 1, false, g.getInactive(), o); }
                    }
                    g.removeDeadMinions();
                    g.notifyBoard(EventType::MinionDied);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else if (inputs >= 1) {
                ss >> i;
                try {
                    int m = stoi(i);
                    bool playCard = g.notifyBoard(EventType::MinionPlayed, m - 1);
                    if (playCard){
                        if (testing){ g.playCard(m - 1, true);} 
                        else { g.playCard(m - 1, false);}
                    }
                    g.removeDeadMinions();
                    g.notifyBoard(EventType::MinionDied);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else cout << "Incorrect number of arguments" << endl;
        } else if (first == "use") {
            if (inputs >= 3) {
                ss >> i >> j >> k;
                try {
                    int m = stoi(i);
                    int n = stoi(j);
                    int o = stoi(k);   
                    if (testing) {
                        if (n == g.getID()) { g.use(m, true, g.getActive(), o); }
                        else { g.use(m, true, g.getInactive(), o); }
                    } else {
                        if (n == g.getID()) { g.use(m, false, g.getActive(), o); }
                        else { g.use(m, false, g.getInactive(), o); }
                    }
                    g.removeDeadMinions();
                    g.notifyBoard(EventType::MinionDied);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else if (inputs >= 1) {
                ss >> i;
                try {
                    int m = stoi(i);
                    if (testing) g.use(m, true); 
                    else g.use(m , false);
                    g.removeDeadMinions();
                    g.notifyBoard(EventType::MinionDied);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else cout << "Incorrect number of arguments" << endl;
        } else if (first == "inspect") {
            if (inputs >= 1) {
                ss >> i;
                try {
                    int m = stoi(i);
                    g.inspectMinion(m);
                } catch (...) {
                    cout << "Error with arguments" << endl;
                }
            } else cout << "Incorrect number of arguments" << endl;
        } else if (first == "hand") {
            g.printHand();
        } else if (first == "board") {
            g.printBoard();
        } else {
            cout << command << " is unrecognized. Please try again" << endl;
        }
    }
    return 0;
}

