#include <iostream>
#include <set>
#include <random>
#include <chrono>
#include <time.h>
#include <fstream>
using namespace std;
using namespace std::chrono;

const char opchar[4] = {'+','-','*','/'};

double f(double res, int op, double operand){
    if (op == 0) return res += operand;
    if (op == 1) return res -= operand;
    if (op == 2) return res *= operand;
    if (op == 3) return res /=operand;
    return res;
}

bool isEqual(double a, double b){
    return abs(a-b) <= 0.00000001;
}

void printKartu(int kartu[4], ostream &outstream){
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
    if (ans.empty()){
        outstream << "No solutions found!\n";
    } else {
        outstream << ans.size() << " solutions found!\n";
        for (auto solusi : ans){
            outstream << solusi << endl;
        }
    }
}

int main(){
    srand(time(0));
    string input;
    int kartu[4];
cout << "================================================================================================\n"
     << " ::::::::   :::                   ::::::::   ::::::::  :::    :::     ::: :::::::::: :::::::::  \n"
     << ":+:    :+: :+:                   :+:    :+: :+:    :+: :+:    :+:     :+: :+:        :+:    :+: \n"
     << "      +:+ +:+ +:+                +:+        +:+    +:+ +:+    +:+     +:+ +:+        +:+    +:+ \n"
     << "    +#+  +#+  +:+  +#++:++#++:++ +#++:++#++ +#+    +:+ +#+    +#+     +:+ +#++:++#   +#++:++#:  \n"
     << "  +#+   +#+#+#+#+#+                     +#+ +#+    +#+ +#+     +#+   +#+  +#+        +#+    +#+ \n"
     << " #+#          #+#                #+#    #+# #+#    #+# #+#      #+#+#+#   #+#        #+#    #+# \n"
     << "##########    ###                 ########   ########  ########## ###     ########## ###    ### \n"
     << "================================================================================================\n";
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
        cout << "Kartu Anda :\n";
        for (int i = 0;i < 4;i++) kartu[i] = rand() % 13+1;
        printKartu(kartu,cout);
    } else {
        cout << "Masukkan nilai empat kartu yang valid (A,2,3,4,5,6,7,8,9,10,J,Q,K) dengan dipisahkan spasi :\n";
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
                        kartu[inpCnt] = kartu[0]-'0';
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
    int cnt = 0;
    for (int i = 0;i < 4;i++){
        for (int j = 0;j < 4;j++){
            if (j == i) continue;
            for (int k = 0;k < 4;k++){
                if (k == i || k == j) continue;
                for (int l = 0;l < 4;l++){
                    if (l == i || l == j || l == k) continue;
                    cnt++;
                    int op[3];
                    for (op[0] = 0;op[0] < 4;op[0]++){
                        for (op[1] = 0;op[1] < 4;op[1]++){
                            for (op[2] = 0;op[2] < 4;op[2]++){
                                if (isEqual(f(f(f(kartu[i],op[0],kartu[j]) ,op[1],kartu[k]) ,op[2],kartu[l]),24)){
                                    string tmp = string("((")+ to_string(kartu[i]) + " " + opchar[op[0]] + " " + to_string(kartu[j]) + ") " + opchar[op[1]] + " " + to_string(kartu[k]) + ") " + opchar[op[2]] + " " + to_string(kartu[l]);
                                    ans.insert(tmp);
                                } if (isEqual(f(f(kartu[i],op[0],f(kartu[j],op[1],kartu[k]) ) ,op[2],kartu[l]),24)){
                                    string tmp = string("(")+ to_string(kartu[i]) + " " + opchar[op[0]] + " (" + to_string(kartu[j]) + " " + opchar[op[1]] + " " + to_string(kartu[k]) + ")) " + opchar[op[2]] + " " + to_string(kartu[l]);
                                    ans.insert(tmp);
                                } if (isEqual(f(kartu[i],op[0],f(f(kartu[j],op[1],kartu[k]) ,op[2],kartu[l]) ),24)){
                                    string tmp = string("")+ to_string(kartu[i]) + " " + opchar[op[0]] + " ((" + to_string(kartu[j]) + " " + opchar[op[1]] + " " + to_string(kartu[k]) + ") " + opchar[op[2]] + " " + to_string(kartu[l]) + ")";
                                    ans.insert(tmp);
                                } if (isEqual(f(kartu[i],op[0],f(kartu[j],op[1],f(kartu[k],op[2],kartu[l]))),24)){
                                    string tmp = string("")+ to_string(kartu[i]) + " " + opchar[op[0]] + " (" + to_string(kartu[j]) + " " + opchar[op[1]] + " (" + to_string(kartu[k]) + " " + opchar[op[2]] + " " + to_string(kartu[l]) + "))";
                                    ans.insert(tmp);
                                } if (isEqual(f(f(kartu[i],op[0],kartu[j]),op[1],f(kartu[k],op[2],kartu[l])),24)){
                                    string tmp = string("(")+ to_string(kartu[i]) + " " + opchar[op[0]] + " " + to_string(kartu[j]) + ") " + opchar[op[1]] + " (" + to_string(kartu[k]) + " " + opchar[op[2]] + " " + to_string(kartu[l]) + ")";
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