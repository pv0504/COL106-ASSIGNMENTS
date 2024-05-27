#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int size = 0;
    int bucket = 100003;
    const int p = 96769;
    const int base = 37;
    void Rehash();
    std::vector<Account> emptyRow;
    double load_factor = 0.8;
    std::vector<std::vector<Account>> bankStorage2d = std::vector<std::vector<Account>>(bucket, emptyRow);
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
