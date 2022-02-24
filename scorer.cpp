#include <bits/stdc++.h>
#include "utils.h"

#define int long long

using namespace std;

int32_t main(int32_t argc, char *argv[]) {
    string input_file = argv[1];
    string answer_file = argv[2];
    ifstream input(input_file);
    ifstream answer(answer_file);

    map<string, Contributor*> contributors;
    int c, p;
    input >> c >> p;
    for (int i = 0; i < c; i++) {
        auto con = new(Contributor);
        con->Read(input);
        contributors[con->name] = con;
    }
    map<string, Project*> projects;
    for (int i = 0; i < p; i++) {
        auto p = new(Project);
        p->Read(input);
        projects[p->name] = p;
    }


    int e;
    answer >> e;
    map<string, int> busy_to;
    long long res = 0;
    for (int i = 0; i < e; i++) {
        string name;
        vector<Contributor*> con_list;
        answer >> name;
        auto p = projects[name];
        for (int j = 0; j < p->roles.size(); j++) {
            string con_name;
            answer >> con_name;
            con_list.push_back(contributors[con_name]);
        }
        if (!p->IsValid(con_list)) {
            cerr << "Invalid on:\n";
            p->Write();
            cerr << "Contribution list:\n";
            for (auto con : con_list) {
                con->Write();
            }
            cout << 0 << '\n';
            return 0;
        }
        int min_time = 0;
        for (auto con : con_list) {
            min_time = max(min_time, busy_to[con->name]);
        }
        auto end_time = min_time + p->duration;
        for (auto &con : con_list) {
            busy_to[con->name] = end_time;
        }
        res += p->Done(con_list, end_time);
    }

    cout << res << '\n';
    input.close();
    answer.close();
    return 0;
} 