/*
  You have been tasked with writing a program for a popular bank that will automate all its incoming transactions (transfer, deposit, and withdraw). The bank has n accounts numbered from 1 to n. The initial balance of each account is stored in a 0-indexed integer array balance, with the (i + 1)th account having an initial balance of balance[i].
  
  Execute all the valid transactions. A transaction is valid if:
  1. The given account number(s) are between 1 and n, and
  2. The amount of money withdrawn or transferred from is less than or equal to the balance of the account.
  
  Implement the Bank class:
  1. Bank(long[] balance) Initializes the object with the 0-indexed integer array balance.
  2. boolean transfer(int account1, int account2, long money) Transfers money dollars from the account numbered account1 to the account numbered account2. Return true if the transaction was successful, false otherwise.
  3. boolean deposit(int account, long money) Deposit money dollars into the account numbered account. Return true if the transaction was successful, false otherwise.
  4. boolean withdraw(int account, long money) Withdraw money dollars from the account numbered account. Return true if the transaction was successful, false otherwise.
*/
struct Bank {
    balance: Vec<i64>,
}

impl Bank {
    fn new(balance: Vec<i64>) -> Self {
        Self { balance }
    }

    // 1-indexed account -> 0-indexed vector index
    fn idx(&self, account: i32) -> Option<usize> {
        if account <= 0 {
            return None;
        }
        let i = (account - 1) as usize;
        if i < self.balance.len() { Some(i) } else { None }
    }

    fn transfer(&mut self, account1: i32, account2: i32, money: i64) -> bool {
        let (i, j) = match (self.idx(account1), self.idx(account2)) {
            (Some(i), Some(j)) => (i, j),
            _ => return false,
        };

        if self.balance[i] < money {
            return false;
        }

        self.balance[i] -= money;
        self.balance[j] += money;
        true
    }

    fn deposit(&mut self, account: i32, money: i64) -> bool {
        let i = match self.idx(account) {
            Some(i) => i,
            None => return false,
        };

        self.balance[i] += money;
        true
    }

    fn withdraw(&mut self, account: i32, money: i64) -> bool {
        let i = match self.idx(account) {
            Some(i) => i,
            None => return false,
        };

        if self.balance[i] < money {
            return false;
        }

        self.balance[i] -= money;
        true
    }
}
