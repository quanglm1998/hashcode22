#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Contributor {
    string name;
    map<string, int> skills;

    void Read() {
        
    }
};

struct Project {
    string name;
    int duration;
    int score;
    int deadline;
    vector< pair<string, int> > roles;

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