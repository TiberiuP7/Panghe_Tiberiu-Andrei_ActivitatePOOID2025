#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Casa {
	bool cuEtaj;
	float amprentaSol;
	int nrCamere;
	bool* camereLaEtaj;

public:

	Casa() {
		this->cuEtaj = false;
		this->amprentaSol = 0.0f;
		this->nrCamere = 0;
		this->camereLaEtaj = NULL;
	}

	Casa(bool cuEtaj, float amprentaSol, int nrCamere, bool* camereLaEtaj) {
		this->cuEtaj = cuEtaj;
		this->amprentaSol = amprentaSol;
		this->nrCamere = nrCamere;
		if (camereLaEtaj != NULL) {
			this->camereLaEtaj = new bool[nrCamere];
			for (int i = 0; i < nrCamere; i++) {
				this->camereLaEtaj[i] = camereLaEtaj[i];
			}
		}
		else {
			this->camereLaEtaj = NULL;
		}
	}

	Casa(const Casa& c) {
		this->cuEtaj = c.cuEtaj;
		this->amprentaSol = c.amprentaSol;
		this->nrCamere = c.nrCamere;
		this->camereLaEtaj = new bool[c.nrCamere];
		for (int i = 0; i < nrCamere; i++) {
			this->camereLaEtaj[i] = c.camereLaEtaj[i];
		}
	}

	~Casa() {
		if (this->camereLaEtaj != NULL) {
			delete[] this->camereLaEtaj;
		}
	}

	Casa& operator=(const Casa& c) {
		if (this != &c) {
			this->cuEtaj = c.cuEtaj;
			this->amprentaSol = c.amprentaSol;
			this->nrCamere = c.nrCamere;
			if (this->camereLaEtaj != NULL) {
				delete[] this->camereLaEtaj;
			}
			this->camereLaEtaj = new bool[c.nrCamere];
			for (int i = 0; i < nrCamere; i++) {
				this->camereLaEtaj[i] = c.camereLaEtaj[i];
			}
		}
		return *this;
	}

	bool getCuEtaj() const {
		return this->cuEtaj;
	}

	void setCuEtaj(bool cuEtaj) {
		this->cuEtaj = cuEtaj;
	}

	friend ostream& operator<<(ostream& out, const Casa& c) {
		out << c.cuEtaj << endl;
		out << c.amprentaSol << endl;
		out << c.nrCamere << endl;
		if (c.camereLaEtaj != NULL) {
			for (int i = 0; i < c.nrCamere; i++) {
				out << c.camereLaEtaj[i] << " ";
			}
			out << endl;
		}
		else {
			out << "Nu are camere la etaj" << endl;
		}

		return out;
	}

	int operator()(bool nivel) {
		int camere = 0;
		if (nivel) {
			for (int i = 0; i < this->nrCamere; i++) {
				if (this->camereLaEtaj[i]) {
					camere += 1;
				}
			}
		}
		else {
			for (int i = 0; i < this->nrCamere; i++) {
				if (!this->camereLaEtaj[i]) {
					camere += 1;
				}
			}
		}

		return camere;
	}

	void mutaCamereLaParter() {
		if(this->cuEtaj) {
			for (int i = 0; i < this->nrCamere; i++) {
				if (this->camereLaEtaj[i]) {
					this->camereLaEtaj[i] = false;
				}
			}
			this->cuEtaj = false;
		}
		else {
			cout << "Casa nu are etaj!" << endl;
		}
	}

	friend ofstream& operator<<(ofstream& out, const Casa& c) {
		out << c.cuEtaj << endl;
		out << c.amprentaSol << endl;
		out << c.nrCamere << endl;
		if (c.camereLaEtaj != NULL) {
			for (int i = 0; i < c.nrCamere; i++) {
				out << c.camereLaEtaj[i] << " ";
			}
			out << endl;
		}
		else {
			out << "Nu are camere la etaj" << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Casa& c) {
		in >> c.cuEtaj;
		in >> c.amprentaSol;
		in >> c.nrCamere;
		if (c.camereLaEtaj != NULL) {
			delete[] c.camereLaEtaj;
		}
		c.camereLaEtaj = new bool[c.nrCamere];
		for (int i = 0; i < c.nrCamere; i++) {
			in >> c.camereLaEtaj[i];
		}
		return in;
	}

	void serialize(string numeFisier) {
		ofstream fout(numeFisier, ios::out, ios::binary);
		if (fout.is_open()) {
			fout.write((char*)&this->cuEtaj, sizeof(cuEtaj));
			fout.write((char*)&this->amprentaSol, sizeof(amprentaSol));
			fout.write((char*)&this->nrCamere, sizeof(nrCamere));
			for (int i = 0; i < this->nrCamere; i++) {
				fout.write((char*)&this->camereLaEtaj[i], sizeof(camereLaEtaj[i]));
			}
		}
	}

	void deserialize(string numeFisier) {
		ifstream fin(numeFisier, ios::in | ios::binary);
		if (fin.is_open()) {
			fin.read((char*)&this->cuEtaj, sizeof(cuEtaj));
			fin.read((char*)&this->amprentaSol, sizeof(amprentaSol));
			fin.read((char*)&this->nrCamere, sizeof(nrCamere));
			if (this->camereLaEtaj != NULL) {
				delete[] this->camereLaEtaj;
			}
			this->camereLaEtaj = new bool[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				fin.read((char*)&this->camereLaEtaj[i], sizeof(camereLaEtaj[i]));
			}
		}
	}

	map<int, int> getCamerePerEtaj() const {
		map<int, int> camerePerEtaj;
		for (int i = 0; i < this->nrCamere; i++) {
			if (this->camereLaEtaj[i]) {
				camerePerEtaj[1]++; // Etaj
			}
			else {
				camerePerEtaj[0]++; // Parter
			}
		}
		return camerePerEtaj;
	}
};

