#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int consonants_cnt(string line) {
    int cnt = 0;
    string consonants = "bcdfghjklmnpqrstvwxyz";

    for (int i = 0; i < line.size(); i++) {
        for (int j = 0; j < consonants.size(); j++) {
            if (line[i] == consonants[j]) {
                cnt++;
            }
        }
    }

    return cnt;
}

int main() {
    string cur_line;
    int N, K, cnt = 0;

    cout << "Enter N and K " << endl;
    cin >> N >> K;

    ifstream fst_file("F1.txt");
    ofstream snd_file("F2.txt", ios::trunc);

    if (fst_file.is_open()) {
        for(int i = 1; getline(fst_file, cur_line); i++) {
            if (i >= N && i <= K) {
                snd_file << cur_line << endl;
                cnt += consonants_cnt(cur_line);
            }
        }
    }
    else {
        cout << "Error!" << endl;
    }

    fst_file.close();
    snd_file.close();

    cout << "Find " << cnt << " consonants" << endl;
    
    return 0;
}