#include "game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

template <typename T>
class CircularBuffer {
public:
	CircularBuffer(size_t capacity) : capacity(capacity) {
		buffer.reserve(capacity);
	}

	void addResult(T result) {
		if (buffer.size() >= capacity) {
			throw std::overflow_error("Circular buffer overflow");
		}
		buffer.push_back(result);
	}

private:
	size_t capacity;
	std::vector<T> buffer;
};

Game::Game() : SCREEN_WIDTH(90), SCREEN_HEIGHT(26), WIN_WIDTH(70), GAP_SIZE(7) {
	konzola = GetStdHandle(STD_OUTPUT_HANDLE);
	pozicijaCijevi = { 3, 3 };
	pozicijaRupe = { 3, 3 };
	zastavaCijevi = { true, false };

	ptica[0][0] = '/';
	ptica[0][1] = '-';
	ptica[0][2] = '-';
	ptica[0][3] = 'o';
	ptica[0][4] = '\\';
	ptica[0][5] = ' ';

	ptica[1][0] = '|';
	ptica[1][1] = '_';
	ptica[1][2] = '_';
	ptica[1][3] = '_';
	ptica[1][4] = ' ';
	ptica[1][5] = '>';
}

void Game::postaviPozicijuKursora(int x, int y) {
	pozicijaKursora.X = x;
	pozicijaKursora.Y = y;
	SetConsoleCursorPosition(konzola, pozicijaKursora);
}

void Game::postaviVidljivostKursora(bool vidljivost, DWORD velicina) {
	if (velicina == 0)
		velicina = 20;

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = vidljivost;
	cursorInfo.dwSize = velicina;
	SetConsoleCursorInfo(konzola, &cursorInfo);
}

void Game::iscrtajOkvir() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		postaviPozicijuKursora(i, 0); std::cout << "±";
		postaviPozicijuKursora(i, SCREEN_HEIGHT); std::cout << "±";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		postaviPozicijuKursora(0, i); std::cout << "±";
		postaviPozicijuKursora(SCREEN_WIDTH, i); std::cout << "±";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		postaviPozicijuKursora(WIN_WIDTH, i); std::cout << "±";
	}
}

void Game::generirajCijev(int ind) {
	pozicijaRupe[ind] = 3 + rand() % 14;
}

void Game::iscrtajCijev(int ind) {
	if (zastavaCijevi[ind]) {
		for (int i = 0; i < pozicijaRupe[ind]; i++) {
			postaviPozicijuKursora(WIN_WIDTH - pozicijaCijevi[ind], i + 1); std::cout << "***";
		}

		for (int i = pozicijaRupe[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
			postaviPozicijuKursora(WIN_WIDTH - pozicijaCijevi[ind], i + 1); std::cout << "***";
		}
	}
}

void Game::izbrisiCijev(int ind) {
	if (zastavaCijevi[ind]) {
		for (int i = 0; i < pozicijaRupe[ind]; i++) {
			postaviPozicijuKursora(WIN_WIDTH - pozicijaCijevi[ind], i + 1); std::cout << "   ";
		}

		for (int i = pozicijaRupe[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
			postaviPozicijuKursora(WIN_WIDTH - pozicijaCijevi[ind], i + 1); std::cout << "   ";
		}
	}
}

void Game::iscrtajPtica() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			postaviPozicijuKursora(j + 2, i + pozicijaPtice); std::cout << ptica[i][j];
		}
	}
}

void Game::izbrisiPtica() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			postaviPozicijuKursora(j + 2, i + pozicijaPtice); std::cout << " ";
		}
		postaviPozicijuKursora(8, i + pozicijaPtice); std::cout << " ";
	}
}

int Game::detekcijaSudara() {
	if (pozicijaCijevi[0] >= 61) {
		if (pozicijaPtice < pozicijaRupe[0] || pozicijaPtice > pozicijaRupe[0] + GAP_SIZE) {
			return 1;
		}
	}
	return 0;
}

void Game::krajIgre() {
	system("cls");
	std::cout << "\n\t\t--------------------------" << std::endl;
	std::cout << "\t\t-------- Kraj igre -------" << std::endl;
	std::cout << "\t\t--------------------------" << std::endl << std::endl;
	std::cout << "\t\t\tRezultat: " << rezultat << std::endl;
	std::cout << "\n\tPritisnite bilo koju tipku za povratak u izbornik.";
	_getch();
}

void Game::azuzirajRezultat() {
	postaviPozicijuKursora(WIN_WIDTH + 7, 5); std::cout << "Rezultat: " << rezultat << std::endl;
}

void Game::upute() {
	system("cls");
	std::cout << "Upute";
	std::cout << "\n----------------";
	std::cout << "\n Pritisnite spacebar za skakanje ptice";
	std::cout << "\n\nPritisnite bilo koju tipku za povratak u izbornik";
	_getch();
}

void Game::igraj() {
	pozicijaPtice = 6;
	rezultat = 0;
	zastavaCijevi[0] = 1;
	zastavaCijevi[1] = 0;
	pozicijaCijevi[0] = pozicijaCijevi[1] = 4;

	system("cls");
	iscrtajOkvir();
	generirajCijev(0);
	azuzirajRezultat();

	postaviPozicijuKursora(WIN_WIDTH + 5, 2); std::cout << "  FLAPPY BIRD";
	postaviPozicijuKursora(WIN_WIDTH + 6, 4); std::cout << "-------------";
	postaviPozicijuKursora(WIN_WIDTH + 6, 6); std::cout << "-------------";
	postaviPozicijuKursora(WIN_WIDTH + 7, 12); std::cout << "  Kontrole ";
	postaviPozicijuKursora(WIN_WIDTH + 7, 13); std::cout << "  -------- ";
	postaviPozicijuKursora(WIN_WIDTH + 2, 14); std::cout << "   Spacebar = skok";

	postaviPozicijuKursora(10, 5); std::cout << "Pritisnite bilo koju tipku za pocetak";
	_getch();
	postaviPozicijuKursora(10, 5); std::cout << "                                             ";

	while (1) {
		if (kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (pozicijaPtice > 3)
					pozicijaPtice -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		iscrtajPtica();
		iscrtajCijev(0);
		iscrtajCijev(1);
		if (detekcijaSudara() == 1) {
			krajIgre();
			return;
		}
		Sleep(100);
		izbrisiPtica();
		izbrisiCijev(0);
		izbrisiCijev(1);
		pozicijaPtice += 1;

		if (pozicijaPtice > SCREEN_HEIGHT - 2) {
			krajIgre();
			return;
		}

		if (zastavaCijevi[0] == 1)
			pozicijaCijevi[0] += 2;

		if (zastavaCijevi[1] == 1)
			pozicijaCijevi[1] += 2;

		if (pozicijaCijevi[0] >= 40 && pozicijaCijevi[0] < 42) {
			zastavaCijevi[1] = 1;
			pozicijaCijevi[1] = 4;
			generirajCijev(1);
		}
		if (pozicijaCijevi[0] > 68) {
			rezultat++;
			azuzirajRezultat();
			zastavaCijevi[1] = 0;
			pozicijaCijevi[0] = pozicijaCijevi[1];
			pozicijaRupe[0] = pozicijaRupe[1];
		}
	}
}