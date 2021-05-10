#include "Pole.h"

Pole::Pole()
{
	x = 0;
	y = 0;
	kwadrat.setSize(sf::Vector2f(RozmiarPola, RozmiarPola));
	kwadrat.setOutlineThickness(5);
	kwadrat.setOutlineColor(czarny);
}

Pole::Pole(const Pole& NowePole)
{
	x = NowePole.x;
	y = NowePole.y;
	
}

Pole::Pole(int x, int y)
{
	this->x = x;
	this->y = y;
	kwadrat.setSize(sf::Vector2f(RozmiarPola, RozmiarPola));
	kwadrat.setOutlineThickness(5);
	kwadrat.setOutlineColor(czarny);
}

void Pole::UstawX(int x)
{
	this->x = x;
}

void Pole::UstawY(int y)
{
	this->y = y;
}

int Pole::PodajX()
{
	return x;
}

int Pole::PodajY()
{
	return y;
}

sf::RectangleShape Pole::Ksztalt()
{
	return kwadrat;
}

void Pole::Pozycja(int x, int y)
{
	kwadrat.setPosition(x * RozmiarPola + 50, y * RozmiarPola + 100);
}

void Pole::Kolor(const sf::Color &kolor)
{
	kwadrat.setFillColor(kolor);
}

void Pole::KolorKonturu(sf::Color kolor)
{
	kwadrat.setOutlineColor(kolor);
}

Pole& Pole::operator=(const Pole& NowePole)
{
	x = NowePole.x;
	y = NowePole.y;
	return *this;
}