export module player;

import card;
import <string>;
import <vector>;
import <fstream>;

using namespace std;

export class Player;

export class Player{
    string name;
    vector<Card> deck;
    vector<Card> hand;
    vector<Card> graveyard;
    // vector<Card*> board;

  public:
    void set_name(string name);
    void set_deck(ifstream& infile);
    
};

