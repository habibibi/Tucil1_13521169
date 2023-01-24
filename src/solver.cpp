#include <iostream>
#include <set>
#include <random>
#include <chrono>
#include <time.h>
#include <fstream>
using namespace std;
using namespace std::chrono;

const char opchar[4] = {'+','-','*','/'};

double f(double operand1, int op, double operand2){
    // menghitung nilai a op b
    if (op == 0) return operand1 += operand2;
    if (op == 1) return operand1 -= operand2;
    if (op == 2) return operand1 *= operand2;
    if (op == 3) return operand1 /= operand2;
    return operand1;
}

bool isEqual(double a, double b){
    // Mengecek apakah bilangan riil a dan b sama
    return abs(a-b) <= 0.00000001;
}

void printKartu(int kartu[4], ostream &outstream){
    // Mencetak kartu pada output stream tertentu
    for (int i = 0;i < 4;i++){
        if (i != 0) outstream << " ";
        if (kartu[i] == 1) outstream << "A";
        else if (kartu[i] == 11) outstream << "J";
        else if (kartu[i] == 12) outstream << "Q";
        else if (kartu[i] == 13) outstream << "K";
        else outstream << kartu[i]; 
    }
    outstream << endl;
}

void printSolusi(set<string> ans, ostream &outstream) {
    // Mencetak solusi pada output stream tertentu
    if (ans.empty()){
        outstream << "No solutions found!\n";
    } else {
        outstream << ans.size() << " solutions found!\n";
        int i = 1;
        for (auto solusi : ans){
            outstream << i << ". " << solusi << endl;
            i++;
        }
    }
}

