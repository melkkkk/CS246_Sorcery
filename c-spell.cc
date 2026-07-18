export module spell;
import <vector>;
import <string>;
import card;

/* A note on Info and State:

   We have separated the collection of fields into two parts: its Info
   and its State.

   Info is for the parts of the subject inherent to what it is: its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.  This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, a direction,
   and a colour.  For more details, see state.h.
*/

using namespace std;

export class Spell: public Card {
    string desc;

  protected:
    //void setState(State newS);
  public:
    Spell(string name, int cost);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void playspell(Player played, Player owner, Spell s, void *p);
    void banish(Player played, Player owner, void *p);
    void unsummon(Player played, Player owner, void *p);
    void recharge(Player played);
    void disenchant(Player played, Player owner, void *p);
    void raisedead(Player played);
    void blizzard(Player played, Player owner);
};

Spell::Spell(string name, int cost): Card{name, cost} {
    if (name == "Banish") { this->desc = "Destroy target minion or ritual"; }
    else if (name == "Unsummon") { this->desc = "Return target minion to its owner's hand"; }
    else if (name == "Recharge") { this->desc = "Your ritual gains 3 charges"; }
    else if (name == "Disenchant") { this->desc = "Destroy the top enchantment"; }
    else if (name == "Raise Dead") { this->desc = "Resurrect the top minion in your graveyard and set its defence to 1"; }
    else if (name == "Blizzard") { this->desc = "Deal 2 damage to all minions"; }
    
}

// |-------------------------------||-------------------------------||-------------------------------|
// | Banish                  |   2 || Unsummon                |   1 || Recharge                |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy target minion or      || Return target minion to its   || Your ritual gains 3 charges   |
// | ritual                        || owner's hand                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------|
// | Disenchant              |   1 || Raise Dead              |   1 || Blizzard                |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy the top enchantment   || Resurrect the top minion in   || Deal 2 damage to all minions  |
// | on target minion              || your graveyard and set its.   ||                               |
// |                               || defence to 1                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
