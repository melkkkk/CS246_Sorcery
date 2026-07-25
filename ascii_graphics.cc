export module ascii_graphics;
import <vector>;
import <string>;

//SIMPLE_GRAPHICS = 0 displays a fancy style.
//SIMPLE_GRAPHICS = 1 displays the style shown in the project specification's examples
//You are encouraged to use SIMPLE_GRAPHICS = 0, but some terminals may not like it.
#define SIMPLE_GRAPHICS 0

export typedef std::vector<std::string> card_template_t;

export card_template_t display_minion_no_ability(std::string name,int cost,int attack,int defence);
export card_template_t display_minion_triggered_ability(std::string name,int cost,int attack,int defence,
                                                 std::string trigger_desc);
export card_template_t display_minion_activated_ability(std::string name,int cost,int attack,int defence,
                                                 int ability_cost, std::string ability_desc);
export card_template_t display_ritual(std::string name,int cost,int ritual_cost,std::string ritual_desc,
                               int ritual_charges);
export card_template_t display_spell(std::string name,int cost,std::string desc);
export card_template_t display_enchantment_attack_defence(std::string name,int cost,std::string desc,
                                                   std::string attack,std::string defence);
export card_template_t display_enchantment(std::string name,int cost,std::string desc);
export card_template_t display_player_card(int player_num,std::string name,int life,int mana);

export extern const card_template_t CARD_TEMPLATE_MINION_NO_ABILITY;
export extern const card_template_t CARD_TEMPLATE_MINION_WITH_ABILITY;
export extern const card_template_t CARD_TEMPLATE_BORDER;
export extern const card_template_t CARD_TEMPLATE_EMPTY;
export extern const card_template_t CARD_TEMPLATE_RITUAL;
export extern const card_template_t CARD_TEMPLATE_SPELL;
export extern const card_template_t CARD_TEMPLATE_ENCHANTMENT_WITH_ATTACK_DEFENCE;
export extern const card_template_t CARD_TEMPLATE_ENCHANTMENT;

export extern const card_template_t PLAYER_1_TEMPLATE;
export extern const card_template_t PLAYER_2_TEMPLATE;

export extern const std::vector<std::string> CENTRE_GRAPHIC;

export extern const std::string EXTERNAL_BORDER_CHAR_UP_DOWN;
export extern const std::string EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
export extern const std::string EXTERNAL_BORDER_CHAR_TOP_LEFT;
export extern const std::string EXTERNAL_BORDER_CHAR_TOP_RIGHT;
export extern const std::string EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
export extern const std::string EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
