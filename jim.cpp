// This is my solution to the "Jim and his LAN party" problem on hackerrank. My solution uses a discrete set with some augmentations to acheive the goal.
// https://www.hackerrank.com/challenges/jim-and-his-lan-party/problem

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class DS {
    public:
    int* people;
    set<int>* groupGames;
    
    int* gameNumGroups;
    vector<int> gameTimes;
    
    DS (vector<int> games, int m) {
        people = new int[games.size()];
        groupGames = new set<int>[games.size()];
        
        gameNumGroups = new int[m];
        
        for (int i = 0; i < games.size(); i++) {
            people[i] = -1;
            groupGames[i].insert(games[i]-1);
            gameNumGroups[games[i]-1] += 1;
        }
        
        for (int i = 0; i < m; i++) {
            if (gameNumGroups[i] == 1) {
                gameTimes.push_back(0);
            } else {
                gameTimes.push_back(-1);
            }
        }
    }

    int find(int i) {
        if (people[i] < 0) { // representative member
            return i;
        }
        int a = find(people[i]); // find representative member
        people[i] = a; // path compression
        return a;
    }

    int getSize(int i) {
        int a = find(i); // get representative member
        return -1 * people[a]; // size is negative
    }

    void connect(int i, int j, int wireNum) {
        int a = find(i); // rep member of i
        int b = find(j); // rep member of j
        if (a == b) {
            return;
        }
        if (people[a] < people[b]) { // a's set has more members
            people[a] += people[b];
            people[b] = a;
            for (auto game: groupGames[b]) {
                if (groupGames[a].find(game) != groupGames[a].end()) {
                    gameNumGroups[game] -= 1;
                    if (gameNumGroups[game] == 1) {
                        gameTimes[game] = wireNum;
                    }
                } else {
                    groupGames[a].insert(game);
                }
            }
        } else { // bs set has more members
            people[b] += people[a];
            people[a] = b;
            for (auto game: groupGames[a]) {
                if (groupGames[b].find(game) != groupGames[b].end()) {
                    gameNumGroups[game] -= 1;
                    if (gameNumGroups[game] == 1) {
                        gameTimes[game] = wireNum;
                    }
                } else {
                    groupGames[b].insert(game);
                }
            }
        }
        
    }
    
    vector<int> getTimes() {
        return gameTimes;
    }
};

/*
 * Complete the lanParty function below.
 */
vector<int> lanParty(vector<int> games, vector<vector<int>> wires, int m) {
    /*
     * Write your code here.
     */
    
    DS ds(games, m);
    
    for (int i = 0; i < wires.size(); i++) {
        ds.connect(wires[i][0]-1, wires[i][1]-1, i+1); // Zero index
    }
    
    return ds.getTimes();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nmq_temp;
    getline(cin, nmq_temp);

    vector<string> nmq = split_string(nmq_temp);

    int n = stoi(nmq[0]);

    int m = stoi(nmq[1]);

    int q = stoi(nmq[2]);

    string games_temp_temp;
    getline(cin, games_temp_temp);

    vector<string> games_temp = split_string(games_temp_temp);

    vector<int> games(n);

    for (int games_itr = 0; games_itr < n; games_itr++) {
        int games_item = stoi(games_temp[games_itr]);

        games[games_itr] = games_item;
    }

    vector<vector<int>> wires(q);
    for (int wires_row_itr = 0; wires_row_itr < q; wires_row_itr++) {
        wires[wires_row_itr].resize(2);

        for (int wires_column_itr = 0; wires_column_itr < 2; wires_column_itr++) {
            cin >> wires[wires_row_itr][wires_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = lanParty(games, wires, m);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