int main(){
    srand(time(0));
    string input;
    int kartu[4];
    cout << "***** 24-SOLVER *****\n";
    cout << "Pilih metode memilih kartu :\n";
    cout << "1. Generate kartu secara random\n";
    cout << "2. Input melalui terminal\n";
    do {
        cout << "Pilihan anda : ";
        cin >> input;
        if (input != "1" && input != "2"){
            cout << "Mohon masukkan pilihan yang sesuai.\n";
        }
    } while (input != "1" && input != "2");
    if (input == "1"){
        // input secara random
        cout << "Kartu Anda :\n";
        for (int i = 0;i < 4;i++) kartu[i] = rand() % 13+1;
        printKartu(kartu,cout);
    } else {
        // input oleh pengguna
        cout << "Masukkan nilai empat kartu yang valid\n";
        cout << "(A,2,3,4,5,6,7,8,9,10,J,Q,K) dengan dipisahkan spasi :\n";
        char tmp;
        getchar(); //flush newline char from cin stream
        while (true){
            string s;
            getline(cin,s);
            int inpCnt = 0;
            bool fail = false;
            int i = 0;
            while (i < s.length() && !fail){
                string word = "";
                while (i < s.length() && s[i] == ' ') i++;
                while (i < s.length() && s[i] != ' '){
                    word += s[i];
                    i++;
                }
                if (inpCnt == 4){
                    if (word.length() != 0) fail = true;
                    else break;
                } else if (word == "10"){
                    kartu[inpCnt] = 10;
                    inpCnt++;
                } else if (word.length() == 1){
                    if (word[0] >= '2' && word[0] <= '9'){
                        kartu[inpCnt] = word[0]-'0';
                        inpCnt++;
                    } else if (word[0] == 'A'){
                        kartu[inpCnt] = 1;
                        inpCnt++;
                    } else if (word[0] == 'J'){
                        kartu[inpCnt] = 11;
                        inpCnt++;
                    } else if (word[0] == 'Q'){
                        kartu[inpCnt] = 12;
                        inpCnt++;
                    } else if (word[0] == 'K'){
                        kartu[inpCnt] = 13;
                        inpCnt++;
                    } else {
                        fail = true;
                    }
                } else {
                    fail = true;
                }
            }
            if (inpCnt != 4) fail = true;
            if (!fail) break;
            cout << "Input tidak valid! Mohon masukkan ulang.\n";
        }
    }
    auto start = high_resolution_clock::now();
    set<string> ans;
    for (int a = 0;a < 4;a++){
        for (int b = 0;b < 4;b++){
            if (b == a) continue;
            for (int c = 0;c < 4;c++){
                if (c == a || c == b) continue;
                for (int d = 0;d < 4;d++){
                    if (d == a || d == b || d == c) continue;
                    int op[3];
                    for (op[0] = 0;op[0] < 4;op[0]++){
                        for (op[1] = 0;op[1] < 4;op[1]++){
                            for (op[2] = 0;op[2] < 4;op[2]++){
                                if (isEqual(f(f(f(kartu[a],op[0],kartu[b]) ,op[1],kartu[c]) ,op[2],kartu[d]),24)){
                                    // Bentuk ((a op b) op c) op d
                                    string tmp = "";
                                    tmp = tmp + "((" + to_string(kartu[a]) + " " + opchar[op[0]] + " " + to_string(kartu[b]) + ") ";
                                    tmp = tmp + opchar[op[1]] + " " + to_string(kartu[c]) + ") ";
                                    tmp = tmp + opchar[op[2]] + " " + to_string(kartu[d]);
                                    ans.insert(tmp);
                                } 
                                if (isEqual(f(f(kartu[a],op[0],f(kartu[b],op[1],kartu[c]) ) ,op[2],kartu[d]),24)){
                                    // Bentuk (a op (b op c)) op d
                                    string tmp = "";
                                    tmp = tmp + "(" + to_string(kartu[a]) + " " + opchar[op[0]] + " ";
                                    tmp = tmp + "(" + to_string(kartu[b]) + " " + opchar[op[1]] + " " + to_string(kartu[c]) + ")) ";
                                    tmp = tmp + opchar[op[2]] + " " + to_string(kartu[d]);
                                    ans.insert(tmp);
                                } 
                                if (isEqual(f(kartu[a],op[0],f(f(kartu[b],op[1],kartu[c]) ,op[2],kartu[d]) ),24)){
                                    // Bentuk a op ((b op c) op d)
                                    string tmp = "";
                                    tmp = tmp + to_string(kartu[a]) + " " + opchar[op[0]] + " ";
                                    tmp = tmp + "((" + to_string(kartu[b]) + " " + opchar[op[1]] + " " + to_string(kartu[c]) + ") ";
                                    tmp = tmp + opchar[op[2]] + " " + to_string(kartu[d]) + ")";
                                    ans.insert(tmp);
                                } 
                                if (isEqual(f(kartu[a],op[0],f(kartu[b],op[1],f(kartu[c],op[2],kartu[d]))),24)){
                                    // Bentuk a op (b op (c op d))
                                    string tmp = "";
                                    tmp = tmp + to_string(kartu[a]) + " " + opchar[op[0]] + " ";
                                    tmp = tmp + "(" + to_string(kartu[b]) + " " + opchar[op[1]] + " ";
                                    tmp = tmp + "(" + to_string(kartu[c]) + " " + opchar[op[2]] + " " + to_string(kartu[d]) + "))";
                                    ans.insert(tmp);
                                } 
                                if (isEqual(f(f(kartu[a],op[0],kartu[b]),op[1],f(kartu[c],op[2],kartu[d])),24)){
                                    // Bentuk (a op b) op (c op d)
                                	string tmp = "";
                                    tmp = tmp + "(" + to_string(kartu[a]) + " " + opchar[op[0]] + " " + to_string(kartu[b]) + ") "; 
                                    tmp = tmp + opchar[op[1]] + " ";
                                    tmp = tmp + "(" + to_string(kartu[c]) + " " + opchar[op[2]] + " " + to_string(kartu[d]) + ")";
                                    ans.insert(tmp);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printSolusi(ans,cout);
    cout << "Runtime : " << duration.count() << " microseconds\n";
    do {
        cout << "Apakah Anda ingin mencetak solusi pada sebuah file (y/n)? ";
        cin >> input;
        if (input != "y" &&  input != "n"){
            cout << "Input tidak valid! Mohon masukkan ulang.\n";
        }
    } while (input != "y" &&  input != "n");
    if (input == "y"){
        string filename;
        ofstream file;
        cout << "Masukkan nama file beserta ekstensi : ";
        cin >> filename;
        file.open("..\\test\\"+filename);
        printKartu(kartu,file);
        printSolusi(ans,file);
        file.close();
        cout << "Solusi berhasil dicetak pada test\\" + filename + "!\n";
    }
}