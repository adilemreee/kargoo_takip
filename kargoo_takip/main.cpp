//
//  main.cpp
//  kargoo_takip
//
//  Created by Adil Emre Karayürek on 18.01.2024.
//

//Adil Emre Karayürek 2112721025
//Kargo Takip Otomasyonu

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_KARGO_SAYISI = 100;

struct Kargo {
    int kargoNo;
    string gonderici;
    string alici;
    string durum;
};

const string dosyaAdi = "kargo_takip.txt";


void yeniKargoEkle(Kargo[], int&);
void kargoAra(const Kargo[], int);
void kargoDuzelt(Kargo[], int);
void kargoSil(Kargo[], int&);
void kargoListele(const Kargo[], int);
void dosyadanOku(Kargo[], int&);
void dosyayaYaz(const Kargo[], int);

int main() {
    Kargo kargolar[MAX_KARGO_SAYISI];
    int kargoSayisi = 0;
    dosyadanOku(kargolar, kargoSayisi);

    int secim;

    do {
        cout << "Kargo Takip Otomasyonu\n";
        cout << "1. Yeni Kargo Ekle\n";
        cout << "2. Kargo Ara\n";
        cout << "3. Kargo Duzelt/Guncelle\n";
        cout << "4. Kargo Sil\n";
        cout << "5. Kargo Listele\n";
        cout << "6. Cikis\n";
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
            case 1:
                yeniKargoEkle(kargolar, kargoSayisi);
                break;
            case 2:
                kargoAra(kargolar, kargoSayisi);
                break;
            case 3:
                kargoDuzelt(kargolar, kargoSayisi);
                break;
            case 4:
                kargoSil(kargolar, kargoSayisi);
                break;
            case 5:
                kargoListele(kargolar, kargoSayisi);
                break;
            case 6:
                cout << "Programdan cikiliyor...\n";
                break;
            default:
                cout << "Gecersiz secim! Tekrar deneyin.\n";
        }

    } while (secim != 6);

    dosyayaYaz(kargolar, kargoSayisi);

    return 0;
}

void yeniKargoEkle(Kargo kargolar[], int& kargoSayisi) {
    if (kargoSayisi < MAX_KARGO_SAYISI) {
        Kargo yeniKargo;
        cout << "Kargo No: ";
        cin >> yeniKargo.kargoNo;
        cin.ignore();
        cout << "Gonderici: ";
        getline(cin, yeniKargo.gonderici);
        cout << "Alici: ";
        getline(cin, yeniKargo.alici);
        cout << "Durum: ";
        getline(cin, yeniKargo.durum);

        kargolar[kargoSayisi] = yeniKargo;
        kargoSayisi++;

        cout << "Yeni kargo eklendi.\n";
    } else {
        cout << "Maksimum kargo sayisina ulasildi!\n";
    }
}

void kargoAra(const Kargo kargolar[], int kargoSayisi) {
    int arananKargoNo;
    cout << "Aranan Kargo No: ";
    cin >> arananKargoNo;

    for (int i = 0; i < kargoSayisi; ++i) {
        if (kargolar[i].kargoNo == arananKargoNo) {
            cout << "Kargo No: " << kargolar[i].kargoNo << "\n";
            cout << "Gonderici: " << kargolar[i].gonderici << "\n";
            cout << "Alici: " << kargolar[i].alici << "\n";
            cout << "Durum: " << kargolar[i].durum << "\n";
            return;
        }
    }

    cout << "Kargo bulunamadi.\n";
}

void kargoDuzelt(Kargo kargolar[], int kargoSayisi) {
    int duzeltilenKargoNo;
    cout << "Duzeltilecek Kargo No: ";
    cin >> duzeltilenKargoNo;

    for (int i = 0; i < kargoSayisi; ++i) {
        if (kargolar[i].kargoNo == duzeltilenKargoNo) {
            cout << "Yeni Gonderici: ";
            cin.ignore();
            getline(cin, kargolar[i].gonderici);
            cout << "Yeni Alici: ";
            getline(cin, kargolar[i].alici);
            cout << "Yeni Durum: ";
            getline(cin, kargolar[i].durum);

            cout << "Kargo bilgileri duzeltildi.\n";
            return;
        }
    }

    cout << "Kargo bulunamadi.\n";
}

void kargoSil(Kargo kargolar[], int& kargoSayisi) {
    int silinecekKargoNo;
    cout << "Silinecek Kargo No: ";
    cin >> silinecekKargoNo;

    for (int i = 0; i < kargoSayisi; ++i) {
        if (kargolar[i].kargoNo == silinecekKargoNo) {
            for (int j = i; j < kargoSayisi - 1; ++j) {
                kargolar[j] = kargolar[j + 1];
            }
            kargoSayisi--;

            cout << "Kargo silindi.\n";
            return;
        }
    }

    cout << "Kargo bulunamadi.\n";
}

void kargoListele(const Kargo kargolar[], int kargoSayisi) {
    cout << "Tum Kargolar:\n";
    for (int i = 0; i < kargoSayisi; ++i) {
        cout << "Kargo No: " << kargolar[i].kargoNo << "\n";
        cout << "Gonderici: " << kargolar[i].gonderici << "\n";
        cout << "Alici: " << kargolar[i].alici << "\n";
        cout << "Durum: " << kargolar[i].durum << "\n";
        cout << "----------------\n";
    }
}

void dosyadanOku(Kargo kargolar[], int& kargoSayisi) {
    ifstream dosya(dosyaAdi);

    if (dosya.is_open()) {
        while (!dosya.eof() && kargoSayisi < MAX_KARGO_SAYISI) {
            dosya >> kargolar[kargoSayisi].kargoNo;
            dosya.ignore();
            getline(dosya, kargolar[kargoSayisi].gonderici);
            getline(dosya, kargolar[kargoSayisi].alici);
            getline(dosya, kargolar[kargoSayisi].durum);

            kargoSayisi++;
        }
        dosya.close();
    }
}

void dosyayaYaz(const Kargo kargolar[], int kargoSayisi) {
    ofstream dosya(dosyaAdi);


    for (int i = 0; i < kargoSayisi; ++i) {
        dosya << kargolar[i].kargoNo << "\n";
        dosya << kargolar[i].gonderici << "\n";
        dosya << kargolar[i].alici << "\n";
        dosya << kargolar[i].durum;

        if (i < kargoSayisi - 1) {
            dosya << "\n";
        }
    }

    dosya.close();
}

