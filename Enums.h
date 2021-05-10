#pragma once

#define bialy sf::Color::White
#define czarny sf::Color::Black
#define czerwony sf::Color::Red

#define BLAD TypPola::INVALID
#define PUSTE TypPola::EMPTY
#define BIALY_PIONEK TypPola::WHITE
#define CZARNY_PIONEK TypPola::BLACK
#define BIALA_DAMKA TypPola::WHITE_KING
#define CZARNA_DAMKA TypPola::BLACK_KING

#define GL Kierunek::GÓRNY_LEWY
#define GP Kierunek::GÓRNY_PRAWY
#define DP Kierunek::DOLNY_PRAWY
#define DL Kierunek::DOLNY_LEWY
#define GL2 Kierunek::PIONEK_PRZECIWNIKA_NA_GÓRNEJ_LEWEJ_PRZEK¥TNEJ
#define GP2 Kierunek::PIONEK_PRZECIWNIKA_NA_GÓRNEJ_PRAWEJ_PRZEK¥TNEJ
#define DP2 Kierunek::PIONEK_PRZECIWNIKA_NA_DOLNEJ_PRAWEJ_PRZEK¥TNEJ
#define DL2 Kierunek::PIONEK_PRZECIWNIKA_NA_DOLNEJ_LEWEJ_PRZEK¥TNEJ

#define BIALY Wygrana::WHITE
#define CZARNY Wygrana::BLACK
#define REMIS Wygrana::DRAW

enum class TypPola
{
	INVALID,
	EMPTY,
	WHITE,
	BLACK,
	WHITE_KING,
	BLACK_KING
};

enum class Kierunek
{
	BRAK,
	GÓRNY_LEWY,
	GÓRNY_PRAWY,
	DOLNY_PRAWY,
	DOLNY_LEWY,
	PIONEK_PRZECIWNIKA_NA_GÓRNEJ_LEWEJ_PRZEK¥TNEJ,
	PIONEK_PRZECIWNIKA_NA_GÓRNEJ_PRAWEJ_PRZEK¥TNEJ,
	PIONEK_PRZECIWNIKA_NA_DOLNEJ_PRAWEJ_PRZEK¥TNEJ,
	PIONEK_PRZECIWNIKA_NA_DOLNEJ_LEWEJ_PRZEK¥TNEJ
};

enum class Wygrana
{
	WHITE,
	BLACK,
	DRAW
};

namespace
{
	const int RozmiarPlanszy = 8;
	const int RozmiarMenuX = 700;
	const int RozmiarMenuY = 900;
	const int RozmiarOknaX = 900;
	const int RozmiarOknaY = 950;
	const int RozmiarKoniecX = 700;
	const int RozmiarKoniecY = 300;
	const int RozmiarPola = 100;
	const int RozmiarPionka = 35;
	sf::Color jasny(238, 232, 170);
	sf::Color ciemny(92, 17, 9);
	sf::Color szary(127, 127, 127);
	sf::Color zolty(255, 225, 77);
}