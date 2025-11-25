#include<iostream>
#include<string>
using namespace std;

class CameraHotel {
	string* facilitatiCamera;
	string numarCamera;
	int numarFacilitati;
	float pretPeNoapte;
public:
	CameraHotel() {
		this->facilitatiCamera = NULL;
		this->numarCamera = "";
		this->numarFacilitati = 0;
		this->pretPeNoapte = 0.0f;
	}

	float getPretPeNoapte() {
		return this->pretPeNoapte;
	}

	CameraHotel(string* facilitatiCamera, int numarFacilitati, float pretPeNoapte) {
		this->facilitatiCamera = new string[this->numarFacilitati];
		for (int i = 0; i < this->numarFacilitati; i++) {
			this->facilitatiCamera[i] = facilitatiCamera[i];
		}
		this->numarCamera = "";
		this->facilitatiCamera = facilitatiCamera;
		this->pretPeNoapte = pretPeNoapte;
	}

	CameraHotel(const CameraHotel& c) {
		this->facilitatiCamera = new string[this->numarFacilitati];
		for (int i = 0; i < this->numarFacilitati; i++) {
			this->facilitatiCamera[i] = c.facilitatiCamera[i];
		}
		this->numarCamera = "";
		this->facilitatiCamera = c.facilitatiCamera;
		this->pretPeNoapte = c.pretPeNoapte;
	}
};  

int main() {  
    CameraHotel c;  
    cout << c.getPretPeNoapte() << endl; // Output: 0.0  
}