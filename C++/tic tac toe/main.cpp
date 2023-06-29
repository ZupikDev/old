#include <iostream>
#include <assert.h>
#include <stddef.h>
#include <limits>
#include <map>


void tests() {

}

void print_line(std::map<int, std::string> line) {
	int counter = 0;
	for (int i = 0; i < 7; i++) {
		if (i % 2 == 0) std::cout << "|";
		else {
			std::cout << line[counter];
			counter++;
		}
	}
}

/*
void _test_print_map(std::map<int, std::string> x) {
	for (int i = 0; i < x.size(); i++) {
		std::cout << x[i] << " - ";
	}
	std::cout << "\n";
}  */

void print_world(std::map<int, std::string> world) {
	int counter = 0;
	std::map<int, std::string> map;

	for (int i = 0; i < 7; i++) {
		std::cout << "-";
	}
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			map[j] = world[counter];
			counter++;
		}
		print_line(map); std::cout << "\n";
	}
	for (int i = 0; i < 7; i++) {
		std::cout << "-";
	}
}

void reset_world(std::map<int, std::string>& world) {
	for (int i = 0; i < 9; i++) {
		world[i] = std::to_string(i + 1);
	}
}

template<typename T>
void sub_ask(T& output, std::string msg) {
	std::cout << msg;
	while (!(std::cin >> output)) {
		std::cout << "An error.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << msg;
	}
}


void ask(std::map<int, std::string>& world, int player) {
	int box = 0;
	do {
		sub_ask(box, "Enter the square to be played : ");
	} while (box < 1 || box > 9 || world[box - 1] == "x" || world[box - 1] == "o");
	if (player == 1) world[box - 1] = "x";
	else world[box - 1] = "o";
}

int check_if_playable(std::map<int, std::string> world) {
	// lines
	for (int i = 0; i < 3; i++) {
		if ((world[i * 3] == world[i * 3 + 1] && world[i * 3 + 1] == world[i * 3 + 2])
			&& world[i * 3] != " ") {
			return 0;
		}
	}
	// colums
	for (int i = 0; i < 3; i++) {
		if ((world[i] == world[i + 3] && world[i + 3] == world[i + 6])
			&& world[i] != " ") {
			return 0;
		}
	}
	// diag
	if (((world[0] == world[4] && world[4] == world[8]) || (world[2] == world[4] && world[4] == world[6]))
		&& world[4] != " ") {
		return 0;
	}

	// empty cases ?
	for (int i = 0; i < 9; i++) {
		if (world[i] == std::to_string(i + 1)) return 1;
	}

	return -1;

}


int main(void) {
	// add functions prototypes

	tests(); // to do

	int playable = 1;
	bool again = true;
	std::string player1, player2;

	sub_ask(player1, "Name of the player 1 : ");
	sub_ask(player2, "Name of the player 2 : ");

	std::map<int, std::string> world;

	do {
		reset_world(world);
		print_world(world); std::cout << "\n";
		while (playable == 1) {
			std::cout << player1 << " :\n";
			ask(world, 1);
			print_world(world); std::cout << "\n";
			playable = check_if_playable(world);
			if (playable == 0) {
				std::cout << player1 << " wins !\n";
				break;
			}
			if (playable == -1) {
				std::cout << "Tie !\n";
				break;
			}
			std::cout << player2 << " :\n";
			ask(world, 2);
			print_world(world); std::cout << "\n\n";
			playable = check_if_playable(world);
			if (playable == 0) {
				std::cout << player2 << " wins !\n";
				break;
			}
			if (playable == -1) {
				std::cout << "Tie !\n";
				break;
			}
		}

		sub_ask(again, "Another game ? ( 1/yes | 0/no ) : ");
		if (again == 1) playable = 1;
	} while (again == true);

}