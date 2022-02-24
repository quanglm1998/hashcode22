#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Contributor {
    string name;
    map<string, int> skills;

    void Read() {
        cin >> name;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string skill_name;
            int lv;
            cin >> skill_name >> lv;
            skills[skill_name] = lv;
        }
    }

    void Write() {
        cout << "Contributor: " << name << '\n';
        for (auto [skill, lv] : skills) {
            cout << skill << ' ' << lv << '\n';
        }
    }
};

struct Project {
    string name;
    int duration;
    int score;
    int deadline;
    vector< pair<string, int> > roles;

    void Read() {
        cin >> name >> duration >> score >> deadline;
        int r;
        cin >> r;
        roles.resize(r);
        for (auto &[skill, lv] : roles) {
            cin >> skill >> lv;
        }
    }

    void Write() {
        cout << "Project: " << name << ' ' << duration << ' ' << score << ' ' << deadline << '\n';
        for (auto &[skill, lv] : roles) {
            cout << skill << ' ' << lv << '\n';
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