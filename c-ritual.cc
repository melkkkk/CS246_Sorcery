export module ritual;
import <vector>;
import <string>;
import card;
import player;

using namespace std;

export class Ritual: public Card {
    int charge;
    int activiation;
    string desc;

  protected:
    //void setState(State newS);
  public:
    Ritual(string name, int cost, int charge, int activation);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void darkRitual(Player played);
    void auraOfPower(Player played);
    void standstill(Player played);
};

//CTOR
Ritual::Ritual(string name, int cost, int charge, int activation): Card{name, cost} {
    if (name == "Dark Ritual") { this->desc = "At the start of your turn, gain 1 magic"; }
    else if (name == "Aura of Power") { this->desc = "Whenever a minion enters play under your control it gains +1/+1"; }
    else if (name == "Standstill") { this->desc = "Whenever a minion enters play, destroy it"; }
}

//selects which spell to use
void Ritual::playRitual(Player *played, Player *owner, int *p) {
    string name = s.getName();
    if (name == "Dark Ritual") { darkRitual(played); }
    else if (name == "Aura of Power") { auraOfPower(played); }
    else if (name == "Standstill") { standstill(played); }
}

void darkRitual(Player played) {}
void auraOfPower(Player played) {}
void standstill(Player played) {}

// |-------------------------------||-------------------------------||-------------------------------|
// | Dark Ritual             |   0 || Aura of Power           |   1 || Standstill              |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                        Ritual ||                        Ritual ||                        Ritual |
// |-------------------------------||-------------------------------||-------------------------------|
// | 1   | At the start of your    || 1   | Whenever a minion enters|| 2   | Whenever a minion       |
// |------ turn, gain 1 magic      ||------ play under your control,||------ enters play, destroy it |
// |                               ||       it gains +1/+1          ||                               |
// |                         ------||                         ------||                         ------|
// |                         |   5 ||                         |   4 ||                         |   4 |
// |-------------------------------||-------------------------------||-------------------------------|
