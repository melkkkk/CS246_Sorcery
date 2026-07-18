import card;
import player;

import <iostream>;
import <fstream>;

using namespace std;

int main(int argc, char *argv []){
    // for testing mode
    // bool testing = false;

    // creating player objects
    Player p1;
    Player p2;
    
    // parsing through command line arguments
    for (int i = 1; i < argc; ++i){
        string command(argv[i]);
        // cout << command << endl;
        if (command == "-deck1") {
            ++i;
            ifstream infile{argv[i]};
            p1.setDeck(infile);
            // create deck for p1 from file
        } else if (command == "-deck2") {
            ++i;
            ifstream infile{argv[i]};
            p2.setDeck(infile);
            // create deck for p2 file
        } else if (command == "-init") {
            ++i;
            ifstream infile{argv[i]};
            // read in commands from  file
        } else if (command == "-testing") {
            // testing = true;
        } else if (command == "-graphics") {
            // activate graphics idk
        } else {
            cerr << "'" << command << "' is an invalid command" << endl;
        }
    }

    // add more initialization stuff here
    
    // get names of players, change if -init is being used
    string name;
    cout << "Input Player 1:" << endl;
    getline(cin, name);
    p1.setName(name);
    cout << "player name is " << p1.getName() << endl;
    cout << "Input Player 2:" << endl;
    getline(cin, name);
    p2.setName(name);
    cout << "player name is " << p2.getName() << endl;

    // main game loop
    string command;
    while (getline(cin, command)){
        cout << command << endl;
    }

    // string 
}
