#include "resep.h"
#include <iostream>
#include <fstream>

using namespace std;

// ========= Array Dinamis =========
Resep* dataR = nullptr;
int jml = 0;   // jumlah data terisi
int kapasitas = 0;   // kapasitas array

// ========= Tree Root =========
Node* root = nullptr;

// ========= CSV Helper =========
// Ganti delimiter sesuai Excel kamu: ',' atau ';'
static const char CSV_DELIM = ';';

// Escape CSV: gandakan " lalu bungkus dengan "
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
    if (!file) {
        cout << "Gagal membuka file resep.csv\n";
        return;
    }
    // Header
    file << "ID" << CSV_DELIM
         << "Nama" << CSV_DELIM
         << "Kategori" << CSV_DELIM
         << "Waktu(menit)" << "\n";
    // Data (tiap kolom di-escape/quote)
    for (int i = 0; i < jml; ++i) {
        file << (i + 1) << CSV_DELIM
             << csvEscape(dataR[i].nama) << CSV_DELIM
             << csvEscape(dataR[i].kategori) << CSV_DELIM
             << dataR[i].waktu << "\n";
    }
    file.close();
    cout << "Data tersimpan rapi ke resep.csv\n";
}

// ========= Util Array Dinamis =========
static void tambahKapasitas() {
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

// ========= Tree =========
static Node* masukTree(Node* a, const Resep& r) {
    if (!a) {
        Node* u = new Node;
        u->data = r;
        u->kiri = u->kanan = nullptr;
        return u;
    }
    if (r.nama < a->data.nama) a->kiri = masukTree(a->kiri, r);
    else                       a->kanan = masukTree(a->kanan, r);
    return a;
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

    dataR[jml] = r;
    jml++;

    root = masukTree(root, r);

    cout << ">> data masuk\n";
    simpanKeCSV();
}

void lihat() {
    if (jml == 0) { cout << "kosong\n"; return; }
    for (int i = 0; i < jml; ++i) {
        cout << dataR[i].id << ". " << dataR[i].nama << " - "
             << dataR[i].kategori << " (" << dataR[i].waktu << "m)\n";
    }
}

void detail() {
    if (jml == 0) { cout << "kosong\n"; return; }
    int id; cout << "ID: "; cin >> id;
    for (int i = 0; i < jml; ++i) {
        if (dataR[i].id == id) {
            cout << "Nama     : " << dataR[i].nama << "\n";
            cout << "Kategori : " << dataR[i].kategori << "\n";
            cout << "Waktu    : " << dataR[i].waktu << " menit\n";
            return;
        }
    }
    cout << "ga ketemu\n";
}

void ubah() {
    if (jml == 0) { cout << "kosong\n"; return; }
    int id; cout << "ID: "; cin >> id;
    for (int i = 0; i < jml; ++i) {
        if (dataR[i].id == id) {
            cin.ignore();
            string s; int w;
            cout << "Nama baru (enter=skip): "; getline(cin, s);
            if (!s.empty()) dataR[i].nama = s;
            cout << "Kategori baru (enter=skip): "; getline(cin, s);
            if (!s.empty()) dataR[i].kategori = s;
            cout << "Waktu baru (0=skip): "; cin >> w;
            if (w != 0) dataR[i].waktu = w;
            cout << ">> sudah diupdate\n";
            simpanKeCSV();
            return;
        }
    }
    cout << "ga ketemu\n";
}

void hapusData() {
    if (jml == 0) { cout << "kosong\n"; return; }
    int id; cout << "ID: "; cin >> id;
    int pos = -1;
    for (int i = 0; i < jml; ++i) if (dataR[i].id == id) pos = i;
    if (pos == -1) { cout << "ga ada\n"; return; }

    for (int i = pos; i < jml - 1; ++i) {
        dataR[i] = dataR[i + 1];
        dataR[i].id = i + 1;
    }
    jml--;
    cout << ">> sudah dihapus\n";
    simpanKeCSV();
}

// ========= Sorting =========
void sortNama() {
    if (jml <= 1) { cout << "data dikit, ga perlu diurut\n"; return; }
    for (int i = 0; i < jml - 1; ++i) {
        for (int j = 0; j < jml - i - 1; ++j) {
            if (dataR[j].nama > dataR[j + 1].nama) {
                Resep t = dataR[j];
                dataR[j] = dataR[j + 1];
                dataR[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < jml; ++i) dataR[i].id = i + 1;
    cout << ">> sudah diurutkan (A-Z)\n";
    simpanKeCSV();
}

// ========= Traversal =========
// ========= Traversal (dengan panah ke bawah) =========
#include <vector>

// helper: cetak vertikal dengan panah
static void printVertical(const std::vector<std::string>& list) {
    if (list.empty()) { std::cout << "kosong\n"; return; }
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << "\n";
        if (i + 1 < list.size()) {
            // pakai ASCII agar aman di semua terminal
            std::cout << "  |\n"
                      << "  v\n";
            // kalau mau panah unicode, ganti jadi:
            // std::cout << "  ↓\n";
        }
    }
}

// --- kolektor rekursif (biar simple, ditaruh lagi di sini) ---
static void preorderCollect(Node* a, std::vector<std::string>& out){
    if(!a) return;
    out.push_back(a->data.nama);
    preorderCollect(a->kiri, out);
    preorderCollect(a->kanan, out);
}
static void inorderCollect(Node* a, std::vector<std::string>& out){
    if(!a) return;
    inorderCollect(a->kiri, out);
    out.push_back(a->data.nama);
    inorderCollect(a->kanan, out);
}
static void postorderCollect(Node* a, std::vector<std::string>& out){
    if(!a) return;
    postorderCollect(a->kiri, out);
    postorderCollect(a->kanan, out);
    out.push_back(a->data.nama);
}

// --- printer:  ----> Nama <----  + garis turun selaras tengah teks ---
static void printInwardArrows(const std::vector<std::string>& list,
                              int padAroundText = 1,   // spasi di kiri/kanan teks
                              int arrowLen      = 4,   // panjang garis panah (jumlah '-')
                              bool useUnicode   = false) {
    if (list.empty()) { std::cout << "kosong\n"; return; }

    // karakter panah & garis (bisa pakai Unicode biar halus)
    const char *arrowR = useUnicode ? u8"→" : ">";
    const char *arrowL = useUnicode ? u8"←" : "<";
    const char *dash   = useUnicode ? u8"─" : "-";
    const char *vbar   = useUnicode ? u8"│" : "|";
    const char *down   = useUnicode ? u8"▼" : "v";

    // helper bikin "---->" dan "<----"
    auto makeRightHead = [&](int n){ return std::string(std::max(0,n-1), dash[0]) + arrowR; };
    auto makeLeftHead  = [&](int n){ return std::string(arrowL) + std::string(std::max(0,n-1), dash[0]); };

    for (size_t i = 0; i < list.size(); ++i) {
        const std::string& s = list[i];

        // Baris 1:  [---->][space][Nama][space][<----]
        std::string left  = makeRightHead(arrowLen);
        std::string right = makeLeftHead(arrowLen);

        std::cout << left
                  << std::string(padAroundText, ' ')
                  << s
                  << std::string(padAroundText, ' ')
                  << right
                  << "\n";

        // Baris 2-3: garis turun di tengah teks (selaras panjang nama)
        if (i + 1 < list.size()) {
            // kolom tengah = panjang left + spasi + posisi tengah teks
            size_t centerCol = left.size() + padAroundText + (s.size() / 2);
            std::cout << std::string(centerCol, ' ') << vbar  << "\n";
            std::cout << std::string(centerCol, ' ') << down  << "\n";
        }
    }
}

// --- wrapper menu 7/8/9: panggil printer di atas ---
void pre(Node* a){
    std::vector<std::string> v; preorderCollect(a, v);
    printInwardArrows(v, /*padAroundText=*/1, /*arrowLen=*/4, /*useUnicode=*/false);
}
void in(Node* a){
    std::vector<std::string> v; inorderCollect(a, v);
    printInwardArrows(v, 1, 4, false);   // InOrder: alfabetic kalau BST
}
void post(Node* a){
    std::vector<std::string> v; postorderCollect(a, v);
    printInwardArrows(v, 1, 4, false);
}