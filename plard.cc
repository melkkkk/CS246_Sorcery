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

  protected:
  
    void setName(std::string s);
    void setCost(int i);
  public:
    Card(std::string name, int cost = 0);

    std::string getName();
    int getCost();

    virtual ~Card();
    
};

export class Observer {
  public:
    // Pass the Subject that called the notify method.
    virtual void notify(EventType event, Player &active, int index, int extra) = 0; 
    virtual ~Observer() = default;
};

export class Player{
  int id;
  string name;
  int life;
  int magic;

  inline static int minionDeaths;
  
  vector<string> deck;
  vector<unique_ptr<Card>> hand;
  vector<unique_ptr<Card>> graveyard;
  vector<unique_ptr<Card>> board;


  inline static std::vector<std::string> minionCards = {"Air Elemental", "Earth Elemental", "Bone Golem", "Potion Seller", 
                                                            "Novice Pyromancer", "Apprentice Summoner", "Fire Elemental", "Master Summoner"};


  public:
    Player(int id, string name = "", int life = 20, int magic = 3);
    void setName(string name);
    void setDeck(ifstream& infile);
    void shuffleDeck(default_random_engine &rng);
    void setMagic(int i);

    void addToHand(unique_ptr<Card> card);

    void moveToFrom(vector<unique_ptr<Card>>& to, vector<unique_ptr<Card>>& from, unique_ptr<Card> card, int index, int i = 1);
    void removeFrom(vector<unique_ptr<Card>>& from, int index, int testing = -1);

    vector<string>& getDeck();

    void addL(int i);
    void addM(int i);

    Card *getCardH(int i);
    Card *getCardB(int i);
    Card *getCardG(int i);
    unique_ptr<Card>& getUniqueH(int i);
    unique_ptr<Card>& getUniqueB(int i);
    unique_ptr<Card>& getUnique(vector<unique_ptr<Card>>& vec, int i);

    int getSizeH();
    int getSizeB();
    int getSize(vector<unique_ptr<Card>>& vec);

    int getId();
    string getName();
    int getLife();
    int getMagic();
    int getMinionDeaths();
    vector<unique_ptr<Card>>& getHand();
    vector<unique_ptr<Card>>& getBoard();
    vector<unique_ptr<Card>>& getGraveyard();

    void addMagic(int i);

    void playEffect(int i);

};
