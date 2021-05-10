#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Plansza.h"
#include "Pole.h"
#include "Error.h"
#include "Enums.h"
#include "Komputer.h"

/**Funkcja wyswietlajaca okno gry. @param font Czcionka. @param Gracz1 Nazwa gracza bialego. @param Gracz2 Nazwa gracza czarnego. @param Komputer Gracz czy komputer?*/
void Gra(sf::Font& font,sf::Text &Gracz1, sf::Text &Gracz2, bool &Komputer);