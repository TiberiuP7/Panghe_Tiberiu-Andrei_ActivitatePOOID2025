#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<list>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class DosarAdmitere {

	int nrOptiuni;
	string numeCandidat;
	float medieAdmitere;
	string* optiuni;
public:

	DosarAdmitere() {
		this->nrOptiuni = 0;
		this->numeCandidat = "";
		this->medieAdmitere = 0.0f;
		this->optiuni = NULL;
	}

	DosarAdmitere(int nrOptiuni, string numeCandidat, float medieAdmitere, string* optiuni) {
		this->nrOptiuni = nrOptiuni;
		this->numeCandidat = numeCandidat;
		this->medieAdmitere = medieAdmitere;
		this->optiuni = new string[nrOptiuni];
		for (int i = 0; i < nrOptiuni; i++) {
			this->optiuni[i] = optiuni[i];
		}
	}

	DosarAdmitere(int nrOptiuni, string* optiuni) {
		this->nrOptiuni = nrOptiuni;
		this->numeCandidat = "Vasile Georgescu";
		this->medieAdmitere = 10;
		this->optiuni = new string[nrOptiuni];
		for (int i = 0; i < nrOptiuni; i++) {
			this->optiuni[i] = optiuni[i];
		}
	}

	DosarAdmitere(const DosarAdmitere& d) {
		this->nrOptiuni = d.nrOptiuni;
		this->numeCandidat = d.numeCandidat;
		this->medieAdmitere = d.medieAdmitere;
		this->optiuni = new string[d.nrOptiuni];
		for (int i = 0; i < d.nrOptiuni; i++) {
			this->optiuni[i] = d.optiuni[i];
		}
	}

	~DosarAdmitere() {
		if (this->optiuni != NULL) {
			delete[] this->optiuni;
		}
	}

	DosarAdmitere& operator=(const DosarAdmitere& d) {
		if (this != &d) {
			if (this->optiuni != NULL) {
				delete[] this->optiuni;
			}
			this->nrOptiuni = d.nrOptiuni;
			this->numeCandidat = d.numeCandidat;
			this->medieAdmitere = d.medieAdmitere;
			this->optiuni = new string[d.nrOptiuni];
			for (int i = 0; i < d.nrOptiuni; i++) {
				this->optiuni[i] = d.optiuni[i];
			}
		}
		return *this;
	}

	void setNrOptiuni(int nrOptiuni) {
		this->nrOptiuni = nrOptiuni;
	}

	int getNrOptiuni() const {
		return this->nrOptiuni;
	}

	string getNumeCandidat() const {
		return this->numeCandidat;
	}
	float getMedieAdmitere() const {
		return this->medieAdmitere;
	}
	string* getOptiuni() const {
		return this->optiuni;
	}

	void setNumeCandidat(const string& numeCandidat) {
		this->numeCandidat = numeCandidat;
	}
	void setMedieAdmitere(float medieAdmitere) {
		this->medieAdmitere = medieAdmitere;
	}
	void setOptiuni(string* optiuni, int nrOptiuni) {
		if (this->optiuni != NULL) {
			delete[] this->optiuni;
		}
		this->nrOptiuni = nrOptiuni;
		this->optiuni = new string[nrOptiuni];
		for (int i = 0; i < nrOptiuni; i++) {
			this->optiuni[i] = optiuni[i];
		}
	}

	friend ostream& operator<<(ostream& out, const DosarAdmitere& d) {
		out << d.nrOptiuni << endl;
		out << d.numeCandidat << endl;
		out << d.medieAdmitere << endl;
		for (int i = 0; i < d.nrOptiuni; i++) {
			out << d.optiuni[i] << " ";
		}
		out << endl;

		return out;
	}

	DosarAdmitere& operator+=(int valoare) {
		/*if (valoare <= this->getOptiuni()->size()) {
			this->nrOptiuni = valoare;
			cout << this->getOptiuni()->size();
		}
		else 
		{
			cout << "Valoarea adaugata depaseste numarul de optiuni disponibile." << endl;
		}*/
		this->nrOptiuni = valoare;
		return *this;
	 }

	explicit operator float() {
		return this->medieAdmitere;
	}

	friend ofstream& operator<<(ofstream& out, const DosarAdmitere& d) {
		out << d.nrOptiuni << endl;
		out << d.numeCandidat << endl;
		out << d.medieAdmitere << endl;
		for (int i = 0; i < d.nrOptiuni; i++) {
			out << d.optiuni[i] << " ";
		}
		out << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, DosarAdmitere& d) {
		in >> d.nrOptiuni;
		in >> ws;
        getline(in, d.numeCandidat); // Read the entire line for numeCandidat
		in >> d.medieAdmitere;
		if (d.optiuni != NULL) {
					delete[] d.optiuni;
		}
		d.optiuni = new string[d.nrOptiuni];
		for (int i = 0; i < d.nrOptiuni; i++) {
			in >> ws;
			getline(in, d.optiuni[i]);
		}
		return in;
	}

	virtual void medieDeTransfer(float medie) {
		if (this->getMedieAdmitere() < medie) {
			this->setMedieAdmitere(medie);
		}
	};
};

