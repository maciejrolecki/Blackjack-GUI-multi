#include "json_gen.h"
std::stringstream &json_gen::generate_json_user_info(std::string name)
{
    ptree tree;
    tree.put("Type","CONNECTION_ESTABLISHED");
    tree.put("User.name",name);
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}

std::stringstream & json_gen::generate_json_game_info(std::string name,size_t db_id,size_t bank,Game game,int player_game_id)
{
    ptree tree;
    tree.put("Type","CONNECTION_ESTABLISHED");
    tree.put("User.player_game_nb",player_game_id);
    tree.put("User.name",name);
    tree.put("User.db_id",std::to_string(db_id));
    tree.put("User.bank",std::to_string(bank));
    auto g_state = std::to_string(static_cast<int>(game.get_game_state()));
    tree.put("Game.state",g_state);
    tree.put("Game.currentPlayer",std::to_string(game.get_current_player()));
    tree.put("Game.croupier.score", std::to_string(game.get_croupier().get_score()));
    auto c_hand = game.get_croupier().get_hand();
    add_cards(tree,c_hand,-1);
    auto player_list= game.get_player_list();
    add_players(tree,player_list);
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
    //aucun code pour le moment
}

void json_gen::add_cards(ptree &tree, std::vector<Card> cards, int id)
{
    ptree child;
    std::vector<ptree>trees;
    std::for_each(cards.begin(),cards.end(),[&trees](Card card){
        auto children = ptree();
        auto card_c = std::to_string(static_cast<int>(card.get_color()));
        children.put("Color", card_c);
        children.put("Value", std::to_string(card.get_value_card()));
        trees.push_back(children);

    });

    std::for_each(trees.begin(), trees.end(),[&child](ptree & children){
        child.push_back(std::make_pair("", children));
    });
    if(id==-1)tree.add_child("Game.croupier.cards", child);
    else tree.add_child("playerCards",child);

}

void json_gen::add_players(ptree & tree, std::vector<Player>players)
{
    ptree child;
    std::vector<ptree>trees;
    std::for_each(players.begin(),players.end(),[&trees,this](Player& player){
        auto children= ptree();
        children.put("mise", std::to_string(player.get_mise()));
        children.put("state", std::to_string(static_cast<int>(player.get_state())));
        children.put("score", std::to_string(player.get_score()));
        children.put("bank", std::to_string(player.get_bank()));
        children.put("id", std::to_string(player.get_server_id()));
        children.put("name", player.get_name());
        add_cards(children,player.get_hand(),player.get_server_id());
        trees.push_back(children);
    });
    std::for_each(trees.begin(),trees.end(), [&child](ptree & children){
        child.push_back(std::make_pair("",children ));
    });
    tree.add_child("Players",child);
}
std::stringstream & json_gen::generate_hit()
{
    ptree tree;
    tree.put("Type","HIT");
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;

}

std::stringstream & json_gen::generate_end_turn()
{
    ptree tree;
    tree.put("Type","END_TURN");
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}

std::stringstream & json_gen::generate_hit(Card & card)
{
    ptree tree;
    tree.put("Type","HIT");
    tree.put("Card.color", std::to_string(static_cast<int>(card.get_color())));
    tree.put("Card.value", std::to_string(card.get_value_card()));
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}

std::stringstream & json_gen::generate_end_round(){
    ptree tree;
    tree.put("Type","END_ROUND");
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}
std::stringstream & json_gen::generate_bet(int who,int amount){
    ptree tree;
    tree.put("Type","BET");
    tree.put("Amount",std::to_string(amount));
    tree.put("Who",std::to_string(who));
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}
std::stringstream & json_gen::generate_add_funds(int who,int amount){
    ptree tree;
    tree.put("Type","ADD_FUNDS");
    tree.put("Amount",std::to_string(amount));
    tree.put("Who",std::to_string(who));
    static std::stringstream input;
    input.flush();
    input.str("");
    boost::property_tree::json_parser::write_json(input,tree);
    return input;
}



