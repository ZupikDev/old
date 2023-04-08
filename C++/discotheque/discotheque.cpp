#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>

struct Morceau
{
	std::string morceau = "Morceau inconnu";
	std::string album = "Album inconnu";
	std::string artiste = "Artiste inconnu";
};

void input(std::string& var)
{
	while (!(std::getline(std::cin, var)))
	{
		std::cout << "Try again. : ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void remove_spaces(std::string& command)
{
	auto first_char = std::find_if_not(command.begin(), command.end(), isspace);
	command.erase(std::begin(command), first_char);
	command.reserve();
	first_char = std::find_if_not(command.begin(), command.end(), isspace);
	command.erase(std::begin(command), first_char);
	command.reserve();
}

std::vector<std::string> get_commands(std::string& string)
{
	std::string main_command; std::string command;
	std::vector<std::string> commands{};
	std::set<std::string> const set_commands{ "afficher", "ajouter", "quitter", "enregistrer", "charger" };
	auto first_space = std::find(std::begin(string), std::end(string), ' ');
	auto previous = std::find(std::begin(string), std::end(string), '|');
	auto old = first_space;

	// add the first word in main_command
	for (auto i = std::begin(string); i != first_space; ++i)
	{
		main_command += *i;
	}

	// if word is not in set_commands -> error
	if (set_commands.find(main_command) == std::end(set_commands))
	{
		throw std::runtime_error("La commande '" + main_command + "' n'existe pas.");
	}

	if (main_command == "quitter")
	{
		commands.push_back(main_command);
		return commands;
	}

	// if the only word in the input is "afficher" or "ajouter or "quitter"
	if (std::find(std::begin(string), std::end(string), ' ') == std::end(string))
	{
		remove_spaces(main_command);
		commands.push_back(main_command);
		return commands;
	}

	commands.push_back(main_command);

	// add all the finds values found in the input in commands
	while (previous != std::end(string))
	{
		for (auto i = old; i != previous - 1; ++i)
		{
			command += *i;
		}

		old = previous + 1;
		previous = std::find(old, std::end(string), '|');
		commands.push_back(command);
		command.clear();
	}

	// the last value in input
	for (auto i = old; i != std::end(string); ++i)
	{
		command += *i;
	}
	commands.push_back(command);

	// remove spaces from each commands
	for (auto& command : commands)
	{
		remove_spaces(command);
	}

	return commands;
}

Morceau ajouter_command(std::vector<std::string>const& commands)
{
	Morceau morceau;

	if (commands.size() == 4 && commands[2].size() != 0)
	{
		morceau.morceau = commands[1];
		morceau.album = commands[2];
		morceau.artiste = commands[3];
	}
	else if (commands.size() == 3)
	{
		morceau.morceau = commands[1];
		morceau.album = commands[2];
	}
	else if (commands.size() == 4 && commands[2].size() == 0)
	{
		morceau.morceau = commands[1];
		morceau.artiste = commands[3];
	}
	else if (commands.size() == 2)
	{
		morceau.morceau = commands[1];
	}
	else if (commands.size() > 4)
	{
		throw std::runtime_error("Trop d'informations.");;
	}

	return morceau;
}

std::ostream& operator<<(std::ostream& flux, const Morceau& var)
{
	return flux << "\nMorceau : " << var.morceau << "\nAlbum : " << var.album << "\nArtiste : " << var.artiste << std::endl;
}

bool operator!=(Morceau& left, Morceau& right)
{
	return !(left.morceau == right.morceau && left.album == right.album && left.artiste == right.artiste);
}

void afficher_albums(std::vector<Morceau>& morceaux)
{
	std::cout << "--> " << morceaux[0].album << " | " << morceaux[0].artiste << std::endl;
	for (auto morceau : morceaux)
	{
		std::cout << "    /--> " << morceau.morceau << std::endl;
	}
}

void afficher_artistes(std::string& found_albums, std::vector<std::string>& found_musics, std::string artist)
{
	std::cout << "--> " << artist << "\n    /--> " << found_albums << std::endl;
	for (auto music : found_musics)
	{
		std::cout << "        /--> " << music << std::endl;
	}
}

void afficher_command(std::vector<Morceau>& data, std::vector<std::string> const& commands)
{
	std::set<std::string> const possible_commands{ "morceaux", "albums", "artistes" };
	std::vector<Morceau> sorted;

	if (commands.size() <= 2)
	{
		if (std::find(std::begin(possible_commands), std::end(possible_commands), commands[1]) != std::end(possible_commands))
		{
			if (commands[1] == "morceaux")
			{
				std::sort(std::begin(data), std::end(data), [](Morceau& left, Morceau& right) -> bool {return left.morceau < right.morceau; });
				for (auto value : data)
				{
					std::cout << "--> " << value.morceau << " | " << value.album << " | " << value.artiste << std::endl;
				}
			}
			else if (commands[1] == "albums")
			{
				std::vector<std::string> taken_artists; std::vector<std::string> taken_albums;
				std::sort(std::begin(data), std::end(data), [](Morceau& left, Morceau& right) -> bool {return left.album < right.album; });
				for (auto& left : data)
				{
					for (auto& right : data)
					{
						if (left.album == right.album && left.artiste == left.artiste)
						{
							sorted.push_back(right);
						}
					}

					if (std::find(std::begin(taken_artists), std::end(taken_artists), left.artiste) == std::end(taken_artists) ||
						(std::find(std::begin(taken_albums), std::end(taken_albums), left.album) == std::end(taken_albums)))
					{
						taken_albums.push_back(left.album);
						taken_artists.push_back(left.artiste);
						afficher_albums(sorted);
					}

					sorted.clear();
				}
			}
			else
			{
				std::vector<std::string> found_albums; std::vector<std::string> found_musics;
				for (Morceau left : data)
				{
					for (Morceau right : data)
					{
						if (right.artiste == left.artiste && right.album == left.album)
						{
							found_musics.push_back(right.morceau);
						}
					}
					if (std::find(std::begin(found_albums), std::end(found_albums), left.album) == std::end(found_albums))
					{
						afficher_artistes(left.album, found_musics, left.artiste);
						found_albums.push_back(left.album);
					}

					found_musics.clear();
				}
			}
		}
		else
		{
			throw std::runtime_error("Commande inconnue.");
		}
	}
	else
	{
		throw std::runtime_error(u8"Trop d'informations entrées.");
	}
}

void enregistrer(std::vector<Morceau>& data, std::string const file_name)
{
	std::ofstream file(file_name);
	std::ifstream ifile(file_name);
	std::string _string = "";
	int count = 1;

	while (std::getline(ifile, _string))
	{
		if (count == 1) {
			if (_string.size() != 0)
			{
				file << "\n";
			}
			break;
		}
	}

	for (Morceau current_song : data)
	{
		file << current_song.morceau << ",";
		file << current_song.album << ",";
		file << current_song.artiste << ",";
		if (current_song != data.back())
		{
			file << "\n";
		}
	}
}

void charger(std::string file_name, std::vector<Morceau>& _where)
{
	std::ifstream file(file_name);
	std::string line = ""; std::string word = "";
	int count = 1;
	Morceau new_morceau;

	if (file.fail())
	{
		throw std::runtime_error("Le fichier n'existe pas.");
	}

	while (std::getline(file, line))
	{
		for (auto letter : line)
		{
			if (letter == ',')
			{
				switch (count)
				{
				case 1:
					new_morceau.morceau = word;
				case 2:
					new_morceau.album = word;
				case 3:
					new_morceau.artiste = word;
				default:
					break;
				}
				++count;
				word.clear();
			}
			else
			{
				word += letter;
			}
		}
		count = 1;
		_where.push_back(new_morceau);
		Morceau reset;
		new_morceau = reset;
	}
	
}

int main()
{
	std::vector<std::string> commands;
	std::vector<Morceau> morceaux;
	bool quit = false;

	do {
		try {
			std::cout << "> ";
			std::string in;
			input(in);
			commands = get_commands(in);

			if (commands[0] == "afficher")
			{
				afficher_command(morceaux, commands);
			}
			else if (commands[0] == "enregistrer")
			{
				if (commands.size() > 2 || commands.size() == 1)
				{
					throw std::runtime_error("Une erreur est survenue");
				}

				enregistrer(morceaux, commands[1]);

			}
			else if (commands[0] == "ajouter") {

				auto command = ajouter_command(commands);
				morceaux.push_back(command);
			}
			else if (commands[0] == "charger")
			{
				if (commands.size() > 2 || commands.size() == 1)
				{
					throw std::runtime_error("Une erreur est survenue.");
				}

				std::string file_name = commands[1];

				charger(file_name, morceaux);
			}
			else
			{
				quit = true;
			}
		}
		catch (std::runtime_error const& except)
		{
			std::cout << except.what() << std::endl;
			continue;
		}
	} while (!quit);

	return 0;
}
