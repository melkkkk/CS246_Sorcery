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
void Card::setName(string s) {name = s;}
void Card::setCost(int i) {cost = i;}

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
Card *Player::getCardG(int i) { return graveyard[i].get(); }

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
}

// adds a card to hand
void Player::addToHand(unique_ptr<Card> card){
    hand.push_back(move(card));
}


void Player::moveToFrom(vector<unique_ptr<Card>>& to, vector<unique_ptr<Card>>& from, unique_ptr<Card> card, int index, int i){
        //leave space for ritual slot
    if (board.size() == 0) board.push_back(nullptr);

    //board specific
    if (&to == &board) {
        if (i != 0) {
            board.push_back(move(card));
        } else if (i == 0) {
            //set ritual slot to given ritual
            board[i] = move(card);
        }
    } //all other locations
    else {
        std::string type = card.get()->getName();
        if (std::find(minionCards.begin(), minionCards.end(), type) != minionCards.end()){
                        
            ++minionDeaths;
        }
        //add to new location
        to.push_back(move(card));
    }
    //removes from original location
    from.erase(from.begin() + index);
}

void Player::removeFrom(vector<unique_ptr<Card>>& from, int index, int testing){
    std::string type = from[index].get()->getName();
    if ((std::find(minionCards.begin(), minionCards.end(), type) != minionCards.end()) && testing != 1){
                    
        ++minionDeaths;
    }
    from.erase(from.begin() + index);
}

void Player::addMagic(int i){
    magic += i;
}

int Player::getMinionDeaths(){
    return minionDeaths;
}
