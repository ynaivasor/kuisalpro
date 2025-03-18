#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

struct Lagu {
    char judul[100];
    char penyanyi[100];
    char genre[100];
    int tahun;
};

// Fungsi sorting
void bubbleSort(Lagu daftar_lagu[], int jmlh_lagu) {
    for (int i = 0; i < jmlh_lagu - 1; i++) {
        for (int j = 0; j < jmlh_lagu - i - 1; j++) {
            if (strcmp(daftar_lagu[j].judul, daftar_lagu[j + 1].judul) > 0) {
                swap(daftar_lagu[j], daftar_lagu[j + 1]);
            }
        }
    }
}

// Fungsi tambah lagu
void tambahLagu() {
    FILE *file = fopen("data.dat", "ab");
    if (!file) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    Lagu lagu;
    cout << "Masukkan Judul Lagu: ";
    cin.ignore();
    cin.getline(lagu.judul, 100);
    cout << "Masukkan Penyanyi: ";
    cin.getline(lagu.penyanyi, 100);
    cout << "Masukkan Genre Lagu: ";
    cin.getline(lagu.genre, 100);
    cout << "Masukkan Tahun Lagu: ";
    cin >> lagu.tahun;
    cin.ignore();
    
    fwrite(&lagu, sizeof(Lagu), 1, file);
    fclose(file);
    cout << "Lagu berhasil ditambah" << endl;
}

// Fungsi tampil lagu
void tampilLagu() {
    FILE *file = fopen("data.dat", "rb");
    if (!file) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    Lagu daftar_lagu[100];
    int jmlh_lagu = 0;
    while (fread(&daftar_lagu[jmlh_lagu], sizeof(Lagu), 1, file) == 1) {
        jmlh_lagu++;
    }
    fclose(file);

    bubbleSort(daftar_lagu, jmlh_lagu);

    cout << "Daftar Lagu" << endl;
    cout << "====================" << endl;
    for (int i = 0; i < jmlh_lagu; i++) {
        cout << "Judul Lagu: " << daftar_lagu[i].judul << endl;
        cout << "Penyanyi: " << daftar_lagu[i].penyanyi << endl;
        cout << "Genre: " << daftar_lagu[i].genre << endl;
        cout << "Tahun: " << daftar_lagu[i].tahun << endl;
        cout << "====================" << endl;
    }
    fclose(file);
}

// Fungsi edit lagu
void editLagu() {
    FILE *file = fopen("data.dat", "rb");
    if (!file) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    char judulCari[100];
    cout << "Masukkan judul lagu yang akan diedit: ";
    cin.ignore();
    cin.getline(judulCari, 100);

    Lagu semua_lagu[100];
    int jumlah = 0;
    bool ditemukan = false;

    while (fread(&semua_lagu[jumlah], sizeof(Lagu), 1, file) == 1) {
        if (strcmp(semua_lagu[jumlah].judul, judulCari) == 0) {
            cout << "Lagu ditemukan! Masukkan data baru." << endl;
            cout << "Masukkan Judul baru: ";
            cin.getline(semua_lagu[jumlah].judul, 100);
            cout << "Masukkan Penyanyi baru: ";
            cin.getline(semua_lagu[jumlah].penyanyi, 100);
            cout << "Masukkan Genre baru: ";
            cin.getline(semua_lagu[jumlah].genre, 100);
            cout << "Masukkan Tahun baru: ";
            cin >> semua_lagu[jumlah].tahun;
            cin.ignore();
            ditemukan = true;
        }
        jumlah++;
    }
    fclose(file);

    if (!ditemukan) {
        cout << "Lagu tidak ditemukan" << endl;
        return;
    }

    file = fopen("data.dat", "wb");
    fwrite(semua_lagu, sizeof(Lagu), jumlah, file);
    fclose(file);
    cout << "Lagu berhasil diperbarui" << endl;
}

// Fungsi cari lagu
void cariLagu() {
    FILE *file = fopen("data.dat", "rb");
    if (!file) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    char judulCari[100];
    cout << "Masukkan judul lagu yang dicari: ";
    cin.ignore();
    cin.getline(judulCari, 100);

    Lagu lagu;
    bool ditemukan = false;
    while (fread(&lagu, sizeof(Lagu), 1, file) == 1) {
        if (strcmp(lagu.judul, judulCari) == 0) {
            cout << "Lagu ditemukan!" << endl;
            cout << "Judul Lagu: " << lagu.judul << endl;
            cout << "Penyanyi: " << lagu.penyanyi << endl;
            cout << "Genre: " << lagu.genre << endl;
            cout << "Tahun: " << lagu.tahun << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Lagu tidak ditemukan" << endl;
    }
    fclose(file);
}

// Main Program
int main() {
    int pilihan;
    do {
        cout << "Playlist Lagu" << endl;
        cout << "===============" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Edit Lagu" << endl;
        cout << "3. Tampilkan Lagu" << endl;
        cout << "4. Cari Lagu" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahLagu();
            break;
        case 2:
            editLagu();
            break;
        case 3:
            tampilLagu();
            break;
        case 4:
            cariLagu();
            break;
        case 5:
            cout << "Keluar dari program." << endl;
            exit(0);
        default:
            cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);

    return 0;
}