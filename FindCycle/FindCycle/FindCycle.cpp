#include <iostream>
#include "functions.h"

int main(int argc, char* argv[])
{
    bool status = true;
    std::string file_name_in, file_name_out;                        //nazwy plik�w wej�ciowego i wyj�ciowego
    GetParams(argc, argv, file_name_in, file_name_out, status);     //sprawdzenie i pobranie parametr�w
    if (status == false) return 0;
    Connection m;                                                   //macierz status�w po�acze�
    Table result;                                                   //tablica znalezionych cykli
    Graph graph = GetGraphFromFile(file_name_in, m);                //pobranie grafu z pliku wej�ciowego
    if (graph.size() == 0) return 0;
    FindCycle(graph, m, result);                                    //wyszukiwanie cykli
    SaveGraphToFile(result, file_name_out);                         //zapisanie grafu do pliku wyj�ciowego
    return 0;
}