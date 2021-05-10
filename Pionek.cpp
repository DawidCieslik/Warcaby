#include "Pionek.h"

Pionek::Pionek()
{
	x = -1;
	y = -1;
	typ = PUSTE;
}

Pionek::Pionek(const Pionek& NowyPionek)
{
	x = NowyPionek.x;
	y = NowyPionek.y;
	typ = NowyPionek.typ;
}

Pionek::Pionek(int x, int y)
{
	this->x = x;
	this->y = y;
	typ = PUSTE;
}

void Pionek::UstawPunktZaczepienia()
{
	kolo.setOrigin(0,-50);
}

void Pionek::Promien()
{
	kolo.setRadius(RozmiarPionka);
}

void Pionek::UsunPionka()
{
	kolo.setRadius(0);
	kolo.setOutlineThickness(0);
}

void Pionek::UstawPionka(int &tura)
{
	ZmienNaDamke();
	kolo.setRadius(RozmiarPionka);
	kolo.setOutlineThickness(4);
	if (typ == BIALA_DAMKA || typ == CZARNA_DAMKA)
		kolo.setOutlineColor(zolty);
	else if (typ == BIALY_PIONEK || typ == CZARNY_PIONEK)
		kolo.setOutlineColor(czarny);
	if (tura % 2 == 0)
		kolo.setFillColor(bialy);
	else if (tura % 2 == 1)
		kolo.setFillColor(czarny);
	kolo.setPosition(x * RozmiarPola + 65, y * RozmiarPola + 115);
}

sf::Vector2f Pionek::DajPunktZaczepienia()
{
	return kolo.getOrigin();
}

int Pionek::PodajX()
{
	return x;
}

int Pionek::PodajY()
{
	return y;
}

sf::CircleShape Pionek::Ksztalt()
{
	return kolo;
}

void Pionek::Pozycja(int x, int y)
{
	kolo.setPosition(x * RozmiarPola + 65, y * RozmiarPola + 115);
}

void Pionek::Kolor(const sf::Color& kolor)
{
	kolo.setFillColor(kolor);
}

void Pionek::Kontur()
{
	kolo.setOutlineThickness(4);
}

void Pionek::KolorKonturu(const sf::Color kolor)
{
	kolo.setOutlineColor(kolor);
}

void Pionek::ZmienNaDamke()
{
	if (y == 0 && typ == BIALY_PIONEK)
		typ = BIALA_DAMKA;
	else if (y == 7 && typ == CZARNY_PIONEK)
		typ = CZARNA_DAMKA;
}

Pionek& Pionek::operator=(const Pionek& NowyPionek)
{
	x = NowyPionek.x;
	y = NowyPionek.y;
	typ = NowyPionek.typ;
	return *this;
}