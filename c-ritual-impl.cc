module ritual;
import <vector>;
import <string>;
import <iostream>;
import <tuple>;
import state;
import plard;
import minion;
import carddata;

using namespace std;

//add charge
//multiply charge
void Ritual::addC(int i) { charges += i; }
void Ritual::multC(int i) { charges *= i; }
int Ritual::getCharges(){return charges;}
int Ritual::getActivation(){ return activation;}
std::string Ritual::getDesc(){ return desc;}

//tuple ctor
Ritual::Ritual(string name, int owner, vector<tuple<string, int, int, string, int, int>> vec) : Card{name} {
  int i = 0;
  if (name == "Dark Ritual") { i = 0; }
  else if (name == "Aura of Power") { i = 1; }
  else if (name == "Standstill") { i = 2; }

  tuple<string, int, int, string, int, int> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->owner = owner;
  this->desc = (get<3>(temp));
  this->charges = (get<4>(temp));
  this->activation = (get<5>(temp));
}

void Ritual::darkRitual(Player &active) {
  if (charges - activation >= 0){
    active.addM(1);
    charges -= activation;
  }
}

void Ritual::auraOfPower(Player &active, int index, int extra) {
  if (extra >= 0) {
    for (int i = 0; i < extra && charges >= activation; ++i) {
      Minion *temp = dynamic_cast<Minion*>(active.getBoard()[active.getSizeB() - 1 - i].get());
      if (temp) {
        temp->addA(1);
        temp->addD(1);
        charges -= activation;
      }
    }
  } else if (owner == active.getId() && charges - activation >= 0 && extra < 0){
    if (!(active.getSizeH() > index && index >= 0)) return;
    Minion *temp = dynamic_cast<Minion*>(active.getHand()[index].get());
    temp->addA(1);
    temp->addD(1);
    temp->addApply("Aura of Power");
    charges -= activation;
  }
}

void Ritual::standstill(Player &active, int index, int ss, int extra) {
  if (extra >= 0) {
    int removed = 0;
    while (removed < extra && charges >= activation) {
      active.removeFrom(active.getBoard(), active.getSizeB() - 1);
      charges -= activation;
      ++removed;
    }
  } else if (((ss && active.getId() == owner) || !ss) && charges - activation >= 0){
    if (!(active.getSizeH() > index && index >= 0)) return;
    active.removeFrom(active.getHand(), index);
    charges -= activation;
  }
}

void Ritual::notify(EventType event, Player &active, int index, int extra) {
  if (event == EventType::StartOfTurn){
    if (this->getName() == "Dark Ritual" && active.getId() == owner){
      darkRitual(active);
    }
  } else if (event == EventType::MinionPlayed) {
    if (this->getName() == "Aura of Power" && active.getId() == owner){
      auraOfPower(active, index);
    } else if (this->getName() == "Standstill"){
      standstill(active, index, extra);
    }
  } else if (event == EventType::MinionSummoned){
    if (this->getName() == "Aura of Power" && active.getId() == owner){
      if (active.getSizeH() > index && index > 0) auraOfPower(active, index, extra);
    } else if (this->getName() == "Standstill"){
      standstill(active, index, -1, extra);
    }
  }
}
