#include "LinearProbing.h"
using namespace std;

void merge1(vector<int>& arr, int l, int m, int r) {
    int a = m - l + 1;
    int b = r - m;
    vector<int> left(a), right(b);
    for (int i = 0; i < a; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < b; i++) {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < a && j < b) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < a) {
        arr[k++] = left[i++];
    }

    while (j < b) {
        arr[k++] = right[j++];
    }

}

void merge1sort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge1sort(arr, l, m);
        merge1sort(arr, m + 1, r);
        merge1(arr, l, m, r);
    }
    else{
        return;
    }
}

void LinearProbing::createAccount(std::string id, int count) {
    
    int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;
    
    while(bankStorage1d[index].id!="" && bankStorage1d[index].balance!=-1){
        index = (index+1)%capacity;
    }
    bankStorage1d[index] = account;
    size++;
    
}


//what happens if the size is greater than k
std::vector<int> LinearProbing::getTopK(int k) {
     std::vector<int> balances;
    for (int i = 0; i < capacity; i++) {
        if (bankStorage1d[i].id!="" && bankStorage1d[i].balance!=-1) {
            balances.push_back(bankStorage1d[i].balance);
        }
    }
    int n = balances.size();
    merge1sort(balances,0,n-1);
    int m = min(k,n);
    vector<int> Topk(m);
    for (int i = 0; i < k && i < n; i++) {
        Topk[i] = balances[n-1-i];
    }
    return Topk;
}

int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    int ind = index;
    while (bankStorage1d[index].id!="") {
        if (bankStorage1d[index].id == id) {
            return bankStorage1d[index].balance;
        }
        index = (index + 1) % capacity;
        if(ind == index){
            return -1;
        }
    }
    return -1;
}
//suppose an account is not present then what happens if we add a transaction
void LinearProbing::addTransaction(std::string ind, int count) {
    int index = hash(ind);
    while(bankStorage1d[index].id!=""){
        if(bankStorage1d[index].id==ind && bankStorage1d[index].balance!=-1){
            bankStorage1d[index].balance+=count;
            return;
        }
        if (bankStorage1d[index].id == ind && bankStorage1d[index].balance == -1) {
            bankStorage1d[index].balance = count;
            size++;
            return;
        }
        index = (index + 1) % capacity;
    }
    createAccount(ind,count);
}

bool LinearProbing::doesExist(std::string id) {
    int index = hash(id);
    while (bankStorage1d[index].id!="") {
        if (bankStorage1d[index].id == id && bankStorage1d[index].balance!=-1) {
            return true;
        }
        if(bankStorage1d[index].id == id && bankStorage1d[index].balance == -1){
            return false;
        }
        index = (index + 1) % capacity;
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int index = hash(id);
    while(bankStorage1d[index].id!=""){
        if(bankStorage1d[index].id == id && bankStorage1d[index].balance!=-1){
            bankStorage1d[index].balance = -1;
            size--;
            return true;
        }else if(bankStorage1d[index].id==id && bankStorage1d[index].balance==-1){
            return false;
        }
        index = (index + 1)%capacity;
    }
    return false;
}

int LinearProbing::databaseSize() {
    return size;
}
int LinearProbing::hash(std::string id) {
    int h = 0;
    for (auto c : id) {
        int val;
        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            val = c - 'A' + 10;
        } else if (c == '_') {
            val = 36;
        } else if (c >= 'a' && c <= 'z') {
            val = c - 'a' + 37;
        } else {
            val = c;
        }
        h = ((h * base) % p + val) % p;
    }
    int index = h % capacity;
    if (index < 0) {
        index += capacity;
    }

    return index;
}
