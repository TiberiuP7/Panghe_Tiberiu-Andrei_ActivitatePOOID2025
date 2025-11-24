#include<iostream>
#include<string>
#include<vector> 
#include<algorithm> 
#include<fstream>
#define CRT_SECURE_NO_WARNINGS
using namespace std;

class Colectionar {
	string nume;
	int nrBancnote;
	int* aniEmisiune;
	float valoareColectie;

public:
	Colectionar() {
		this->nume = "";
		this->nrBancnote = 0;
		this->aniEmisiune = NULL;
		this->valoareColectie = 0.0f;
	}

	Colectionar(string nume, int nrBancnote, int* aniEmisiune) {
		this->nume = nume;
		this->nrBancnote = nrBancnote;
		this->aniEmisiune = new int[nrBancnote];
		for (int i = 0; i < nrBancnote; i++) {
			this->aniEmisiune[i] = aniEmisiune[i];
		}
		float valoareColectie = 0.0f;
		for (int i = 0; i < nrBancnote; i++) {
			valoareColectie += aniEmisiune[i]; // Exemplu de calcul al valorii
		}
		this->valoareColectie = valoareColectie;
	}

	int getNrBancnote() {
		return this->nrBancnote;
	}

	void setNrBancnote(int nrBancnote) {
		this->nrBancnote = nrBancnote;
	}

	float getValoareColectie() {
		return this->valoareColectie;
	}

	void setValoareColectie(float valoareColectie) {
		this->valoareColectie = valoareColectie;
	}

	Colectionar(const Colectionar& c) {
		this->nume = c.nume;
		this->nrBancnote = c.nrBancnote;
		this->aniEmisiune = new int[c.nrBancnote];
		for (int i = 0; i < c.nrBancnote; i++) {
			this->aniEmisiune[i] = c.aniEmisiune[i];
		}
		this->valoareColectie = c.valoareColectie;
	}

	~Colectionar() {
		if (this->aniEmisiune != NULL) {
			delete[] this->aniEmisiune;
		}
	}

	friend ostream& operator<<(ostream& os, const Colectionar& c) { // Fix: Pass ostream and Colectionar by reference
		os << "Nume: " << c.nume << endl;
		os << "Numar Bancnote: " << c.nrBancnote << endl;
		os << "Ani Emisiune: ";
		for (int i = 0; i < c.nrBancnote; i++) {
			os << c.aniEmisiune[i] << " ";
		}
		os << endl;
		os << "Valoare Colectie: " << c.valoareColectie << endl;
		return os;
	}

	Colectionar& operator=(const Colectionar& c) { // Fix: Pass Colectionar by reference
		if (this != &c) { // Avoid self-assignment
			this->nume = c.nume;
			this->nrBancnote = c.nrBancnote;
			if (this->aniEmisiune != NULL) {
				delete[] this->aniEmisiune;
			}
			this->aniEmisiune = new int[c.nrBancnote];
			for (int i = 0; i < c.nrBancnote; i++) {
				this->aniEmisiune[i] = c.aniEmisiune[i];
			}
			this->valoareColectie = c.valoareColectie;
		}
		return *this;
	}

	operator float() const {
		// Conversion operator to float
		return this->valoareColectie;
	}

	float medieBancnote() const {
		if (nrBancnote == 0) return 0.0f; // Avoid division by zero
		float suma = 0.0f;
		for (int i = 0; i < nrBancnote; i++) {
			suma += aniEmisiune[i];
		}
		return suma / nrBancnote;
	}

	friend ofstream& operator<<(ofstream& out, const Colectionar& c) {
		out << c.nume << endl;
		out << c.nrBancnote << endl;
		for (int i = 0; i < c.nrBancnote; i++) {
			out << c.aniEmisiune[i] << " ";
		}
		out << endl;
		out << c.valoareColectie << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Colectionar& c) {
		in >> c.nume;
		in >> c.nrBancnote;
		if (c.aniEmisiune != NULL) {
			delete[] c.aniEmisiune;
		}
		c.aniEmisiune = new int[c.nrBancnote];
		for (int i = 0; i < c.nrBancnote; i++) {
			in >> c.aniEmisiune[i];
		}
		in >> c.valoareColectie;
		return in;
	}

	bool operator<(const Colectionar& c) const {
		return this->valoareColectie < c.valoareColectie;
	}

