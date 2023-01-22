#include <iostream>
#include <set>
#include <random>
#include <chrono>
#include <time.h>
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
    return abs(a-b) <=0.00000001;
}


int main(){
    srand(time(0));
    char input;
    int arr[4];
    cout << "Pilih metode input\n";
    cout << "1. Generate kartu secara random\n";
    cout << "2. Input melalui terminal\n";
    do {
        cout << "Pilihan anda : ";
        cin >> input;
        if (input != '1' && input != '2'){
            cout << "Mohon masukkan pilihan yang sesuai.\n";
        }
    } while (input != '1' && input != '2');
    if (input == '1'){
        cout << "Kartu anda :\n";
        for (int i = 0;i < 4;i++){
            if (i != 0) cout << " ";
            arr[i] = rand() % 13+1;
            if (arr[i] == 1) cout << "A";
            else if (arr[i] == 11) cout << "J";
            else if (arr[i] == 12) cout << "Q";
            else if (arr[i] == 13) cout << "K";
            else cout << arr[i]; 
        }
        cout << endl;
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
                string kartu = "";
                while (i < s.length() && s[i] == ' ') i++;
                while (i < s.length() && s[i] != ' '){
                    kartu += s[i];
                    i++;
                }
                if (inpCnt == 4){
                    if (kartu.length() != 0) fail = true;
                    else break;
                } else if (kartu == "10"){
                    arr[inpCnt] = 10;
                    inpCnt++;
                } else if (kartu.length() == 1){
                    if (kartu[0] >= '2' && kartu[0] <= '9'){
                        arr[inpCnt] = kartu[0]-'0';
                        inpCnt++;
                    } else if (kartu[0] == 'A'){
                        arr[inpCnt] = 1;
                        inpCnt++;
                    } else if (kartu[0] == 'J'){
                        arr[inpCnt] = 11;
                        inpCnt++;
                    } else if (kartu[0] == 'Q'){
                        arr[inpCnt] = 12;
                        inpCnt++;
                    } else if (kartu[0] == 'K'){
                        arr[inpCnt] = 13;
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
            cout << "Input tidak valid, mohon input ulang!\n";
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
                                if (isEqual(f(f(f(arr[i],op[0],arr[j]) ,op[1],arr[k]) ,op[2],arr[l]),24)){
                                    string tmp = string("((")+ to_string(arr[i]) + " " + opchar[op[0]] + " " + to_string(arr[j]) + ") " + opchar[op[1]] + " " + to_string(arr[k]) + ") " + opchar[op[2]] + " " + to_string(arr[l]);
                                    ans.insert(tmp);
                                } if (isEqual(f(f(arr[i],op[0],f(arr[j],op[1],arr[k]) ) ,op[2],arr[l]),24)){
                                    string tmp = string("(")+ to_string(arr[i]) + " " + opchar[op[0]] + " (" + to_string(arr[j]) + " " + opchar[op[1]] + " " + to_string(arr[k]) + ")) " + opchar[op[2]] + " " + to_string(arr[l]);
                                    ans.insert(tmp);
                                } if (isEqual(f(arr[i],op[0],f(f(arr[j],op[1],arr[k]) ,op[2],arr[l]) ),24)){
                                    string tmp = string("")+ to_string(arr[i]) + " " + opchar[op[0]] + " ((" + to_string(arr[j]) + " " + opchar[op[1]] + " " + to_string(arr[k]) + ") " + opchar[op[2]] + " " + to_string(arr[l]) + ")";
                                    ans.insert(tmp);
                                } if (isEqual(f(arr[i],op[0],f(arr[j],op[1],f(arr[k],op[2],arr[l]))),24)){
                                    string tmp = string("")+ to_string(arr[i]) + " " + opchar[op[0]] + " (" + to_string(arr[j]) + " " + opchar[op[1]] + " (" + to_string(arr[k]) + " " + opchar[op[2]] + " " + to_string(arr[l]) + "))";
                                    ans.insert(tmp);
                                } if (isEqual(f(f(arr[i],op[0],arr[j]),op[1],f(arr[k],op[2],arr[l])),24)){
                                    string tmp = string("(")+ to_string(arr[i]) + " " + opchar[op[0]] + " " + to_string(arr[j]) + ") " + opchar[op[1]] + " (" + to_string(arr[k]) + " " + opchar[op[2]] + " " + to_string(arr[l]) + ")";
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
    cout << ans.size() << " solutions found!\n";
    for (auto i : ans){
        cout << i << endl;
    }
    cout << "Runtime : " << duration.count() << " microseconds\n";
    
}