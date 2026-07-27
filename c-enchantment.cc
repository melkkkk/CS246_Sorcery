export module enchantment;
import <vector>;
import <string>;
import plard;
import minion;

using namespace std;

export class Enchantment: public Card {
  std::string desc = "";
  std::string attack = "";
  std::string defense = "";

  protected:
    //void setState(State newS);
  public:
    Enchantment(string name, int cost);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void giantStrength(Player *played, Player *owner, int p);
    void enrage(Player *played, Player *owner, int p);
    void haste(Player *played, Player *owner, int p);
    void magicFatigue(Player *played, Player *owner, int p);
    void silence(Player *played, Player *owner, int p);

    void giantStrength(Minion *temp);
    void enrage(Minion *temp);
    void haste(Minion *temp);
    void magicFatigue(Minion *temp);
    void silence(Minion *temp);

    std::string getAttack();
    std::string getDefense();
    std::string getDesc();

};

// //CTOR
// Enchantment::Enchantment(string name, int cost): Card{name, cost} {
    
//     if (name == "Giant Strength") { this->attack = "+2"; this->defense = "+2"; }
//     if (name == "Engrage") { this->attack = "*2"; this->defense = "*2"; }
//     else if (name == "Haste") { this->desc = "Enchanted minion gains +1 action each turn"; }
//     else if (name == "Magic Fatigue") { this->desc = "Enchanted minion's activated ability costs 2 more"; }
//     else if (name == "Silence") { this->desc = "Whenever a minion enters play, destroy it"; }
// }

// //selects which spell to use
// // void Ritual::playRitual(Player *played, Player *owner, int *p) {
// //     string name = s.getName();
// //     if (name == "Giant Strength") { giantStrength(played, owner, p); }
// //     else if (name == "Enrage") { enrage(played, owner, p); }
// //     else if (name == "Haste") { haste(played, owner, p); }
// //     else if (name == "Magic Fatigue") { magicFatigue(played, owner, p); }
// //     else if (name == "Silence") { silence(played, owner, p); }
// // }

// void giantStrength(Player *played, Player *owner, int *p) {
//   cout << "giantStrength called" << endl;
//   // owner->hand[p].addA(2);
//   // owner->hand[p].addD(2);
// }
// void enrage(Player *played, Player *owner, int *p) {
//   cout << "enrage called" << endl;
//   // owner->hand[p].multA(2);
//   // owner->hand[p].multD(2);
// }
// void haste(Player *played, Player *owner, int *p) {
//   cout << "haste called" << endl;
//   //owner->hand[p].addAction();
// }
// void magicFatigue(Player *played, Player *owner, int *p) {
//   cout << "magicFatigue called" << endl;}
// void silence(Player *played, Player *owner, int *p) {
//   cout << "silence called" << endl;}


// |-------------------------------||-------------------------------||-------------------------------|
// | Giant Strength          |   1 || Enrage                  |   2 || Haste                   |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                   Enchantment ||                   Enchantment ||                   Enchantment |
// |-------------------------------||-------------------------------||-------------------------------|
// |                               ||                               || Enchanted minion gains +1     |
// |                               ||                               || action each turn              |
// |                               ||                               ||                               |
// |------                   ------||------                   ------||                               |
// | +2  |                   |  +2 || *2  |                   |  *2 ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------|
// | Magic Fatigue           |   0 || Silence                 |   1 |
// |-------------------------------||-------------------------------|
// |                   Enchantment ||                   Enchantment |
// |-------------------------------||-------------------------------|
// | Enchanted minion's activated  || Enchanted minion cannot use   |
// | ability costs 2 more          || abilities                     |
// |                               ||                               |
// |                               ||                               |
// |                               ||                               |
// |-------------------------------||-------------------------------|
