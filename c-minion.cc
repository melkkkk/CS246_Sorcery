export module minion;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import state;
import plard;

using namespace std;

export class Minion: public Card, public Observer {
    int owner;
    int attack;
    int defense;
    string desc;
    int actions = 1;
    int abilityCost = -1;
    
    bool hasAbility = false;

    int ogAttack;
    int ogDefense;
    int ogAbilityCost = -1;
    int ogActions = 1;
    int ogHasAbility = false;
    
    vector<unique_ptr<Card>> enchanted;
    // vector of enchantments
    //vector<Enchantment *> enchanted;

  protected:
    //void setState(State newS);
  public:
    Minion(string name, int cost, int owner);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    std::vector<std::unique_ptr<Card>>& getEnchantments();
    int getEnchantmentsSize();

    //void airElemental(Player *played, int *target);
    //void earthElemental(Player *played, int *target);
    void boneGolem(Player &active);
    void fireElemental(Player &active, int index);
    void potionSeller(Player &active);
    void novicePyromancer(Player *owner, int target);
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

    //observer overrides
    void notify(EventType event, Player &active, int index, bool bothStandstill) override;
    
    

};

// int Minion::getAttack() { return attack; }
// int Minion::getDefense() { return defense; }
// //add Attack
// //add Defense
// void Minion::addA(int i = 1) { attack += i; }
// void Minion::addD(int i = 1) { defense += i; }
// void Minion::addAction(int i = 1) { attack += i; }

// //multiply Attack
// //multiply Defense
// void Minion::multA(int i = 1) { attack *= i; }
// void Minion::multD(int i = 1) { defense *= i; }

// Minion::Minion(string name, int cost, int attack = 0, int defense = 0, string desc = "", int actions = 0) {

// }

// //void Minion::airElemental(Player *played, int *target) {}
// //void Minion::earthElemental(Player *played, int *target) {}
// void Minion::boneGolem(Player *played, int *target) {}
// void Minion::fireElemental(Player *played, int *target) {}
// void Minion::potionSeller(Player *played, int *target) {}
// void Minion::novicePyromancer(Player *played, int *target) {}
// void Minion::apprenticeSummoner(Player *played, int *target) {}
// void Minion::masterSummoner(Player *played, int *target) {}

// //if int i is negative then attacks player instead
// //deoesnt remove if one of them dies,,,
// void attack(Player *active, int indexM, Player *other = nullptr, int i = -1) {
//   if (i < 0) {
//     int damage = active->board[indexM]->getAttack() * -1;
//     other.addL(damage);
//   } else {
//     int damageTo = active->board[indexM]->getAttack() * -1;
//     int damageFrom = other->board[i]->getAttack() * -1;
//     other->board[i]->addD(damageTo);
//     active->board[i]->addD(damageFrom);
//   }
// }

// //export enum class StateType { StartOfTurn, EndOfTurn, MinionPlayed, Other };
// //export enum class CardType { Ritual, Spell, Enchantment, Minion };

// void Minion::notify(State &whoFrom, Player *active) {
//   if (whoFrom.sType == StateType::StartOfTurn) {
//     //check enchantment haste (+1 each start of turn)
//   }
//   else if (whoFrom.sType == StateType::EndOfTurn) {
//     // would add any cards of end of turn type here
//   } else if (whoFrom.sType == StateType::MinionPlayed) {
//     if (whoFrom.cType == CardType::Minion) {
      
//     }
//   }
// }



// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | Air Elemental           |   0 || Earth Elemental         |   3 || Bone Golem              |   2 || Fire Elemental          |   2 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                        Minion ||                        Minion ||                        Minion ||                        Minion |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                               ||                               || Gain +1/+1 whenever a minion  || Whenever an opponent's minion |
// |                               ||                               || leaves play.                  || enters play, deal 1 damage to |
// |                               ||                               ||                               || it.                           |
// |------                   ------||------                   ------||------                   ------||------                   ------|
// | 1   |                   |   1 || 4   |                   |   4 || 1   |                   |   3 || 2   |                   |   2 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | Potion Seller           |   2 || Novice Pyromancer       |   1 || Apprentice Summoner     |   1 || Master Summoner         |   3 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                        Minion ||                        Minion ||                        Minion ||                        Minion |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | At the end of your turn, all  || 1   | Deal 1 damage to target || 1   | Summon a 1/1 air        || 2   | Summon up to three 1/1  |
// | your minions gain +0/+1.      ||------  minion                 ||------ elemental               ||------ air elementals          |
// |                               ||                               ||                               ||                               |
// |------                   ------||------                   ------||------                   ------||------                   ------|
// | 1   |                   |   3 || 0   |                   |   1 || 1   |                   |   1 || 2   |                   |   3 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
