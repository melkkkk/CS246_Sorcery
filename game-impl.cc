module game;

import state;
import plard;

import minion;

// CAN COMMMENT OUT IF NOT READY
import ritual;
import enchantment;
import spell;

import board;
import carddata;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import <tuple>;

using namespace std;

Game::~Game() {
    // delete active;
    // delete inactive;
}

Game::Game() {
    p1 = std::make_unique<Player>(1);
    p2 = std::make_unique<Player>(2);
    active = p1.get();
    inactive = p2.get();
}

void Game::changeTurn(){
    std::swap(active, inactive);
}

void Game::setDeck(int i, std::ifstream& infile){
    if (i == 1){
        p1->setDeck(infile);
    } else {
        p2->setDeck(infile);
    }
}

void Game::shuffleDeck(int i, std::default_random_engine &rng){
    if (i == 1){
        p1->shuffleDeck(rng);
    } else {
        p2->shuffleDeck(rng);
    }
}

void Game::setName(int i, std::string name){
    if (i == 1){
        p1->setName(name);
    } else {
        p2->setName(name);
    }
}


int Game::getID() { return active->getId();}

std::string Game::getName(int i){
    std::string s;
    if (i == 1){
        s = p1->getName();
    } else {
        s = p2->getName();
    }
    return s;
}

//do not need anymore cuz changed game logic
std::string Game::getName(){ return active->getName(); }

Player *Game::getActive() {return active;}
Player *Game::getInactive() {return inactive;}

//apply vec of enchantments to specific minion
void Game::applyEnchantments(Minion *m) { //add ability thing here
  m->reset();
  int len = m->getSizeE();
  Enchantment *temp = nullptr;
  string name = "";
  for (int i = 0; i < len; i++) {
    temp = dynamic_cast<Enchantment*>(m->getCardE(i));
    name = temp->getName();
    if (name == "Giant Strength") { temp->giantStrength(m); }
    else if (name == "Enrage") { temp->enrage(m); }
    else if (name == "Haste") { temp->haste(m); }
    else if (name == "Magic Fatigue") { temp->magicFatigue(m); }
    else if (name == "Silence") { temp->silence(m); }
  }
}

//apply vec of enchantments to specific minion
void Game::applyEffects(Minion *m) { //add ability thing here
  m->reset();
  int enchantmentLen = m->getSizeE(); //get size of enchantments vec
  int totalLen = m->getAllApplied().size(); //get size of total applied things vec

  if (enchantmentLen == totalLen) { //if same len that means total is equal to enchantment vec
    this->applyEnchantments(m);
    return;
  }

  Enchantment *temp = nullptr; // to set to each card in enchantment vec
  string name = ""; // to set to each card in enchantment vec
  string applied = ""; // to set to each card in total vec
  int enchantmentIndex = 0; // to loop through each one in time with total vec

  for (int totalIndex = 0; totalIndex < totalLen; totalIndex++) { //total always moves forward since it is longer than enchantment vec
    applied = m->getAllApplied()[totalIndex];
    cout << "inside loop of apply all: " <<  totalIndex << " / " << totalLen << " " << applied;
    if (enchantmentIndex < enchantmentLen) {
        temp = dynamic_cast<Enchantment*>(m->getCardE(enchantmentIndex));
        name = temp->getName();    
        if (name == applied) { // if equal to each other then that means same index, should just apply immediately
            cout << " enchantment loop: " <<  enchantmentIndex << " / " << enchantmentLen << " " << name << endl;
            if (name == "Giant Strength") { temp->giantStrength(m); }
            else if (name == "Enrage") { temp->enrage(m); }
            else if (name == "Haste") { temp->haste(m); }
            else if (name == "Magic Fatigue") { temp->magicFatigue(m); }
            else if (name == "Silence") { temp->silence(m); }
            enchantmentIndex++; // only moves to next enchantment if current is applied properly
        }
    } else { //this means ability is first
        cout << endl;
        if (applied == "Raise Dead") { m->raiseDeadApply(); }
        else if (applied == "Aura of Power") { m->auraOfPowerApply(); }
        else if (applied == "Blizzard") { m->blizzardApply(); }
        else if (applied == "Potion Seller") { m->potionSeller(*active, -1); }
        else if (applied == "Novice Pyromancer") { m->novicePyromancer(active, active, 1, -1); }
        else if (applied == "Bone Golem" && m->getName() == applied) { m->boneGolem(); }
        else if (applied == "Fire Elemental") { m->fireElemental(*active, -1); }
    }
  }
}




