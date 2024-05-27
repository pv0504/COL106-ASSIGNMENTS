#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
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
    int capacity = 210011;
    //double load_factor = 0.5;
    const int p =  96769;
    const int base = 37;
    //void rehash();
    std::vector<Account>bankStorage1d =  std::vector<Account>(capacity);
    //std::vector<bool>aux = std::vector<bool>(capacity,false);
    // Other data members and functions specific to Quadratic Probing
};

#endif // QUADRATICPROBING_H
