/* 
 * main.cpp
 * Driver file for CSC 240 Group Lab
 * Graham Brunning, Farhan Ahmed, Emilia Michalek, Janam Mehta
 * the driver itself launches one of two driver functions
 *   for the linked-list and the hash-table implementations of Bank
 *  Created on: May 3, 2023
 */

#include "account.h"
#include "bank.h"
#include "hashbank.h"
#include <iostream>

int list_driver();
int hash_driver();

int main() {
  enum bank_type {
    linked_list,
    hash_table
  } mode;
  int in = -1;
  while (in < linked_list || in > hash_table) {
    cout << "Choose linked-list (0) or hash-table (1): ";
    cin >> in;
  }
  mode = bank_type(in);
  if (mode == linked_list) return list_driver();
  if (mode == hash_table)  return hash_driver();
}

int list_driver() {
  const int START = 123000;
  Bank b(START);
  b.addAcc("Graham Brunning");
  b.updateBal(START, 100.00);
  b.addAcc("Graham Braham");
  b.updateBal(START + 1, 1.30);
  
  cout << endl << "Welcome to the bank!" << endl;

  string input = "";
  while(input != "quit") {
    cout << endl << "try 'print' 'add' 'withdraw' 'deposit' 'view' 'delete' 'quit'" << endl;
    cin >> input;
    if (input == "print") { // print a summary of all accounts
      b.print();
    } else if (input == "add") { // add a new account
      string fname, lname;
      cout << "What is the first name on the account? ";
      cin >> fname;
      cout << "What is the last name on the account? ";
      cin >> lname;
      b.addAcc(fname + " " + lname);
    } else if (input != "quit") {
      int accNum;
      cout << "Enter an account number (123XXX): ";
      cin >> accNum;
      if (input == "view") { // print an account
        b.getAcc(accNum)->print();
      } else if (input == "delete") { // delete an account
        b.delAcc(accNum);
      } else { // deposit or withdraw money from an account
        double delta = 0.0;
        cout << "Enter the " 
             << (input == "deposit" ? "deposit" : "withdrawl")
             << " amount (DD.CC): $";
        cin >> delta;
        if (delta < 0.0) cout << "Please enter a positive number." << endl;
        else if (input == "deposit")  b.updateBal(accNum, delta);
        else if (input == "withdraw") b.updateBal(accNum, -delta);
      }
    }
    cin.clear();
  }
  b.print();
  return 0;
}

int hash_driver() {
  const int START = 123000;
  HBank h(START);

  h.addAcc("Graham Brunning");
  h.updateBal(START, 100.00);
  h.addAcc("Graham Braham");
  h.updateBal(START + 1, 1.30);

  cout << endl << "Welcome to the bank!" << endl;

  string input = "";
  while (input != "quit") {
    cout << endl << "try 'print' 'add' 'withdraw' 'deposit' 'view' 'delete' 'quit'" << endl;
    cin >> input;
    if (input == "print") { // print a summary of all accounts
      h.print();
    } else if (input == "add") { // add a new account
      string fname, lname;
      cout << "What is the first name on the account? ";
      cin >> fname;
      cout << "What is the last name on the account? ";
      cin >> lname;
      h.addAcc(fname + " " + lname);
    } else if (input != "quit") {
      int accNum;
      cout << "Enter an account number (123XXX): ";
      cin >> accNum;
      if (h.getAcc(accNum).getAccNum() != accNum) {
        cout << "Account not found." << endl;
      } else if (input == "view") { // print an account
        h.getAcc(accNum).print();
      } else if (input == "delete") { // delete an account
        h.delAcc(accNum);
      } else { // deposit or withdraw money from an account
        double delta = 0.0;
        cout << "Enter the " << (input == "deposit" ? "deposit" : "withdrawl")
             << " amount (DD.CC): $";
        cin >> delta;
        if (delta <= 0.0) cout << "Please enter a positive number." << endl;
        else if (input == "deposit")  h.updateBal(accNum, delta);
        else if (input == "withdraw") h.updateBal(accNum, -delta);
      }
    }
    cin.clear();
  }
  h.print();
  return 0;
}