class DosarAdmitereCibernetica : public DosarAdmitere {
	string Facultate;
	string Specializare;
public:
	DosarAdmitereCibernetica() : DosarAdmitere() {
		this->Facultate = "";
		this->Specializare = "";
	}

	DosarAdmitereCibernetica(int nrOptiuni, string* optiuni, string facultate, string specializare)
		: DosarAdmitere(nrOptiuni, optiuni) {
		this->Facultate = facultate;
		this->Specializare = specializare;
	};

	DosarAdmitereCibernetica(const DosarAdmitereCibernetica& d)
		: DosarAdmitere(d) {
		this->Facultate = d.Facultate;
		this->Specializare = d.Specializare;
	}

	DosarAdmitereCibernetica& operator=(const DosarAdmitereCibernetica& d) {
		if (this != &d) {
			DosarAdmitere::operator=(d);
			this->Facultate = d.Facultate;
			this->Specializare = d.Specializare;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const DosarAdmitereCibernetica& d) {
		out << d.Facultate << endl;
		out << d.Specializare << endl;
		out << (DosarAdmitere)d; // Call the base class operator<<
		return out;
	}

    //friend istream& operator>>(istream& in, DosarAdmitereCibernetica& d) {
    //    // Correct the function signature to be a friend function
    //    in >> (DosarAdmitere&)d; // Call the base class operator>>
    //    in >> ws;
    //    getline(in, d.Facultate);
    //    in >> ws;
    //    getline(in, d.Specializare);
    //    return in;
    //}

	void setFacultate(const string& facultate) {
		this->Facultate = facultate;
	}

	string getFacultate() const {
		return this->Facultate;
	}

	void medieDeTransfer(float medie) {
		if(this->getMedieAdmitere() < medie) {
			this->setMedieAdmitere(medie);
		}
	}

	DosarAdmitereCibernetica(const DosarAdmitere& d) : DosarAdmitere(d) {
		this->Facultate = "Cibernetica";
		this->Specializare = "Informatica Cibernetica";
	}

};

class ConcursAdmitere {
	string denumire;
	int an;
	int nrDosare;
	DosarAdmitere* dosare;
public:

	ConcursAdmitere() {
		this->denumire = "";
		this->an = 0;
		this->nrDosare = 0;
		this->dosare = NULL;
	}

	ConcursAdmitere(string denumire, int an, int nrDosare, DosarAdmitere* dosare) {
		this->denumire = denumire;
		this->an = an;
		this->nrDosare = nrDosare;
		this->dosare = new DosarAdmitere[nrDosare];
		for (int i = 0; i < nrDosare; i++) {
			this->dosare[i] = dosare[i];
		}
	}

	ConcursAdmitere(const ConcursAdmitere& c) {
		this->denumire = c.denumire;
		this->an = c.an;
		this->nrDosare = c.nrDosare;
		this->dosare = new DosarAdmitere[c.nrDosare];
		for (int i = 0; i < c.nrDosare; i++) {
			this->dosare[i] = c.dosare[i];
		}
	}

	~ConcursAdmitere() {
		if (this->dosare != NULL) {
			delete[] this->dosare;
		}
	}

