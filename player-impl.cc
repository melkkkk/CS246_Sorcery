module player;

import card;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;


using namespace std;

void Player::set_name(string name){
    this->name = name;
}

void Player::set_deck(ifstream& infile){
    string card_name;
    while (getline(infile, card_name)){
        deck.emplace_back(card_name);
        cout << card_name << endl;
    }
}