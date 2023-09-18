/*
 * hashbank.h
 * Bank class using hash table to store accounts
 * hash function is simply accNum % 1000
 * there is linear collision resolution
 * however adding to a full table will throw a
 *   FullBank exception rather than resize the table
 * Created on: May 3, 2023
 */

#ifndef HASH_BANK_H_
#define HASH_BANK_H_

#include "account.h"
#include <iostream>
using namespace std;

#define MAX 1000

class FullBank {};

class HBank {
public:
  // Functions:
  HBank(int firstAccNum) : nextAccNum(firstAccNum) {}
  inline AccountType& getAcc(int accNum) { return accounts[accNum % MAX]; }
  void addAcc(string name);
  void delAcc(int accNum);
  void updateBal(int accNum, double delta);
  void print();
  int fill();
private:
  // Data Members:
  int nextAccNum;
  AccountType accounts[MAX];
};

void HBank::print() {
  cout << "Number of Accounts: " << fill() << endl;
  for (int i = 0; i < MAX; i++) if (accounts[i].getAccNum() > 0) accounts[i].print();
}

int HBank::fill() {
  int n = 0;
  for (int i = 0; i < MAX; i++) n += accounts[i].getAccNum() > 0;
  return n;
}

void HBank::addAcc(string name) {
  if (fill() >= MAX) throw new FullBank();
  while (accounts[nextAccNum % MAX].getAccNum()) nextAccNum++;
  accounts[nextAccNum % MAX] = AccountType(name, nextAccNum);
  cout << "Account created with number: " << accounts[nextAccNum % MAX].getAccNum() << endl;
  cout << "Number of accounts:          " << fill() << endl;
  nextAccNum++;
}

void HBank::delAcc(int accNum) {
  if (accounts[accNum % MAX].getAccNum() == accNum)
    accounts[accNum % MAX] = AccountType();
  else cout << "Account not found." << endl;
}

void HBank::updateBal(int accNum, double delta) {
  if (accounts[accNum % MAX].getAccNum() == accNum)
    accounts[accNum % MAX].update(delta);
  else cout << "Account not found." << endl;
}

#endif /* HASH_BANK_H_ */
