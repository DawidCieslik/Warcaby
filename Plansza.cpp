#include "Plansza.h"

int Plansza::LiczbaBialych = 12;
int Plansza::LiczbaCzarnych = 12;
int Plansza::Rundy = 30;

Plansza::Plansza()
{
	this->pHead = nullptr;
	this->pPionek = nullptr;
}

Plansza::~Plansza()
{
	while (pHead)
	{
		ListaPol* temp = pHead->pNext;
		delete pHead;
		pHead = temp;
	}
	while (pPionek)
	{
		ListaPionkow* temp = pPionek->pNext;
		delete pPionek;
		pPionek = temp;
	}
}

Pionek& Plansza::DajPionka(int x, int y)
{
	ListaPionkow* temp = pPionek;
	while (temp)
	{
		if (temp->pionek.PodajX() == x && temp->pionek.PodajY() == y)
			return temp->pionek;
		temp = temp->pNext;
	}
	Blad(1);
}

Pole& Plansza::DajPole(int x, int y)
{
	ListaPol* temp = pHead;
	while (temp)
	{
		if (temp->pole.PodajX() == x && temp->pole.PodajY() == y)
			return temp->pole;
		temp = temp->pNext;
	}
	Blad(1);
}

void Plansza::InicjalizujPlansze()
{
	for (int y = 0; y < RozmiarPlanszy; y++)
	{
		for (int x = 0; x < RozmiarPlanszy; x++)
		{
			ListaPol* NowePole = new ListaPol;
			ListaPionkow* NowyPionek = new ListaPionkow;
			NowePole->pole.UstawX(x);
			NowePole->pole.UstawY(y);
			NowyPionek->pionek.UstawX(x);
			NowyPionek->pionek.UstawY(y);
			if ((x + y) % 2 == 0)
			{
				NowePole->pole.Kolor(jasny);
				NowyPionek->pionek.typ = BLAD;
			}
			else if ((x + y) % 2 == 1)
			{
				NowePole->pole.Kolor(ciemny);
				if (y >= 0 && y <= 2)
				{
					NowyPionek->pionek.typ = CZARNY_PIONEK;
					NowyPionek->pionek.Promien();
					NowyPionek->pionek.Kontur();
					NowyPionek->pionek.KolorKonturu(czarny);
					NowyPionek->pionek.Kolor(sf::Color::Black);
					NowyPionek->pionek.Pozycja(x, y);
				}
				else if (y >= 5 && y <= 7)
				{
					NowyPionek->pionek.typ = BIALY_PIONEK;
					NowyPionek->pionek.Promien();
					NowyPionek->pionek.Kontur();
					NowyPionek->pionek.KolorKonturu(czarny);
					NowyPionek->pionek.Kolor(sf::Color::White);
					NowyPionek->pionek.Pozycja(x, y);
				}
			}
			NowePole->pole.Pozycja(x, y);
			(*this) += NowePole;
			(*this) += NowyPionek;
		}
	}
}

void Plansza::WyswietlPlansze(sf::RenderWindow &window)
{
	for (int y = 0; y < RozmiarPlanszy; y++)
	{
		for (int x = 0; x < RozmiarPlanszy; x++)
		{
			window.draw(DajPole(x, y).Ksztalt());
			window.draw(DajPionka(x, y).Ksztalt());
		}
	}
}

