#include <iostream>
#include <string>
using namespace std;

struct Buku {
    int kode;
    string judul;
    string pengarang;
    Buku* kiri;
    Buku* kanan;

    Buku(int k, string j, string p) {
        kode = k;
        judul = j;
        pengarang = p;
        kiri = kanan = nullptr;
    }
};

Buku* tambahBuku(Buku* root, int kode, string judul, string pengarang) {
    if (!root) return new Buku(kode, judul, pengarang);
    if (kode < root->kode)
        root->kiri = tambahBuku(root->kiri, kode, judul, pengarang);
    else if (kode > root->kode)
        root->kanan = tambahBuku(root->kanan, kode, judul, pengarang);
    else
        cout << "Kode buku sudah ada!\n";
    return root;
}

Buku* cariBuku(Buku* root, int kode) {
    if (!root || root->kode == kode) return root;
    if (kode < root->kode)
        return cariBuku(root->kiri, kode);
    else
        return cariBuku(root->kanan, kode);
}

void tampilkanBuku(Buku* root) {
    if (!root) return;
    tampilkanBuku(root->kiri);
    cout << "Kode: " << root->kode
         << " | Judul: " << root->judul
         << " | Pengarang: " << root->pengarang << endl;
    tampilkanBuku(root->kanan);
}

Buku* bukuTerkecil(Buku* root) {
    while (root && root->kiri)
        root = root->kiri;
    return root;
}

Buku* hapusBuku(Buku* root, int kode) {
    if (!root) return nullptr;
    if (kode < root->kode)
        root->kiri = hapusBuku(root->kiri, kode);
    else if (kode > root->kode)
        root->kanan = hapusBuku(root->kanan, kode);
    else {
        if (!root->kiri && !root->kanan) {
            delete root;
            return nullptr;
        }
        else if (!root->kiri) {
            Buku* temp = root->kanan;
            delete root;
            return temp;
        }
        else if (!root->kanan) {
            Buku* temp = root->kiri;
            delete root;
            return temp;
        }
        else {
            Buku* succ = bukuTerkecil(root->kanan);
            root->kode = succ->kode;
            root->judul = succ->judul;
            root->pengarang = succ->pengarang;
            root->kanan = hapusBuku(root->kanan, succ->kode);
        }
    }
    return root;
}

int main() {
    Buku* root = nullptr;
    int pilihan, kode;
    string judul, pengarang;

    do {
        cout << "\n=== SISTEM DATA BUKU PERPUSTAKAAN ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Tampilkan Semua Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "Masukkan kode buku: "; cin >> kode; cin.ignore();
            cout << "Masukkan judul buku: "; getline(cin, judul);
            cout << "Masukkan nama pengarang: "; getline(cin, pengarang);
            root = tambahBuku(root, kode, judul, pengarang);
        }
        else if (pilihan == 2) {
            cout << "Masukkan kode buku yang dicari: "; cin >> kode;
            Buku* hasil = cariBuku(root, kode);
            if (hasil)
                cout << "Ditemukan! Judul: " << hasil->judul
                     << " | Pengarang: " << hasil->pengarang << endl;
            else
                cout << "Buku tidak ditemukan.\n";
        }
        else if (pilihan == 3) {
            cout << "\nDaftar Buku di Perpustakaan:\n";
            tampilkanBuku(root);
        }
        else if (pilihan == 4) {
            cout << "Masukkan kode buku yang ingin dihapus: "; cin >> kode;
            root = hapusBuku(root, kode);
            cout << "Jika buku ada, maka telah dihapus.\n";
        }
    } while (pilihan != 5);

    cout << "Terima kasih telah menggunakan sistem ini!\n";
    return 0;
}