	void serializare(string numeFisier) {
		ofstream file(numeFisier, ios::out | ios::binary);
		if (file.is_open()) {
			int lungimeNume = this->nume.size();
			file.write((char*)&lungimeNume, sizeof(lungimeNume));
			file.write(this->nume.c_str(), lungimeNume + 1);
			file.write((char*)&this->nrBancnote, sizeof(nrBancnote));
			for (int i = 0; i < this->nrBancnote; i++) {
				file.write((char*)&this->aniEmisiune[i], sizeof(aniEmisiune[i]));
			}
			file.write((char*)&this->valoareColectie, sizeof(valoareColectie));
			file.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului pentru scriere." << endl;
		}
	}

	void deserializare(string numeFisier) {
		ifstream file(numeFisier, ios::in | ios::binary);
		if (file.is_open()) {
			int lungimeNume = 0;
			file.read((char*)&lungimeNume, sizeof(lungimeNume));
			char* aux = new char[lungimeNume + 1];
			file.read(aux, lungimeNume + 1);
			this->nume = aux;
			delete[] aux;

			file.read((char*)&this->nrBancnote, sizeof(nrBancnote));
			if (this->aniEmisiune != NULL) {
				delete[] this->aniEmisiune;
			}
			this->aniEmisiune = new int[this->nrBancnote];
			for (int i = 0; i < nrBancnote; i++) {
				file.read((char*)&this->aniEmisiune[i], sizeof(aniEmisiune[i]));
			}
			file.read((char*)&this->valoareColectie, sizeof(valoareColectie));
			file.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului pentru citire." << endl;
		}
	}

};

class Catalog{
	string nume;
	int nrColectii;
	Colectionar* colectii;

public:
	Catalog() {
		this->nume = "";
		this->nrColectii = 0;
		this->colectii = NULL;
	}

	Catalog(string nume, int nrColectii, Colectionar* colectii) {
		this->nume = nume;
		this->nrColectii = nrColectii;
		this->colectii = new Colectionar[nrColectii];
		for (int i = 0; i < nrColectii; i++) {
			this->colectii[i] = colectii[i];
		}
	}

	~Catalog() {
		if (this->colectii != NULL) {
			delete[] this->colectii;
		}
	}

	friend ostream& operator<<(ostream& os, const Catalog& c) {
		os << "Nume Catalog: " << c.nume << endl;
		os << "Numar Colectii: " << c.nrColectii << endl;
		for (int i = 0; i < c.nrColectii; i++) {
			os << c.colectii[i];
		}
		return os;
	}

	Catalog(const Catalog& c) {
		this->nume = c.nume;
		this->nrColectii = c.nrColectii;
		this->colectii = new Colectionar[c.nrColectii];
		for (int i = 0; i < c.nrColectii; i++) {
			this->colectii[i] = c.colectii[i];
		}
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	int getNrColectii() {
		return this->nrColectii;
	}
	void setNrColectii(int nrColectii) {
		this->nrColectii = nrColectii;
	}
};  

class ColectieDeLux : public Colectionar {
	string tutore;

public:
	ColectieDeLux() : Colectionar() {
		this->tutore = "";
	}

	ColectieDeLux(string nume, int nrBancnote, int* aniEmisiune, string tutore) : Colectionar(
		nume, nrBancnote, aniEmisiune) {
		this->tutore = tutore;
	}

	ColectieDeLux(const ColectieDeLux& cl) : Colectionar(cl) {
		this->tutore = cl.tutore;
	}

	~ColectieDeLux() {

	}

