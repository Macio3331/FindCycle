#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "functions.h"

void GetParams(int& argc, char* argv[], std::string& file_name_in, std::string& file_name_out, bool& status)
{
	if (argc == 1)
	{
		ShowInformation();                              //wyswietlenie informacji o dzialaniu programu
		status = false;
		return;
	}
	if (argc != 5 || (strcmp(argv[1], "-g") || strcmp(argv[3], "-c")) && (strcmp(argv[1], "-c") || strcmp(argv[3], "-g")))
	{
		ShowMessage();                                  //wyswietlenie komunikatu o blednych danych wejsciowych
		status = false;
		return;
	}
	if (!strcmp(argv[1], "-g"))                       //pobranie nazw pliku wejsciowego i wyjsciowego
	{
		file_name_in = std::string(argv[2]);
		file_name_out = std::string(argv[4]);
	}
	else
	{
		file_name_out = std::string(argv[2]);
		file_name_in = std::string(argv[4]);
	}
}

void ShowInformation()
{
	std::cout << std::endl
		<< "Program pozwala na wyznaczanie wszystkich cykli w grafie skierowanym." << std::endl
		<< "Program uzywa dwoch przelacznikow:" << std::endl
		<< "-g <plik_wejsciowy_z_grafem>" << std::endl
		<< "-c <plik_wyjsciowy_ze_znalezionymi_cyklami>" << std::endl
		<< "Format zapisu okreslonych polaczen w grafie:" << std::endl
		<< "<wierzcholek_poczatkowy> -> <wierzcholek_koncowy>" << std::endl
		<< "Poszczegolne luki oddzielone sa od siebie przecinkami." << std::endl
		<< "Znalezione cykle sa zapisane w osobnych liniach w formacie: " << std::endl
		<< "\"1-szy_punkt -> 2-gi_punkt -> .... -> n-ty_punkt -> 1-szy_punkt,\"" << std::endl
		<< "Aby uzyc programu nalezy wpisac do konsoli:" << std::endl
		<< "<nazwa_programu> -g <nazwa_pliku_wejsciowego> -c <nazwa_pliku_wyjsciowego>" << std::endl
		<< std::endl;
}

void ShowMessage()
{
	std::cout << "Podano niepoprawne dane wejsciowe." << std::endl;
}

Graph GetGraphFromFile(const std::string& file_name, Connection& m)					//odczytanie grafu z pliku
{
	Graph graph;
	std::ifstream file(file_name);
	if (file)
	{
		std::string line;
		while (std::getline(file, line, ','))
		{
			std::stringstream ss(line);
			char c1, c2;
			unsigned int first, second;
			if (!(ss >> first)) continue;											//jesli ktorys z odczytow nie powiedzie sie - czytanie z nastepnej linii
			if (!(ss >> c1)) continue;
			if (!(ss >> c2)) continue;
			if (!(ss >> second)) continue;
			graph[first].insert({ second });										//dodanie polaczenia do listy
			m[std::pair<unsigned int, unsigned int>{first, second}] = false;		//ustalenie statusu polaczenia na "nieprzebyte"
		}
		file.close();
	}
	else std::cout << "Odczyt pliku nie powiodl sie." << std::endl;
	return graph;
}

void FindCycle(Graph& graph, Connection& m, Table& result)
{
	std::vector<unsigned int> stack;												//stos
	for (auto& el : graph)
	{
		DFS(graph, result, stack, m, el.first, el.first, el.first);					//wywolanie szukania cykli dla danego wierzcholka
	}
}

void DFS(Graph& graph, Table& result, std::vector<unsigned int> stack, Connection m, const unsigned int& previous_point, const unsigned int& actual_point, const unsigned int& ending_point)
{
	if (stack.size() != 0)															//zabezpieczenie przed szukaniem cyklu w jednym punkcie
	{
		m[{previous_point, actual_point}] = true;									//ustalenie statusu polaczenia na "przebyte"
		if (actual_point == ending_point)
		{
			stack.push_back(actual_point);											//dodanie poczatkowego punktu do sciezki (zakonczenie cyklu)
			PushToResult(stack, result);											//dodanie cyklu do tablicy znalezionych cykli
			return;
		}
	}
	stack.push_back(actual_point);													//dodanie aktualnie rozpatrywanego punktu
	for (auto& connection : graph[actual_point])
	{
		if (m[std::pair<unsigned int, unsigned int>{actual_point, connection}] == false) DFS(graph, result, stack, m, actual_point, connection, ending_point);
		//sprawdzenie statusu sciezki, jesli status to "nieprzebyte" - wybranie danej sciezki 
	}
}

void PushToResult(std::vector<unsigned int>& stack, Table& result)
{
	result.push_back(stack);														//Dodanie znalezionego cyklu do wektora wynikow
}

void SaveGraphToFile(Table& result, const std::string& file_name)					//zapisanie znalezionych cykli do pliku: "1_punkt -> 2_punkt -> .... -> n-ty_punkt,"
{
	std::ofstream file(file_name);
	if (file)
	{
		if (result.empty())
		{
			file << "Nie znaleziono ¿adnych cykli." << std::endl;
			return;
		}
		int j = 0;
		for (auto& el : result)
		{
			int i = 0;
			j++;
			for (auto& el1 : el)
			{
				file << el1;
				if (i != el.size() - 1) file << " -> ";
				i++;
			}
			if (!(result.size() == j)) file << "," << std::endl;
		}
		file.close();
	}
	else std::cout << "Nie udalo sie utworzyc pliku." << std::endl;
}