contianers:
My first container was the map obviously: it took a string as the key which was the player's positions which let you look up and separate each position,
then the value was a vector which had 3-4 players with the index[0] being the starter and foloowing thayt was the backups

2nd container was a set of integers called used_numbers to hold the used numbers and make sure there were no duplicates

then i had a 3rd which was another vector of strings that held the five basketball posiitons which was used for validation and for making sure they printed in order

algorithms:
i used a find_if with the lambda to find the player with the entered number
i used a remove_if and erase with the lambda to delete players
i used a rotate and swap in my move player function to move players in the index, rotate moves the selected all the way to the first index and swap switches two values

lambda:
[number](const Player& p) { return p.number == number; }
it took the inputted number and then found the player with that same number, it would return that player as true if it found a match or false if it didnt
it was used in the find_if and remove_if algorithms

also forgot to use that template display function so i added a 9th option to just display the used numbers using it at the very end after i finished everything
