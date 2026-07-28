export module minion;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import <tuple>;
import state;
import plard;
import carddata;

using namespace std;

export class Minion: public Card, public Observer {
    int owner;
    string desc;

    int ogAttack;
    int ogDefense;
    int ogAbilityCost = -1;
    int ogActions = 1;
    bool ogHasAbility = false;

    int attack;
    int defense;
    int actions = 0;
    int abilityCost = -1;
    bool hasAbility = false;
    
    vector<unique_ptr<Card>> enchanted;
    vector<string> allApplied;
  public:
    Minion(string name, int owner, vector<tuple<string, int, int, string, int, int, int, int, bool>> vec);
    
    std::vector<std::unique_ptr<Card>>& getEnchantments();
    int getEnchantmentsSize();
    std::vector<std::string>& getAllApplied();
    int getSizeA();
    void addApply(string s);
    void removeA(int i);

    void clearEffects();

    void boneGolem(int extra = 0);
    void fireElemental(Player &active, int index, int extra = -1);
    void potionSeller(Player &active, int extra = 0);
    void novicePyromancer(Player *activeP, Player *targetP, int target, int extra = 0);
    void apprenticeSummoner(Player *played);
    void masterSummoner(Player *played);

    //call before applying enchantments
    void reset();

    //add Attack
    //add Defense
    void addA(int i = 1);
    void addD(int i = 1);
    void addAction(int i = 1);
    void addAbilityCost(int i = 1);
    //multiply Attack
    //multiply Defense
    void multA(int i = 1);
    void multD(int i = 1);

    int getAttack();
    int getDefense();
    int getAction();

    string getDesc();
    int getAbilityCost();
    bool getHasAbility();

    int getAttackO();
    int getDefenseO();
    int getActionO();
    int getAbilityCostO();
    bool getHasAbilityO();

    int getSizeE();
    Card *getCardE(int i);
    void removeE(int i);

    unique_ptr<Card>& getUniqueE(int i);

    void setHasAbility(bool b);
    void setAttack(int i);
    void setDefense(int i);
    void setAction(int i = 1);
    void setAbilityCost(int i);

    //extra functions for purpose of apply all only
    void raiseDeadApply();
    void auraOfPowerApply();
    void blizzardApply();

    //observer overrides
    void notify(EventType event, Player &active, int index, int extra) override;
    
};
