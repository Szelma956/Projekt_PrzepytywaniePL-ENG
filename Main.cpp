#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <stdlib.h> 
#include <time.h>

using namespace std;

string filep;
string filee;
string fileex;

struct word {

    string polish;
    string english;

};


void open_filep() {

	int check = 0;

	do {
	
		cout << "Prosze podac nazwe pliku zawierajacego polskie slowa" << " ";
		cout << "(Plik musi sie znajdowac w tym samym katalogu co program)" << endl;

		cin >> filep;

		filep += ".txt";

		cout << endl;

		ifstream polish;
		polish.open(filep);

		if (polish.good() == true) {

			check = 1;

			cout << "Uzyskano dostep do pliku z polskimi slowami !";
			cout << endl << endl;

			system("pause");

			system("cls");
		}
		else {
			cout << "Dostep do pliku z polskimi slowami zostal zabroniony!";
			cout << endl << endl;
			cout << "Przykladowe powody bledu odczytu :" << endl << endl;
			cout << "Plik nie istnieje na dysku" << endl;
			cout << "Brak uprawnien odczytu do pliku" << endl << endl;

			cout << "Prosimy sprobowac ponownie" << endl;

			system("pause");

			system("cls");
		}

		polish.close();

	} while (check != 1);

}

void open_filee() {

	bool check = false;

	do {

		cout << "Prosze podac nazwe pliku zawierajacego angielskie slowa" << " ";
		cout << "(Plik musi sie znajdowac w tym samym katalogu co program)" << endl;

		cin >> filee;

		filee += ".txt";

		cout << endl;

		ifstream english;
		english.open(filee);

		
			if (english.good() == true) {

				check = true;

				cout << "Uzyskano dostep do pliku z angielskimi slowami !";
				cout << endl << endl;

				system("pause");

				system("cls");
			}
			else {
				cout << "Dostep do pliku z polskimi slowami zostal zabroniony!";
				cout << endl << endl;
				cout << "Przykladowe powody bledu odczytu :" << endl << endl;
				cout << "Plik nie istnieje na dysku" << endl;
				cout << "Brak uprawnien odczytu do pliku" << endl << endl;

				system("pause");

				system("cls");
			}

			english.close();
		
		
	} while (check != true);
	
}

int to_test_filep() {

	unsigned int number_of_linesp = 0;
	string line;

	ifstream polish;
	polish.open(filep);

	do {
		getline(polish, line);
		number_of_linesp++;
	} while (!polish.eof());
	
	polish.close();

	return number_of_linesp;
}

int to_test_filee() {

	unsigned int number_of_linese = 0;
	string line;

	ifstream english;
	english.open(filee);

	do {
		getline(english, line);
		number_of_linese++;
	} while (!english.eof());

	english.close();

	return number_of_linese;
	
}

void start(unsigned int* p, unsigned int* e) {

	do {
		open_filep();
		open_filee();

		if (filee != filep) {
			
			(*p) = to_test_filep();
			(*e) = to_test_filee();

			if ((*p) == (*e)) {

				cout << "Liczba linii w plikach jest zgodna" << endl << endl;

				system("pause");

				system("cls");

			}
			else {

				cout << "Liczba linii w plikach nie jest zgodna" << endl << endl;
				cout << "Prosimy o ponowne wczytanie poprawnych plikow" << endl << endl;

				system("pause");

				system("cls");
			}
		}
		else {
		
			cout << "Plik ze slowami polskimi, oraz plik ze slowami angielskimi to ten sam plik !" << endl << endl;
			 cout << "Prosimy o ponowne wczytanie poprawnych plikow" << endl << endl;

			(*p) = 1;
			(*e) = 0;

			system("pause");

			system("cls");
				
		}


	} while ((*p) != (*e));

	cout << "Prosze podac nazwe zadanego pliku, ktory bedzie zawierac wyniki" << endl;
	cin >> fileex;
	fileex += ".txt";

	system("cls");


}

void load_files(word* tab) {
	
	unsigned ID = 0;
	string line;
	string transformed;

	ifstream english;
	english.open(filee);

	do {
		getline(english, line);
		transformed = "";

		locale loc;
		for (string::size_type i = 0; i < line.length(); ++i) {
			transformed += tolower(line[i], loc);
		}

		tab[ID].english = transformed;

		ID++;
	} while (!english.eof());

	english.close();

	ID = 0;

	ifstream polish;
	polish.open(filep);

	do {
		getline(polish, line);
		
		transformed = "";

		locale loc;
		for (string::size_type i = 0; i < line.length(); ++i) {
			transformed += tolower(line[i], loc);
		}

		tab[ID].polish = transformed;

		ID++;
	} while (!polish.eof());

	polish.close();
	
}

