#include <iostream>
#include <set>
#include <chrono>
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
    int arr[4];
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
        cout << "Input salah, mohon masukkan ulang!\n";
    }

    set<string> ans;
    auto start = high_resolution_clock::now();
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
    
    for (auto i : ans){
        cout << i << endl;
    }
    cout << ans.size() << " solutions found!\n";
    cout << "Runtime: " << duration.count() << " microseconds\n";
    
}