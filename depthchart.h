#pragma once
#ifndef BASTA_DEPTHCHART_H
#define BASTA_DEPTHCHART_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>

struct Player {
	std::string name;
	int number; // jersey number
	int age;
	std::string country;
	std::string height;
	std::string weight;
};

// validation functions
int get_number(const std::string& prompt);
int get_menu_choice();
std::string get_required_text(const std::string& prompt);
std::vector<std::string> get_positions();
bool is_valid_position(const std::string& position);

//display and search functions
void display_all(const std::map<std::string, std::vector<Player> >& players);
void search_players(const std::map<std::string, std::vector<Player> >& players);
void show_starter(const std::map<std::string, std::vector<Player> >& players);
void show_starting_five(const std::map<std::string, std::vector<Player> >& players);

//modifying
void add_player(std::map<std::string, std::vector<Player> >& players, std::set<int>& used_numbers);
void remove_player(std::map<std::string, std::vector<Player> >& players, std::set<int>& used_numbers);
void update_player(std::map<std::string, std::vector<Player> >& players, std::set<int>& used_numbers);
void move_player(std::map<std::string, std::vector<Player> >& players);

//template display funtion
template <typename Display>
void display_template(const std::string& title, const Display& items) {
    std::cout << title << ": ";
    if (items.empty()) {
        std::cout << "(NULL)";
    } else {
        for (const auto& item : items) {
            std::cout << item << " ";
        }
    }
    std::cout << "\n";
}


#endif
