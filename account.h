/* 
 * account.h
 * Account class
 * stores an int set at initialization,
 *   a string name, and a double balance
 * negative balances and account numbers are strictly forbidden
 *  Created on: Apr 26, 2023
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
using namespace std;

class AccountType {
public:
  // Functions:
  AccountType();
  AccountType(const AccountType &other);
  AccountType(string newName, int newAccNum);
  void print() const;
  void update(double delta);
  /* Merged into update() above. GB
  void deposit(double bal);
  void withdraw(double bal); */
  inline void newName(string newName)   { name = newName; }
  inline void newBalance(double newBal) { bal = newBal; }
  inline int    getAccNum()  const      { return accNum; }
  inline string getName()    const      { return name; }
  inline double getBalance() const      { return bal; }
private:
  // Data Members:
  int accNum;
  string name;
  double bal;
};

AccountType::AccountType() {
  accNum = 0;
  name   = "";
  bal    = 0.0;
}

AccountType::AccountType(string newName, int newAccNum) {
  accNum = newAccNum;
  name   = newName;
  bal    = 0.0;
}

AccountType::AccountType(const AccountType &other) {
  accNum = other.getAccNum();
  name   = other.getName();
  bal    = other.getBalance();
}

void AccountType::print() const {
  cout << "Account Number: "  << accNum << endl;
  cout << "Name:           "  << name   << endl;
  cout << "Balance:        $" << bal    << endl;
}

void AccountType::update(double delta) {
  if (bal + delta < 0.0) {
    cout << "You have insufficient funds to make this withdrawl." << endl;
  } else {
    bal += delta;
  }
  cout << "Your current balance is: $" << bal << endl;
}

/* Merged these two into the above update() function. GB
void AccountType::deposit(double depBal){
  bal += depBal;
}

void AccountType::withdraw(double withBal){
  if(withBal > bal){
    cout << "You don't have sufficient funds to make this withdrawl." << endl;
    cout << "Your current balance is: " << bal << endl;
  }else{
    bal -= withBal;
  }
}
*/

#endif /* ACCOUNT_H_ */