	ConcursAdmitere& operator=(const ConcursAdmitere& c) {
		if (this != &c) {
			if (this->dosare != NULL) {
				delete[] this->dosare;
			}
			this->denumire = c.denumire;
			this->an = c.an;
			this->nrDosare = c.nrDosare;
			this->dosare = new DosarAdmitere[c.nrDosare];
			for (int i = 0; i < c.nrDosare; i++) {
				this->dosare[i] = c.dosare[i];
			}
		}
		return *this;
	}

	void setDenumire(const string& denumire) {
		this->denumire = denumire;
	}

	string getDenumire() const {
		return this->denumire;
	}

	friend ostream& operator<<(ostream& out, const ConcursAdmitere& c) {
		out << c.denumire << endl;
		out << c.an << endl;
		out << c.nrDosare << endl;
		for (int i = 0; i < c.nrDosare; i++) {
			out << c.dosare[i] << endl;
		}
		return out;
	}

	void medieDeTransfer(float medie) {
		for (int i = 0; i < this->nrDosare; i++) {
			this->dosare[i].medieDeTransfer(medie);
		}
	}
};


int main() {
	string optiuni[] = {"Informatica", "Matematica", "Fizica"};
	DosarAdmitere dosar(3, optiuni);
	
	DosarAdmitere dosar2 = dosar; // Test copy constructor
	DosarAdmitere dosar3(dosar2);

	dosar3.setNumeCandidat("Ion Popescu");
	dosar3.setMedieAdmitere(9.5f);
	dosar3.setOptiuni(optiuni, 3);


	cout << dosar << endl;
	cout << dosar2 << endl;
	cout << dosar3 << endl;
	cout << dosar3.getNrOptiuni() << endl;
	dosar3.setNrOptiuni(2);
	cout << dosar3.getNrOptiuni() << endl;
	dosar2 += 2; // Test operator+=
	cout << dosar2.getNrOptiuni() << endl;
	cout << dosar2 << endl;
	cout << endl;

	ofstream fout("dosar.txt");
	fout << dosar2; // Test operator<< for ofstream
	fout.close();

	ifstream fin("dosar.txt");
	DosarAdmitere dosarCitit;
	fin >> dosarCitit; // Test operator>> for ifstream
	fin.close();

	cout << "Dosar citit din fisier:" << endl;	
	cout << dosarCitit << endl;
	
	DosarAdmitereCibernetica dc(3, optiuni, "Facultatea de Cibernetica", "Informatica Aplicata");
	cout << dc << endl;
	cout << endl;

	dc.medieDeTransfer(9.0f); // Test medieDeTransfer
	cout << "Dosar de admitere dupa medie de transfer:" << endl;
	cout << dc << endl;
	cout << endl;

	//Upcasting example
	DosarAdmitere dosar4 = (DosarAdmitereCibernetica)dc;
	cout << "Dosar de admitere cibernetica:" << endl;
	cout << dosar4 << endl;

	//Downcasting example
	DosarAdmitereCibernetica dc3 = (DosarAdmitere)dosar4;
	cout << "Dosar de admitere cibernetica dupa downcasting:" << endl;
	cout << dc3 << endl;

	DosarAdmitere dosarPtr[3] = { dosar, dosar2, dosar3 };
	ConcursAdmitere concurs("Informatica Economica", 2023, 3, dosarPtr);
	cout << "Concurs de admitere:" << endl;
	cout << concurs << endl;
	cout << endl;

	concurs.medieDeTransfer(9.0f);

	cout << "Concurs de admitere dupa medie de transfer:" << endl;
	cout << concurs << endl;
	cout << endl;

	list<DosarAdmitere> listaDosare;
	listaDosare.push_back(dosar);
	listaDosare.push_back(dosar2);
	listaDosare.push_back(dosar3);
	for (const auto& d : listaDosare) {
		cout << "Dosar din lista: " << endl;
		cout << d << endl;
	}

	int dosare = listaDosare.size();
	float suma = 0;
	auto it = listaDosare.begin();
	while (it != listaDosare.end()) {
		suma += it->getMedieAdmitere();
		it++;
	}

	float medie = suma / dosare;
	
	cout << "Media admitere din lista dosare: " << medie << endl;
	cout << endl;

	return 0;
}