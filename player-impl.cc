module player;

import card;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;


using namespace std;

Player::Player(string name, int life, int magic): name{name}, life{life}, magic{magic}{}

void Player::setName(string name) {this->name = name;}

void Player::setDeck(ifstream& infile){
    string card_name;
    while (getline(infile, card_name)){
        deck.emplace_back(card_name);
    }
}

string Player::getName(){return name;}