void Plansza::PokazZasieg(int& x, int& y, bool& bicie)
{
	//RYSOWANIE MO¯LIWYCH RUCHÓW PIONKA
	if (x != -1 && y != -1)
	{
		if (DajPionka(x, y).typ != BLAD && DajPionka(x, y).typ != PUSTE)
		{
			DajPionka(x, y).KolorKonturu(czerwony);

			//BIA£Y PIONEK
			if (DajPionka(x, y).typ == BIALY_PIONEK)
			{
				if (x >= 1 && y >= 1)
				{
					if (bicie == false && DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(czerwony);					//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
						if ((DajPionka(x - 1,y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1,y - 1).typ == CZARNA_DAMKA) && (DajPionka(x - 2,y - 2).typ == PUSTE))
							DajPole(x - 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y >= 1)
				{
					if (bicie == false && DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(czerwony);					//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
						if ((DajPionka(x + 1,y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1,y - 1).typ == CZARNA_DAMKA) && (DajPionka(x + 2,y - 2).typ == PUSTE))
							DajPole(x + 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
				}
			}

			//BIA£A DAMKA
			if (DajPionka(x, y).typ == BIALA_DAMKA)
			{
				if (x >= 1 && y <= 6)
				{
					if (bicie == false && DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(czerwony);					//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
						if ((DajPionka(x - 1,y + 1).typ == CZARNY_PIONEK || DajPionka(x - 1,y + 1).typ == CZARNA_DAMKA) && (DajPionka(x - 2,y + 2).typ == PUSTE))
							DajPole(x - 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y <= 6)
				{
					if (bicie == false && DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(czerwony);					//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
						if ((DajPionka(x + 1,y + 1).typ == CZARNY_PIONEK || DajPionka(x + 1,y + 1).typ == CZARNA_DAMKA) && (DajPionka(x + 2,y + 2).typ == PUSTE))
							DajPole(x + 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
				}
				if (x >= 1 && y >= 1)
				{
					if (bicie == false && DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(czerwony);					//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
						if ((DajPionka(x - 1,y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1,y - 1).typ == CZARNA_DAMKA) && (DajPionka(x - 2,y - 2).typ == PUSTE))
							DajPole(x - 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y >= 1)
				{
					if (bicie == false && DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(czerwony);					//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
						if ((DajPionka(x + 1,y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1,y - 1).typ == CZARNA_DAMKA) && (DajPionka(x + 2,y - 2).typ == PUSTE))
							DajPole(x + 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
				}
			}

			//CZARNY PIONEK
			if (DajPionka(x, y).typ == CZARNY_PIONEK)
			{
				if (x >= 1 && y <= 6)
				{
					if (bicie == false && DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(czerwony);					//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
						if((DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA) && (DajPionka(x - 2, y + 2).typ == PUSTE))
							DajPole(x - 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y <= 6)
				{
					if (bicie == false && DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(czerwony);					//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
						if((DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA) && (DajPionka(x + 2, y + 2).typ == PUSTE))
							DajPole(x + 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
				}
			}

			//CZARNA DAMKA
			if (DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x >= 1 && y <= 6)
				{
					if (bicie == false && DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(czerwony);					//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
						if((DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA) && (DajPionka(x - 2, y + 2).typ == PUSTE))
							DajPole(x - 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y <= 6)
				{
					if (bicie == false && DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(czerwony);					//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
						if((DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA) && (DajPionka(x + 2, y + 2).typ == PUSTE))
							DajPole(x + 2, y + 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
				}
				if (x >= 1 && y >= 1)
				{
					if (bicie == false && DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(czerwony);					//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
						if((DajPionka(x - 1, y - 1).typ == BIALY_PIONEK || DajPionka(x - 1, y - 1).typ == BIALA_DAMKA) && (DajPionka(x - 2, y - 2).typ == PUSTE))
							DajPole(x - 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
				}
				if (x <= 6 && y >= 1)
				{
					if (bicie == false && DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(czerwony);					//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
						if((DajPionka(x + 1, y - 1).typ == BIALY_PIONEK || DajPionka(x + 1, y - 1).typ == BIALA_DAMKA) && (DajPionka(x + 2, y - 2).typ == PUSTE))
							DajPole(x + 2, y - 2).Kolor(czerwony);				//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
				}
			}
		}
	}
}

void Plansza::UsunZaznaczenie(int& x, int& y)
{
	//ODZNACZENIE MO¯LIWYCH RUCHÓW PIONKA
	if (x != -1 && y != -1)
	{
		if (DajPionka(x, y).typ != BLAD && DajPionka(x, y).typ != PUSTE)
		{
			if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == CZARNY_PIONEK)
				DajPionka(x, y).KolorKonturu(czarny);
			else if (DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNA_DAMKA)
				DajPionka(x, y).KolorKonturu(zolty);

			//BIA£Y PIONEK
			if (DajPionka(x, y).typ == BIALY_PIONEK)
			{
				if (x >= 1 && y >= 1)
				{
					if (DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(ciemny);				//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
					{
						if (DajPionka(x - 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y - 1).typ == CZARNA_DAMKA)
							DajPole(x - 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y >= 1)
				{
					if (DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(ciemny);				//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
					{
						if (DajPionka(x + 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y - 1).typ == CZARNA_DAMKA)
							DajPole(x + 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
					}
				}
			}

			//BIA£A DAMKA
			if (DajPionka(x, y).typ == BIALA_DAMKA)
			{
				if (x >= 1 && y <= 6)
				{
					if (DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(ciemny);				//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
					{
						if (DajPionka(x - 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y + 1).typ == CZARNA_DAMKA)
							DajPole(x - 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y <= 6)
				{
					if (DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(ciemny);				//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
					{
						if (DajPionka(x + 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y + 1).typ == CZARNA_DAMKA)
							DajPole(x + 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
					}
				}
				if (x >= 1 && y >= 1)
				{
					if (DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(ciemny);				//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
					{
						if (DajPionka(x - 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y - 1).typ == CZARNA_DAMKA)
							DajPole(x - 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y >= 1)
				{
					if (DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(ciemny);				//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
					{
						if (DajPionka(x + 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y - 1).typ == CZARNA_DAMKA)
							DajPole(x + 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
					}
				}
			}

			//CZARNY PIONEK
			if (DajPionka(x, y).typ == CZARNY_PIONEK)
			{
				if (x >= 1 && y <= 6)
				{
					if (DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(ciemny);				//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
					{
						if (DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA)
							DajPole(x - 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y <= 6)
				{
					if (DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(ciemny);				//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
					{
						if (DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA)
							DajPole(x + 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
					}
				}
			}

			//CZARNA DAMKA
			if (DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x >= 1 && y <= 6)
				{
					if (DajPionka(x - 1, y + 1).typ == PUSTE)
						DajPole(x - 1, y + 1).Kolor(ciemny);				//DOLNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y <= 5)
					{
						if (DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA)
							DajPole(x - 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y <= 6)
				{
					if (DajPionka(x + 1, y + 1).typ == PUSTE)
						DajPole(x + 1, y + 1).Kolor(ciemny);				//DOLNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y <= 5)
					{
						if (DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA)
							DajPole(x + 2, y + 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEKATNEJ
					}
				}
				if (x >= 1 && y >= 1)
				{
					if (DajPionka(x - 1, y - 1).typ == PUSTE)
						DajPole(x - 1, y - 1).Kolor(ciemny);				//GÓRNA LEWA PRZEK¥TNA PUSTA
					else if (x >= 2 && y >= 2)
					{
						if (DajPionka(x - 1, y - 1).typ == BIALY_PIONEK || DajPionka(x - 1, y - 1).typ == BIALA_DAMKA)
							DajPole(x - 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEKATNEJ
					}
				}
				if (x <= 6 && y >= 1)
				{
					if (DajPionka(x + 1, y - 1).typ == PUSTE)
						DajPole(x + 1, y - 1).Kolor(ciemny);				//GÓRNA PRAWA PRZEK¥TNA PUSTA
					else if (x <= 5 && y >= 2)
					{
						if (DajPionka(x + 1, y - 1).typ == BIALY_PIONEK || DajPionka(x + 1, y - 1).typ == BIALA_DAMKA)
							DajPole(x + 2, y - 2).Kolor(ciemny);			//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEKATNEJ
					}
				}
			}
		}
	}
}

bool Plansza::SprawdzPozycje(int& x, int& y, Kierunek& kierunek)
{
	if (kierunek == GL)
		if (x >= 1 && y >= 1)
			if (DajPionka(x - 1, y - 1).typ != PUSTE)
				return true;
	if (kierunek == GP)
		if (x <= 6 && y >= 1)
			if (DajPionka(x + 1, y - 1).typ != PUSTE)
				return true;
	if (kierunek == DP)
		if (x <= 6 && y <= 6)
			if (DajPionka(x + 1, y + 1).typ != PUSTE)
				return true;
	if (kierunek == DL)
		if (x >= 1 && y <= 6)
			if (DajPionka(x - 1, y + 1).typ != PUSTE)
				return true;
	if (kierunek == GL2)
		if (x >= 2 && y >= 2)
			if (DajPionka(x - 2, y - 2).typ != PUSTE)
				return true;
	if (kierunek == GP2)
		if (x <= 5 && y >= 2)
			if (DajPionka(x + 2, y - 2).typ != PUSTE)
				return true;
	if (kierunek == DP2)
		if (x <= 5 && y <= 5)
			if (DajPionka(x + 2, y + 2).typ != PUSTE)
				return true;
	if (kierunek == DL2)
		if (x >= 2 && y <= 5)
			if (DajPionka(x - 2, y + 2).typ != PUSTE)
				return true;
	return false;
}

Kierunek Plansza::LosujKierunek(int& x, int& y, Kierunek& kierunek, bool& bialy_czarny)
{
	int direction = 0;

	bool gl = false;
	bool gp = false;
	bool dp = false;
	bool dl = false;
	bool gl2 = false;
	bool gp2 = false;
	bool dp2 = false;
	bool dl2 = false;

	while (gl == false || gp == false || dp == false || dl == false || gl2 == false || gp2 == false || dp2 == false || dl2 == false)
	{
		direction = rand() % 8;

		if (gl == false && direction == 0 && x >= 1 && y >= 1)
		{
			gl = true;
			if (DajPionka(x - 1, y - 1).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) == sf::Vector2i(-1, -1))
				{
					kierunek = GL;
					break;
				}
			}
		}
		if (gp == false && direction == 1 && x <= 6 && y >= 1)
		{
			gp = true;
			if (DajPionka(x + 1, y - 1).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) == sf::Vector2i(-1, -1))
				{
					kierunek = GP;
					break;
				}
			}
		}
		if (dp == false && direction == 2 && x <= 6 && y <= 6)
		{
			dp = true;
			if (DajPionka(x + 1, y + 1).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) == sf::Vector2i(-1, -1))
				{
					kierunek = DP;
					break;
				}
			}
		}
		if (dl == false && direction == 3 && x >= 1 && y <= 6)
		{
			dl = true;
			if (DajPionka(x - 1, y + 1).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) == sf::Vector2i(-1, -1))
				{
					kierunek = DL;
					break;
				}
			}
		}
		if (gl2 == false && direction == 4 && x >= 2 && y >= 2)
		{
			gl2 = true;
			if (DajPionka(x - 2, y - 2).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) != sf::Vector2i(-1, -1))
				{
					kierunek = GL2;
					break;
				}
			}
		}
		if (gp2 == false && direction == 5 && x <= 5 && y >= 2)
		{
			gp2 = true;
			if (DajPionka(x + 2, y - 2).typ == PUSTE)
			{
				if (MozliwoscBicia(bialy_czarny) != sf::Vector2i(-1, -1))
				{
					kierunek = GP2;
					break;
				}
			}
		}
		if (dp2 == false && direction == 6 && x <= 5 && y <= 5)
		{
			dp2 = true;
			if (MozliwoscBicia(bialy_czarny) != sf::Vector2i(-1, -1))
			{
				kierunek = DP2;
				break;
			}
		}
		if (dl2 == false && direction == 7 && x >= 2 && y <= 5)
		{
			dl2 = true;
			if (MozliwoscBicia(bialy_czarny) != sf::Vector2i(-1, -1))
			{
				kierunek = DL2;
				break;
			}
		}
		else
		{
			kierunek = Kierunek::BRAK;
			break;
		}
	}
	return kierunek;
}

bool Plansza::PrzesunPionka(int& tura, bool& bicie, bool& ruch, int& x, int& y, int& NoweX, int& NoweY, Kierunek& kierunek)
{
	if (kierunek == GL)															//GÓRNA LEWA PRZEK¥TNA
	{
		if (bicie == false)
		{
			if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x >= 1 && y >= 1)
				{
					if (DajPole(x - 1, y - 1).Ksztalt().getFillColor() == czerwony)
					{
						if (DajPionka(x - 1, y - 1).typ == PUSTE)
						{
							UsunZaznaczenie(x, y);

							//ZMIANA TYPU PIONKA
							if (DajPionka(x, y).typ == BIALY_PIONEK)
								DajPionka(x - 1, y - 1).typ = BIALY_PIONEK;
							else if (DajPionka(x, y).typ == BIALA_DAMKA)
								DajPionka(x - 1, y - 1).typ = BIALA_DAMKA;
							else if (DajPionka(x, y).typ == CZARNA_DAMKA)
								DajPionka(x - 1, y - 1).typ = CZARNA_DAMKA;

							DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

							DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
							DajPionka(x - 1, y - 1).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

							NoweX = x - 1;
							NoweY = y - 1;

							ruch = true;

							Rundy--;

							return true;
						}
					}
				}
			}
		}
	}
	else if (kierunek == GP)													//GÓRNA PRAWA PRZEK¥TNA
	{
		if (bicie == false)
		{
			if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x <= 6 && y >= 1)
				{
					if (DajPole(x + 1, y - 1).Ksztalt().getFillColor() == czerwony)
					{
						if (DajPionka(x + 1, y - 1).typ == PUSTE)
						{
							UsunZaznaczenie(x, y);

							//ZMIANA TYPU POLA
							if (DajPionka(x, y).typ == BIALY_PIONEK)
								DajPionka(x + 1, y - 1).typ = BIALY_PIONEK;
							else if (DajPionka(x, y).typ == BIALA_DAMKA)
								DajPionka(x + 1, y - 1).typ = BIALA_DAMKA;
							else if (DajPionka(x, y).typ == CZARNA_DAMKA)
								DajPionka(x + 1, y - 1).typ = CZARNA_DAMKA;

							DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

							DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
							DajPionka(x + 1, y - 1).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

							NoweX = x + 1;
							NoweY = y - 1;

							ruch = true;

							Rundy--;

							return true;
						}
					}
				}
			}
		}
	}
	else if (kierunek == DP)													//DOLNA PRAWA PRZEK¥TNA
	{
		if (bicie == false)
		{
			if (DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x <= 6 && y <= 6)
				{
					if (DajPole(x + 1, y + 1).Ksztalt().getFillColor() == czerwony)
					{
						if (DajPionka(x + 1, y + 1).typ == PUSTE)
						{
							UsunZaznaczenie(x, y);

							//ZMIANA TYPU POLA
							if (DajPionka(x, y).typ == CZARNY_PIONEK)
								DajPionka(x + 1, y + 1).typ = CZARNY_PIONEK;
							else if (DajPionka(x, y).typ == BIALA_DAMKA)
								DajPionka(x + 1, y + 1).typ = BIALA_DAMKA;
							else if (DajPionka(x, y).typ == CZARNA_DAMKA)
								DajPionka(x + 1, y + 1).typ = CZARNA_DAMKA;

							DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

							DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
							DajPionka(x + 1, y + 1).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

							NoweX = x + 1;
							NoweY = y + 1;

							ruch = true;

							Rundy--;

							return true;
						}
					}
				}
			}
		}
	}
	else if (kierunek == DL)													//DOLNA LEWA PRZEK¥TNA
	{
		if (bicie == false)
		{
			if (DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
			{
				if (x >= 1 && y <= 6)
				{
					if (DajPole(x - 1, y + 1).Ksztalt().getFillColor() == czerwony)
					{
						if (DajPionka(x - 1, y + 1).typ == PUSTE)
						{
							UsunZaznaczenie(x, y);

							//ZMIANA TYPU POLA
							if (DajPionka(x, y).typ == CZARNY_PIONEK)
								DajPionka(x - 1, y + 1).typ = CZARNY_PIONEK;
							else if (DajPionka(x, y).typ == BIALA_DAMKA)
								DajPionka(x - 1, y + 1).typ = BIALA_DAMKA;
							else if (DajPionka(x, y).typ == CZARNA_DAMKA)
								DajPionka(x - 1, y + 1).typ = CZARNA_DAMKA;

							DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

							DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
							DajPionka(x - 1, y + 1).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

							NoweX = x - 1;
							NoweY = y + 1;

							ruch = true;

							Rundy--;

							return true;
						}
					}
				}
			}
		}
	}
	else if (kierunek == GL2)												//PIONEK PRZECIWNIKA NA GÓRNEJ LEWEJ PRZEK¥TNEJ
	{
		if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNA_DAMKA)
		{
			if (x >= 2 && y >= 2)
			{
				if (DajPole(x - 2, y - 2).Ksztalt().getFillColor() == czerwony)
				{
					if (DajPionka(x - 2, y - 2).typ == PUSTE)
					{
						UsunZaznaczenie(x, y);

						//ZMIANA TYPU POLA
						if (DajPionka(x, y).typ == BIALY_PIONEK && DajPionka(x - 2, y - 2).typ == PUSTE)
							DajPionka(x - 2, y - 2).typ = BIALY_PIONEK;
						else if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x - 2, y - 2).typ == PUSTE)
							DajPionka(x - 2, y - 2).typ = BIALA_DAMKA;
						else if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x - 2, y - 2).typ == PUSTE)
							DajPionka(x - 2, y - 2).typ = CZARNA_DAMKA;

						DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

						if (tura % 2 == 0)										//BIJE CZARNEGO PIONKA
							LiczbaCzarnych--;
						else if (tura % 2 == 1)									//BIJE BIA£EGO PIONKA
							LiczbaBialych--;
						DajPionka(x - 1, y - 1).typ = PUSTE;					//USTAWIA TYP POLA USUNIÊTEGO PIONKA PRZECIWNIKA NA PUSTY
						DajPionka(x - 1, y - 1).UsunPionka();					//USUWA PIONKA PRZECIWNIKA NA DRODZE

						DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
						DajPionka(x - 2, y - 2).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

						NoweX = x - 2;
						NoweY = y - 2;

						ruch = false;

						Rundy = 30;

						return true;
					}
				}
			}
		}
	}
	else if (kierunek == GP2)												//PIONEK PRZECIWNIKA NA GÓRNEJ PRAWEJ PRZEK¥TNEJ
	{
		if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNA_DAMKA)
		{
			if (x <= 5 && y >= 2)
			{
				if (DajPole(x + 2, y - 2).Ksztalt().getFillColor() == czerwony)
				{
					if (DajPionka(x + 2, y - 2).typ == PUSTE)
					{
						UsunZaznaczenie(x, y);

						//ZMIANA TYPU POLA
						if (DajPionka(x, y).typ == BIALY_PIONEK && DajPionka(x + 2, y - 2).typ == PUSTE)
							DajPionka(x + 2, y - 2).typ = BIALY_PIONEK;
						else if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x + 2, y - 2).typ == PUSTE)
							DajPionka(x + 2, y - 2).typ = BIALA_DAMKA;
						else if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x + 2, y - 2).typ == PUSTE)
							DajPionka(x + 2, y - 2).typ = CZARNA_DAMKA;

						DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

						if (tura % 2 == 0)										//BIJE CZARNEGO PIONKA
							LiczbaCzarnych--;
						else if (tura % 2 == 1)									//BIJE BIA£EGO PIONKA
							LiczbaBialych--;
						DajPionka(x + 1, y - 1).typ = PUSTE;					//USTAWIA TYP POLA USUNIÊTEGO PIONKA PRZECIWNIKA NA PUSTY
						DajPionka(x + 1, y - 1).UsunPionka();					//USUWA PIONKA PRZECIWNIKA NA DRODZE

						DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
						DajPionka(x + 2, y - 2).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

						NoweX = x + 2;
						NoweY = y - 2;

						ruch = false;

						Rundy = 30;

						return true;
					}
				}
			}
		}
	}
	else if (kierunek == DP2)												//PIONEK PRZECIWNIKA NA DOLNEJ PRAWEJ PRZEK¥TNEJ
	{
		if (DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
		{
			if (x <= 5 && y <= 5)
			{
				if (DajPole(x + 2, y + 2).Ksztalt().getFillColor() == czerwony)
				{
					if (DajPionka(x + 2, y + 2).typ == PUSTE)
					{
						UsunZaznaczenie(x, y);

						//ZMIANA TYPU POLA
						if (DajPionka(x, y).typ == CZARNY_PIONEK && DajPionka(x + 2, y + 2).typ == PUSTE)
							DajPionka(x + 2, y + 2).typ = CZARNY_PIONEK;
						else if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x + 2, y + 2).typ == PUSTE)
							DajPionka(x + 2, y + 2).typ = BIALA_DAMKA;
						else if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x + 2, y + 2).typ == PUSTE)
							DajPionka(x + 2, y + 2).typ = CZARNA_DAMKA;

						DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

						if (tura % 2 == 0)										//BIJE CZARNEGO PIONKA
							LiczbaCzarnych--;
						else if (tura % 2 == 1)									//BIJE BIA£EGO PIONKA
							LiczbaBialych--;
						DajPionka(x + 1, y + 1).typ = PUSTE;					//USTAWIA TYP POLA USUNIÊTEGO PIONKA PRZECIWNIKA NA PUSTY
						DajPionka(x + 1, y + 1).UsunPionka();					//USUWA PIONKA PRZECIWNIKA NA DRODZE

						DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
						DajPionka(x + 2, y + 2).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

						NoweX = x + 2;
						NoweY = y + 2;

						ruch = false;

						Rundy = 30;

						return true;
					}
				}
			}
		}
	}
	else if (kierunek == DL2)												//PIONEK PRZECIWNIKA NA DOLNEJ LEWEJ PRZEK¥TNEJ
	{
		if (DajPionka(x, y).typ == BIALA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
		{
			if (x >= 2 && y <= 5)
			{
				if (DajPole(x - 2, y + 2).Ksztalt().getFillColor() == czerwony)
				{
					if (DajPionka(x - 2, y + 2).typ == PUSTE)
					{
						UsunZaznaczenie(x, y);

						//ZMIANA TYPU POLA
						if (DajPionka(x, y).typ == CZARNY_PIONEK && DajPionka(x - 2, y + 2).typ == PUSTE)
							DajPionka(x - 2, y + 2).typ = CZARNY_PIONEK;
						else if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x - 2, y + 2).typ == PUSTE)
							DajPionka(x - 2, y + 2).typ = BIALA_DAMKA;
						else if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x - 2, y + 2).typ == PUSTE)
							DajPionka(x - 2, y + 2).typ = CZARNA_DAMKA;

						DajPionka(x, y).typ = PUSTE;							//USTAWIA TYP STAREGO POLA NA PUSTE

						if (tura % 2 == 0)										//BIJE CZARNEGO PIONKA
							LiczbaCzarnych--;
						else if (tura % 2 == 1)									//BIJE BIA£EGO PIONKA
							LiczbaBialych--;
						DajPionka(x - 1, y + 1).typ = PUSTE;					//USTAWIA TYP POLA USUNIÊTEGO PIONKA PRZECIWNIKA NA PUSTY
						DajPionka(x - 1, y + 1).UsunPionka();					//USUWA PIONKA PRZECIWNIKA NA DRODZE

						DajPionka(x, y).UsunPionka();							//USUWA PIONKA ZE STAREJ POZYCJI
						DajPionka(x - 2, y + 2).UstawPionka(tura);				//USTAWIA PIONKA NA NOWEJ POZYCJI

						NoweX = x - 2;
						NoweY = y + 2;

						ruch = false;

						Rundy = 30;

						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Plansza::Bicie(int& tura, bool& bicie, int& x, int& y, int& NoweX, int& NoweY, Kierunek& kierunek)
{
	x = NoweX;
	y = NoweY;

	//GÓRNA LEWA
	if (x >= 2 && y >= 2)
	{
		if (((DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA) &&
			 (DajPionka(x - 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y - 1).typ == CZARNA_DAMKA)) ||
			 (DajPionka(x, y).typ == CZARNA_DAMKA &&
			 (DajPionka(x - 1, y - 1).typ == BIALY_PIONEK || DajPionka(x - 1, y - 1).typ == BIALA_DAMKA)))
		{
			if (DajPionka(x - 2, y - 2).typ == PUSTE)
			{
				bicie = true;
				return true;
			}
		}
	}

	//GÓRNA PRAWA
	if (x <= 5 && y >= 2)
	{
		if (((DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA) &&
			 (DajPionka(x + 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y - 1).typ == CZARNA_DAMKA)) ||
			 (DajPionka(x, y).typ == CZARNA_DAMKA &&
			 (DajPionka(x + 1, y - 1).typ == BIALY_PIONEK || DajPionka(x + 1, y - 1).typ == BIALA_DAMKA)))
		{
			if (DajPionka(x + 2, y - 2).typ == PUSTE)
			{
				bicie = true;
				return true;
			}
		}
	}

	//DOLNA PRAWA
	if (x <= 5 && y <= 5)
	{
		if ((DajPionka(x, y).typ == BIALA_DAMKA &&
		    (DajPionka(x + 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y + 1).typ == CZARNA_DAMKA)) ||
		   ((DajPionka(x, y).typ == CZARNA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK) &&
		    (DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA)))
		{
			if (DajPionka(x + 2, y + 2).typ == PUSTE)
			{
				bicie = true;
				return true;
			}
		}
	}

	//DOLNA LEWA
	if (x >= 2 && y <= 5)
	{
		if ((DajPionka(x, y).typ == BIALA_DAMKA &&
			(DajPionka(x - 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y + 1).typ == CZARNA_DAMKA)) ||
		   ((DajPionka(x, y).typ == CZARNA_DAMKA || DajPionka(x, y).typ == CZARNY_PIONEK) &&
			(DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA)))
		{
			if (DajPionka(x - 2, y + 2).typ == PUSTE)
			{
				bicie = true;
				return true;
			}
		}
	}

	return false;
}

sf::Vector2i Plansza::MozliwoscBicia(bool& bialy_czarny)
{
	for (int x = 0; x < RozmiarPlanszy; x++)
	{
		for (int y = 0; y < RozmiarPlanszy; y++)
		{
			if (DajPionka(x, y).typ != PUSTE && DajPionka(x, y).typ != BLAD)
			{
				if (bialy_czarny == false)					//KOMPUTER GRA BIALYMI
				{
					if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA)
					{
						//GÓRNA LEWA
						if (x >= 2 && y >= 2)
						{
							if (DajPionka(x - 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y - 1).typ == CZARNA_DAMKA)
							{
								if (DajPionka(x - 2, y - 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//GÓRNA PRAWA
						if (x <= 5 && y >= 2)
						{
							if (DajPionka(x + 1, y - 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y - 1).typ == CZARNA_DAMKA)
							{
								if (DajPionka(x + 2, y - 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//DOLNA PRAWA
						if (x <= 5 && y <= 5)
						{
							if (DajPionka(x, y).typ == BIALA_DAMKA &&
						   	   (DajPionka(x + 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x + 1, y + 1).typ == CZARNA_DAMKA))
							{
								if (DajPionka(x + 2, y + 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//DOLNA LEWA
						if (x >= 2 && y <= 5)
						{
							if (DajPionka(x, y).typ == BIALA_DAMKA &&
							   (DajPionka(x - 1, y + 1).typ == CZARNY_PIONEK || DajPionka(x - 1, y + 1).typ == CZARNA_DAMKA))
							{
								if (DajPionka(x - 2, y + 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
					}
				}
				if (bialy_czarny == true)					//KOMPUTER GRA CZARNYMI
				{
					if (DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
					{
						//GÓRNA LEWA
						if (x >= 2 && y >= 2)
						{
							if (DajPionka(x, y).typ == CZARNA_DAMKA && 
							   (DajPionka(x - 1, y - 1).typ == BIALY_PIONEK || DajPionka(x - 1, y - 1).typ == BIALA_DAMKA))
							{
								if (DajPionka(x - 2, y - 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//GÓRNA PRAWA
						if (x <= 5 && y >= 2)
						{
							if (DajPionka(x, y).typ == CZARNA_DAMKA && 
							   (DajPionka(x + 1, y - 1).typ == BIALY_PIONEK || DajPionka(x + 1, y - 1).typ == BIALA_DAMKA))
							{
								if (DajPionka(x + 2, y - 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//DOLNA PRAWA
						if (x <= 5 && y <= 5)
						{
							if (DajPionka(x + 1, y + 1).typ == BIALY_PIONEK || DajPionka(x + 1, y + 1).typ == BIALA_DAMKA)
							{
								if (DajPionka(x + 2, y + 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
						//DOLNA LEWA
						if (x >= 2 && y <= 5)
						{
							if (DajPionka(x - 1, y + 1).typ == BIALY_PIONEK || DajPionka(x - 1, y + 1).typ == BIALA_DAMKA)
							{
								if (DajPionka(x - 2, y + 2).typ == PUSTE)
								{
									return sf::Vector2i(x, y);
								}
							}
						}
					}
				}
			}
		}
	}
	return sf::Vector2i(-1, -1);
}

bool Plansza::CzyZablokowany(int& tura, Wygrana& wygral)
{
	bool zablokowany = true;
	for (int x = 0; x < RozmiarPlanszy; x++)
	{
		for (int y = 0; y < RozmiarPlanszy; y++)
		{
			if (tura % 2 == 0)
			{
				if (DajPionka(x, y).typ == BIALY_PIONEK || DajPionka(x, y).typ == BIALA_DAMKA)
				{
					if (x >= 1 && y >= 1)
						if (DajPionka(x - 1, y - 1).typ == PUSTE)
							zablokowany = false;
					if (x <= 6 && y >= 1)
						if (DajPionka(x + 1, y - 1).typ == PUSTE)
							zablokowany = false;
					if (x <= 6 && y <= 6)
						if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x + 1, y + 1).typ == PUSTE)
							zablokowany = false;
					if (x >= 1 && y <= 6)
						if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x - 1, y + 1).typ == PUSTE)
							zablokowany = false;
					if (x >= 2 && y >= 2)
						if (DajPionka(x - 2, y - 2).typ == PUSTE)
							zablokowany = false;
					if (x <= 5 && y >= 2)
						if (DajPionka(x + 2, y - 2).typ == PUSTE)
							zablokowany = false;
					if (x <= 5 && y <= 5)
						if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x + 2, y + 2).typ == PUSTE)
							zablokowany = false;
					if (x >= 2 && y <= 5)
						if (DajPionka(x, y).typ == BIALA_DAMKA && DajPionka(x - 2, y + 2).typ == PUSTE)
							zablokowany = false;
					if (zablokowany == true)
						wygral = CZARNY;
				}
			}
			else if (tura % 2 == 1)
			{
				if (DajPionka(x, y).typ == CZARNY_PIONEK || DajPionka(x, y).typ == CZARNA_DAMKA)
				{
					if (x >= 1 && y >= 1)
						if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x - 1, y - 1).typ == PUSTE)
							zablokowany = false;
					if (x <= 6 && y >= 1)
						if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x + 1, y - 1).typ == PUSTE)
							zablokowany = false;
					if (x <= 6 && y <= 6)
						if (DajPionka(x + 1, y + 1).typ == PUSTE)
							zablokowany = false;
					if (x >= 1 && y <= 6)
						if (DajPionka(x - 1, y + 1).typ == PUSTE)
							zablokowany = false;
					if (x >= 2 && y >= 2)
						if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x - 2, y - 2).typ == PUSTE)
							zablokowany = false;
					if (x <= 5 && y >= 2)
						if (DajPionka(x, y).typ == CZARNA_DAMKA && DajPionka(x + 2, y - 2).typ == PUSTE)
							zablokowany = false;
					if (x <= 5 && y <= 5)
						if (DajPionka(x + 2, y + 2).typ == PUSTE)
							zablokowany = false;
					if (x >= 2 && y <= 5)
						if (DajPionka(x - 2, y + 2).typ == PUSTE)
							zablokowany = false;
					if (zablokowany == true)
						wygral = BIALY;
				}
			}
		}
	}
	return zablokowany;
}

void Plansza::Koniec(sf::RenderWindow& window, sf::Font& font, int& tura, bool& Komputer, sf::Text& Gracz1, sf::Text& Gracz2)
{
	Wygrana wygral = REMIS;
	if (Rundy == 0)
	{
		window.close();
		koniec(font, Komputer, REMIS, Gracz1, Gracz2);
	}
	if (LiczbaCzarnych == 0 || (CzyZablokowany(tura, wygral) == true && wygral == BIALY))
	{
		window.close();
		koniec(font, Komputer, BIALY, Gracz1, Gracz2);
	}
	if (LiczbaBialych == 0 || (CzyZablokowany(tura, wygral) == true && wygral == CZARNY))
	{
		window.close();
		koniec(font, Komputer, CZARNY, Gracz1, Gracz2);
	}
}

Plansza& Plansza::operator+=(ListaPol* NowePole)
{
	if (pHead == nullptr)
		pHead = NowePole;
	else
	{
		ListaPol* temp = pHead;
		if(temp->pNext)
			while (temp->pNext)
			{
				temp = temp->pNext;
			}
		temp->pNext = NowePole;
		NowePole->pNext = nullptr;
	}
	return *this;
}

Plansza& Plansza::operator+=(ListaPionkow* NowyPionek)
{
	if (pPionek == nullptr)
		pPionek = NowyPionek;
	else
	{
		ListaPionkow* temp = pPionek;
		if (temp->pNext)
			while (temp->pNext)
			{
				temp = temp->pNext;
			}
		temp->pNext = NowyPionek;
		NowyPionek->pNext = nullptr;
	}
	return *this;
}