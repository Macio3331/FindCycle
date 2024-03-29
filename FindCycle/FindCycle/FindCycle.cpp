#include <iostream>
#include "functions.h"

int main(int argc, char* argv[])
{
    bool status = true;
    std::string file_name_in, file_name_out;                        //nazwy plików wejściowego i wyjściowego
    GetParams(argc, argv, file_name_in, file_name_out, status);     //sprawdzenie i pobranie parametrów
    if (status == false) return 0;
    Connection m;                                                   //macierz statusów połaczeń
    Table result;                                                   //tablica znalezionych cykli
    Graph graph = GetGraphFromFile(file_name_in, m);                //pobranie grafu z pliku wejściowego
    if (graph.size() == 0) return 0;
    FindCycle(graph, m, result);                                    //wyszukiwanie cykli
    SaveGraphToFile(result, file_name_out);                         //zapisanie grafu do pliku wyjściowego
    return 0;
}