class ComplexRezidential {
	float suprafataTotala;
	//float suprafataGradina;
	int nrCase;
	Casa* caseRezidentiale;

public:

	ComplexRezidential() {
		this->suprafataTotala = 0.0f;
		this->nrCase = 0;
		this->caseRezidentiale = NULL;
	}

	ComplexRezidential(float suprafataTotala, int nrCase, Casa* caseRezidentiale) {
		this->suprafataTotala = suprafataTotala;
		this->nrCase = nrCase;
		if (caseRezidentiale != NULL) {
			this->caseRezidentiale = new Casa[nrCase];
			for (int i = 0; i < nrCase; i++) {
				this->caseRezidentiale[i] = caseRezidentiale[i];
			}
		}
		else {
			this->caseRezidentiale = NULL;
		}
	}

	ComplexRezidential(const ComplexRezidential& cr) {
		this->suprafataTotala = cr.suprafataTotala;
		this->nrCase = cr.nrCase;
		if (cr.caseRezidentiale != NULL) {
			this->caseRezidentiale = new Casa[cr.nrCase];
			for (int i = 0; i < cr.nrCase; i++) {
				this->caseRezidentiale[i] = cr.caseRezidentiale[i];
			}
		}
		else {
			this->caseRezidentiale = NULL;
		}
	}

	~ComplexRezidential() {
		if (this->caseRezidentiale != NULL) {
			delete[] this->caseRezidentiale;
		}
	}

	ComplexRezidential& operator=(const ComplexRezidential& cr) {
		if(this != &cr) {
			this->suprafataTotala = cr.suprafataTotala;
			this->nrCase = cr.nrCase;
			if (this->caseRezidentiale != NULL) {
				delete[] this->caseRezidentiale;
			}
			if (cr.caseRezidentiale != NULL) {
				this->caseRezidentiale = new Casa[cr.nrCase];
				for (int i = 0; i < cr.nrCase; i++) {
					this->caseRezidentiale[i] = cr.caseRezidentiale[i];
				}
			}
			else {
				this->caseRezidentiale = NULL;
			}
		}

		return *this;
	}

	float getSuprafataTotala() const {
		return this->suprafataTotala;
	}

	void setSuprafataTotala(float suprafataTotala) {
		this->suprafataTotala = suprafataTotala;
	}

	friend ostream& operator<<(ostream& out, const ComplexRezidential& cr) {
		out << cr.suprafataTotala << endl;
		out << cr.nrCase << endl;
		if (cr.caseRezidentiale != NULL) {
			for (int i = 0; i < cr.nrCase; i++) {
				out << cr.caseRezidentiale[i] << endl;
			}
		}
		else {
			out << "Nu exista case in complex." << endl;
		}
		return out;
	}
};

int main() {
	Casa c1;
	cout << c1 << endl;
	bool camereLaEtaj[] = { true, false, true };
	Casa c2(true, 120.5f, 3, camereLaEtaj);
	cout << c2 << endl;
	Casa c3(c2);
	cout << c3 << endl;
	c3.mutaCamereLaParter();
	cout << c3 << endl;
	c3.setCuEtaj(true);
	cout << c3 << endl;
	cout << "Numar camere la etaj: " << c3(1) << endl;
	cout << "Numar camere la parter: " << c3(0) << endl;
	cout << endl;

	ofstream fout("casa.txt");
	fout << c3;
	fout << c2;
	fout << c1;
	fout.close();

	c2.serialize("casa2.bin");
	Casa c4;
	c4.deserialize("casa2.bin");
	cout << "Dupa deserializare: " << endl;
	cout << c4 << endl;


	ComplexRezidential cr1;
	cout << cr1 << endl;
	Casa caseComplex[] = { c1, c2, c3 };
	ComplexRezidential cr2(500.0f, 3, caseComplex);
	cout << cr2 << endl;
	ComplexRezidential cr3(cr2);
	cout << cr3 << endl;
	cr3.setSuprafataTotala(600.0f);
	cout << "Dupa modificare suprafata totala: " << endl;
	cout << cr3 << endl;

	/*cout << c3.getCamerePerEtaj().size() << endl;

	auto camerePerEtaj= c3.getCamerePerEtaj();
	cout << camerePerEtaj.find(first) << endl;*/

	vector<Casa> caseList;

	caseList.push_back(c1);
	caseList.push_back(c2);
	caseList.push_back(c3);
	caseList.push_back(c4);
	cout << caseList.size() << endl;
	for (Casa casa : caseList) {
		auto camerePerEtaj = casa.getCamerePerEtaj();
		for (const auto& pair : camerePerEtaj) {
			cout << "Etaj: " << pair.first << ", Numar camere: " << pair.second << endl;
		}
	}
}