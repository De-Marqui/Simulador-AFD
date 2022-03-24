#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct transition
{
	int initState;
	string symbols;
	int nextState;
	bool isFinalState;
};

struct AFDConfig
{
	int qtdLinhas;
	int symbolQTD;
	vector<string> symbols;
	int stateNumber;
	int finalStateQTD;
	vector<int> finalState;
	int transitionsQTD;
	struct transition transitionsStruct[30];
};

bool isDigitNumber(int*, string);
bool AFDReading();
void fileReading();
bool AFDAccept(struct transition[]);
void printQuintuple();
void auxPrint(string, char, string, vector<string>);
void stringCheck(string);
