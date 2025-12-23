#include <iostream>
#include "resep.h"
#include "resep.cpp"

using namespace std;

int main() {
    initData();
    int p;
    do {
        cout << "\n== MENU BUKU RESEP ==\n";
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
        case 7: 
                cout << "\n[PRE-ORDER - Jalur Root ke Anak]\n"; 
                pre(root, 0, "ROOT"); 
                break;
            case 8: 
                cout << "\n[IN-ORDER - Jalur Urutan Abjad]\n"; 
                in(root, 0, "ROOT"); 
                break;
            case 9: 
                cout << "\n[POST-ORDER - Jalur Hapus/Bawah ke Atas]\n"; 
                post(root, 0, "ROOT"); 
                break;            case 0: cout << "bye\n"; break;
        default: cout << "salah input\n";
        }
    } while (p != 0);

    return 0;

}

