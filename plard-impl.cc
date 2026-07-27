module plard;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import state;

using namespace std;

//destructor
Card::~Card() {}

Card::Card(string name, int cost): name{name}, cost{cost} {}
std::string Card::getName() {return name;}
int Card::getCost() {return cost; }
//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }


Player::Player(int id, string name, int life, int magic): id{id}, name{name}, life{life}, magic{magic} {
}

int Player::getLife(){return life;}
int Player::getMagic(){return magic;}
void Player::setMagic(int i){magic = i;}
vector<unique_ptr<Card>>& Player::getHand(){return hand;}
vector<unique_ptr<Card>>& Player::getBoard(){return board;}
vector<unique_ptr<Card>>& Player::getGraveyard(){return graveyard;}

//adding
void Player::addL(int i) { life += i; }
void Player::addM(int i) { magic += i; }

Card *Player::getCardH(int i) { return hand[i].get(); }
Card *Player::getCardB(int i) { return board[i].get(); }

unique_ptr<Card>& Player::getUniqueH(int i) { return hand[i]; }
unique_ptr<Card>& Player::getUniqueB(int i) { return board[i]; }
unique_ptr<Card>& Player::getUnique(vector<unique_ptr<Card>>& vec, int i) { return vec[i]; }

int Player::getSizeH() { return hand.size(); }
int Player::getSizeB() { return board.size(); }
//general version of previous 2 functions
int Player::getSize(vector<unique_ptr<Card>>& vec) { return vec.size(); }

vector<string>& Player::getDeck() { return deck; }

int Player::getId() {return id;}

// name getter and setters
string Player::getName() {return name;}
void Player::setName(string name) {this->name = name;}

// gets the strings from the fstream and adds it to the vector
void Player::setDeck(ifstream& infile){
    string card_name;
    while (getline(infile, card_name)){
        deck.push_back(card_name);
    }
}

// shuffles deck vector
void Player::shuffleDeck(default_random_engine &rng){
    shuffle(deck.begin(), deck.end(), rng);
    // for (const auto& card : deck) {
    //     cout << card << endl;
    // }
    // cout << endl;
}

// adds a card to hand
void Player::addToHand(unique_ptr<Card> card){
    hand.push_back(move(card));

    int i = hand.size() - 1;
    std::cout << hand[i]->getName() << " has been added to hand!" << endl;
}

//remove from hand when card is played (used up a spell)
// void Player::removeFromHand(int indexH){
//     std::cout << hand[indexH]->getName() << " has been removed from hand!" << endl;
//     hand.erase(hand.begin() + indexH);
// }


//remove from board (for spell banish but can be used for other things also)
// void Player::removeFromBoard(int indexB){
//     std::cout << board[indexB]->getName() << " has been removed from board!" << endl;
//     board.erase(board.begin() + indexB);
// }

// void Player::moveToBoard(unique_ptr<Card> card, int indexH, int i){
//     //leave space for ritua;
//     if (board.size() == 0) {
//         board.push_back(nullptr);
//     }
    
//     if (i != 0) {
//         board.push_back(move(card));
//         int j = board.size() - 1;
//         std::cout << board[j]->getName() << " has been added to board!" << endl;
//     } else if (i == 0) {
//         //set ritual pointer to given ritual
//         board[i] = move(card);
//         std::cout << board[i]->getName() << " has been added to board!" << endl;
//     }
//     //deletes from hand
//     hand.erase(hand.begin() + indexH);
// }

// void Player::moveToGraveyard(unique_ptr<Card> card, int indexB){
//     graveyard.push_back(move(card));
//     int j = graveyard.size() - 1;
//     std::cout << graveyard[j]->getName() << " has been added to graveyard!" << endl;
//     board.erase(board.begin() + indexB);
// }


void Player::moveToFrom(vector<unique_ptr<Card>>& to, vector<unique_ptr<Card>>& from, unique_ptr<Card> card, int index, int i){
    
    //leave space for ritual
    if (board.size() == 0) board.push_back(nullptr);
    cout << "reached move" << endl;

    //board specific
    if (&to == &board) {
        if (i != 0) {
            board.push_back(move(card));
            int j = board.size() - 1;
            std::cout << board[j]->getName() << " has been added to board!" << endl;
        } else if (i == 0) {
            //set ritual pointer to given ritual
            board[i] = move(card);
            std::cout << board[i]->getName() << " has been added to board!" << endl;
        }
    } //all other locations
    else {
        cout << "reached else" << endl;

        // if (auto* temp = dynamic_cast<Minion*>(card.get())) {
        // REPLACE WITH TUPLE LATER TT THIS IS JUST A TEST I SWEAR
        std::string type = card.get()->getName();
        if (type == "Air Elemental" || type == "Earth Elemental" || type == "Bone Golem" 
                    || type == "Potion Seller" || type == "Novice Pyromancer" || type == "Apprentice Summoner"
                    || type == "Fire Elemental" || type == "Master Summoner"){
            cout << "this is a minion not being moved to board, so it must have died!!!" << endl;
            ++minionDeaths;
        }

        to.push_back(move(card));
        std::cout << "moved" << endl;
    }
    
    //deletes from original place
    from.erase(from.begin() + index);
}


void Player::removeFrom(vector<unique_ptr<Card>>& from, int index){
    std::string type = from[index].get()->getName();
    if (type == "Air Elemental" || type == "Earth Elemental" || type == "Bone Golem" 
                || type == "Potion Seller" || type == "Novice Pyromancer" || type == "Apprentice Summoner"
                || type == "Fire Elemental" || type == "Master Summoner"){
        cout << "this is a minion being removed from somehwere, so it must have died!!!" << endl;
        ++minionDeaths;
    }
    std::cout << "removed" << endl;
    from.erase(from.begin() + index);
}

void Player::addMagic(int i){
    magic += i;
}

int Player::getMinionDeaths(){
    return minionDeaths;
}
