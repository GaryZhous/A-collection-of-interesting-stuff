/**
  *You have been tasked with writing a program for a popular bank that will automate all its incoming transactions (transfer, deposit, and withdraw). The bank has n accounts numbered from 1 to n. The initial balance of each account is stored in a 0-indexed integer array balance, with the (i + 1)th account having an initial balance of balance[i].
  *Execute all the valid transactions. A transaction is valid if:
    1. The given account number(s) are between 1 and n, and
    2. The amount of money withdrawn or transferred from is less than or equal to the balance of the account.
  *Implement the Bank class:
    1. Bank(long[] balance) Initializes the object with the 0-indexed integer array balance.
    2. boolean transfer(int account1, int account2, long money) Transfers money dollars from the account numbered account1 to the account numbered account2. Return true if the transaction was successful, false otherwise.
    3. boolean deposit(int account, long money) Deposit money dollars into the account numbered account. Return true if the transaction was successful, false otherwise.
    4. boolean withdraw(int account, long money) Withdraw money dollars from the account numbered account. Return true if the transaction was successful, false otherwise.
*/
type Bank []int64

func Constructor(balance []int64) Bank {
	return balance
}

func (b Bank) Transfer(account1, account2 int, money int64) bool {
	if account1 > len(b) || account2 > len(b) || b[account1-1] < money {
		return false
	}
	b[account1-1] -= money
	b[account2-1] += money
	return true
}

func (b Bank) Deposit(account int, money int64) bool {
	if account > len(b) {
		return false
	}
	b[account-1] += money
	return true
}

func (b Bank) Withdraw(account int, money int64) bool {
	if account > len(b) || b[account-1] < money {
		return false
	}
	b[account-1] -= money
	return true
}
