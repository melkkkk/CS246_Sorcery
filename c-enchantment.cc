export module enchantment;
import <vector>;
import <string>;
import card;
import player;
import minion;

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
    void giantStrength(Player *played, Player *owner, int *p);
    void enrage(Player *played, Player *owner, int *p);
    void haste(Player *played, Player *owner, int *p);
    void magicFatigue(Player *played, Player *owner, int *p);
    void silence(Player *played, Player *owner, int *p);
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
    if (name == "Giant Strength") { giantStrength(played, owner, p); }
    else if (name == "Enrage") { enrage(played, owner, p); }
    else if (name == "Haste") { haste(played, owner, p); }
    else if (name == "Magic Fatigue") { magicFatigue(played, owner, p); }
    else if (name == "Silence") { silence(played, owner, p); }
}

void giantStrength(Player *played, Player *owner, int *p) {
  owner->hand[p].addA(2);
  owner->hand[p].addD(2);
}
void enrage(Player *played, Player *owner, int *p) {}
void haste(Player *played, Player *owner, int *p) {}
void magicFatigue(Player *played, Player *owner, int *p) {}
void silence(Player *played, Player *owner, int *p) {}

string name;
    int life;
    int magic;
    vector<string> deck;
    vector<Card> hand;
    vector<Card> graveyard;

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
