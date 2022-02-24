#include <bits/stdc++.h>

using namespace std;

#define int long long


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


struct Contributor {
    string name;
    map<string, int> skills;

    void Read(ifstream& I) {
        I >> name;
        int n;
        I >> n;
        for (int i = 0; i < n; i++) {
            string skill_name;
            int lv;
            I >> skill_name >> lv;
            skills[skill_name] = lv;
        }
    }

    void Write() {
        cerr << "Contributor: " << name << '\n';
        for (auto [skill, lv] : skills) {
            cerr << skill << ' ' << lv << '\n';
        }
    }
};

struct Project {
    string name;
    int duration;
    int score;
    int deadline;
    vector< pair<string, int> > roles;

    void Read(ifstream& I) {
        I >> name >> duration >> score >> deadline;
        int r;
        I >> r;
        roles.resize(r);
        for (auto &[skill, lv] : roles) {
            I >> skill >> lv;
        }
    }

    void Write() {
        cerr << "Project: " << name << ' ' << duration << ' ' << score << ' ' << deadline << '\n';
        for (auto &[skill, lv] : roles) {
            cerr << skill << ' ' << lv << '\n';
        }
    }

    bool IsValid(vector<Contributor*>& list) {
        if (list.size() != roles.size()) {
            return 0;
        }
        for (int i = 0; i < roles.size(); i++) {
            int level = list[i]->skills[roles[i].first];
            if (level >= roles[i].second) {
                continue;
            }
            if (level + 1 < roles[i].second) {
                return 0;
            }
            for (int j = 0; j < roles.size(); j++) {
                if (list[j]->skills[roles[i].first] >= roles[i].second) {
                    return 1;
                }
            }
            return 0;
        }
        return 1;
    }

    // returns the score
    int Done(vector<Contributor*>& list, int time_done) {
        assert(list.size() == roles.size());
        for (int i = 0; i < roles.size(); i++) {
            if (list[i]->skills[roles[i].first] <= roles[i].second) {
                list[i]->skills[roles[i].first]++;
            }
        }
        if (time_done <= deadline) return score;
        return max(0ll, score - time_done + deadline);
    }
};