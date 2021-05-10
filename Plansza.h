#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Pionek.h"
#include "Error.h"
#include "Enums.h"
#include "Menu.h"

/**Klasa reprezentujaca plansze do gry.*/
class Plansza
{
	/**Lista przechowujaca pola.*/
	ListaPol* pHead;
	/**Lista przechowujaca pionki.*/
	ListaPionkow* pPionek;
	/**Aktualna liczba bialych pionkow.*/
	static int LiczbaBialych;	
	/**Aktualna liczba czarnych pionkow.*/
	static int LiczbaCzarnych;
	/**Liczba rund do remisu.*/
	static int Rundy;
public:
	/**Konstruktor domyslny.*/
	Plansza();
	/**Destruktor.*/
	~Plansza();
	/**Zwraca pionka. @param x Wspolrzedna x. @param y Wspolrzedna y. @return Pionek o wskazanych wspolrzednych.*/
	Pionek& DajPionka(int x, int y);
	/**Zwraca pole. @param x Wspolrzedna x. @param y Wspolrzedna y. @return Pole o wskazanych wspolrzednych.*/
	Pole& DajPole(int x, int y);
	/**Inicjalizuje plansze.*/
	void InicjalizujPlansze();
	/**Wyswietla plansze na ekranie.*/
	void WyswietlPlansze(sf::RenderWindow &window);
	/**Pokazuje zasieg ruchu pionka. @param x Wspolrzedna x. @param y Wspolrzedna y. @param bicie Czy wielokrotne bicie?*/
	void PokazZasieg(int& x, int& y, bool& bicie);
	/**Usuwa zaznaczenie zasiegu ruchu pionka. @param x Wspolrzedna x. @param y Wspolrzedna y.*/
	void UsunZaznaczenie(int& x, int& y);
	/**Sprawdza, czy pionek moze sie ruszyc we wskazanym kierunku. @param x Wspolrzedna x. @param y Wspolrzedna y. @param kierunek Kierunek przesuniecia. @return False - nie moze sie poruszyc we wskazanym kierunku; True - moze sie poruszyc we wskazanym kierunku.*/
	bool SprawdzPozycje(int& x, int& y, Kierunek& kierunek);
	/**Losuje kierunek dla komputera. @param x Wspolrzedna x. @param y Wspolrzedna y. @param kierunek Kierunek przesuniecia. @param bialy_czarny Bialy czy czarny? @return Wylosowany kierunek.*/
	Kierunek LosujKierunek(int& x, int& y, Kierunek& kierunek, bool& bialy_czarny);
	/**Przesuwa pionka we wskazanym kierunku. @param tura Tura gry. @param bicie Czy wielokrotne bicie? @param ruch Bicie czy ruch? @param x Wspolrzedna x. @param y Wspolrzedna y. @param NoweX Nowa wspolrzedna x. @param NoweY Nowa wspolrzedna y. @param kierunek kierunek przesuniecia. @return False - nie przesunieto; True - przesunieto.*/
	bool PrzesunPionka(int& tura, bool& bicie, bool& ruch, int& x, int& y, int& NoweX, int& NoweY, Kierunek& kierunek);
	/**Wykonuje obowiazkowe bicie. @param tura Tura gry. @param bicie Czy wielokrotne bicie? @param x Wspolrzedna x. @param y Wspolrzedna y. @param NoweX Nowa wspolrzedna x. @param NoweY Nowa wspolrzedna y. @param kierunek kierunek przesuniecia. @return False - nie ma wielokrotnego bicia; True - jest wielokrotne bicie.*/
	bool Bicie(int& tura, bool& bicie, int& x, int& y, int& NoweX, int& NoweY, Kierunek& kierunek);
	/**Sprawdza mozliwosc bicia. @param bialy_czarny Bialy czy czarny? @return Wspolrzedne X i Y pierwszego znalezionego pionka, ktory moze bic.*/
	sf::Vector2i MozliwoscBicia(bool& bialy_czarny);
	/**Sprawdza, czy gracz zostal zablokowany. @param tura Tura gry. @param wygral Kto wygral? @return False - nie zablokowany; True - zablokowany.*/
	bool CzyZablokowany(int& tura, Wygrana& wygral);
	/**Koniec gry. @param window Okno gry. @param font Czcionka. @param tura Tura gry. @param Komputer Gracz czy komputer? @param Gracz1 Nazwa gracza bialego. @param Gracz2 Nazwa gracza czarnego.*/
	void Koniec(sf::RenderWindow& window, sf::Font& font, int& tura, bool& Komputer, sf::Text& Gracz1, sf::Text& Gracz2);
	/**Dodaje nowe pole do listy pol. @param NowePole Pole do dodania. @return Element klasy Plansza.*/
	Plansza& operator+=(ListaPol* NowePole);
	/**Dodaje nowego pionka do listy pionkow. @param NowyPionek Pionek do dodania. @return Element klasy Plansza.*/
	Plansza& operator+=(ListaPionkow* NowyPionek);
};