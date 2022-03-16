/*
Guilherme Rodrigues Santos- 32012209
Gustavo Hiroshi Yoshio - 32033273
Victor de Marqui - 32014287
*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cstring>
#include <algorithm> 

using namespace std;


struct AFDConfig
{
	int symbolQTD;
	vector<string> symbols;
	int stateNumber;
	int finalStateQTD;
	int finalState;
	vector<string> transitions;
};

int qtdLinhas;

void AFDReading(){
	AFDConfig AFD;
  ifstream file;
  string arqName;
  string line;
	bool flag = false;
  int counter = 1;
  int counts = 0;
  
  cout << "Digite o Nome do Arquivo AFDM Para Ser Lido: ";
  cin >> arqName;
	file.open(arqName);

  if(!file){
    cout << "[ARQUIVO NAO PODE SER LIDO]\n" << endl;
    cout << "[NOME DE ARQUIVO INVALIDO]\n" << endl;
	}
	
	while(getline(file, line)){
		switch(counter){
      case 1:
				for (int i = 0; i < line.size(); i++){
					if(!isdigit(line[i])){
						cout << "[ERRO - A QUANTIDADE DE CADEIAS NAO EH INTEIRO]\n" << endl;
						return;
					}
				}	
				AFD.symbolQTD  = stoi(line);
				counter++;
			  break;
			
      case 2:
				stringstream ss(line);
				string temp;
				while (ss >> temp){
					counts++;
					if(islower(temp[0]) && (temp.size() == 1) && counts <= 12)
						AFD.symbols.push_back(temp);  
					else{
						flag = true;
						if(temp.size() > 1)
							cout << "[ERROR -> CHAR.SIZE() > 1]" << endl;
          	else if(counts > 12){
							cout << "[ERROR -> SIZEOF() > 12]" << endl;
							break;
						}
						else
							cout << "[ERROR -> CHAR != LOWER]" << endl;
					} 
				}
			
		    
				if ((unique(AFD.symbols.begin(), AFD.symbols.end()) != AFD.symbols.end())) 
					cout << "[ERROR -> REPITED CHAR]" << endl;
				
				if (flag) return;

				counter++;
        break;
    }
				
	}
  counter++;
}


void fileReading(){
  ifstream file;
  string fileName;
  string line;
  int counter = 1;

  cout << "Digite o Nome do Arquivo Para ser lido: ";
  cin >> fileName;
  file.open(fileName);
  
  if(!file){
    cout << "[ARQUIVO NAO PODE SER LIDO]\n" << endl;
    cout << "[NOME DE ARQUIVO INVALIDO]\n" << endl;
  }
  
  while(getline(file, line)){
    if(counter == 1){
      for (int i = 0; i < line.size(); i++){
        if(!isdigit(line[i])){
          cout << "[ERRO - A QUANTIDADE DE CADEIAS NAO EH INTEIRO]\n" << endl;
          return;
        }
				qtdLinhas = stoi(line);
      }		
    }
		if ( line.size() > 100){
			cout << "[ERRO - A QUANTIDADE DE CARACTERES PRESENTES NA LINHA " << counter << " EH SUPERIOR A 100]\n" << endl;
			return;
		}
    counter++;
  }

  cout << "[ARQUIVO LIDO COM SUCESSO]\n" << endl;
}

int main() {
  int option;

  while(option!=0){
    cout << "Escolha a opção digitando um número: " << endl;
    cout << "1. Ler dados do AFD de arquivo." << endl;
    cout << "2. Mostrar a quíntupla para o AFD lido." << endl;
    cout << "3. Avaliar cadeias lidas de arquivo." << endl;
    cout << "4. Avaliar novas cadeias pelo teclado." << endl;
    cout << "0. Encerrar a sessão." << endl;
    cout << "Resposta: ";
    cin >> option;
    cout << "\n";
    switch(option){
      case 1:
        AFDReading();
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
    }
  }
}
