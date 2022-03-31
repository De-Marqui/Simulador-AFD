#include "afd.hpp"
#include <string>

using namespace std;
AFDConfig AFD = { 0,			// int LinesQTD;
		  0,			// int symbolQTD;
		  {},			// vector<string> symbols;
		  0,			// int stateNumber;
		  0,			// int finalStateQTD;
		  {},			// vector<int> finalState;
		  0,			// int transitionsQTD;
		  {0, "", 0, false}	// struct transition transitionsStruct[30];
};


bool isDigitNumber(int* Data, string line)
{
	// -------------------------------------------------------------------------------------------------------
	// | Function that Returns whether or not the Parsed Data in question is a digit and returns a 		 |
	// | boolean value in the result of this comparison, true if it is, or false if it is not an integer	 |
	// -------------------------------------------------------------------------------------------------------
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
	// -------------------------------------------------------------------------------------------------------
	// | For Generalized To print the most diverse types of variables -> Adaptive int i value...		 |
	// | ... i checks if the read value in question is a vector or number, and executes the loop 		 |
	// ------------------------------------------------ ------------------------------------------------------
	// | Adaptive Impressions, using ternary operators to verify data entry 				 |
	// | variable value "indexVar" -> represents whether struct values will be handled or not 		 |
	// | States == Vector -> Vector | States != Normal array indexing method				 |
	// -------------------------------------------------------------------------------------------------------
	int indexVar = ((States != "Vector") ? stoi(States) : Vector.size());
	
	cout << "| ";
	(Prefix == "TRANSITIONS")? (cout << "\n| s: "):(cout << Symbol << " = { ");

	for (int i = 0; i < indexVar; i++)
	{
		if (Prefix != "TRANSITIONS") {
			(States != "Vector") ? (cout << Prefix << i << ((i != indexVar - 1) ? ", " : " ")) :
									(cout << Prefix << Vector.at(i) << ((i != indexVar - 1) ? ", " : " "));
		}
		else {
			cout << endl << "| f( q" << AFD.transitionsStruct[i].initState << ", " << AFD.transitionsStruct[i].symbols << " )";
			cout << " = q" << AFD.transitionsStruct[i].nextState;
		}
	}
	(Prefix != "TRANSITIONS") ? (cout << "}" << endl) : cout << endl;
}

void printQuintuple()
{
	// -------------------------------------------------------------------------------------------------------
	// | Quintuple Print, passing the parameters to be printed to the aux Print function	                 |
	// -------------------------------------------------------------------------------------------------------
	vector<string> temp;
	transform(begin(AFD.finalState), end(AFD.finalState), back_inserter(temp), [](int i) { return to_string(i); });

	cout << "\nM = ( Q, E, s, q0, F )" << endl << endl;
	auxPrint(to_string(AFD.stateNumber), 'Q', "q", AFD.symbols);
	auxPrint(to_string(AFD.stateNumber), 'Q', "q", AFD.symbols);
	auxPrint("Vector", 'E', "", AFD.symbols);
	cout << "| q0 = q0\n";
	auxPrint("Vector", 'F', "q", temp);
	auxPrint(to_string(AFD.transitionsQTD), '\0', "TRANSITIONS", temp);
}


bool AFDAccept()
{
	// -------------------------------------------------------------------------------------------------------
	// | Checking transitions in .txt															         |
	// -------------------------------------------------------------------------------------------------------
	vector<string> symbolFound;
	int stateFound = 0;

	for (int i = 0; i < AFD.transitionsQTD; i++)
	{
		// -------------------------------------------------------------------------------------------------------
		// | Check when there is a state change -> clear symbols already checked in that state 			 |
		// | Avoiding divergence of transitions with the same symbol           					 |
		// -------------------------------------------------------------------------------------------------------
		
		if (stateFound != AFD.transitionsStruct[i].initState)
		{
			symbolFound.clear();
			stateFound = AFD.transitionsStruct[i].initState;
		}
		else{
			symbolFound.push_back(AFD.transitionsStruct[i].symbols);
		}
			

		// -------------------------------------------------------------------------------------------------------
		// | Checking transitions from a state (x) with the same symbol -> Not AFD				 |	
		// -------------------------------------------------------------------------------------------------------
		if (count(symbolFound.begin(), symbolFound.end(), AFD.transitionsStruct[i].symbols)>1)
		{
			cout << "\n[ERROR -> MULTIPLE TRANSITIONS FROM A SAME SYMBOL <NON-DETERMINISTIC>]\n";
			return 0;
		}

		// -------------------------------------------------------------------------------------------------------
		// | Verification of Symbols established in .txt, avoiding transitions with symbols not informed	 |	
		// -------------------------------------------------------------------------------------------------------
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
	}
	return 1;
}


