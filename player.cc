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
    // vector<Card> board;
    // Board B;

  public:
    void setName(string name);
    void setDeck(ifstream& infile);
    string getName();
    
};

// export class Board{
//   vector<Card> board;
//  public:
//   print(p1, p2);
//   printMiddle();
//   notifyWhenTriggered(p1, p2);
// }

// export class Board{
//   player p1, p2;
//  public:
//   print();
//   notifyWhenTriggered();
// }

// export class Player{
//     string name;
//     vector<Card> deck;
//     vector<Card> hand;
//     vector<Card> graveyard;
//     vector<Card> board;
//     // Board B;

//   public:
//     void setName(string name);
//     void setDeck(ifstream& infile);
//     string getName();
    
// };

