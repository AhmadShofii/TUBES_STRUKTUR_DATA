#include <iostream>
#include "resep.h"
#include "resep.cpp"

using namespace std;

int main() {
    int p;
    do {
        cout << "\n== MENU ==\n";
        cout << "1. tambah\n";
        cout << "2. lihat\n";
        cout << "3. detail\n";
        cout << "4. ubah\n";
        cout << "5. hapus\n";
        cout << "6. sort nama (A-Z)\n";
        cout << "7. pre order\n";
        cout << "8. in order\n";
        cout << "9. post order\n";
        cout << "0. keluar\n";
        cout << "pilih: ";
        cin >> p;

        switch (p) {
        case 1: tambah(); break;
        case 2: lihat(); break;
        case 3: detail(); break;
        case 4: ubah(); break;
        case 5: hapusData(); break;
        case 6: sortNama(); break;
        case 7: if (!root) cout << "tree kosong\n"; else pre(root); break;
        case 8: if (!root) cout << "tree kosong\n"; else in(root); break;
        case 9: if (!root) cout << "tree kosong\n"; else post(root); break;
        case 0: cout << "bye\n"; break;
        default: cout << "salah input\n";
        }
    } while (p != 0);

    return 0;
}