export module enchantment;
import <vector>;
import <string>;
import card;
import player;

using namespace std;

export class Enchantment: public Card {
    int attack;
    int defense;
    string desc;

  protected:
    //void setState(State newS);
  public:
    Ritual(string name, int cost, int attack = 0, int defense = 0, string desc = "");
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void darkRitual(Player played);
    void auraOfPower(Player played);
    void standstill(Player played);
};

//CTOR
Ritual::Ritual(string name, int cost, int attack = 0, int defense = 0, string desc = ""): Card{name, cost} {
    if (attack != 0) this->attack = attack;
    if (defense != 0) this->defense = defense;
    if (name == "Haste") { this->desc = "Enchanted minion gains +1 action each turn"; }
    else if (name == "Magic Fatigue") { this->desc = "Enchanted minion's activated ability costs 2 more"; }
    else if (name == "Silence") { this->desc = "Whenever a minion enters play, destroy it"; }
}

//selects which spell to use
void Ritual::playRitual(Player *played, Player *owner, int *p) {
    string name = s.getName();
    if (name == "Giant Strength") { darkRitual(played); }
    else if (name == "Enrage") { auraOfPower(played); }
    else if (name == "Haste") { this->desc = "Enchanted minion gains +1 action each turn"; }
    else if (name == "Magic Fatigue") { this->desc = "Enchanted minion's activated ability costs 2 more"; }
    else if (name == "Silence") { this->desc = "Whenever a minion enters play, destroy it"; }
}

void giantStrength(Player *played, Player *owner, int *p) {}
void enrage(Player *played, Player *owner, int *p) {}
void haste(Player *played, Player *owner, int *p) {}
void magicFatigue(Player *played, Player *owner, int *p) {}
void silence(Player *played, Player *owner, int *p) {}

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
