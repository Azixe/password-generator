#include <iostream>
#include <vector> //Digunakan untuk menggunakan vector
#include <algorithm> //Digunakan untuk menggunakan sort() dan random_shuffle()
#include <cstdlib> // Digunakan untuk menggunakan fungsi rand() dan system()
#include <ctime> // Digunakan untuk mengakses fungsi yang berkaitan dengan waktu, seperti time() dan ctime()

using namespace std;
const int table_size = 100;

class hashnode {
public:
    string password;
    time_t timeCreated;

    hashnode(string password) {
        this->password = password;
        this->timeCreated = time(nullptr); // Set waktu saat password dibuat
    }
};

class Hashmap {
private:
    vector<vector<hashnode*>> table;

public:
    Hashmap() {
        table.resize(table_size); // Mengubah ukuran tabel menjadi ukuran yang ditentukan
    }

    size_t hashFunc(string key) {
        // Fungsi hash yang ditingkatkan menggunakan polynomial rolling hash
        const int p = 31; // Bilangan prima untuk hashing
        const int m = table_size; // Nilai modulo
        size_t hash_val = 0;//menyimpan hasil hash akhir.
        size_t p_pow = 1;

        for (char c : key) {
            hash_val = (hash_val + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }

        return hash_val;
    }

    void insert(string password) { //yang digunakan untuk menyisipkan (insert) password ke dalam hash table.
        size_t index = hashFunc(password);
        hashnode* newNode = new hashnode(password);
        table[index].push_back(newNode); //menambahkan objek newNode ke dalam vektor yang sesuai dalam tabel
    }

    // Membandingkan dua objek hashnode berdasarkan waktu penciptaan
    static bool compareByTime(const hashnode* node1, const hashnode* node2) {
        return node1->timeCreated < node2->timeCreated;
    }

    void displayHistory() {
        cout << "\t\t======= Riwayat Password =======" << endl;
        vector<hashnode*> allPasswords; //berfungsi untuk mengumpulkan objek semua hashnode

        // Mengumpulkan semua password dari tabel
        for (size_t i = 0; i < table.size(); i++) {
            for (hashnode* node : table[i]) {
                allPasswords.push_back(node);
            }
        }

        // Mengurutkan password berdasarkan waktu penciptaan
        sort(allPasswords.begin(), allPasswords.end(), compareByTime);

        // Menampilkan password secara kronologis
        for (hashnode* node : allPasswords) {
            cout << "Password: " << node->password << " | Waktu Dibuat: " << ctime(&node->timeCreated);
        }
    }
};



/* program ini menginisialisasi tiga vector untuk menyimpan karakter huruf, angka, dan simbol
    yang nantinya akan digunakan dalam pembuatan password. */
string generate_custom_password(int nr_huruf, int nr_simbol, int nr_angka) {
    vector<char> huruf = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    vector<char> angka = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    vector<char> simbol = {'!', '#', '$', '%', '&', '(', ')', '*', '+'};

    string pw_huruf = "";
    string pw_simbol = "";
    string pw_angka = "";

    /* Setelah mengambil input dari user, ngejalan for loop untuk membuat password yang sesuai dengan jumlah karakter yang diinput.
    Setiap kali melakukan iterasi pada loop, ia akan memilih karakter secara acak dari setiap vector huruf, simbol, atau angka
    menggunakan fungsi rand() dan operator modulus %. */
    for (int i = 0; i < nr_huruf; i++) {
        pw_huruf += huruf[rand() % huruf.size()];
    }

    for (int i = 0; i < nr_simbol; i++) {
        pw_simbol += simbol[rand() % simbol.size()];
    }

    for (int i = 0; i < nr_angka; i++) {
        pw_angka += angka[rand() % angka.size()];
    }

    // menggabungkan semua karakter yang tadi di input menjadi satu string password
    string pw = pw_huruf + pw_simbol + pw_angka;
    random_shuffle(pw.begin(), pw.end());

    return pw;
}

string generate_random_password(int panjang_pw){
    // inisialisasi vector kata_kata yang berisi karakter huruf, angka, dan simbol
     vector<char> kata_kata = {'!', '#', '$', '%', '&', '(', ')', '*', '+','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    //Kata2 acak yang dari for loop akan di masukan ke variabel ini nanti
    string random_password = "";

    // membangun password acak dengan memilih karakter secara acak dari vector kata_kata. Ini loopnya sama kayak di fungsi generate_custom_password
    for (int i = 0; i < panjang_pw; i++){
        random_password += kata_kata[rand() % kata_kata.size()];
    }

    // yang tadi variabel random_password akan jadi variabel pw yang nanti akan diacak menggunakan fungsi random_shuffle()
    string pw = random_password;
    random_shuffle(pw.begin(), pw.end());
    
    return pw;
}

int main() {
    Hashmap history;
    int pilihan = -1;
    while (pilihan != 0){
    // tampilan menu program
    cout << "==============================" << endl;
    cout << "Password Generator Sederhana C++" << endl;
    cout << "==============================" << endl;
    cout << "1. Generate Custom Random Password (input simbol,kata,huruf)" << endl;
    cout << "2. Langsung Generate Random Password" << endl;
    cout << "3. Liat History Password " << endl;
    cout << "0. Exit" << endl;
    cout << "==============================" << endl;

     // meminta input dari user untuk memilih menu yang diinginkan
    cout << "Pilih menu: ";
    cin >> pilihan;
    // clear screen setelah memilih pilihan, agar keliat rapih saja :v
    system("CLS");

    switch(pilihan){
        case 0: {
            cout << "\nKeluar Dari Program... Terima kasih Telah Memakai :D";
        }
            break;

        case 1: {
        int nr_huruf, nr_simbol, nr_angka;
            cout << "\t====== Generate Password Custom ===== ";
            cout << "\nBerapa banyak huruf yang Anda mau dalam password: ";
            cin >> nr_huruf;
            cout << "Berapa banyak simbol yang Anda inginkan: ";
            cin >> nr_simbol;
            cout << "Berapa banyak angka yang Anda inginkan: ";
            cin >> nr_angka;
            string password = generate_custom_password(nr_huruf, nr_simbol, nr_angka);
            cout << "\nPassword kamu adalah: " << password << endl;
            history.insert(password); // Menyimpan password ke dalam history
            cout << "\n\n\n\n";
        }
            break;

        case 2: {
        int panjang_pw;
            cout << "\t====== Random Password ======" << endl;
            cout << "Mau berapa panjang password Anda? : ";
            cin >> panjang_pw;
            string random_pw = generate_random_password(panjang_pw);
            cout << "\nPassword kamu adalah: " << random_pw << endl;
            history.insert(random_pw); // Menyimpan password ke dalam history
            cout << "\n\n\n";
        }
            break;

        case 3: {
        history.displayHistory(); // Menampilkan history password
            cout << "\n\n\n";
            }
            break;

        default:{
            cout << "Pilihan tidak valid, silakan coba lagi!\n\n\n" << endl;
                }

        }
    }
}

