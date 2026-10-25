#include "depthchart.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

//validating
int get_number(const string& prompt){
	int number;
	while (true)
        {
                cout << prompt;
                if (cin >> number && number >= 0){
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return number; // valid number, clear stream and return number
                }

                cout << "Please enter a valid positive number\n";

                if (cin.eof()){
                        throw runtime_error("Input stream closed!");
                }

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
}

int get_menu_choice(){
	cout << "\nDEPTH CHART DIRECTORY\n"
	       << "---------------------\n"
	       << "1. Display Depth Chart\n"
	       << "2. Search for player by jersey number\n"
	       << "3. Display starter by entered position\n"
	       << "4. Display All Starters\n"
	       << "5. Add New Player\n"
	       << "6. Update Player\n"
	       << "7. Move Player\n"
	       << "8. Remove Player\n"
	       << "9. Check used numbers\n"
	       << "10. Exit\n\n";

	int choice;
        while (true) {
                choice = get_number("Choice: ");

                if (choice >=1 && choice <=10){
                        return choice;
                }

                cout << "Please choose an option from 1 to 10!\n";
        }
}

string get_required_text(const string& prompt){
	string text;

        while (true){
                cout << prompt;

                if (!getline(cin, text)){
                        throw runtime_error("Input stream closed!\n");
                }

                if (text.find_first_not_of(" \t") != string::npos){
                        return text;
                }

                cout << "This field cannot be empty!\n";
        }
}

vector<string> get_positions(){
	return {"PG", "SG", "SF", "PF", "C"};
}

bool is_valid_position(const string& position){
	vector<string> positions = get_positions();

	for (string pos : positions) {
        	if (pos == position) {
            	return true;
        	}
    	}

    	return false;
}

//display and search functions
void display_all(const map<string, vector<Player> >& players)
{
	cout << "\nDEPTH CHART\n"
	        <<"-----------\n";

	if (players.empty()) {
		cout << "No players found...\n";
		return;
	}

	cout << left << setw(10) << "Position" << setw(8) << "Depth" <<setw(25) << "Name" << setw(9) << "Number" << setw(7) << "Age" << setw(16) << "Country" <<
	setw(10) << "Height" << setw(10) << "Weight" << endl;

	//for (const auto& player : players){
	//	cout << left << setw(8) << player.first << setw(length) << player.name << setw(6) << player.number <<
	//	setw(3) << player.age << setw(length) << player.country << setw(8) << player.height << setw(8) <<
	//	player.weight << endl;
	//}

	//since i have a vector inside my map I couldn't print it the same as we normally do, so i had to ask ai for help,
	//it had me put it inside of another for loop that uses my get_positions function to get the players from each one
	//it also added a counter that says what place they are in their position
	// made the printed_any bool as well 

	bool printed_any = false;

	for (const auto& position : get_positions()) {
    		auto it = players.find(position);
    		if (it == players.end() || it->second.empty()) {
        		continue;   // nobody at this position, skip it
    		}
		cout << "----------------------------------------------------------------------------------------------\n";
    		int depth = 1;
    		for (const auto& player : it->second) {
        	cout << left << setw(10) << position
             	<< setw(8) << depth
             	<< setw(25) << player.name
             	<< setw(9) << player.number
             	<< setw(7) << player.age
             	<< setw(16) << player.country
             	<< setw(10) << player.height
             	<< setw(10) << player.weight << endl;
        	depth++;
        	printed_any = true;
    		}
	}

	if (!printed_any) {
    	cout << "The depth chart is empty." << endl;
	}
}

void search_players(const map<string, vector<Player> >& players)
{
	//once again took way too long to figure out because of the vector inside my map, since im searching through the indivual
	//vectors not the map itself the find() doesnt work, so I used if(player.number == number) instead to display the one ur searching for,
	// i put it in two for loops again because thats how i fixed the last problem, it didn't work at first but after i got rid of find()
	// and replaced it with the if statement it worked, i didnt feel like testing if the for loops actually did anything or if it was only
	//the find() that was the whole issue, the for loops were what ai wanted me to do to the last one but it made the posiitons go out of order
	// so i figured i would use them on this one instead because the order doesnt matter if its one person
	int number = get_number("Enter a player's number: ");

   	for (const auto& entry : players) {
        	for (const auto& player : entry.second) {
            		if (player.number == number) {
                		cout << "Player Found:\n"
                     		<< "Position: " << entry.first << endl
                     		<< "Name: " << player.name << endl
                     		<< "Age: " << player.age << endl
                     		<< "Number: " << player.number << endl
                     		<< "Country: " << player.country << endl
                     		<< "Height: " << player.height << endl
                     		<< "Weight: " << player.weight << endl;
                		return;
            	}
        }
    }

    cout << "Player not found...\n";
}

void show_starter(const map<string, vector<Player> >& players)
{
	//basically im asking for the position(pg,sg,sf,pf,c) and showing who is at the first position in whatever the user inputs
	// dont know how well it will work because the depth position was somethin gthat was declared in a function not in a struct so well see
	string starter = get_required_text("Enter the position of the starter you would like to view (PG, SG, SF, PF, C): ");

	auto it = players.find(starter);
	if(it != players.end() && !it->second.empty()){
		cout << "\nSTARTER\n"
		       << "-------\n" << it->second[0].name << endl;
	} else {
		cout << "Could not find starter at selected position, please make sure input is uppercase\n";
	}
}

void show_starting_five(const map<string, vector<Player> >& players)
{
	// same idea as the last function but theres no input it just shows who is at the first position in all five
	cout << left << setw(10) << "Position" << setw(24) << "Starter" << setw(8) << "Number\n"
	<< "---------------------------------------------\n";

	for (const auto& position : get_positions()) {
        	auto it = players.find(position);

        	if (it != players.end() && !it->second.empty()) {
            		const Player& starter = it->second[0];
            		cout << left << setw(10) << position
                 	<< setw(24) << starter.name
                 	<< setw(8) << starter.number << endl;
        	} else {
			cout << "Could not retrieve starting five..." << endl;
        	}
        }
}

//modifying
void add_player(map<string, vector<Player> >& players, set<int>& used_numbers)
{
	//get position
	string position = get_required_text("Enter position (PG, SG, SF, PF, C) or type 'exit' to leave: ");
	while (!is_valid_position(position))
	{
		cout << "Invalid position, please try again with uppercase letters or type 'exit' to leave" << endl;
		position = get_required_text("Enter position: ");
	} if (position == "exit"){
		return;
	}

	//get unique number
	int number = get_number("Enter jersey number: ");
    	while (number < 0 || used_numbers.count(number) > 0) {
        	cout << "That jersey number is already taken." << endl;
        	number = get_number("Enter jersey number: ");
    	}

    	//everything else
    	string name = get_required_text("Enter player name: ");

    	int age = get_number("Enter age: ");

    	string country = get_required_text("Enter country: ");

    	string height = get_required_text("Enter height (6'7\"): ");

    	string weight = get_required_text("Enter weight  (200 lbs): ");

    	//insert player, ai assisted
    	Player player = {name, number, age, country, height, weight};
    	players[position].push_back(player);
    	used_numbers.insert(number);

    	cout << name << "inserted successfully." << endl;
}

void remove_player(map<string, vector<Player> >& players, set<int>& used_numbers)
{
	string position = get_required_text("Enter position of the player to remove: ");

    	auto it = players.find(position);
    	if (it == players.end() || it->second.empty()) {
        	cout << "No players at that position." << endl;
        	return;
    	}
	// asked ai to display the players at the inputted position to show the user who to choose from
    	vector<Player>& depth_list = it->second;

    	cout << "Players at " << position << ":" << endl;
    	int depth = 1;
    	for (const auto& player : depth_list) {
        	cout << depth << ". " << player.name << " (#" << player.number << ")" << endl;
        	depth++;
    	}

    	int number = get_number("Enter jersey number of the player to remove: ");
	//needed ai for this, remove_if clears all the info but leaves blank leftover and brings anything after the chosen player to the front i believe, then the erase fully deletes
    	depth_list.erase(remove_if(depth_list.begin(), depth_list.end(),
        	         [number](const Player& p) { return p.number == number; }),
                	 depth_list.end());
    	used_numbers.erase(number);

    	cout << "Removed player #" << number << " from " << position << "." << endl;
}

void update_player(map<string, vector<Player> >& players, set<int>& used_numbers)
{
	string position = get_required_text("Enter position of the player to update: ");
    	while (position != "exit" && !is_valid_position(position)) {
        	cout << "Invalid position." << endl;
        	position = get_required_text("Enter position: ");
    	}
    	if (position == "exit") {
        	cout << "Update cancelled." << endl;
        	return;
    	}
	//check if the vector is empty
    	auto it = players.find(position);
    	if (it == players.end() || it->second.empty()) {
        	cout << "There are no players at " << position << "." << endl;
        	return;
    	}
//copied from the remove to display players in the vector
	vector<Player>& depth_list = it->second;

         cout << "Players at " << position << ":" << endl;
         int depth = 1;
         for (const auto& player : depth_list) {
                 cout << depth << ". " << player.name << " (#" << player.number << ")" << endl;
                 depth++;
         }


    	int number = get_number("Enter jersey number of the player to update: ");

    	auto found = find_if(it->second.begin(), it->second.end(),
        	            [number](const Player& p) { return p.number == number; });
    	if (found == it->second.end()) {
        	cout << "No player with number " << number << " at " << position << "." << endl;
        	return;
    	}

	//wanted another switch case and ai had me do it like this it recommended to do the iterator like this instead of using the -> on every case
    	Player& player = *found;

    	cout << "Updating " << player.name << " (#" << player.number << ")" << endl;
    	cout << "1. Name" << endl;
    	cout << "2. Jersey number" << endl;
    	cout << "3. Age" << endl;
    	cout << "4. Country" << endl;
    	cout << "5. Height" << endl;
    	cout << "6. Weight" << endl;

	//originally just copied it from main but had to swithc it to getnumber because it would display the maincpp menu because it used get_menu_choice
    	int choice = get_number("Choose what to update: ");
    	while (choice < 1 || choice > 6) {
        	cout << "Please choose 1 to 6." << endl;
        	choice = get_number("Choose what to update: ");
    	}

    	switch (choice) {
        	case 1:
            		player.name = get_required_text("Enter new name: ");
            		break;
            	//same validation so you dont pick a used number
        	case 2: {
            		int new_number = get_number("Enter new jersey number: ");
            		while (new_number < 0 || used_numbers.count(new_number) > 0) {
                		cout << "That number is negative or already in use." << endl;
                		new_number = get_number("Enter new jersey number: ");
            		}
            		used_numbers.erase(player.number);
            		used_numbers.insert(new_number);
            		player.number = new_number;
            		break;
        		}
        	case 3:
            		player.age = get_number("Enter new age: ");
            		break;
        	case 4:
            		player.country = get_required_text("Enter new country: ");
            		break;
        	case 5:
            		player.height = get_required_text("Enter new height: ");
            		break;
        	case 6:
            		player.weight = get_required_text("Enter new weight: ");
            		break;
    	}

    	cout << "Player updated." << endl;
}
//the start of all these is pretty much exactly the same and then the new stuff is at the end
void move_player(map<string, vector<Player> >& players)
{
	string position = get_required_text("Enter position of the player to move: ");

	auto it = players.find(position);
         if (it == players.end()) {
                 cout << "No players at that position." << endl;
                 return;
        }

//copied from the remove to display players in the vector
         vector<Player>& depth_list = it->second;

          cout << "Players at " << position << ":" << endl;
          int depth = 1;
          for (const auto& player : depth_list) {
                  cout << depth << ". " << player.name << " (#" << player.number << ")" << endl;
                  depth++;
          }

	int number = get_number("Enter jersey number of the player to move: ");

    	auto found = find_if(depth_list.begin(), depth_list.end(),
                         [number](const Player& p) { return p.number == number; });
    	if (found == depth_list.end()) {
        	cout << "No player with that number at " << position << "." << endl;
        	return;
    	}

    	string name = found->name;

    	cout << "1. Promote one spot" << endl;
    	cout << "2. Demote one spot" << endl;
    	cout << "3. Make starter" << endl;
    	int choice = get_number("Choose a move: ");
	//wasnt working how i wanted it so i pasted it into ai and it had me do this and also added the 'this player is already first or last stuff too'
    	if (choice == 1) {
        	if (found == depth_list.begin()) {
            	cout << name << " is already the starter." << endl;
        	} else {
            		swap(*found, *(found - 1)); //swap just makes them trade places
            		cout << name << " was promoted one spot." << endl;
        	}
    	} else if (choice == 2) {
        	if (found + 1 == depth_list.end()) {
            		cout << name << " is already last." << endl;
        	} else {
            		swap(*found, *(found + 1));
            	cout << name << " was demoted one spot." << endl;
        	}
    	} else if (choice == 3) {
        	if (found == depth_list.begin()) {
            		cout << name << " is already the starter." << endl;
        	} else {
            		rotate(depth_list.begin(), found, found + 1); // rotate takes 3 items from the vector begin, middle, end and makes the chosen one first
            		cout << name << " is now the starter." << endl;
        	}
    	} else {
        	cout << "Invalid choice." << endl;
    	}
}