	ColectieDeLux& operator=(const ColectieDeLux& cl) {
		if (this != &cl) {
			Colectionar::operator=(cl);
			this->tutore = cl.tutore;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const ColectieDeLux& cl) {
		out << (Colectionar&)cl;
		out << cl.tutore << endl;
		return out;
	}

	ColectieDeLux(const Colectionar& cl) : Colectionar(cl) {
		this->tutore = "Spaniolul";
	}
};

int main() {  
    Colectionar c1("Ion", 3, new int[3]{ 1990, 1995, 2000 });  
    cout << c1 << endl;  
    Colectionar c2 = c1; // Copy constructor  
    cout << c2 << endl;  
    Colectionar c3;  
    c3 = c1; // Assignment operator  
    cout << c3 << endl;  

    Colectionar c4("Maria", 2, new int[2]{ 1985, 1990 });  
    cout << c4 << endl;  
    float valoare = (float)c4; // Conversion operator  

    cout << "Valoarea colectiei lui Maria: " << valoare << endl;  

    Catalog catalog("Catalog Bancnote", 2, new Colectionar[2]{ c1, c4 });  
    cout << catalog << endl;  

    Catalog catalog2 = catalog; // Copy constructor  
    cout << catalog2 << endl;  

    Catalog catalog3("Catalog Nou", 1, new Colectionar[1]{ c2 });  
    cout << catalog3 << endl;  

	float media = c1.medieBancnote();
	cout << "Media bancnotelor lui Ion: " << media << endl;
	cout << "Valoarea colectiei lui Ion: " << (float)c1 << endl;
	cout << endl;

    // Fix: Ensure vector is defined and used correctly  
 //   vector<Catalog> cataloage;  
 //   cataloage.push_back(catalog);  
 //   cataloage.push_back(catalog2);  
 //   cataloage.push_back(catalog3);

	//cout << "Numar cataloage: " << cataloage.size() << endl;

	//for (int i = 0; i < cataloage.size(); i++) {
	//	cout << "Catalog " << i + 1 << ": " << endl << cataloage[i] << endl;
	//}

	///*std::sort(cataloage.begin(), cataloage.end(), [](const Catalog& a, const Catalog& b) {
	//	return a.getNrColectii() < b.getNrColectii();
	//	});*/
	//std::sort(cataloage.begin(), cataloage.end());
	///*long duplicate = std::count(cataloage.begin(), cataloage.end(), catalog3);

	//cout << "Numar duplicate pentru catalog3: " << duplicate << endl;*/

	//for (int i = 0; i < cataloage.size(); i++) {
	//	cout << "Catalog " << i + 1 << ": " << endl << cataloage[i] << endl;
	//}

	vector<Colectionar> colectionari;
	colectionari.push_back(c1);
	colectionari.push_back(c4);
	colectionari.push_back(c2);
	colectionari.push_back(c3);

	for(int i = 0; i < colectionari.size(); i++) {
		cout << "Colectionar " << i + 1 << ": " << endl << colectionari[i] << endl;
	}
	cout << endl;
	// Sortare dupa valoarea colectiei
	std::sort(colectionari.begin(), colectionari.end());


	for(int i = 0; i < colectionari.size(); i++) {
		cout << "Colectionar sortat " << i + 1 << ": " << endl << colectionari[i] << endl;
	}
	cout << endl;

	long duplicate = std::count(colectionari.begin(), colectionari.end(), c1); // Count occurrences of c1

	cout << "Numar duplicate pentru c1: " << duplicate << endl;
	cout << endl;

	bool isLess = c1 < c4; // Test operator<

	bool isLessCatalog = c1 < c3; // Test operator< for Catalog

	cout << "C1 este mai mic decat C4: " << (isLess ? "Da" : "Nu") << endl;

	cout << (isLessCatalog ? "C1 este mai mic decat C3" : "C1 nu este mai mic decat C3")<< endl;

    ofstream fout("colectionari.txt", ios::out);
	fout << c1 << endl;
	fout << c4 << endl;
	fout << c2 << endl;
	fout << c3 << endl;
	cout << "Obiectul c1 a fost scris in fisierul colectionari.txt" << endl;
	fout.close();

	ifstream fin("colectionari.txt", ios::in);
	if (fin.is_open()) {
		Colectionar c5;
		fin >> c5;
		cout << "Obiectul c5 citit din fisierul colectionari.txt: " << endl;
		cout << c5 << endl;
		fin.close();
	}
	else {
		cout << "Nu s-a putut deschide fisierul colectionari.txt" << endl;
	}
	cout << endl;

	c4.serializare("colectionari.bin");

	c3.serializare("colectionari2.bin");

	Colectionar c6;
	c6.deserializare("colectionari.bin");

	cout << "Obiectul c6 citit din fisierul colectionari.bin:" << endl;
	cout << c6;
	cout << endl;

	int colectie[] = {200, 50, 2};

	ColectieDeLux cl1;
	cout << cl1;

	ColectieDeLux cl2("Ion Popescu", 3, colectie, "Americanul");
	ColectieDeLux cl3("Ion Vasilescu", 2, colectie, "Smecherul");
	ColectieDeLux cl4("Ana", 3, colectie, "Matroana");

	cout << endl;
	cl1 = cl2;
	cout << cl1;

	ColectieDeLux cl5 = cl4;

	cout << endl;

	cout << cl5 << endl << endl;
	Colectionar c7 = cl4;
	cout << c7;

	ColectieDeLux cl6 = c7;

	cout << endl << endl;
	cout << cl6;

    return 0;  
}
