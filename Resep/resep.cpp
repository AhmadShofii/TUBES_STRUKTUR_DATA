#include "resep.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Resep* dataR = nullptr;
int jml = 0;   
int kapasitas = 0;   
Node* root = nullptr;

static const char CSV_DELIM = ';';

// ========= Utility (Sesuai Kode Kamu) =========
static string csvEscape(const string& s) {
    string out; out.reserve(s.size() + 2);
    out.push_back('"');
    for (char c : s) {
        if (c == '"') out += "\"\"";
        else out.push_back(c);
    }
    out.push_back('"');
    return out;
}

static void simpanKeCSV() {
    ofstream file("resep.csv", ios::trunc);
    if (!file) return;
    file << "ID" << CSV_DELIM << "Nama" << CSV_DELIM << "Kategori" << CSV_DELIM << "Waktu\n";
    for (int i = 0; i < jml; ++i) {
        file << (i + 1) << CSV_DELIM << csvEscape(dataR[i].nama) << CSV_DELIM 
             << csvEscape(dataR[i].kategori) << CSV_DELIM << dataR[i].waktu << "\n";
    }
    file.close();
    cout << ">>> Data telah berhasil diperbarui di resep.csv\n";
}

void tambahKapasitas() {
    if (kapasitas == 0) {
        kapasitas = 5;
        dataR = new Resep[kapasitas];
    } else if (jml >= kapasitas) {
        int baru = kapasitas * 2;
        Resep* temp = new Resep[baru];
        for (int i = 0; i < jml; ++i) temp[i] = dataR[i];
        delete[] dataR;
        dataR = temp;
        kapasitas = baru;
    }
}

static Node* masukTree(Node* a, const Resep& r) {
    if (!a) { // Jika tempatnya kosong, buat node baru di sini
        Node* u = new Node;
        u->data = r;
        u->kiri = u->kanan = nullptr;
        return u;
    }
    
    // LOGIKA PENENTUAN KIRI/KANAN:
    if (r.nama < a->data.nama) {
        // Jika abjad lebih kecil, paksa masuk ke KIRI
        a->kiri = masukTree(a->kiri, r);
    } else {
        // Jika abjad lebih besar/sama, paksa masuk ke KANAN
        a->kanan = masukTree(a->kanan, r);
    }
    return a;
}

void initData() {
    Resep def[] = {
        {1, "Cah Kangkung", "Sayuran", 10}, // Jadi Root
        {2, "Bakso Bakar", "Jajanan", 15},  // Masuk ke Kiri Cah
        {3, "Donat Madu", "Kue Kering", 60},// Masuk ke Kanan Cah
        {4, "Ayam Goreng", "Lauk Pauk", 30}  // Masuk ke Kiri Bakso
    };

    for(int i = 0; i < 4; i++) {
        tambahKapasitas();
        dataR[jml] = def[i];
        root = masukTree(root, def[i]);
        jml++;
    }
}

// ========= CRUD =========
void tambah() {
    tambahKapasitas();
    Resep r;
    r.id = jml + 1;
    cin.ignore();
    cout << "Nama      : "; getline(cin, r.nama);
    cout << "Kategori  : "; getline(cin, r.kategori);
    cout << "Waktu (m) : "; cin >> r.waktu;
    dataR[jml++] = r;
    root = masukTree(root, r);
    simpanKeCSV();
    
}

void lihat() {
    if (jml == 0) { cout << "kosong\n"; return; }
    for (int i = 0; i < jml; ++i)
        cout << dataR[i].id << ". " << dataR[i].nama << " [" << dataR[i].kategori << "] (" << dataR[i].waktu << "m)\n";
}

void detail() {
    int id; cout << "ID: "; cin >> id;
    for (int i = 0; i < jml; ++i) if (dataR[i].id == id) {
        cout << "Nama: " << dataR[i].nama << "\nKat: " << dataR[i].kategori << "\nWaktu: " << dataR[i].waktu << "m\n";
        return;
    }
}

void ubah() {
    int id; cout << "ID: "; cin >> id;
    for (int i = 0; i < jml; ++i) if (dataR[i].id == id) {
        cin.ignore(); string s;
        cout << "Nama baru: "; getline(cin, s);
        if (!s.empty()) dataR[i].nama = s;
        simpanKeCSV(); return;
    }
}

void hapusData() {
    int id; cout << "ID: "; cin >> id;
    int pos = -1;
    for (int i = 0; i < jml; ++i) if (dataR[i].id == id) pos = i;
    if (pos == -1) return;
    for (int i = pos; i < jml - 1; ++i) dataR[i] = dataR[i + 1];
    jml--; simpanKeCSV();
}

void sortNama() {
    for (int i = 0; i < jml - 1; ++i)
        for (int j = 0; j < jml - i - 1; ++j)
            if (dataR[j].nama > dataR[j + 1].nama) swap(dataR[j], dataR[j+1]);
    simpanKeCSV();
}

void cetakGaris(int level) {
    for (int i = 0; i < level; i++) {
        cout << "|   "; // Membuat garis vertikal untuk level sebelumnya
    }
}

// ========= Traversal yang Diperbaiki (Lebih Mudah Dipahami) =========
void pre(Node* a, int level, string posisi) {
    if (a) {
        cetakGaris(level);
        cout << "|--[" << posisi << "] " << a->data.nama << endl;
        pre(a->kiri, level + 1, "L");
        pre(a->kanan, level + 1, "R");
    }
}

void in(Node* a, int level, string posisi) {
    if (a) {
        in(a->kiri, level + 1, "L");
        cetakGaris(level);
        cout << "|--[" << posisi << "] " << a->data.nama << endl;
        in(a->kanan, level + 1, "R");
    }
}

void post(Node* a, int level, string posisi) {
    if (a) {
        post(a->kiri, level + 1, "L");
        post(a->kanan, level + 1, "R");
        cetakGaris(level);
        cout << "|--[" << posisi << "] " << a->data.nama << endl;
    }
}