void test1(word* tab, unsigned int n) {
	
	string test;
	string test2;
	unsigned int score = 0;

	unsigned int * list = new unsigned int[n];

	for (unsigned int i = 0; i < n; i++) {
		list[i] = i;
	}
	
	srand(time(NULL));
	unsigned int x = 0;
	
	unsigned int to_check = n;

	do {

		unsigned int random;

		random = (rand() % (to_check)) + 0;
		
		test2 = "";
		
		cout << "Przetlumacz slowo : " << tab[list[random]].english << endl <<endl;
		cin >> test;
		cout << endl;

		locale loc;
		for (string::size_type i = 0; i < test.length(); ++i) {
			test2 += tolower(test[i], loc);
		}

		if (test2 == tab[list[random]].polish) {
			cout << "Dobrze!" << endl << endl;
			score++;
		}
		else{
			cout << "Zle!" << endl << endl;
		}

		for (unsigned int i = random; i < n; i++) {
		
			if (i < n - 1) {
				list[i] = list[i + 1];
			}

		}

		x++;
		to_check = n - x;

	} while (to_check != 0);

	cout << "Koniec Testu" << endl << endl;
	cout << "Wyniki zostana zapisane w pliku : " << fileex << endl;
	system("pause");
	system("cls");

	ofstream result;
	result.open(fileex);
	result << "Liczba pytan : " << n << endl;
	result << "Liczba poprawnych odpowiedzi : " << score << endl;

	delete[] list;

}

void test2(word* tab, unsigned int n) {
	string test;
	string test2;
	unsigned int score = 0;
	unsigned int opt;

	unsigned int* list = new unsigned int[n];

	for (unsigned int i = 0; i < n; i++) {
		list[i] = i;
	}

	srand(time(NULL));
	unsigned int x = 0;

	unsigned int to_check = n;

	do {

		unsigned int random;

		random = (rand() % (to_check)) + 0;

		test2 = "";

		opt = (rand() % 2) + 1;
		if (opt == 1) {
			cout << "Przetlumacz slowo (obcy -> polski) : " << tab[list[random]].english << endl << endl;
			cin >> test;
			cout << endl;

			locale loc;
			for (string::size_type i = 0; i < test.length(); ++i) {
				test2 += tolower(test[i], loc);
			}

			if (test2 == tab[list[random]].polish) {
				cout << "Dobrze!" << endl << endl;
				score++;
			}
			else {
				cout << "Zle!" << endl << endl;
			}
		}
		else if (opt == 2) {
			cout << "Przetlumacz slowo (polski -> obcy) : " << tab[list[random]].polish << endl << endl;
			cin >> test;
			cout << endl;

			locale loc;
			for (string::size_type i = 0; i < test.length(); ++i) {
				test2 += tolower(test[i], loc);
			}

			if (test2 == tab[list[random]].english) {
				cout << "Dobrze!" << endl << endl;
				score++;
			}
			else {
				cout << "Zle!" << endl << endl;
			}
		
		}



		for (unsigned int i = random; i < n; i++) {

			if (i < n - 1) {
				list[i] = list[i + 1];
			}

		}

		x++;
		to_check = n - x;

	} while (to_check != 0);

	cout << "Koniec Testu" << endl <<endl;
	cout << "Wyniki zostana zapisane w pliku : " << fileex << endl;
	system("pause");
	system("cls");

	ofstream result;
	result.open(fileex);
	result << "Liczba pytan : " << n << endl;
	result << "Liczba poprawnych odpowiedzi : " << score << endl;

	delete[] list;


}

void testing(unsigned int n, word* tab, unsigned int opt) {

	
	switch (opt) {
	case 1:test1(tab,n);
		break;
	case 2:test2(tab,n);
		break;
	}


}

void menu(unsigned int* opt) {
	system("cls");
	cout << "Wybierz opcje:" << endl;
	cout << "1: Tlumacz slowa z angielskiego na polski" << endl;
	cout << "2: Tlumacz slowa z angielskiego na polski, lub polskiego na angielski" << endl;
	cout << "0: Wyjdz z programu" << endl << endl;

	cout << "Podaj swoj wybor: ";
	cin >> (*opt);

	system("cls");
};

int main()
{
	unsigned int p;
	unsigned int e;
	unsigned int n;
	unsigned int opt;

			
	do{

		menu(&opt);

		if (opt == 1 or opt == 2) {
			start(&p, &e);
			
			n = p;
		}
		else {
			n = 0;
		}

		word* table;
		table = new word[n];

		if(opt == 1 or opt == 2){
			load_files(table);
		}

		switch (opt) {

		case 1:
			testing(n, table, opt);
			break;

		case 2:
			testing(n, table, opt);
			break;
		case 0:
			break;
		default:
			cout << "Niepoprawna opcja!" << endl << endl;
			system("pause");
			break;
		}

		delete[] table;
	} while (opt != 0);


	return 0;
}
