#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

int32_t main() {
    map<string, Contributor*> m;
    int c, p;
    cin >> c >> p;
    for (int i = 0; i < c; i++) {
        auto con = new(Contributor);
        con->Read();
        m[con->name] = con;
    }
    map<string, Project*> projects;
    for (int i = 0; i < p; i++) {
        auto p = new(Project);
        p->Read();
        projects[p->name] = p;
    }
    for (auto [u, v] : m) {
        v->Write();
    }
    for (auto [u, v] : projects) {
        v->Write();
    }
    return 0;
}