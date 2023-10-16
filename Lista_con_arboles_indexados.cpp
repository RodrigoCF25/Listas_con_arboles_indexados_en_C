#include <iostream>
#include "Estructuras.h"

using namespace std;

int main()
{
    DList lLista = DList(tipo_Arbol::NoRepeticiones);

    lLista.push_back("Albert", "Einstein", "1879-03-14", 100);
    lLista.push_back("Issac", "Newton", "1643-01-04", 300);
    lLista.push_back("Neils", "Bohr", "1885-10-07", 250);
    lLista.push_back("Hipatia", "De Alejandria", "455-01-01", 200);
    lLista.push_back("Albert", "Einstein", "1879-03-14", 100);

    lLista.repr(ECampos::nombre);
}