//apply vec of enchantments to all minions of active player
void Game::applyAll() {
  cout << "getting size" << endl;
  int len = active->getSizeB();
  cout <<"got size:" << len << endl;
  Minion *temp = nullptr;
  for (int i = 1; i < len; i++) {
    temp = dynamic_cast<Minion*>(active->getCardB(i));
    this->applyEffects(temp);
  }
}

//if int i is negative then attacks player instead
//deoesnt remove if one of them dies,,,

//default args aready declared for last 2
void Game::attackM(int indexM, int i) {
    if ((active->getSizeB() > indexM) && (indexM > 0) && ((i == -1) || ((inactive->getSizeB() > i) && (i > 0)))) {
        cout << "called attack" << endl;
        Minion *temp = dynamic_cast<Minion*>(active->getCardB(indexM));
        cout << temp << endl;
        cout << temp->getName() << endl;
        if (temp->getAction() > 0) {
            temp->addAction(-1);
            if (i < 0) {
                cout << "attacked player" << endl;
                int damage = temp->getAttack();
                damage *= -1;
                inactive->addL(damage);
            } else {
                cout << "attacked minion: " << i << endl;
                Minion *tempOther = dynamic_cast<Minion*>(inactive->getCardB(i));
                int damageTo = temp->getAttack();
                damageTo *= -1;
                int damageFrom = tempOther->getAttack();
                damageFrom *= -1;
                tempOther->addD(damageTo);
                temp->addD(damageFrom);
            } 
        } else cerr << "No actions left!" << endl;
        //delete temp;
    } else cerr << "Incorrect index played/Cannot attack that target." << endl;
}

// Use minion's special ability, optionally targeting target-card owned by target-player 
//minion only
void Game::use(int indexM, bool testing, Player *other, int i) {
    if ((active->getSizeB() > indexM) && (indexM > 0) && ((i == -1) || ((other->getSizeB() > i) && (i > 0)))) {
        cout << "called use" << endl;
        Minion *temp = dynamic_cast<Minion*>(active->getCardB(indexM));
        string name = temp->getName();

        //if not enough magic and not in testing mode, do nothing
        if ((active->getMagic() < temp->getAbilityCost()) && (!testing)) return;

        if (testing || active->getMagic() >= temp->getAbilityCost()) {
            
            // else if (name == "Air Elemental") { airElemental(active, i); }
            // else if (name == "Earth Elemental") { earthElemental(active, i); }
            // if (name == "Bone Golem") { temp->boneGolem(); }
            // else if (name == "Fire  Elemental") { temp->fireElemental(); }
            // else if (name == "Potion Seller") { temp->potionSeller(); }
            if (name == "Apprentice Summoner") { 
                int prev = active->getSizeB();
                temp->apprenticeSummoner(active); 
                int summons = active->getSizeB() - prev;
                b.setState(EventType::MinionSummoned);
                b.notifyObservers(*active, *inactive, indexM, summons);
            } else if (name == "Master Summoner") { 
                int prev = active->getSizeB();
                temp->masterSummoner(active); 
                int summons = active->getSizeB() - prev;
                b.setState(EventType::MinionSummoned);
                b.notifyObservers(*active, *inactive, indexM, summons);
            }
            else if (!other) return; //needs other
            else if (name == "Novice Pyromancer") { temp->novicePyromancer(active, other, i); }

            // temp->addAction(-1);
            // active->addM(temp->getAbilityCost() * -1); // remove the magic required to play card
            if ((testing) && (active->getMagic() < 0)) active->setMagic(0);

        } else cerr << "No actions left!" << endl;
        //delete temp;
    } else cerr << "Incorrect index played/Cannot attack that target." << endl;
}


