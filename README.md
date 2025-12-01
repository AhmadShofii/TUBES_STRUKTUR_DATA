# Aplikasi Buku Resep (C++)

Aplikasi console sederhana buat nyimpen **resep** (nama, kategori, waktu).  
Fitur inti: **CRUD**, **sorting nama (A–Z)**, **Binary Search Tree** (pre/in/post order), dan **export otomatis ke CSV** (biar gampang buka di Excel).  
Gaya kodenya sengaja santai—biar enak dibaca pas asistensi.

---

## ✨ Fitur
- Tambah / Lihat / Detail / Ubah / Hapus resep
- Sorting nama pakai **Bubble Sort** + perbaikan ID otomatis
- BST berdasarkan **nama** (Traversal: PreOrder, InOrder, PostOrder)
- **CSV rapi** (tiap kolom di-quote & escape), delimiter default **`;`**

---

## 📁 Struktur Projek

├─ main.cpp # menu + routing use case
├─ BukuResep.h # struct + deklarasi fungsi
├─ BukuResep.cpp # implementasi (CRUD, sort, tree, CSV)
└─ resep.csv # file output (otomatis kebuat setelah ada perubahan)

## 🚀 Cara Build & Run

### Kompilasi (g++)
```bash
g++ main.cpp BukuResep.cpp -o ResepApp


## Cara Pakai (Menu)

1. tambah            -> input nama, kategori, waktu  (masuk array + tree + simpan csv)
2. lihat             -> tampil semua
3. detail            -> input ID, tampil detail
4. ubah              -> input ID, isi yang mau diubah (enter = skip)
5. hapus             -> input ID, geser array & perbaiki ID
6. sort nama (A-Z)   -> bubble sort + simpan csv
7. pre order         -> traversal tree
8. in order          -> traversal tree (hasil A-Z)
9. post order        -> traversal tree
0. keluar

 ## Catatan Implementasi (biar gampang jelasin)

Array dinamis: pointer dataR akan dilipat ganda kapasitasnya (kap *= 2) saat penuh.

ID: diset dari 1..n. Setelah hapus / sort, ID di-refresh.

BST: kunci = nama. Insert saat tambah resep. Traversal:

InOrder → alfabetis A–Z

Pre/Post → buat demo struktur

CSV: seluruh perubahan (tambah/ubah/hapus/sort) bakal auto save ke resep.csv.

