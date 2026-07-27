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
  cout << "Minion ctor" << endl;
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

// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> airelementalM{"Air Elemental", 0, 0, "", 1, 1, -1, 0, false};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> earthelementalM{"Earth Elemental", 3, 0, "", 4, 4, -1, 0, false};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> bonegolemM{"Bone Golem", 2, 0, "Gain +1/+1 whenever a minion leaves play.", 1, 3, -1, 0, true};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> fireelementalM{"Fire Elemental", 2, 0, "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2,-1, 0, true};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> potionsellerM{"Potion Seller", 2, 0, "At the end of your turn, all your minions gain +0/+1.", 1, 3, -1, 0, true};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> novicepyromancerM{"Novice Pyromancer", 1, 0, "Deal 1 damage to target minion", 0, 1, 1, 0, true};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> apprenticesummonerM{"Apprentice Summoner", 1, 0, "Summon a 1/1 air elemental", 1, 1, 1, 0, true};
// export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> mastersummonerM{"Master Summoner", 3, 0, "Summon up to three 1/1 air elementals", 2, 3, 2, 0, true};

// export std::vector<std::tuple<std::string, int, int, std::string, int, int, int, int, bool>> minionData = {airelementalM, earthelementalM, bonegolemM, fireelementalM, potionsellerM, novicepyromancerM, apprenticesummonerM, mastersummonerM};


vector<unique_ptr<Card>>& Minion::getEnchantments(){return enchanted;}

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
    std::cout << "removed" << endl;
    enchanted.erase(enchanted.begin() + i);
  }
}

//multiply Attack
//multiply Defense
void Minion::multA(int i) { attack *= i; }
void Minion::multD(int i) { defense *= i; }

// Minion::Minion(string name, int cost, int owner): Card{name, cost}, owner{owner} {
//     //set defense and actions if applicable

//     cout << "minion ctor" << endl;
    

//     // if (name == "Dark Ritual") { 
//     //   desc = "At the start of your turn, gain 1 magic"; 
//     //   abilityCost = 1;
//     //   //charges = 5;
//     //   //activation = 1;
//     // }
//     // else if (name == "Apprentice Summoner") { 
//     //   desc = "Whenever a minion enters play under your control it gains +1/+1"; 
//     //   abilityCost = 1;
//     //   //charges = 4;
//     //   //activation = 1;
//     // }
//     // else if (name == "Master Summoner") { 
//     //   desc = "Whenever a minion enters play, destroy it"; 
//     //   abilityCost = 2;
//     //   //charges = 4;
//     //   //activation = 2;
//     // }
// }


//void Minion::airElemental(Player *played, int *target) {}
//void Minion::earthElemental(Player *played, int *target) {}
void Minion::boneGolem(Player &active) {
  //needs notify implementation
  cout << "bone golem called" << endl;
  this->addD(1);
  this->addA(1);
}

void Minion::fireElemental(Player &active, int index) {
  //needs notify implementation
  cout << "fire elemental called" << endl;
  if (active.getId() != owner){
    Minion *temp = dynamic_cast<Minion*>(active.getHand()[index].get());
    temp->addD(-1);
  }
}

void Minion::potionSeller(Player &active) {
  //needs notify implementation
  cout << "potion seller called" << endl;

  if (active.getId() == owner){
    for (int i = 1; i < active.getSizeB(); ++i) {
      Minion *temp = dynamic_cast<Minion*>(active.getBoard()[i].get());
      temp->addD(1);
    }
  }
}

void Minion::novicePyromancer(Player *activeP, Player *targetP, int target) {
  cout << "novice pyromancer called" << endl;
  if (actions > 0 && hasAbility){
    Minion *tempOther = dynamic_cast<Minion*>(targetP->getCardB(target));
    tempOther->addD(-1);

    actions -= 1;
    activeP->addM(abilityCost * -1);
    if (actions <= 0) { hasAbility = !hasAbility; }
  } else {
    std::cerr << "Not enough items to use this ability" << std::endl;
  }
}

void Minion::apprenticeSummoner(Player *active) {
  cout << "apprentice summoner called" << endl;
  if (actions > 0 && hasAbility && active->getSizeB() < 6){
    std::string s = "Air Elemental"; 
    active->addToHand(make_unique<Minion>(s, active->getId(), minionData));
    active->moveToFrom(active->getBoard(), active->getHand(), move(active->getUniqueH(active->getSizeH() -1)), active->getSizeH() -1);

    actions -= 1;
    active->addM(abilityCost * -1);
    if (actions <= 0) { hasAbility = !hasAbility; }
  } else {
    std::cerr << "Not enough items to use this ability" << std::endl;
  }
}

void Minion::masterSummoner(Player *active) {
  cout << "master summoner called" << endl;
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
    std::cerr << "Not enough items to use this ability" << std::endl;
  }
}


void Minion::notify(EventType event, Player &active, int index, bool bothStandstill) {
  cout << "notified minion" << endl;
  if (event == EventType::EndOfTurn){
    if (this->getName() == "Potion Seller") {potionSeller(active);}
  } else if (event == EventType::MinionPlayed) {
    if (this->getName() == "Fire Elemental") {fireElemental(active, index);}
  } else if (event == EventType::MinionDied) {
    if (this->getName() == "Bone Golem") {boneGolem(active);}
  }
}

int Minion::getEnchantmentsSize(){return enchanted.size();}



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
