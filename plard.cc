export module plard;
import <vector>;
import <string>;
import <fstream>;
import <chrono>;   
import <random>;
import <iostream>;
import state;

using namespace std; 

export class Card;

export class Player;

export class Card {
    std::string name;
    int cost;
    //std::vector<Observer*> observers;
    //State state;
  protected:
    //void setState(State newS);
  public:
    Card(std::string name, int cost = 0);

    std::string getName();
    int getCost();
    
    virtual ~Card();
    // player that played card i from their deck
    // owner is the selected players card
    // void pointer is for card i, or ritual r
    //void playcard(Player played, int i, Player owner, void *p);

    //void attach(Observer *o);  
    //void notifyObservers();
    //virtual Info getInfo() const = 0;
    //State getState() const;
};

export class Observer {
  public:
    // Pass the Subject that called the notify method.
    virtual void notify(State &whoFrom, Player *active) = 0; 
    virtual ~Observer() = default;
};

//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }


export class Player{
    string name;
    int life;
    int magic;
    vector<string> deck;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Card>> graveyard;
    
    vector<unique_ptr<Card>> board;
    // Board B;

  public:
    Player(string name = "", int life = 20, int magic = 3);
    string getName();
    void setName(string name);
    void setDeck(ifstream& infile);
    void shuffleDeck(default_random_engine &rng);

    // new functions because everything is private ohhh soft private
    void addToHand(unique_ptr<Card> card);
    void moveToBoard(unique_ptr<Card> card, int indexH, int i = 1);
    void moveToGraveyard(unique_ptr<Card> card, int indexB);

    void removeFromHand(int indexH);

    vector<string>& getDeck();

    void addL(int i);
    void addM(int i);

    Card *getCardH(int i);
    Card *getCardB(int i);
    unique_ptr<Card>& getUniqueH(int i);
    unique_ptr<Card>& getUniqueB(int i);

    int getSizeH();
    int getSizeB();

    int getLife();
    int getMagic();
    vector<unique_ptr<Card>>& getHand();
    vector<unique_ptr<Card>>& getBoard();
    vector<unique_ptr<Card>>& getGraveyard();

    void playEffect(int i);

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

