#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"

void GameWithResult::krajIgre() {
	Game::krajIgre();
	std::cout << "\tRezultat: " << getRezultat() << std::endl;
}

int main() {
	GameWithResult flappyBird;
	flappyBird.postaviVidljivostKursora(false, 0);
	srand(static_cast<unsigned>(time(NULL)));

	do {
		system("cls");
		flappyBird.postaviPozicijuKursora(10, 5);
		std::cout << " -------------------------- ";
		flappyBird.postaviPozicijuKursora(10, 6);
		std::cout << " |      Flappy Bird       | ";
		flappyBird.postaviPozicijuKursora(10, 7);
		std::cout << " --------------------------";
		flappyBird.postaviPozicijuKursora(10, 9);
		std::cout << "\t1. Pokreni igru";
		flappyBird.postaviPozicijuKursora(10, 10);
		std::cout << "\t2. Upute";
		flappyBird.postaviPozicijuKursora(10, 11);
		std::cout << "\t3. Izlaz";
		flappyBird.postaviPozicijuKursora(10, 13);
		std::cout << "\tOdaberi opciju: ";
		char opcija;
		std::cin >> opcija;

		if (opcija == '1') {
			try {
				flappyBird.igraj();
			}
			catch (const std::exception& ex) {
				std::cerr << "Exception caught: " << ex.what() << std::endl;
			}
		}
		else if (opcija == '2') {
			flappyBird.upute();
		}
		else if (opcija == '3') {
			exit(0);
		}
	} while (1);

	return 0;
}