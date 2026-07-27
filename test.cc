export module carddata;

import state;
import plard;
import minion;
import ritual;
import enchantment;
import spell;

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
std::tuple<std::string, int, std::string> banishS{"Banish", 2,"Destroy target minion or ritual"};
std::tuple<std::string, int, std::string> unsummonS{"Unsummon", 1, "Return target minion to its owner's hand"};
std::tuple<std::string, int, std::string> rechargeS{"Recharge", 1, "Your ritual gains 3 charges"};
std::tuple<std::string, int, std::string> disenchantS{"Disenchant", 1, "Destroy the top enchantment"};
std::tuple<std::string, int, std::string> raisedeadS{"Raise Dead", 1, "Resurrect the top minion in your graveyard and set its defence to 1"};
std::tuple<std::string, int, std::string> blizzardS{"Blizzard", 3, "Deal 2 damage to all minions"};

std::vector<std::tuple<std::string, int, std::string>> spellData = {banishS, unsummonS, rechargeS, disenchantS, raisedeadS, blizzardS};

// |-------------------------------||-------------------------------||-------------------------------|
// | Banish                  |   2 || Unsummon                |   1 || Recharge                |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy target minion or      || Return target minion to its   || Your ritual gains 3 charges   |
// | ritual                        || owner's hand                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------|
// | Disenchant              |   1 || Raise Dead              |   1 || Blizzard                |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy the top enchantment   || Resurrect the top minion in   || Deal 2 damage to all minions  |
// | on target minion              || your graveyard and set its.   ||                               |
// |                               || defence to 1                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|

// all enchantment card data
///card name, card cost, enchantment desc, enchantment attack, enchantment defense
std::tuple<std::string, int, std::string, std::string, std::string> giantstrengthE{"Giant Strength", 1, "", "+2", "+2"};
std::tuple<std::string, int, std::string, std::string, std::string> enrageE{"Enrage", 2, "", "*2", "*2"};
std::tuple<std::string, int, std::string, std::string, std::string> hasteE{"Haste", 1, "Enchanted minion gains +1 action each turn", "", ""};
std::tuple<std::string, int, std::string, std::string, std::string> magicfatigueE{"Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more", "", ""};
std::tuple<std::string, int, std::string, std::string, std::string> silenceE{"Silence", 1, "Enchanted minion cannot use abilities", "", ""};

std::vector<std::tuple<std::string, int, std::string, std::string, std::string>> enchantmentData = {giantstrengthE, enrageE, hasteE, magicfatigueE, silenceE};

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


// all ritual card data
///card name, card cost, ritual id set to 0 TUPLE CTOR WILL ACCEPT INT ARG TO SET CORRECT ID, ritual desc, ritual charges, ritual activation
std::tuple<std::string, int, int, std::string, int, int> darkritualR{"Dark Ritual", 0, 0, "At the start of your turn, gain 1 magic", 5, 1};
std::tuple<std::string, int, int, std::string, int, int> auraofpowerR{"Aura of Power", 1, 0, "Whenever a minion enters play under your control it gains +1/+1", 4, 1};
std::tuple<std::string, int, int, std::string, int, int> standstillR{"Standstill", 3, 0, "Whenever a minion enters play, destroy it", 4, 2};

std::vector<std::tuple<std::string, int, int, std::string, int, int>> ritualData = {darkritualR, auraofpowerR, standstillR};

// |-------------------------------||-------------------------------||-------------------------------|
// | Dark Ritual             |   0 || Aura of Power           |   1 || Standstill              |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                        Ritual ||                        Ritual ||                        Ritual |
// |-------------------------------||-------------------------------||-------------------------------|
// | 1   | At the start of your    || 1   | Whenever a minion enters|| 2   | Whenever a minion       |
// |------ turn, gain 1 magic      ||------ play under your control,||------ enters play, destroy it |
// |                               ||       it gains +1/+1          ||                               |
// |                         ------||                         ------||                         ------|
// |                         |   5 ||                         |   4 ||                         |   4 |
// |-------------------------------||-------------------------------||-------------------------------|

// all minion card data
///card name, card cost, minion id set to 0 TUPLE CTOR WILL ACCEPT INT ARG TO SET CORRECT ID, minion ogAttack, minion ogDefense, minion ogAbilityCost, minion ogactions, minion oghasability
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> airelementalM{"Air Elemental", 0, 0, "", 1, 1, -1, 0, false};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> earthelementalM{"Earth Elemental", 3, 0, "", 4, 4, -1, 0, false};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> bonegolemM{"Bone Golem", 2, 0, "Gain +1/+1 whenever a minion leaves play.", 1, 3, -1, 0, true};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> fireelementalM{"Fire Elemental", 2, 0, "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2,-1, 0, true};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> potionsellerM{"Potion Seller", 2, 0, "At the end of your turn, all your minions gain +0/+1.", 1, 3, -1, 0, true};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> novicepyromancerM{"Novice Pyromancer", 1, 0, "Deal 1 damage to target minion", 0, 1, 1, 0, true};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> apprenticesummonerM{"Apprentice Summoner", 1, 0, "Summon a 1/1 air elemental", 1, 1, 1, 0, true};
std::tuple<std::string, int, int, std::string, int, int, int, int, bool> mastersummonerM{"Master Summoner", 3, 0, "Summon up to three 1/1 air elementals", 2, 3, 2, 0, true};

std::vector<std::tuple<std::string, int, int, std::string, int, int, int, int, bool>> ritualData = {airelementalM, earthelementalM, bonegolemM, fireelementalM, potionsellerM, novicepyromancerM, apprenticesummonerM, mastersummonerM};

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