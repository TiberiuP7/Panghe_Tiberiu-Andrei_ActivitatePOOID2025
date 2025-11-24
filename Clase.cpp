#include<iostream>
#include<string>
#include<fstream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class TelefonMobil {
	string producator;
	string model;
	int nivelBaterie;
public:
	void incarca(int nivelIncarcare) {
		nivelBaterie += nivelIncarcare;
		if (nivelBaterie > 100) {
			nivelBaterie = 100;
		}
	}

	int getNivelBaterie() const {
		return nivelBaterie;
	}

	void setNivelBaterie(int nivel) {
		if (nivel >= 0 && nivel <= 100) {
			nivelBaterie = nivel;
		} else {
			cout << "Nivelul bateriei trebuie sa fie intre 0 si 100." << endl;
		}
	}
};

class TelefonMobilPliabil : public TelefonMobil {
	int dimensiunePliat;
	char* model;
public:
	TelefonMobilPliabil() {
		dimensiunePliat = 10;
	}

	TelefonMobilPliabil(string producator,
		int nivelBaterie, int dimensiunePliat, char* modelPliabil) : TelefonMobil(producator, nivelBaterie) {
		if(model != nullptr) {
			this->model = new char[strlen(model) + 1];
			strcpy(this->model, model);
		} else {
			this->model = nullptr;
		}
	}

	TelefonMobilPliabil(const TelefonMobilPliabil& tmp) : TelefonMobil(tmp) {
		this->dimensiunePliat = tmp.dimensiunePliat;
		if(tmp.model != nullptr) {
			this->model = new char[strlen(tmp.model) + 1];
			strcpy(this->model, tmp.model);
		} else {
			this->model = nullptr;
		}
	}

	~TelefonMobilPliabil() {
		if (model != nullptr) {
			delete[] model;
		}
	}

	TelefonMobilPliabil& operator=(const TelefonMobilPliabil& tmp) {
		if (this != &tmp) {
			TelefonMobil::operator=(tmp);
			this->dimensiunePliat = tmp.dimensiunePliat;
			if (this->model != nullptr) {
				delete[] this->model;
			}
			if (tmp.model != nullptr) {
				this->model = new char[strlen(tmp.model) + 1];
				strcpy(this->model, tmp.model);
			} else {
				this->model = nullptr;
			}
		}
		return *this;
	}
};

int main() {
	TelefonMobil telefonPersonal;
	TelefonMobil telefonDeServiciu;
	TelefonMobil t3;
	
	telefonPersonal.incarca(30);
	telefonPersonal.setNivelBaterie(50);
	cout << "Telefon mobil creat." << endl;

	TelefonMobilPliabil tmp1, tmp2;

	t3 = tmp1;
	TelefonMobilPliabil tmp3 = tmp1;

	tmp3 = tmp2;
	return 0;
}