void Game::playCard(int indexC, bool testing, Player *other, int i) {
    cout << indexC << endl;
    cout << active->getSizeH() << endl;
    // indexC is within hand bounds and if other is non null then i is within board bounds
    if ((active->getSizeH() > indexC) && (indexC >= 0) && (!other || ((i > 0) && (other->getSizeB() > i)))){ 

        Card *c = active->getCardH(indexC);
        
        //if not enough magic and not in testing mode, do nothing
        if ((active->getMagic() < c->getCost()) && (!testing)) return;
        int lostM = 0; //magic required to play card
        string name = c->getName();


        if (std::find(spellCards.begin(), spellCards.end(), name) != spellCards.end()) {
            Spell *temp = dynamic_cast<Spell*>(c);
            
            if (name == "Recharge") { temp->recharge(active, indexC); }
            else if (name == "Raise Dead") { temp->raiseDead(active, indexC); }
            else if (name == "Blizzard") { temp->blizzard(active, inactive); }
            else if (!other) {
                cerr << "Incorrect arguments given to play spell:" << name << endl; 
                // cout << "other = " << other << endl;
                // cout << "i = " << i << endl;
                return;
            }
            else if (name == "Banish") { temp->banish(active, indexC, other, i); }
            else if (name == "Unsummon") { temp->unsummon(active, indexC, other, i); }
            else if (name == "Disenchant") { 
                temp->disenchant(active, indexC, other, i); 
                Card *othercard = other->getCardB(i); // card that the spell is played on
                Minion *m = dynamic_cast<Minion*>(othercard); // dynamic cast the card to minion
                this->applyEffects(m);
            }

            lostM = c->getCost() * -1;
            active->addM(lostM); // remove the magic required to play spell card 
            
            //if in testing mode, only need to set magic to 0
            if ((testing) && (active->getMagic() < 0)) active->setMagic(0);

            active->removeFrom(active->getHand(), indexC); //remove played spell

        } else if (std::find(enchantmentCards.begin(), enchantmentCards.end(), name) != enchantmentCards.end()) {
            if (!other) {
                cerr << "Incorrect arguments given to play enchantment:" << name << endl; 
                return;
            }// all enchantments need other
            Enchantment *temp = dynamic_cast<Enchantment*>(c);
            Card *othercard = other->getCardB(i); // card that the enchantment is played on
            Minion *m = dynamic_cast<Minion*>(othercard); // dynamic cast the card to minion

            if (name == "Giant Strength") { temp->giantStrength(active, other, i); }
            else if (name == "Enrage") { temp->enrage(active, other, i); }
            else if (name == "Haste") { temp->haste(active, other, i); }
            else if (name == "Magic Fatigue") { temp->magicFatigue(active, other, i); }
            else if (name == "Silence") { temp->silence(active, other, i); }
            lostM = c->getCost() * -1;
            active->addM(lostM); // remove the magic required to play card

            m->addApply(name); // add string enchantment to list of total applied
            
            //if in testing mode, only need to set magic to 0
            if ((testing) && (active->getMagic() < 0)) active->setMagic(0);
            
            cout << othercard << '\n';
            cout << m << '\n';
            cout << othercard->getName() << '\n';
            if (!m) {
                cout << "othercard is not a Minion" << endl;
                return;
            }

            active->moveToFrom(m->getEnchantments(), active->getHand(), move(active->getUniqueH(indexC)), indexC);
            cout << "Moved the enchantment to minion" << endl;
            

        } else if (std::find(ritualCards.begin(), ritualCards.end(), name) != ritualCards.end()) {
            // Ritual *temp = dynamic_cast<Ritual*>(c);

            // if (name == "Dark Ritual") { temp->darkRitual(active); }
            // else if (name == "Aura of Power") { temp->auraOfPower(active); }
            // else if (name == "Standstill") { temp->standstill(active); }

            lostM = c->getCost() * -1;
            active->addM(lostM); // remove the magic required to play card
            //if in testing mode, only need to set magic to 0
            if ((testing) && (active->getMagic() < 0)) active->setMagic(0);

            active->moveToFrom(active->getBoard(), active->getHand(), move(active->getUniqueH(indexC)), indexC, 0);
            //active->removeFromHand(indexC);
            //delete temp;

            // function call the tell board smth has been added
            
        } else if (std::find(minionCards.begin(), minionCards.end(), name) != minionCards.end()) {
            //Minion *temp = dynamic_cast<Minion*>(c);

            lostM = c->getCost() * -1;
            active->addM(lostM); // remove the magic required to play card
            //if in testing mode, only need to set magic to 0
            if ((testing) && (active->getMagic() < 0)) active->setMagic(0);

            active->moveToFrom(active->getBoard(), active->getHand(), move(active->getUniqueH(indexC)), indexC);
            

            // function call the tell board smth has been added

            // else if (name == "Air Elemental") { airElemental(active, i); }
            // else if (name == "Earth Elemental") { earthElemental(active, i); }
            // else if (name == "Bone Golem") { boneGolem(active, i); }
            // else if (name == "Fire  Elemental") { fireElemental(active, i); }
            // else if (name == "Potion Seller") { potionSeller(active, i); }
            // else if (name == "Novice Pyromancer") { novicePyromancer(active, i); }
            // else if (name == "Apprentice Summoner") { apprenticeSummoner(active, i); }
            // else if (name == "Master Summoner") { masterSummoner(active, i); }
        }
    //delete c;
    } else {
        cerr << "Incorrect arguments given to play card!" << endl;
    }
}

