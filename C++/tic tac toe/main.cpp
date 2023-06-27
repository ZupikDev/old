#include <iostream>
#include <assert.h>

const int SIZE = 3;

void print_line(int item[SIZE])
{
	int line_size = SIZE * SIZE - SIZE / 3 - 1;
	int compteur = 0;

	for (int i = 0; i < line_size; i++) {
		if (i % 2 == 0) std::cout << "|";
		else {
			switch (item[compteur]) {
			case 0:
				std::cout << " ";
				break;
			case 1:
				std::cout << "x";
				break;
			case 2:
				std::cout << "o";
				break;
			default:
				std::cout << "?";
				break;
			}
			compteur++;
		}
	}
}

void print_world(const int size, int items[SIZE][SIZE])
{
	int input[SIZE] = { 0 };
	int line_size = SIZE * SIZE - SIZE / 3 - 1;

	for (int i = 0; i < line_size; i++) {
		std::cout << "-";
	}
	std::cout << "\n";

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) input[j] = items[i][j];
		print_line(input);
		std::cout << "\n";
	}

	for (int i = 0; i < line_size; i++) {
		std::cout << "-";
	}
	
}

template<typename T>
void sub_ask(T &output, std::string msg) {
	std::cout << msg;
	while (!(std::cin >> output)) {
		std::cout << "An error.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << msg;
	}
}

void ask(int output[SIZE][SIZE], int player) {
	int line = 1, col = 1;
	do {
		do {
			sub_ask(line, "Enter the target line : ");
		} while (!(line > 0 && line <= 3));

		do {
			sub_ask(col, "Enter the target colum : ");
		} while (!(col > 0 && col <= 3));
	} while (output[line - 1][col - 1] != 0) ;

	output[line - 1][col - 1] = player;
}

int check_if_playable(int pos[SIZE][SIZE]) {
	// lines
	for (int i = 0; i < 3; i++) {
		if ((pos[i][0] == pos[i][1] && pos[i][1] == pos[i][2]) && pos[i][0] != 0) return 0;
	}
	// cols
	for (int i = 0; i < 3; i++) {
		if ((pos[0][i] == pos[1][i] && pos[1][i] == pos[2][i]) && pos[0][i] != 0) return 0;
	}
	// diagonals
	if (((pos[0][0] == pos[1][1] && pos[1][1] == pos[2][2])
		|| (pos[0][2] == pos[1][1] && pos[1][1] == pos[2][0])) && pos[1][1] != 0) return 0;

	// empty cases ? 
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (pos[i][j] == 0) count++;
		}
	}

	if (count > 0) return 1;
	return -1;
}

void change_line_test(int line_to_change, int arr[3][3], int num) {
	for (int i = 0; i < 3; i++) {
		arr[line_to_change][i] = num;
	}
}

void change_col_test(int col_to_change, int arr[3][3], int num) {
	for (int i = 0; i < 3; i++) {
		arr[i][col_to_change] = num;
	}
}

void tests() {
	/* Checks the 'check_if_playable' function */

	// lines
	int world[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		change_line_test(i, world, 1);
		assert(check_if_playable(world) == false);
		change_line_test(i, world, 0);
	}
	// cols
	for (int i = 0; i < 3; i++) {
		change_col_test(i, world, 1);
		assert(check_if_playable(world) == false);
		change_col_test(i, world, 0);
	}
	// diagonals
	world[0][0] = world[1][1] = world[2][2] = 1;
	assert(check_if_playable(world) == false);
	world[0][0] = 0; world[0][2] = world[2][0] = 1;
	assert(check_if_playable(world) == false);
}


int main(void) {
	void tests(void);
	void print_world(const int, int[SIZE][SIZE]);
	void ask(int[SIZE][SIZE], int);
	int check_if_playable(int[SIZE][SIZE]);

	tests();

	int playable = 1; // -1 = jeu nul | 0 = plus jouable | 1 = jouable | 
	std::string player1, player2;
	sub_ask(player1, "Name of the player 1 : ");
	sub_ask(player2, "Name of the player 2 : ");

	bool again = true;
	do {
		int positions[SIZE][SIZE] = {{ 0,0,0 },
									 { 0,0,0 },
									 { 0,0,0 } };
		print_world(SIZE, positions); std::cout << "\n";
		while (playable == 1)
		{
			std::cout << player1 << "\n";
			ask(positions, 1); std::cout << "\n";
			print_world(SIZE, positions); std::cout << "\n";
			playable = check_if_playable(positions);
			if (playable == 0) {
				std::cout << "Bravo à " << player1 << " !\n";
				break;
			}
			if (playable == -1) {
				std::cout << "jeu nul !\n";
				break;
			}
			std::cout << player2 << "\n";
			ask(positions, 2); std::cout << "\n";
			print_world(SIZE, positions); std::cout << "\n";
			playable = check_if_playable(positions);
			if (playable == 0) {
				std::cout << "Bravo à " << player2 << " !\n";
				break;
			}
			if (playable == -1) {
				std::cout << "jeu nul !\n";
				break;
			}
		}
		sub_ask(again, "Encore une partie ? (1 pour oui, 0 pour non) : ");
		if (again == 1) playable = 1;
	} while (again == true);

	return 0;
}