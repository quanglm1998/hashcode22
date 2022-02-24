#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

int32_t main(int32_t argc, char *argv[]) {
    string input_file = argv[1];
    string answer_file = argv[2];
    ifstream input(input_file);
    ifstream answer(answer_file);

    map<string, Contributor*> m;
    int c, p;
    input >> c >> p;
    for (int i = 0; i < c; i++) {
        auto con = new(Contributor);
        con->Read(input);
        m[con->name] = con;
    }
    map<string, Project*> projects;
    for (int i = 0; i < p; i++) {
        auto p = new(Project);
        p->Read(input);
        projects[p->name] = p;
    }
    for (auto [u, v] : m) {
        v->Write();
    }
    for (auto [u, v] : projects) {
        v->Write();
    }

    input.close();
    answer.close();
    return 0;
} 