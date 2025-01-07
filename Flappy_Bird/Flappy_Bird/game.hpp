#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <windows.h>
#include <iostream>

class Game {
public:
	Game();
	void postaviPozicijuKursora(int x, int y);
	void postaviVidljivostKursora(bool vidljivost, DWORD velicina);
	void iscrtajOkvir();
	void generirajCijev(int ind);
	void iscrtajCijev(int ind);
	void izbrisiCijev(int ind);
	void iscrtajPtica();
	void izbrisiPtica();
	int detekcijaSudara();
	virtual void krajIgre();
	void azuzirajRezultat();
	void upute();
	void igraj();

	virtual int getRezultat() const { return rezultat; }

private:
	HANDLE konzola;
	COORD pozicijaKursora;
	int pozicijaPtice;
	int rezultat;
	std::vector<int> pozicijaCijevi;
	std::vector<int> pozicijaRupe;
	std::vector<bool> zastavaCijevi;
	char ptica[2][6];
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int WIN_WIDTH;
	const int GAP_SIZE;
};

class GameWithResult : public Game {
public:
	void krajIgre() override;
};

#endif
