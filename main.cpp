#include <vector>
#include<iostream>
using namespace std;
class SET {
    vector<pair<bool, vector<int>>> sets;
public:
    SET() : sets(100001, make_pair(false, vector<int>())) {}
int insert(int n, int data) {
    auto &vec = sets[n].second;
    if (!sets[n].first) {
        sets[n].first = true;
    }
    vector<int>new_vec;
    int i = 0;
    while (i < vec.size() && vec[i] < data) {
        new_vec.push_back(vec[i]);
        i++;
    }
    if (i < vec.size() && vec[i] == data) {
        return vec.size();
    }else{
        new_vec.push_back(data);
        while(i<vec.size()){
            new_vec.push_back(vec[i]);
            i++;
        }
        vec = new_vec;
        return vec.size();
    }

}

    int Delete(int n, int data) {
    if (!sets[n].first) {
        return -1;
    } else {
        auto &vec = sets[n].second;
            vector<int> new_vec;
            for (int i:vec) {
                if (i!=data) {
                    new_vec.push_back(i);
                }
            }
            vec = new_vec;        
        return vec.size();
    }
}
    int Belongs_To(int n,int data) {
    if (!sets[n].first)
        return -1;
    else {
        vector<int>& vec = sets[n].second;
        int l = 0, h = vec.size() - 1;
        while (l <= h) {
            int mid = l + (h - l) / 2;
            if (vec[mid] == data)
                return 1;
            else if (vec[mid] < data)
                l = mid + 1;
            else
                h = mid - 1;
        }
        return 0;
    }
    }
    int Union(int n, int m) {
    if (!sets[n].first) {
        sets[n].first = true;
    }
    if (!sets[m].first) {
        sets[m].first = true;
    }
    vector<int>& a = sets[n].second;
    vector<int>& b = sets[m].second;
    vector<int> ans;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            ans.push_back(a[i]);
            i++;
        } else if (b[j] < a[i]) {
            ans.push_back(b[j]);
            j++;
        } else {
            ans.push_back(a[i]);
            i++;
            j++;
        }
    }
    while (i<a.size()) {
        ans.push_back(a[i]);
        i++;
    }
    while (j<b.size()) {
        ans.push_back(b[j]);
        j++;
    }
    sets[n].second = ans;
    return ans.size();
}
    int intersection(int n, int m) {
    if (!sets[n].first) {
        sets[n].first = true;
    }
    if (!sets[m].first) {
        sets[m].first = true;
    }
    vector<int> ans;
    vector<int>& a = sets[n].second;
    vector<int>& b = sets[m].second;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            ans.push_back(a[i]);
            i++;
            j++;
        }
    }
    sets[n].second = ans;
    return ans.size();
}
    int Difference(int n, int m) {
    if (!sets[n].first) {
        sets[n].first = true;
    }
    if (!sets[m].first) {
        sets[m].first = true;
    }
    vector<int> ans;
    vector<int>& a = sets[n].second;
    vector<int>& b = sets[m].second;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            ans.push_back(a[i]);
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < a.size()) {
        ans.push_back(a[i]);
        i++;
    }

    sets[n].second = ans;
    return ans.size();
}
        int Symmetric_Difference(int n, int m) {
    if (!sets[n].first) {
        sets[n].first = true;
    }
    if (!sets[m].first) {
        sets[m].first = true;
    }   
    vector<int>&a = sets[n].second;
    vector<int>&b = sets[m].second;
    vector<int> ans;
    int i = 0, j = 0;
    while (i<a.size() && j<b.size()) {
        if (a[i] < b[j]) {
            ans.push_back(a[i]);
            i++;
        } else if (a[i] > b[j]) {
            ans.push_back(b[j]);
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i<a.size()) {
        ans.push_back(a[i]);
        i++;
    }
    while (j < b.size()) {
        ans.push_back(b[j]);
        j++;
    }
    sets[n].second = ans;
    return ans.size();
    }
    int size(int n) {
    if (!sets[n].first) {
        sets[n].first = true;
        return 0;
    } else {
        return sets[n].second.size();
    }
}
void print(int n) {
    if (sets[n].first) {
        for (int i = 0; i < sets[n].second.size(); ++i) {
            cout << sets[n].second[i];
            if (i < sets[n].second.size() - 1) {
                cout << ",";
            }
        }
    }
    cout << endl;
}

};
int main() {
    SET set;
    int a,b,c;
    while (cin>>a>>b) {
        if(a!=9 && a!=6){
            cin>>c;
        }
        switch (a) {
            case 1:
                cout << set.insert(b, c) << endl;
                break;
            case 2:
                cout << set.Delete(b, c) << endl;
                break;
            case 3:
                cout << set.Belongs_To(b,c) << endl;
                break;
            case 4:
                cout << set.Union(b, c) << endl;
                break;
            case 5:
                cout << set.intersection(b, c) << endl;
                break;
            case 6:
                cout << set.size(b) << endl;
                break;
            case 7:
                cout << set.Difference(b, c) << endl;
                break;
            case 8:
                cout << set.Symmetric_Difference(b, c) << endl;
                break;
            case 9:
                set.print(b);
                break;
            default:
                break;
        }
    }
    return 0;
}

