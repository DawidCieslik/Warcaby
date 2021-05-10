#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enums.h"
#include "Pole.h"

/**Klasa reprezentujaca pojedynczy pionek na planszy.*/
class Pionek : public Pole
{
	/**Ksztalt pionka (kolo).*/
	sf::CircleShape kolo;
public:
	/**Typ pola.*/
	TypPola typ;
	/**Konstruktor domyslny.*/
	Pionek();
	/**Konstruktor kopiujacy. @param NowyPionek Pionek do skopiowania.*/
	Pionek(const Pionek& NowyPionek);
	/**Konstruktor ustawiajacy pionka we wskazanych wspolrzednych. @param x Wspolrzedna x. @param y Wspolrzedna y.*/
	Pionek(int x, int y);
	/**Ustawia punkt zaczepienia pionka.*/
	void UstawPunktZaczepienia();
	/**Ustawia promien pionka.*/
	void Promien();
	/**Usuwa pionka.*/
	void UsunPionka();
	/**Ustawia nowego pionka. @param tura Aktualna tura*/
	void UstawPionka(int &tura);
	/**Zwraca wspolrzedne punktu zaczepienia. @return Wspolrzedne X i Y punktu zaczepienia pionka.*/
	sf::Vector2f DajPunktZaczepienia();
	/**Zwraca aktualna wspolrzedna x pionka. @return Wspolrzedna X pionka.*/
	int PodajX();
	/**Zwraca aktualna wspolrzedna y pionka. @return Wspolrzedna Y pionka.*/
	int PodajY();
	/**Zwraca ksztalt pionka (kolo). @return Ksztalt pionka.*/
	sf::CircleShape Ksztalt();
	/**Ustawia pionek we wskazanym punkcie (x,y). @param x Wspolrzedna x. @param y Wspolrzedna y.*/
	void Pozycja(int x, int y);
	/**Ustawia kolor pionka. @param kolor Kolor pionka*/
	void Kolor(const sf::Color& kolor);
	/**Ustawia grubosc konturu pionka.*/
	void Kontur();
	/**Ustawia kolor konturu pionka. @param kolor Kolor konturu pionka*/
	void KolorKonturu(const sf::Color kolor);
	/**Zmienia pionka na damke.*/
	void ZmienNaDamke();
	/**Przypisuje jeden pionek drugiemu. @param NowyPionek Przypisywany pionek. @return Element klasy Pionek.*/
	Pionek& operator=(const Pionek& NowyPionek);
};

/**Klasa reprezentujaca liste pionkow na planszy.*/
class ListaPionkow
{
public:
	/**Element pola.*/
	Pionek pionek;
	/**Wskaznik na nastepny element listy pol.*/
	ListaPionkow* pNext;
	/**Konstruktor domyslny.*/
	ListaPionkow() : pionek(), pNext(nullptr) {};
	/**Konstruktor kopiujacy. @param Pionek Pionek do skopiowania.*/
	ListaPionkow(const Pionek& NowyPionek) : pionek(NowyPionek), pNext(nullptr) {};
};