#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enums.h"

/**Klasa reprezentujaca pojedynczy kwadrat na planszy.*/
class Pole
{
	/**Ksztalt pola (prostokat).*/
	sf::RectangleShape kwadrat;
protected:
	/**Wspolrzedna x.*/
	int x;
	/**Wspolrzedna y.*/
	int y;
public:
	/**Konstruktor domyslny.*/
	Pole();
	/**Konstruktor kopiujacy. @param NowePole Referencja na pole, z ktorego kopiujemy.*/
	Pole(const Pole& NowePole);
	/**Konstruktor ustawiajacy pole we wskazanych wspolrzednych. @param x Wspolrzedna x. @param y Wspolrzedna y.*/
	Pole(int x, int y);
	/**Przypisuje dla pola podana wspolrzedna x. @param x Wspolrzedna x.*/
	void UstawX(int x);
	/**Przypisuje dla pola podana wspolrzedna y. @param y Wspolrzedna y.*/
	void UstawY(int y);
	/**Zwraca aktualna wspolrzedna x pola. @return Wspolrzedna X pola.*/
	int PodajX();
	/**Zwraca aktualna wspolrzedna y pola. @return Wspolrzedna Y pola.*/
	int PodajY();
	/**Zwraca ksztalt pola (prostokat). @return Ksztalt pola.*/
	sf::RectangleShape Ksztalt();
	/**Ustawia pole we wskazanym punkcie (x,y). @param x Wspolrzedna x. @param y Wspolrzedna y.*/
	void Pozycja(int x, int y);
	/**Ustawia kolor pola. @param kolor Kolor pola.*/
	void Kolor(const sf::Color &kolor);
	/**Ustawia kolor konturu pola. @param kolor Kolor konturu pola.*/
	void KolorKonturu(sf::Color kolor);
	/**Przypisuje jedno pole drugiemu. @param NowePole Referencja na pole przypisane. @return Element klasy Pole.*/
	Pole& operator=(const Pole& NowePole);
};

/**Klasa reprezentujaca liste pol.*/
class ListaPol
{
public:
	/**Element pola.*/
	Pole pole;
	/**Wskaznik na nastepny element listy pol.*/
	ListaPol* pNext;
	/**Konstruktor domyslny.*/
	ListaPol() : pole(), pNext(nullptr) {};
	/**Konstruktor kopiujacy. @param NowePole Referencja na pole, z ktorego kopiujemy.*/
	ListaPol(const Pole& NowePole) : pole(NowePole), pNext(nullptr) {};
};