/*
Guilherme Rodrigues Santos - 32012209
Gustavo Hiroshi Yoshio - 32033273
Victor De Marqui - 32014287
*/
#include "afd.hpp"
#include <string>

using namespace std;
AFDConfig AFD = { 
                 0,		
                 0,		
                 {},	
                 0,		
                 0,		
                 {},	
                 0,		
                 {0, "", 0, false}	
                };


bool isDigitNumber(int* Data, string line)
{
	int lineSize = line.size();
	for (int i = 0; i < lineSize; i++)
	{
		if (!isdigit(line[i]))
		{
			cout << "\n[ERROR - NOT A INTEGER NUMBER WAS READED]\n" << endl;
			return false;
		}
	}
	*Data = stoi(line);
	return true;
}

void auxPrint(string States, char Symbol, string Prefix, vector<string> Vector)
{
	int indexVar = ((States != "Vector") ? stoi(States) : Vector.size());
  
	cout << "| ";
  (Prefix == "TRANSITIONS")? (cout << "\n| s: "):(cout << Symbol << " = { ");
  
	for (int i = 0; i < indexVar; i++)
	{
		if (Prefix != "TRANSITIONS") 
    {
			(States != "Vector") ? (cout << Prefix << i << ((i != indexVar - 1) ? ", " : " ")) :
                             (cout << Prefix << Vector.at(i) << ((i != indexVar - 1) ? ", " : " "));
		}
		else 
    {
			cout << endl << "| f( q" << AFD.transitionsStruct[i].initState << ", " << AFD.transitionsStruct[i].symbols << " )";
			cout << " = q" << AFD.transitionsStruct[i].nextState;
		}
	}
	(Prefix != "TRANSITIONS") ? (cout << "}" << endl) : cout << endl;
}

void printQuintuple()
{
	vector<string> temp;
	transform(begin(AFD.finalState), end(AFD.finalState), back_inserter(temp), [](int i) { return to_string(i); });

	cout << "\nM = ( Q, E, s, q0, F )" << endl << endl;
	auxPrint(to_string(AFD.stateNumber), 'Q', "q", AFD.symbols);
	auxPrint("Vector", 'E', "", AFD.symbols);
	cout << "| q0 = q0\n";
	auxPrint("Vector", 'F', "q", temp);
	auxPrint(to_string(AFD.transitionsQTD), '\0', "TRANSITIONS", temp);
}

void stringCheck(string cadeia)
{
	int actualState = 0;
	string formatIsFinal1 = " ",
		   formatIsFinal2 = " ";

	cout << "Cadeia Analisada: " << cadeia << endl;
	int cadeiaLength = cadeia.length();
	for (int i = 0; i < cadeiaLength; i++)
	{
		char letter = cadeia[i];
		if (!count(AFD.symbols.begin(), AFD.symbols.end(), string(1, letter)))
		{
			cout << endl << "[ERROR -> SYMBOL " << letter << " NOT INFORMED IN afd.txt]" << endl;
			return;
		}

		for (int j = 0; j < AFD.transitionsQTD; j++)
		{
			if ((actualState == AFD.transitionsStruct[j].initState) && (string(1, letter) == AFD.transitionsStruct[j].symbols))
			{
				cout << "[ " << formatIsFinal1 << "q" << actualState << formatIsFinal2;
				actualState = AFD.transitionsStruct[j].nextState;

				formatIsFinal1 = (count(AFD.finalState.begin(), AFD.finalState.end(), actualState)) ? "(" : " ";
				formatIsFinal2 = (count(AFD.finalState.begin(), AFD.finalState.end(), actualState)) ? ")" : " ";

				cout << " >> " << string(1, letter) << " >> " << formatIsFinal1 << "q" << actualState << formatIsFinal2 << "]" << endl;
				break;
			}
		}
	}
	cout << "[>> Cadeia " << (count(AFD.finalState.begin(), AFD.finalState.end(), actualState) ? "Aceita" : "Rejeitada") << " <<]" << endl << endl;
}


bool AFDAccept(struct transition transitions[])
{
	vector<string> symbolFound;
	vector<int> stateFound;

	for (int i = 0; i < AFD.transitionsQTD; i++)
	{
		if (count(stateFound.begin(), stateFound.end(), AFD.transitionsStruct[i].initState))
			symbolFound.clear();
		else
			stateFound.push_back(AFD.transitionsStruct[i].initState);


		if (count(symbolFound.begin(), symbolFound.end(), AFD.transitionsStruct[i].symbols))
		{
			cout << "\n[ERROR -> MULTIPLE TRANSITIONS FROM A SAME SYMBOL <NON-DETERMINISTIC>]\n";
			return 0;
		}
		else
		{
			if (count(AFD.symbols.begin(), AFD.symbols.end(), AFD.transitionsStruct[i].symbols))
				symbolFound.push_back(AFD.transitionsStruct[i].symbols);
			else
			{
				cout << "\n[ERROR-> SYMBOL (" << (AFD.transitionsStruct[i].symbols) << ") NOT DECLARED PREVIOUSLY IN <TXT>]";
				return 0;
			}
		}
		cout << endl << "[SUCCESS! -> AUTOMATO WAS READED SUCCESSFULLY!]" << endl;
	}
	return 1;
}

