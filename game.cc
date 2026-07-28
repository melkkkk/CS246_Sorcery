export module game;

import state;
import plard;
import minion;
import ritual;
import enchantment;
import spell;
import board;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import <algorithm>;
import <memory>;


export class Game;

export class Game{
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;

    Player *active;
    Player *inactive;

    Board b;

    int pastMinionDeath = 0;

    // MAY CHANGE LOCATION LATER
    inline static std::vector<std::string> spellCards = {"Banish", "Unsummon", "Recharge", "Disenchant", "Raise Dead", "Blizzard"};
    inline static std::vector<std::string> ritualCards = {"Dark Ritual", "Aura of Power", "Standstill"};
    inline static std::vector<std::string> minionCards = {"Air Elemental", "Earth Elemental", "Bone Golem", "Potion Seller", 
                                                            "Novice Pyromancer", "Apprentice Summoner", "Fire Elemental", "Master Summoner"};
    inline static std::vector<std::string> enchantmentCards = {"Giant Strength", "Enrage", "Haste", "Magic Fatigue", "Silence"};

  public:
    Game(); 
    void attackM(int indexM, int i = -1);
    void use(int indexM, bool testing = false, Player *other = nullptr, int i = -1);
    void playCard(int indexC, bool testing = false, Player *other = nullptr, int i = -1);
    void checkBoard(int indexC, Player *other = nullptr, int i = -1);
    void changeTurn();
    int getID();
    void applyEnchantments(Minion *m);
    void applyEffects(Minion *m);
    void applyAll();

    void setDeck(int i, std::ifstream& infile);
    void shuffleDeck(int i, std::default_random_engine &rng);
    void setName(int i, std::string name);
    std::string getName(int i);
    
    std::string getName();

    Player *getActive();
    Player *getInactive();

    void drawCard();

    void printBoard();
    void printHand();
    void inspectMinion(int index);

    bool notifyBoard(EventType e, int index = 0);
    void removeDeadMinions();

    bool playerWin();

    ~Game();
};
