/** @file */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <set>
#include <vector>
#include <string>

/** Struktura grafu - macierz sasiedztwa.
*/
typedef std::map<unsigned int, std::set<unsigned int>> Graph;

/** Mapa statusow polaczen, poczatkowo wszystkie maja ustawiony status false (nieodwiedzone).
*/
typedef std::map<std::pair<unsigned int, unsigned int>, bool> Connection;

/** Tablica znalezionych cykli.
*/
typedef std::vector<std::vector<unsigned int>> Table;

/** Funkcja sprawdza i pobiera parametry wejsciowe programu.
* @param argc Ilosc wprowadzonych argumentow
* @param argv Kolejne parametry
* @param file_name_in Nazwa pliku wejsciowego
* @param file_name_out Nazwa pliku wyjsciowego
* @param status Zmienna logiczna zarzadzajaca dalszym dzialaniem lub przerwaniem programu
*/
void GetParams(int& argc, char* argv[], std::string& file_name_in, std::string& file_name_out, bool& status);

/** Funkcja wyswietla informacje o tym, jak nalezy uzywac programu.
*/
void ShowInformation();

/** Funkcja wyswietla komunikat o blednym wprowadzeniu danych do podprogramu.
*/
void ShowMessage();

/** Funkcja wczytuje z pliku graf w zadanej postaci do struktury grafu. Funkcja dodaje polaczenia i ustawia ich status na nieodwiedzony.
* @param file_name Nazwa pliku wejsciowego
* @param m Mapa statusow polaczen (poczatkowo wszystkie sa nieodwiedzone)
* @return Wczytany graf do struktury grafu
*/
Graph GetGraphFromFile(const std::string& file_name, Connection& m);

/** Funkcja zarzadza wyszukiwaniem cykli dla wszystkich wierzcholkow.
* @param graph Struktura polaczen w grafie
* @param m Mapa statusow polaczen (odwiedzony lub nieodwiedzony)
* @param result Tablica znalezionych cykli
*/
void FindCycle(Graph& graph, Connection& m, Table& result);

/** Funkcja wyszukuje cykle dla danego wierzcholka (rekurencyjnie).
* @param graph Struktura polaczen w grafie
* @param result Tablica znalezionych cykli
* @param stack Stos na ktorym sa odkladane kolejne wierzcholki
* @param m Mapa statusow polaczen (odwiedzony lub nieodwiedzony)
* @param previous_point Poprzednio analizowany wierzcholek
* @param actual_point Aktualnie analizowany wierzcholek
* @param ending_point Poczatkowy wierzcholek (konczacy wyszukiwanie cyklu)
*/
void DFS(Graph& graph, Table& result, std::vector<unsigned int> stack, Connection m, const unsigned int& previous_point, const unsigned int& actual_point, const unsigned int& ending_point);

/** Funkcja zapisuje znalezione cykle do tablicy znalezionych wierzcholkow.
* @param stack Stos zawierajacy znaleziony cykl
* @param result Tablica znalezionych cykli
*/
void PushToResult(std::vector<unsigned int>& stack, Table& result);

/** Funkcja zapisuje znalezione cykle do pliku wyjsciowego.
* @param result Tablica znalezionych cykli
* @param file_name Nazwa pliku wyjsciowego
*/
void SaveGraphToFile(Table& result, const std::string& file_name);

#endif