bool AFDReading() {
	ifstream file;
	string arqName;
	string line;

	do
	{
		cout << endl << "[Digite o Nome do Arquivo AFDM Para Ser Lido]" << endl << ">> ";
		cin >> arqName;
		file.open(arqName);
	} while (!file.is_open());

	getline(file, line);
	if ((!isDigitNumber(&AFD.symbolQTD, line)) || AFD.symbolQTD > 12)
	{
		if (AFD.symbolQTD > 12) cout << "[ERROR -> MAX SYMBOL QTD == 12]" << endl;
		return 0;
	}

	getline(file, line);
	stringstream ss(line);
	string temp;
	int counts = 0;
	while (ss >> temp)
	{
		counts++;
		bool charIsLower = islower(temp[0]),
			   charSize = (temp.size() == 1),
			   charCount = counts <= 12,
			   isDigitOrNum = (isdigit(temp[0]) || isalpha(temp[0]));

		bool comparator = (isdigit(temp[0])) ? (charSize && charCount && isDigitOrNum) : 
											      (charIsLower && charSize && charCount && isDigitOrNum);

		if (comparator)
		{
			AFD.symbols.push_back(temp);
		}
		else
		{
			if (!charCount)
			{
				cout << "[ERROR -> SYMBOL QTD > 12]" << endl;
				break;
			}
			else if (!charSize) cout << "[ERROR -> CHAR.SIZE() > 1]" << endl;
			else if (!isDigitOrNum) cout << "[ERROR -> CHAR NOT INTEGER OR LETTER]" << endl;
			else cout << "[ERROR -> CHAR != LOWER]" << endl;
			return 0;
		}
	}

	if (AFD.symbols.size() != AFD.symbolQTD)
	{
		cout << "\n[ERROR -> SYMBOLS QTD NOT EQUIVALENT TO WHAT WAS SPECIFIED]" << endl;
		return 0;
	}

	sort(AFD.symbols.begin(), AFD.symbols.end());
	auto it = unique(AFD.symbols.begin(), AFD.symbols.end());
	bool wasUnique = (it == AFD.symbols.end());
	if (!wasUnique)
	{
		cout << "[ERROR -> REPITED CHAR]" << endl;
		return 0;
	}

	getline(file, line);
	if (!isDigitNumber(&AFD.stateNumber, line)) return 0;
	if (AFD.stateNumber > 30)
	{
		cout << "[ERROR -> STATES NUM > 30]" << endl;
		return 0;
	}

	getline(file, line);
	if (!isDigitNumber(&AFD.finalStateQTD, line) || (AFD.finalStateQTD > AFD.stateNumber))
	{
		if (AFD.finalStateQTD > AFD.stateNumber) cout << endl << "[ERROR -> FINAL STATE QTD WAS GREATER THAN STATE NUMBER QTD]" << endl;
		return 0;
	}

	getline(file, line);
	stringstream nums(line);
	while (nums >> temp)
	{
		if (isdigit(temp[0]))
		{
			if (stoi(temp) <= AFD.stateNumber)
				AFD.finalState.push_back(stoi(temp));
		}
		else
		{
			cout << "[ERRO - NOT A INTEGER NUMBER WAS READED]\n" << endl;
			return 0;
		}
	}

	int  finalStateSize = AFD.finalState.size();
	if (finalStateSize > AFD.stateNumber)
	{
		cout << "[ERROR - HÁ MAIS ESTADOS FINAIS QUE ESTADOS EXISTENTES]" << endl;
		return 0;
	}

	getline(file, line);
	if (!isDigitNumber(&AFD.transitionsQTD, line)) return 0;

	int flag = 0;
	for (int i = 0; i < AFD.transitionsQTD; i++)
	{
		getline(file, line);
		stringstream elem(line);
		string tempor;
		while (elem >> tempor)
		{
			bool charSize = (tempor.size() == 1);
			if (isdigit(tempor[0]) && flag == 0)
			{
				AFD.transitionsStruct[i].initState = stoi(tempor);
				flag++;
			}
			else if (isdigit(tempor[0]) && flag == 2)
			{
				AFD.transitionsStruct[i].nextState = stoi(tempor);

				if (count(AFD.finalState.begin(), AFD.finalState.end(), AFD.transitionsStruct[i].nextState))
					AFD.transitionsStruct[i].isFinalState = true;
				else
					AFD.transitionsStruct[i].isFinalState = false;
				flag = 0;
			}
			else
			{
				if ((isdigit(tempor[0]) || isalpha(tempor[0])) && charSize)
					AFD.transitionsStruct[i].symbols = tempor;
				else
				{
					cout << "[ERROR -> TRANSITION SYMBOL NOT INT OR ALPHA]" << endl;
					return 0;
				}
				flag++;
			}
		}
	}
	cout << "[SUCCESS! -> .txt FILE READED!]" << endl;
	return 1;
}

void fileReading() {
	ifstream file;
	string fileName;
	string line;
	int counter;
	vector<string> cadeias;

	do
	{
		cout << endl << "[Digite o Nome do Arquivo de Cadeias Para Ser Lido]" << endl << ">> ";
		cin >> fileName;
		file.open(fileName);
	} while (!file.is_open());

	cout << "[ARQUIVO LIDO COM SUCESSO]\n" << endl;

	getline(file, line);
	if (!isDigitNumber(&counter, line)) return;

	while (getline(file, line))
	{
		int  lineSize = line.size();
		if (line.size() > 100)
		{
			cout << "[ERRO - A QUANTIDADE DE CARACTERES PRESENTES NA LINHA " << counter << " EH SUPERIOR A 100]\n" << endl;
			return;
		}
		cadeias.push_back(line);
	}

	int cadeiaSize = cadeias.size();
	for (int i = 0; i < cadeiaSize; i++)
		stringCheck(cadeias.at(i));
}
