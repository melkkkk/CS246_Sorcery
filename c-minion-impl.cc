module minion;
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

void Minion::reset() {
  this->setAttack(this->getAttackO());
  this->setDefense(this->getDefenseO());
  this->setAction(this->getActionO());
  this->setAbilityCost(this->getAbilityCostO());
  this->setHasAbility(this->getHasAbilityO());
}

Minion::Minion(string name, int owner, vector<tuple<string, int, int, string, int, int, int, int, bool>> vec) : Card{name} {
  int i = 0;
  if (name == "Air Elemental") { i = 0; }
  else if (name == "Earth Elemental") { i = 1; }
  else if (name == "Bone Golem") { i = 2; }
  else if (name == "Fire Elemental") { i = 3; }
  else if (name == "Potion Seller") { i = 4; }
  else if (name == "Novice Pyromancer") { i = 5; }
  else if (name == "Apprentice Summoner") { i = 6; }
  else if (name == "Master Summoner") { i = 7; }

  tuple<string, int, int, string, int, int, int, int, bool> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->owner = owner;
  this->desc = (get<3>(temp));
  this->ogAttack = (get<4>(temp));
  this->ogDefense = (get<5>(temp));
  this->ogAbilityCost = (get<6>(temp));
  this->ogActions = (get<7>(temp));
  this->ogHasAbility = (get<8>(temp));
  this->reset();
}

vector<unique_ptr<Card>>& Minion::getEnchantments(){return enchanted;}
vector<string>& Minion::getAllApplied() { return allApplied; }
int Minion::getSizeA() { return allApplied.size(); }

int Minion::getAttack() { return attack; }
int Minion::getDefense() { return defense; }
int Minion::getAction() { return actions; }
std::string Minion::getDesc() {return desc;};
int Minion::getAbilityCost() {return abilityCost;};
bool Minion::getHasAbility() {return hasAbility;};
// int Minion::getOwner(){ return owner; }


int Minion::getAttackO() { return ogAttack; }
int Minion::getDefenseO() { return ogDefense; }
int Minion::getActionO() { return ogActions; }
int Minion::getAbilityCostO() {return ogAbilityCost;};
bool Minion::getHasAbilityO() {return ogHasAbility;};


//add Attack
//add Defense
void Minion::addA(int i) { attack += i; }
void Minion::addD(int i) { defense += i; }
void Minion::addAction(int i) { actions += i; }
void Minion::addAbilityCost(int i) { abilityCost += i; }

void Minion::setHasAbility(bool b) { hasAbility = b; }
void Minion::setAttack(int i) { attack = i; }
void Minion::setDefense(int i) { defense = i; }
void Minion::setAction(int i) { actions = i; }
void Minion::setAbilityCost(int i) { abilityCost = i;};



Card *Minion::getCardE(int i) { return enchanted[i].get(); }
unique_ptr<Card>& Minion::getUniqueE(int i) { return enchanted[i]; }

int Minion::getSizeE() { return enchanted.size(); }

void Minion::removeE(int i) {
  if (this->getSizeE() > i) {
    enchanted.erase(enchanted.begin() + i);
  }
}

int Minion::getEnchantmentsSize(){return enchanted.size();}

void Minion::removeA(int i) {
  if (this->getSizeA() > i) {
    allApplied.erase(allApplied.begin() + i);
  }
}

void Minion::clearEffects() {
  int enchantmentLen = this->getSizeE() - 1;
  int totalLen = this->getAllApplied().size() - 1;
  
  string name = ""; 
  string current = ""; 
  int enchantmentIndex = enchantmentLen;

  for (int totalIndex = totalLen; totalIndex >= 0; totalIndex--) { //total always moves forward since it is longer than enchantment vec
    current = this->getAllApplied()[totalIndex];
    if (enchantmentIndex >= 0) {
      this->removeE(enchantmentIndex);
      enchantmentIndex--; // only moves to next enchantment if within bounds
    }
    if (current == "Giant Strength" || current == "Enrage" || current == "Haste" || current == "Magic Fatigue" || current == "Silence") {
      this->removeA(totalIndex);
    }
  }
}

//multiply Attack
//multiply Defense
void Minion::multA(int i) { attack *= i; }
void Minion::multD(int i) { defense *= i; }

