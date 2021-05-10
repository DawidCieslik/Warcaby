#include "Komputer.h"

Komputer::Komputer(bool& bialy_czarny)
{
	this->bialy_czarny = bialy_czarny;
}

void Komputer::TuraKomputera(Plansza& plansza, int& tura, bool& bicie, bool& ruch, int& NoweX, int& NoweY)
{
	//WSPÓ£RZÊDNE PIONKA
	int x = rand() % 8;
	int y = rand() % 8;

	//LOSOWANIE KIERUNKU
	Kierunek kierunek = Kierunek::BRAK;

	//PÊTLA LOSUJ¥CA
	while (kierunek == Kierunek::BRAK)
	{
		if (plansza.MozliwoscBicia(bialy_czarny) == sf::Vector2i(-1,-1))
		{
			//LOSOWANIE PIONKA
			if (bialy_czarny == false)						//BIALY
			{
				while (plansza.DajPionka(x, y).typ != BIALY_PIONEK && plansza.DajPionka(x, y).typ != BIALA_DAMKA)
				{
					x = rand() % 8;
					y = rand() % 8;
				}
			}

			else if (bialy_czarny == true)					//CZARNY
			{
				while (plansza.DajPionka(x, y).typ != CZARNY_PIONEK && plansza.DajPionka(x, y).typ != CZARNA_DAMKA)
				{
					x = rand() % 8;
					y = rand() % 8;
				}
			}
		}
		else
		{
			x = plansza.MozliwoscBicia(bialy_czarny).x;
			y = plansza.MozliwoscBicia(bialy_czarny).y;
		}

		//LOSOWANIE KIERUNKU
		kierunek = plansza.LosujKierunek(x, y, kierunek, bialy_czarny);

		plansza.PokazZasieg(x, y, bicie);

		//PRZESUWA PIONKA NA NOWE MIEJSCE
		if (plansza.PrzesunPionka(tura, bicie, ruch, x, y, NoweX, NoweY, kierunek))
		{
			//WIELOKROTNE BICIE
			if (ruch == false && plansza.Bicie(tura, bicie, x, y, NoweX, NoweY, kierunek))
			{
				kierunek = Kierunek::BRAK;
				continue;
			}

			x = -1;
			NoweX = -1;
			y = -1;
			NoweY = -1;
			ruch = false;
			bicie = false;
			kierunek = Kierunek::BRAK;
			tura++;
			break;
		}
		//Z£Y PIONEK - SZUKAJ DALEJ
		plansza.UsunZaznaczenie(x, y);
		kierunek = Kierunek::BRAK;
		x = 0;
		y = 0;
	}
}