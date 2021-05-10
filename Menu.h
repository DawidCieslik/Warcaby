#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Plansza.h"
#include "Error.h"
#include "Gra.h"
#include "Enums.h"

/**Funkcja wywolujaca okno menu wyboru gry z komputerem czy graczem.*/
void menu1();

/**Funkcja wywolujaca okno menu wyboru nazwy i koloru gracza (gra z komputerem) lub nazw graczy (gra wieloosobowa). @param font Czcionka. @param komputer Gracz czy komputer?*/
void menu2(sf::Font& font, bool komputer);

/**Funkcja okno konca gry. @param font Czcionka. @param komputer Gracz czy komputer? @param KtoWygral Kto wygral? @param Gracz1 Nazwa gracza bialego. @param Gracz2 Nazwa gracza czarnego.*/
void koniec(sf::Font& font, bool& komputer, Wygrana KtoWygral, sf::Text& Gracz1, sf::Text& Gracz2);