
#ifndef BUKURESEP_H
#define BUKURESEP_H

#include <string>
using namespace std;

// data inti yang kita simpan
struct Resep {
    int id;         // biar gampang refer ke item
    string nama;    // nama resep
    string kategori;// misal: lauk, sayur, kue
    int waktu;      // menit
};

// node buat binary search tree (dibanding nama)
struct Node {
    Resep data;
    Node *kiri, *kanan;
};

// akar tree bisa dipakai di main
extern Node* root;

// ===== CRUD =====
void initData();
void tambah();      // masukin 1 resep
void lihat();       // print semua (default menu)
void detail();      // lihat 1 menu
void ubah();        // edit yang ada
void hapusData();   // hapus menu
void sortNama();

// Tambahkan nilai default pada deklarasi di header
void pre(Node* a, int level = 0, string posisi = "ROOT");
void in(Node* a, int level = 0, string posisi = "ROOT");
void post(Node* a, int level = 0, string posisi = "ROOT");

#endif

