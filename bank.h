/*
 * bank.h
 * Bank class using a linked list to store accounts
 * a rear pointer is maintained to allow O(1) insertion speed
 * the max number of accounts is unlimited,
 *   only set by the integer ceiling for account numbers
 *  Created on: Apr 26, 2023
 */

#ifndef BANK_H_
#define BANK_H_

#include "account.h"
#include <iostream>
using namespace std;

struct NodeType {
  NodeType() { next = nullptr; }
  AccountType* info;
  NodeType* next;
};

class Bank {
public:
  // Functions:
  Bank(int firstAccNum);
  inline int getSize() const { return size; }
  AccountType* getAcc(int accNum);
  void addAcc(string name);
  void delAcc(int accNum);
  void updateBal(int accNum, double delta);
  void print();
private:
  // Data Members:
  int size;             // number of accounts
  int nextAccNum;       // next account number
  NodeType* currentPos; // used for searches
  NodeType* front;      // first account added
  NodeType* rear;       // last account added
};

Bank::Bank(int firstAccNum) {
  size = 0;
  front = nullptr;
  rear = nullptr;
  currentPos = nullptr;
  nextAccNum = firstAccNum;
}

void Bank::print() {
  cout << "Number of Accounts: " << size << endl;
  currentPos = front;
  for (int i = 0; i < size; i++) {
    currentPos->info->print();
    currentPos = currentPos->next;
  }
}

AccountType* Bank::getAcc(int accNum) {
  currentPos = front;
  for (int i = 0; i < size; i++) {
    if (currentPos->info->getAccNum() == accNum) return (currentPos->info);
    else currentPos = currentPos->next;
  }
  cout << "Account not found." << endl;
  return nullptr;
}

void Bank::updateBal(int num, double delta) {
  AccountType* a = getAcc(num);
  if (a == nullptr) cout << "Account not found." << endl;
  else a->update(delta);
}

void Bank::addAcc(string name) {
  if (size) {
    rear->next = new NodeType();
    rear = rear->next;
  } else {
    rear = new NodeType();
    front = rear;
  }
  rear->info = new AccountType(name, nextAccNum++);
  cout << "Account created with number: " << rear->info->getAccNum() << endl;
  cout << "Number of accounts:          " << ++size << endl;
}

void Bank::delAcc(int num) {
  if (!size)
    return;
  NodeType* nodeToDel = front;
  NodeType* temp;
  if (front->info->getAccNum() == num) {
    temp = front;
    front = front->next;
    delete temp;
    cout << "Account deleted. Number of accounts: " << size << endl;
    return;
  }
  while (nodeToDel != rear && nodeToDel->next->info->getAccNum() != num) {
    nodeToDel = nodeToDel->next;
  }
  if (nodeToDel == rear) {
    cout << "Account not found." << endl;
  }
  temp = nodeToDel->next;
  nodeToDel->next = temp->next;
  delete temp;
  cout << "Account deleted. Number of accounts: " << size << endl;
}

#endif /* BANK_H_ */