// draws top card from the deck, probably needs to raise error later on?
void Game::drawCard() {
    // if (i == 1){
    //     active = p1.get();
    // } else {
    //     active = p2.get();
    // }

    // checking if the deck is empty
    if (active->getDeck().empty()){
        cout << "Deck is empty" << endl;
        return;
    }

    // get the top card of the deck
    string s = active->getDeck().at(0);
    active->getDeck().erase(active->getDeck().begin());
    // active->addToHand(make_unique<Minion>(s, 0));
    
    // cout << s << endl;

    // Based on what the name is, the correct card is created
    if (std::find(minionCards.begin(), minionCards.end(), s) != minionCards.end()) {
        active->addToHand(make_unique<Minion>(s, active->getId(), minionData));
    } else if (std::find(spellCards.begin(), spellCards.end(), s) != spellCards.end()) {
        active->addToHand(make_unique<Spell>(s, spellData));
    } else if (std::find(ritualCards.begin(), ritualCards.end(), s) != ritualCards.end()) {
        active->addToHand(make_unique<Ritual>(s, active->getId(), ritualData));
    } else if (std::find(enchantmentCards.begin(), enchantmentCards.end(), s) != enchantmentCards.end()) {
        active->addToHand(make_unique<Enchantment>(s, enchantmentData));
    } else {
        cout << "Card found in deck does not match up: " << s << endl;
    }
}

void Game::printBoard(){
    b.printBoard(*p1, *p2);
}

void Game::printHand(){
    b.printHand(*active);
}

bool validStandstill(Player* p){
    if (!p->getBoard().empty()) {
        auto* tempA = dynamic_cast<Ritual*>(p->getBoard()[0].get());
        if (tempA && tempA->getName() == "Standstill" && tempA->getCharges() - tempA->getActivation() >= 0) {
            std::cout << "checking validSTandstill values " << tempA->getCharges() << " " << tempA->getActivation() << std::endl;
            return true;
        }
    }
    return false;
}

bool Game::notifyBoard(EventType e, int index){
    if (e == EventType::MinionPlayed && active->getSizeH() > index && index >= 0 && dynamic_cast<Minion*>(active->getHand()[index].get()) == nullptr){
        std::cout << "This is not a minion played " << std:: endl;
        return true;
    } else if (e == EventType::MinionPlayed && active->getSizeH() > index && index >= 0) {
        std::cout << "minion about to be played" << std::endl;
        bool bothStandstill = validStandstill(active) && validStandstill(inactive);
        bool playCard = !(validStandstill(active) || validStandstill(inactive));
        b.setState(e);
        b.notifyObservers(*active, *inactive, index, bothStandstill);
        return playCard;
    } else if (e == EventType::MinionDied) {
        int deaths = active->getMinionDeaths();
        if (pastMinionDeath != deaths){
            b.setState(e);
            for (int i = pastMinionDeath; i < deaths; ++i){
                b.notifyObservers(*active, *inactive, index, 0);
            }
        }
        pastMinionDeath = deaths;
        return true;
    } else {
        std::cout << "else case called in notify game" << std::endl;
        b.setState(e);
        b.notifyObservers(*active, *inactive, index, 0);
        return true;
    }
}

// complete implementation once vector of enchantments is sorted out
void Game::inspectMinion(int index){
    b.inspectMinion(*active, index);
}

void removeDeadMinionsP(Player &p){
    for (int i = 1; i < p.getSizeB();){
        auto* temp = dynamic_cast<Minion*>(p.getBoard()[i].get());
        if (temp->getDefense() <= 0){
            // add removing enchantment function
            temp->clearEffects();

            p.moveToFrom(p.getGraveyard(), p.getBoard(), std::move(p.getBoard()[i]), i);
        } else {++i;}
    }
}

void Game::removeDeadMinions(){
    removeDeadMinionsP(*active);
    removeDeadMinionsP(*inactive);
}

bool Game::playerWin(){
    if (inactive->getLife() <= 0){
        std::cout << "Player " << active->getId() << " won!" << std::endl;
        return true;
    }
    return false;
}
