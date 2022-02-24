#include <bits/stdc++.h>

using namespace std;

// debugger, source: tourist
template <typename A, typename B>
string to_string(pair<A, B> p);
string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
    return res;
}
template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}
template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int C, P;

struct Skill {
    string skill;
    int level;
};

struct Contributor {
    string name;
    map<string, int> skills;
    vector<Skill> vskills;
};

struct Project {
    string name;
    int duration, score, deadline;
    map<string, int> roles;
    vector<Skill> vskills;
};

struct AssignedProject {
    int pId, startTime;
    vector<int> cIds;
};

vector<Contributor> contributors;
vector<Project> projects; 
vector<AssignedProject> aps;

void input() {
    cin >> C >> P;

    contributors.resize(C);
    projects.resize(P);

    for (auto &c : contributors) {
        cin >> c.name;
        int nSkills;
        cin >> nSkills;
        for (int i = 0; i < nSkills; i++) {
            string skill;
            int level;
            cin >> skill >> level;
            c.skills[skill] = level;
            c.vskills.push_back({skill, level});
        }
    }
    for (auto &p : projects) {
        cin >> p.name >> p.duration >> p.score >> p.deadline;
        int nRoles;
        cin >> nRoles;
        for (int i = 0; i < nRoles; i++) {
            string skill;
            int level;
            cin >> skill >> level;
            p.roles[skill] = level;
            p.vskills.push_back({skill, level});
        }
    }
}

set<int> availableC;

pair<bool, vector<int>> matchRoles(vector<Skill> skills) {
    vector<int> res;
    map<string, int> mxLevel;
    for (Skill skill : skills) {
        int found = -1;
        for (int cId : availableC) {
            auto &c = contributors[cId];
            int level = (c.skills.find(skill.skill) != c.skills.end() ? c.skills[skill.skill] : 0);
            if (level >= skill.level || (level >= skill.level - 1) && mxLevel[skill.skill] >= skill.level) {
                found = cId;
                break;
            } 
        }
        if (found == -1) {
            for (int e : res) {
                availableC.insert(e);
            }
            return make_pair(0, vector<int>(0));
        }
        availableC.erase(found);
        res.push_back(found);
        for (auto &e : contributors[found].vskills) {
            mxLevel[e.skill] = max(mxLevel[e.skill], e.level);
        }
    }
    // debug(skills.size(), res.size(), res);
    return make_pair(true, res);
}

void solve(vector<int> p) {
    for (int i = 0; i < C; i++) {
        availableC.insert(i);
    }

    // aps ids
    set<pair<int, int>> freed;
    int prev = aps.size();
    int curTime = 0;
    while (true) {
        for (int i = 0; i < p.size();) {
            int pid = p[i];
            auto foo = matchRoles(projects[pid].vskills);
            if (foo.first == false) {
                i++;
            } else {
                AssignedProject ap;
                ap.pId = pid;
                ap.startTime = curTime;
                ap.cIds = foo.second;
                aps.push_back(ap);
                freed.insert({curTime + projects[pid].duration, aps.size() - 1});
                
                // erase p[i]
                swap(p[i], p.back());
                p.pop_back();
            }
        }
        // go to next time
        auto foo = *freed.begin();
        freed.erase(freed.begin());
        curTime = foo.first;
        int apsId = foo.second;
        int pid = aps[apsId].pId;
        vector<int> cIds = aps[apsId].cIds;
        assert(cIds.size() == projects[pid].vskills.size());
        for (int i = 0; i < projects[pid].vskills.size(); i++) {
            string skill = projects[pid].vskills[i].skill;
            int curSkill = contributors[cIds[i]].skills[skill];
            if (curSkill <= projects[pid].vskills[i].level) {
                contributors[cIds[i]].skills[skill]++;
                for (auto &e : contributors[cIds[i]].vskills) {
                    if (e.skill == skill) e.level++;
                }
            }
            availableC.insert(cIds[i]);
        }

        if (aps.size() == prev && freed.empty()) {
            break;
        }
        prev = aps.size();
    }
}

void output() {
    cout << aps.size() << '\n';
    for (auto ap : aps) {
        cout << projects[ap.pId].name << "\n";
        for (int cId : ap.cIds) {
            cout << contributors[cId].name << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    vector<int> p(P);
    for (int i = 0; i < P; i++) p[i] = i;
    solve(p);

    output();

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";

    return 0;
}