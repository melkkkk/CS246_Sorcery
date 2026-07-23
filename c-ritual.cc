export module ritual;
import <vector>;
import <string>;
import card;
import player;

using namespace std;

export class Ritual: public Card {
    int charges;
    int activation;
    string desc;

  protected:
    //void setState(State newS);
  public:
    Ritual(string name, int cost, int charges, int activation);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void darkRitual(Player played);
    void auraOfPower(Player played);
    void standstill(Player played);

    //add charge
    //multiply charge
    void addC(int i = 1);
    void multC(int i = 1);

    //removes the activation from charge
    void played();
};

//add charge
//multiply charge
void Ritual::addC(int i = 1) { charges += i; }
void Ritual::multC(int i = 1) { charges *= i; }

//removes the activation from charge
void played() {
  this.addC(-(activation));
}

//CTOR
Ritual::Ritual(string name, int cost, int charges, int activation): Card{name, cost} {
    this->charges = charges;
    this->activation = activation;
    if (name == "Dark Ritual") { this->desc = "At the start of your turn, gain 1 magic"; }
    else if (name == "Aura of Power") { this->desc = "Whenever a minion enters play under your control it gains +1/+1"; }
    else if (name == "Standstill") { this->desc = "Whenever a minion enters play, destroy it"; }
}

//selects which spell to use
// void Ritual::playRitual(Player *played, Player *owner, int *p) {
//     string name = s.getName();
//     if (name == "Dark Ritual") { darkRitual(played); }
//     else if (name == "Aura of Power") { auraOfPower(played); }
//     else if (name == "Standstill") { standstill(played); }
// }

void darkRitual(Player played) {
  //change condition to activated at start of turn, gains value
}
void auraOfPower(Player played) {
  //change condition to activated for minion in play under activated players control, add to value
}
void standstill(Player played) {
  //change condition to activated for minion in play, destory it
}

void Ritual::notify(State &whoFrom, Player *active) {
  if (whoFrom.sType == StateType::StartOfTurn) {
    //check if dark ritual then add 1 to magic
    if (this.getname() == "Dark Ritual") {
      if (charges > activation) { active->addM(1); this.played(); }
    }
  }
  else if (whoFrom.sType == StateType::EndOfTurn) {
    // would add any cards of end of turn type here
  } else if (whoFrom.sType == StateType::MinionPlayed) {
    if (whoFrom.cType == CardType::Minion) {
      if (this->getname() == "Standstill") { active->board.pop_back(); }
      else if (this->getname() == "Aura of Power") { this.addA(); this.addD(); }
      //any other minion play activated things
    }
  }
}

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