bool AFDReading() {
	// -------------------------------------------------------------------------------------------------------
	// | Reading the AFD Automato Configuration File						         |
	// -------------------------------------------------------------------------------------------------------
	
	ifstream file;
	string arqName;
	string line;

	// -------------------------------------------------------------------------------------------------------
	// | Repetition As long as the supplied .txt containing the settings is not entered correctly 	         |
	// -------------------------------------------------------------------------------------------------------
	do
	{
		cout << endl << "[Enter AFD File Name To Read]" << endl << ">> ";
		cin >> arqName;
		file.open(arqName);
	} while (!file.is_open());


	/* First Line A. Number of Alphabet Symbols (qty E)*/
	getline(file, line);
	if ((!isDigitNumber(&AFD.symbolQTD, line)) || AFD.symbolQTD > 12)
	{
		if (AFD.symbolQTD > 12) cout << "[ERROR -> MAX SYMBOL QTD == 12]" << endl;
		return 0;
	}

	/* Second Line A. The Symbols of the Alphabet (E)*/
	getline(file, line);
	stringstream ss(line);
	string temp;
	int counts = 0;
	while (ss >> temp)
	{
		counts++;

		/* Booleans containing the conditions that must be followed */
		bool charIsLower = islower(temp[0]),
			 charSize = (temp.size() == 1),
			 charCount = counts <= 12,
			 isDigitOrNum = (isdigit(temp[0]) || isalpha(temp[0]));
	
		/* adaptive boolean comparator, changing parameters depending on whether symbols are numbers or letters*/
		bool comparator = (isdigit(temp[0])) ? (charSize && charCount && isDigitOrNum) : 
											   (charIsLower && charSize && charCount && isDigitOrNum);

		/* If all conditions are met, pushback the symbols vector in the AFD struct */
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
	
	/* Checking if the number of symbols corresponds to the one informed in line 1 */
	if (AFD.symbols.size() != AFD.symbolQTD)
	{
		cout << "\n[ERROR -> SYMBOLS QTD NOT EQUIVALENT TO WHAT WAS SPECIFIED]" << endl;
		return 0;
	}

	/* Checking if the vector contains only unique symbols */
	sort(AFD.symbols.begin(), AFD.symbols.end());
	auto it = unique(AFD.symbols.begin(), AFD.symbols.end());
	bool wasUnique = (it == AFD.symbols.end());
	if (!wasUnique)
	{
		cout << "[ERROR -> REPEATED CHAR]" << endl;
		return 0;
	}


	/* Third Line A. Numbers of States in the DFA (Q) */
	getline(file, line);
	if (!isDigitNumber(&AFD.stateNumber, line)) return 0;
	if (AFD.stateNumber > 30)
	{
		cout << "[ERROR -> STATES NUM > 30]" << endl;
		return 0;
	}

	/* Fourth line A. Number of final states (qty F) */
	getline(file, line);
	if (!isDigitNumber(&AFD.finalStateQTD, line) || (AFD.finalStateQTD > AFD.stateNumber))
	{
		if (AFD.finalStateQTD > AFD.stateNumber) cout << endl << "[ERROR -> FINAL STATE QTD WAS GREATER THAN STATE NUMBER QTD]" << endl;
		return 0;
	}

	/* Fifth Line A. Numbers corresponding to the final states (F) */
	getline(file, line);
	stringstream nums(line);
	while (nums >> temp)
	{
		if (isdigit(temp[0]))
		{
			if (stoi(temp) < AFD.stateNumber && stoi(temp) >= 0)
				AFD.finalState.push_back(stoi(temp));
		}
		else
		{
			cout << "[ERROR - NOT A INTEGER NUMBER WAS READED]\n" << endl;
			return 0;
		}
	}
	if (AFD.finalState.size() != AFD.finalStateQTD)
	{
		cout << endl << "[ERROR - finalStatesSymbolQTD != finalStatesQTD]\n" << endl;
		return 0;
	}

	int  finalStateSize = AFD.finalState.size();
	if (finalStateSize > AFD.stateNumber)
	{
		cout << "[ERROR - THERE ARE MORE FINAL STATES THAN EXISTING STATES]" << endl;
		return 0;
	}

	/* sixth Line A. Number of State Transitions and Transitions */
	getline(file, line);
	if (!isDigitNumber(&AFD.transitionsQTD, line)) return 0;

	bool is = false, s = false, ns = false;
	int initstatetemp = -1, nextstatetemp = -1, flag = 0;
	string symbols = "null";

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
				if (stoi(tempor) >= AFD.stateNumber)
				{
					cout << "\n[ERROR - STATE NOT DECLARED PRESENT IN TRANSITION LINE]\n";
					return 0;
				}

				if (i == AFD.transitionsQTD - 1 && (stoi(tempor) == initstatetemp)) 
					is = true;

				initstatetemp = stoi(tempor);
				AFD.transitionsStruct[i].initState = stoi(tempor);
				flag++;
			}
			else if (isdigit(tempor[0]) && flag == 2)
			{
				if (stoi(tempor) >= AFD.stateNumber)
				{
					cout << "\n[ERROR - STATE NOT DECLARED PRESENT IN TRANSITION LINE]\n";
					return 0;
				}

				if (i == AFD.transitionsQTD - 1 && (stoi(tempor) == nextstatetemp)) 
					ns = true;
				
				nextstatetemp = stoi(tempor);
				AFD.transitionsStruct[i].nextState = stoi(tempor);

				if (count(AFD.finalState.begin(), AFD.finalState.end(), AFD.transitionsStruct[i].nextState))
					AFD.transitionsStruct[i].isFinalState = true;
				else
					AFD.transitionsStruct[i].isFinalState = false;

				flag = 0;
			}
			else
			{
				if ((isdigit(tempor[0]) || isalpha(tempor[0])) && charSize) {
					if (!count(AFD.symbols.begin(), AFD.symbols.end(), string(1, tempor[0])))
					{
						cout << endl << "[ERROR -> SYMBOL " << tempor << " NOT INFORMED IN afd.txt]" << endl;
						return 0;
					}
					
					if (i == AFD.transitionsQTD - 1 && (tempor == symbols)) 
						s = true;
					
					symbols = tempor;
					AFD.transitionsStruct[i].symbols = tempor;
				}
				else
				{
					cout << "[ERROR -> TRANSITION SYMBOL NOT INT OR ALPHA]" << endl;
					return 0;
				}
				flag++;
			}
			if (is && ns && s) {
				cout << "\n[ERROR - MORE NUMBER OF TRANSITION STATES REPORTED THAN PRESENT]\n";
				return 0;
			}
		}
	}
	if (AFDAccept()) {
		cout << "[SUCCESS! -> .txt FILE READED!]" << endl;
		return 1;
	}
	return 0;
}


