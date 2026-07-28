export module carddata;

import state;
import plard;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import <algorithm>;
import <memory>;
import <tuple>;


// all spell card data
///card name, card cost, spell desc
export std::tuple<std::string, int, std::string> banishS{"Banish", 2,"Destroy target minion or ritual"};
export std::tuple<std::string, int, std::string> unsummonS{"Unsummon", 1, "Return target minion to its owner's hand"};
export std::tuple<std::string, int, std::string> rechargeS{"Recharge", 1, "Your ritual gains 3 charges"};
export std::tuple<std::string, int, std::string> disenchantS{"Disenchant", 1, "Destroy the top enchantment"};
export std::tuple<std::string, int, std::string> raisedeadS{"Raise Dead", 1, "Resurrect the top minion in your graveyard and set its defence to 1"};
export std::tuple<std::string, int, std::string> blizzardS{"Blizzard", 3, "Deal 2 damage to all minions"};

export std::vector<std::tuple<std::string, int, std::string>> spellData = {banishS, unsummonS, rechargeS, disenchantS, raisedeadS, blizzardS};

// all enchantment card data
///card name, card cost, enchantment desc, enchantment attack, enchantment defense
export std::tuple<std::string, int, std::string, std::string, std::string> giantstrengthE{"Giant Strength", 1, "", "+2", "+2"};
export std::tuple<std::string, int, std::string, std::string, std::string> enrageE{"Enrage", 2, "", "*2", "*2"};
export std::tuple<std::string, int, std::string, std::string, std::string> hasteE{"Haste", 1, "Enchanted minion gains +1 action each turn", "", ""};
export std::tuple<std::string, int, std::string, std::string, std::string> magicfatigueE{"Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more", "", ""};
export std::tuple<std::string, int, std::string, std::string, std::string> silenceE{"Silence", 1, "Enchanted minion cannot use abilities", "", ""};

export std::vector<std::tuple<std::string, int, std::string, std::string, std::string>> enchantmentData = {giantstrengthE, enrageE, hasteE, magicfatigueE, silenceE};

// all ritual card data
///card name, card cost, ritual id set to 0 TUPLE CTOR WILL ACCEPT INT ARG TO SET CORRECT ID, ritual desc, ritual charges, ritual activation
export std::tuple<std::string, int, int, std::string, int, int> darkritualR{"Dark Ritual", 0, 0, "At the start of your turn, gain 1 magic", 5, 1};
export std::tuple<std::string, int, int, std::string, int, int> auraofpowerR{"Aura of Power", 1, 0, "Whenever a minion enters play under your control it gains +1/+1", 4, 1};
export std::tuple<std::string, int, int, std::string, int, int> standstillR{"Standstill", 3, 0, "Whenever a minion enters play, destroy it", 4, 2};

export std::vector<std::tuple<std::string, int, int, std::string, int, int>> ritualData = {darkritualR, auraofpowerR, standstillR};

// all minion card data
///card name, card cost, minion id set to 0 TUPLE CTOR WILL ACCEPT INT ARG TO SET CORRECT ID, minion ogAttack, minion ogDefense, minion ogAbilityCost, minion ogactions, minion oghasability
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> airelementalM{"Air Elemental", 0, 0, "", 1, 1, -1, 1, false};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> earthelementalM{"Earth Elemental", 3, 0, "", 4, 4, -1, 1, false};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> bonegolemM{"Bone Golem", 2, 0, "Gain +1/+1 whenever a minion leaves play.", 1, 3, -1, 1, true};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> fireelementalM{"Fire Elemental", 2, 0, "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2,-1, 1, true};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> potionsellerM{"Potion Seller", 2, 0, "At the end of your turn, all your minions gain +0/+1.", 1, 3, -1, 1, true};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> novicepyromancerM{"Novice Pyromancer", 1, 0, "Deal 1 damage to target minion", 0, 1, 1, 1, true};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> apprenticesummonerM{"Apprentice Summoner", 1, 0, "Summon a 1/1 air elemental", 1, 1, 1, 1, true};
export std::tuple<std::string, int, int, std::string, int, int, int, int, bool> mastersummonerM{"Master Summoner", 3, 0, "Summon up to three 1/1 air elementals", 2, 3, 2, 1, true};

export std::vector<std::tuple<std::string, int, int, std::string, int, int, int, int, bool>> minionData = {airelementalM, earthelementalM, bonegolemM, fireelementalM, potionsellerM, novicepyromancerM, apprenticesummonerM, mastersummonerM};
