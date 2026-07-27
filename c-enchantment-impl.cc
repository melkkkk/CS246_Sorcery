module enchantment;
import <vector>;
import <string>;
import <iostream>;
import plard;
import minion;

using namespace std;

std::string Enchantment::getAttack() {return attack;}
std::string Enchantment::getDefense() {return defense;}
std::string Enchantment::getDesc() {return desc;}

//CTOR
Enchantment::Enchantment(string name, int cost): Card{name, cost} {
    cout << "enchantment ctor" << endl;
    if (name == "Giant Strength") { this->attack = "+2"; this->defense = "+2"; }
    else if (name == "Enrage") { this->attack = "*2"; this->defense = "*2"; }
    else if (name == "Haste") { this->desc = "Enchanted minion gains +1 action each turn"; }
    else if (name == "Magic Fatigue") { this->desc = "Enchanted minion's activated ability costs 2 more"; }
    else if (name == "Silence") { this->desc = "Enchanted minion cannot use abilities"; }
}

//tuple ctor
Enchantment::Enchantment(string name, vector<tuple<string, int, string, string, string>> vec) : Card{name} {
  cout << "Enchantment ctor" << endl;
  int i = 0;
  if (name == "Giant Strength") { i = 0; }
  else if (name == "Enrage") { i = 1; }
  else if (name == "Haste") { i = 2; }
  else if (name == "Magic Fatigue") { i = 3; }
  else if (name == "Silence") { i = 4; }

  tuple<string, int, string, string, string> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->desc = (get<2>(temp));
  this->attack = (get<3>(temp));
  this->defense = (get<4>(temp));
}

// export std::tuple<std::string, int, std::string, std::string, std::string> giantstrengthE{"Giant Strength", 1, "", "+2", "+2"};
// export std::tuple<std::string, int, std::string, std::string, std::string> enrageE{"Enrage", 2, "", "*2", "*2"};
// export std::tuple<std::string, int, std::string, std::string, std::string> hasteE{"Haste", 1, "Enchanted minion gains +1 action each turn", "", ""};
// export std::tuple<std::string, int, std::string, std::string, std::string> magicfatigueE{"Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more", "", ""};
// export std::tuple<std::string, int, std::string, std::string, std::string> silenceE{"Silence", 1, "Enchanted minion cannot use abilities", "", ""};

// export std::vector<std::tuple<std::string, int, std::string, std::string, std::string>> enchantmentData = {giantstrengthE, enrageE, hasteE, magicfatigueE, silenceE};


//selects which spell to use
// void Ritual::playRitual(Player *played, Player *owner, int *p) {
//     string name = s.getName();
//     if (name == "Giant Strength") { giantStrength(played, owner, p); }
//     else if (name == "Enrage") { enrage(played, owner, p); }
//     else if (name == "Haste") { haste(played, owner, p); }
//     else if (name == "Magic Fatigue") { magicFatigue(played, owner, p); }
//     else if (name == "Silence") { silence(played, owner, p); }
// }

void Enchantment::giantStrength(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->giantStrength(temp);
  } else cout << "bad index" << endl;
  cout << "giantStrength called" << endl;
}

void Enchantment::giantStrength(Minion *temp) {
  temp->addA(2);
  temp->addD(2);
}

void Enchantment::enrage(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->enrage(temp);
  } else cout << "bad index" << endl;
  cout << "enrage called" << endl;
}

void Enchantment::enrage(Minion *temp) {
  temp->multA(2);
  temp->multD(2);
}

void Enchantment::haste(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
    this->haste(temp);
  } else cout << "bad index" << endl;
  cout << "haste called" << endl;
}

void Enchantment::haste(Minion *temp) {
    temp->addAction(1);
}

void Enchantment::magicFatigue(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->magicFatigue(temp);
  } else cout << "bad index" << endl;
  cout << "magicFatigue called" << endl;
}

void Enchantment::magicFatigue(Minion *temp) {
  temp->addAbilityCost(2);
}

void Enchantment::silence(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->silence(temp);
  } else cout << "bad index" << endl;
  cout << "silence called" << endl;
}

void Enchantment::silence(Minion *temp) {
  temp->setHasAbility(false);
}


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