void stringCheck(string cadeia)
{
	// ------------------------------------------------ -------------------------------------------------- -----
	// | Checking the given string in question, to see if it was accepted or not according to the configuration |
	// ------------------------------------------------ -------------------------------------------------- -----
	int actualState = 0;
	string formatIsFinal1 = " ",
		   formatIsFinal2 = " ";

	cout << "Analyzed String: " << cadeia << endl;
	int cadeiaLength = cadeia.length();
	for (int i = 0; i < cadeiaLength; i++)
	{
		char letter = cadeia[i];
		if (!count(AFD.symbols.begin(), AFD.symbols.end(), string(1, letter)))
		{
			cout << "[ERROR -> SYMBOL " << letter << " NOT INFORMED IN afd.txt]" << endl << "[>> String Rejected <<]" << endl << endl;
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
	cout << "[>> String " << (count(AFD.finalState.begin(), AFD.finalState.end(), actualState) ? "Accepted" : "Rejected") << " <<]" << endl << endl;
}

void fileReading() {
	// -------------------------------------------------------------------------------------------------------
	// | Reading the File Containing the Chains for reading	   					         |
	// -------------------------------------------------------------------------------------------------------

	ifstream file;
	string fileName;
	string line;
	int counter;
	vector<string> cadeias;

	// -------------------------------------------------------------------------------------------------------
	// | Repetition As long as the given .txt containing the settings is not correctly entered	         |
	// -------------------------------------------------------------------------------------------------------
	do
	{
		cout << endl << "[Enter the name of the strings file to be read]" << endl << ">> ";
		cin >> fileName;
		file.open(fileName);
	} while (!file.is_open());
	cout << "[FILE READ SUCCESSFULLY]\n" << endl;

	// -------------------------------------------------------------------------------------------------------
	// | Reading and Storage of Strings								         |
	// -------------------------------------------------------------------------------------------------------
	getline(file, line);
	if (!isDigitNumber(&counter, line)) return;
	int cadeiaSize = stoi(line);

	while (getline(file, line))
	{
		int  lineSize = line.size();
		if (line.size() > 100)
		{
			cout << "[ERROR - THE NUMBER OF CHARACTERS IN THE LINE " << counter << " IS OVER 100]\n" << endl;
			return;
		}
		cadeias.push_back(line);
	}

	// -------------------------------------------------------------------------------------------------------
	// | Loop that checks whether the linestring is accepted or not						 |
	// -------------------------------------------------------------------------------------------------------
	int linhascadeiaSize = cadeias.size();
	for (int i = 0; i < cadeiaSize; i++) {
		if (i < linhascadeiaSize) stringCheck(cadeias.at(i));
	}	
}
