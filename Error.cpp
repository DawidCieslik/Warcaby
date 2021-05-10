#include "Error.h"

void Blad(unsigned int RodzajBledu)
{
    switch (RodzajBledu)
    {
    case 1:
    {
        std::string error = "Nie ma takiego pola lub pionka!";
        throw error;
        break;
    }
    case 2:
    {
        std::string error = "Wczytywanie pliku nie powiod³o siê!";
        throw error;
        break;
    }
    case 3:
    {
        std::string error = "Gracz nie moze przyjmowac nazwy Komputer!";
        throw error;
        break;
    }
    case 4:
    {
        std::string error = "Nazwy graczy nie moga byc puste!";
        throw error;
        break;
    }
    }
}