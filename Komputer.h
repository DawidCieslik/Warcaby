#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Plansza.h"
#include "Enums.h"
class Plansza;

/**Klasa reprezentujaca komputer.*/
class Komputer
{
	/**Komputer gra bialym czy czarnym? False - bialy; true - czarny.*/
	bool bialy_czarny;
public:
	/**Konstruktor. @param bialy_czarny Komputer gra bialymi czy czarnymi?*/
	Komputer(bool& bialy_czarny);
	/**Wykonuje ture komputera. @param plansza Plansza gry. @param tura Tura gry. @param bicie Czy wielokrotne bicie? @param ruch Bicie czy ruch? @param NoweX Nowa wspolrzedna x. @param NoweY Nowa wspolrzedna y.*/
	void TuraKomputera(Plansza& plansza, int& tura, bool& bicie, bool& ruch, int& NoweX, int& NoweY);
};