//extra functions for purpose of apply all only
void Minion::raiseDeadApply() { this->setDefense(1); }
void Minion::auraOfPowerApply() {
  this->addD(1);
  this->addA(1);
}

void Minion::blizzardApply() {
  this->addD(-2);
}

void Minion::addApply(string s) { this->allApplied.emplace_back(s); }

void Minion::boneGolem(int extra) {
  this->addD(1);
  this->addA(1);
  if (extra < 0) this->addApply("Bone Golem");
}

void Minion::fireElemental(Player &active, int index, int extra) {
  if (index < 0) { //this is only for apply effects
    this->addD(-1);
    return;
  } else if (active.getId() != owner && extra < 0 && active.getSizeH() > index && index >= 0){
    Minion *temp = dynamic_cast<Minion*>(active.getHand()[index].get());
    temp->addD(-1);
    temp->addApply("Fire Elemental");
  } else if (active.getId() != owner && active.getSizeB() > extra && extra >= 0){
    for (int i = 0; i < extra; ++i){
      Minion *temp = dynamic_cast<Minion*>(active.getBoard()[active.getSizeB() - 1 - i].get());
      temp->addD(-1);
      temp->addApply("Fire Elemental");
    }
  }
}

void Minion::potionSeller(Player &active, int extra) {

  if (extra < 0) { //this is only for apply effects
    this->addD(1);
    return;
  } else if (active.getId() == owner){
    for (int i = 1; i < active.getSizeB(); ++i) {
      Minion *temp = dynamic_cast<Minion*>(active.getBoard()[i].get());
      temp->addD(1);
      temp->addApply("Potion Seller");
    }
  }
}

void Minion::novicePyromancer(Player *activeP, Player *targetP, int target, int extra) {
  if (extra < 0) { //this is only for apply effects
    this->addD(-1);
    return;
  } else if (actions > 0 && hasAbility){
    Minion *tempOther = dynamic_cast<Minion*>(targetP->getCardB(target));
    tempOther->addD(-1);
    tempOther->addApply("Novice Pyromancer");

    actions -= 1;
    activeP->addM(abilityCost * -1);
    if (actions <= 0) { hasAbility = !hasAbility; }
  } else {
    std::cerr << "Not enough items to use this ability!" << std::endl;
  }
}

void Minion::apprenticeSummoner(Player *active) {
  if (actions > 0 && hasAbility && active->getSizeB() < 6){
    std::string s = "Air Elemental"; 
    active->addToHand(make_unique<Minion>(s, active->getId(), minionData));
    active->moveToFrom(active->getBoard(), active->getHand(), move(active->getUniqueH(active->getSizeH() -1)), active->getSizeH() -1);
    actions -= 1;
    active->addM(abilityCost * -1);
    if (actions <= 0) { hasAbility = !hasAbility; }
  } else {
    std::cerr << "Not enough items to use this ability!" << std::endl;
  }
}

void Minion::masterSummoner(Player *active) {
  if (actions > 0 && hasAbility && active->getSizeB() < 6){
    std::string s = "Air Elemental"; 
    int times = 3;
    if (6 - active->getSizeB() < times) {times = 6 - active->getSizeB();}

    for (int i = 0; i < times; ++i){
      active->addToHand(make_unique<Minion>(s, active->getId(), minionData));
      active->moveToFrom(active->getBoard(), active->getHand(), move(active->getUniqueH(active->getSizeH() -1)), active->getSizeH() -1);
    }
    
    actions -= 1;
    active->addM(abilityCost * -1);
    if (actions <= 0) { hasAbility = !hasAbility; }
  } else {
    std::cerr << "Not enough items to use this ability!" << std::endl;
  }
}


void Minion::notify(EventType event, Player &active, int index, int extra) {
  if (event == EventType::EndOfTurn){
    if (this->getName() == "Potion Seller") {potionSeller(active);}
  } else if (event == EventType::MinionPlayed) {
    if (this->getName() == "Fire Elemental") {fireElemental(active, index);}
  } else if (event == EventType::MinionSummoned) {
    if (this->getName() == "Fire Elemental") {fireElemental(active, index, extra);}
  } else if (event == EventType::MinionDied) {
    if (this->getName() == "Bone Golem") {boneGolem(-1);}
  } else if (event == EventType::StartOfTurn) {
    if (actions < 1 && active.getId() == owner) {actions = 1;}
  }
}
