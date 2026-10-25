#include <iostream>
#include <stdexcept>
#include "depthchart.h"

using namespace std;

int main()
{
	// used ai to fill out the whole team, cause i aint typin allthat
	map<string, vector<Player> > players {
		{"PG", {
		{"LaMelo Ball", 1, 25, "USA", "6'7\"", "180 lbs"},
		{"Zyon Pullin", 15, 25, "USA", "6'4\"", "206 lbs"},
		{"Bones Hyland", 8, 26, "USA", "6'2\"", "169 lbs"}
		}},
		{"SG", {
		{"Anthony Edwards", 5, 25, "USA", "6'4\"", "225 lbs"},
		{"Ayo Dosunmu", 13, 26, "USA", "6'4\"", "201 lbs"},
		{"Jaylen Clark", 7, 25, "USA", "6'5\"", "205 lbs"},
		{"Donte DiVincenzo", 0, 29, "USA", "6'4\"", "203 lbs"}
		}},
		{"SF", {
		{"Jaden McDaniels", 3, 26, "USA", "6'9\"", "185 lbs"},
		{"Terrence Shannon Jr.", 4, 26, "USA", "6'6\"", "215 lbs"},
		{"Isaiah Evans", 33, 20, "USA", "6'6\"", "175 lbs"}
		}},
		{"PF", {
		{"Jonathan Kuminga", 24, 24, "DR Congo", "6'7\"", "225 lbs"},
		{"Cody Williams", 9, 21, "USA", "6'8\"", "190 lbs"},
		{"Trey Lyles", 41, 30, "Canada", "6'9\"", "234 lbs"}
		}},
		{"C", {
		{"Rudy Gobert", 27, 34, "France", "7'1\"", "258 lbs"},
		{"Joan Beringer", 19, 19, "France", "6'11\"", "230 lbs"},
		{"Rocco Zikarsky", 44, 20, "Australia", "7'3\"", "227 lbs"}
		}}
	};
	set<int> used_numbers;
	//ai had to add this because this only would work on numbers you added not the preloaded ones
	for (const auto& entry : players) {
    		for (const auto& player : entry.second) {
        		used_numbers.insert(player.number);
    		}
	}
	try {
		int choice = 1;
		while (choice != 10){
			choice = get_menu_choice();

			switch(choice){
				case 1:
					display_all(players);
					break;
				case 2:
					search_players(players);
					break;
				case 3:
					show_starter(players);
					break;
				case 4:
					show_starting_five(players);
					break;
				case 5:
					add_player(players, used_numbers);
					break;
				case 6:
					update_player(players, used_numbers);
					break;
				case 7:
					move_player(players);
					break;
				case 8:
					remove_player(players, used_numbers);
					break;
				case 9:
					display_template("Jersey Numbers in use: ", used_numbers);
					break;
			}
		}
	}
	catch (const runtime_error& e){
                cout << "Error: " << e.what() << endl;
        }
        return 0;

}


















