#include "afd.hpp"
#include <string>
using namespace std;

int main()
{
	int option = -1;
	int controlFlag = 0;
	string screenClearControl = "0";
	string cadeia = "";

	while (option != 0) {
		cout << "[Bem vindo, a seguir, temos algumas opções para escolher]" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "| 1. Ler dados do AFD de arquivo" << endl
			 << "| 2. Mostrar a quíntupla para o AFD lido" << endl
			 << "| 3. Avaliar cadeias lidas de arquivo" << endl
			 << "| 4. Avaliar novas cadeias pelo teclado" << endl
			 << "| 0. Encerrar a aplicação" << endl << endl
			 << endl << ">> Insira a opção: ";

		cin >> option;

		switch (option) {
		case 0:
			exit(0);
		case 1:
			if(AFDReading()) 
				controlFlag++;
			break;

		case 2:
			if (controlFlag >= 1) 
				printQuintuple();
			break;

		case 3:
			if (controlFlag >= 1) 
				fileReading();
			break;

		case 4:
			if (controlFlag >= 1)
			{
				while (cadeia != "RETURN")
				{
					cout << endl << "Se deseja voltar, digite RETURN";
					cout << endl << "Digite a cadeia que deseja validar: ";
					cin >> cadeia;
					if (cadeia != "RETURN")	
						stringCheck(cadeia);
				}
				cadeia = "";
			}
			break;
		}
		
		if (controlFlag < 1) cout << "[ERROR -> afd.txt NOT READED CORRECTLY]" << endl;

		do {
			cout << endl << "[1. TO CONTINUE]" << endl << ">> ";
			cin >> screenClearControl;
		} while (screenClearControl != "1");

		system("cls");
		screenClearControl = "0";
	}
}
