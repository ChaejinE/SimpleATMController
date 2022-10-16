# SimpleATMController

# Build
```
g++ -o main -I ./include src/main.cpp src/server.cpp src/simpleATM.cpp src/storage.cpp
```

# Run
```
./main
```

# Example
## Situation
```
DB

- [{Card Number : 1111 1111 1111 1111, PIN : 1588, Accounts: [{123-456-789: 5}]},
   {Card Number : 2222 2222 2222 2222, PIN : 3082, Accounts: [{135-791-113: 20}, {246-810-121: 100}]},
   {Card Number : 3333 3333 3333 3333, PIN : 5700, Accounts: []}]
```
- Card Number, PIN Number, Accounts(AccountNumber, money)

## See Balance Example 
```
Please insert your card. Ex) 0000 0000 0000 0000
2222 2222 2222 2222
Please enter your PIN number. Ex) 0000
2468
Please select your account that want to process. Ex) 1
1: 246-810-121
2: 135-791-113
1
Please select your process that you need Ex) 1
1: See Balance
2: Deposit
3: Withdraw
1
Balance : $5
Could you process again ? [y/n]
```

## Deposit Example
```
Please insert your card. Ex) 0000 0000 0000 0000
1111 1111 1111 1111
Please enter your PIN number. Ex) 0000
1588
Please select your account that want to process. Ex) 1
1: 123-456-789
1
Please select your process that you need Ex) 1
1: See Balance
2: Deposit
3: Withdraw
2
Please enter amount of money that want to deposit
Ex) 15  -> this means 15 dollars deposit
10
Atfter deposit, current balance : $15
Could you process again ? [y/n]
```

## Withdraw Example
```
Please insert your card. Ex) 0000 0000 0000 0000
2222 2222 2222 2222
Please enter your PIN number. Ex) 0000
3082
Please select your account that want to process. Ex) 1
1: 246-810-121
2: 135-791-113
2
Please select your process that you need Ex) 1
1: See Balance
2: Deposit
3: Withdraw
3
Please enter amount of money that want to withdraw
Ex) 15  -> this means 15 dollars withdraw
50
[Account Error] Insufficient balance
Atfter withdraw, current balance : $20
Could you process again ? [y/n]
y

Please insert your card. Ex) 0000 0000 0000 0000
2222 2222 2222 2222
Please enter your PIN number. Ex) 0000
3082
Please select your account that want to process. Ex) 1
1: 246-810-121
2: 135-791-113
2
Please select your process that you need Ex) 1
1: See Balance
2: Deposit
3: Withdraw
3
Please enter amount of money that want to withdraw
Ex) 15  -> this means 15 dollars withdraw
10
Atfter withdraw, current balance : $10
Could you process again ? [y/n]
```
