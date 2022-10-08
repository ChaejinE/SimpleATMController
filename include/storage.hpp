#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>

class Account
{
public:
    Account(int _balance);
    Account();
    ~Account();

    bool deposit(int money);
    bool withdraw(int money);
    int getBalance();

private:
    int balance;
};

class ClientInfo
{
public:
    ClientInfo(int _pinNumber);
    ClientInfo(int _pinNumber, std::string _accountNumber, int _money);
    ClientInfo();
    ~ClientInfo();

    bool validPinNumber(int pinNumber);
    std::pair<bool, std::shared_ptr<Account>> getAccount(std::string accountNumber);
    std::pair<bool, std::vector<std::string>> getAccountNumbers();
    bool openAccount(std::string accountNumber, int money);

private:
    int pinNumber;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
};

class Storage
{
public:
    Storage();
    ~Storage();

    bool enrollClient(std::string cardNumber, int pinNumber, std::string accountNumber, int money);
    bool addAccount(std::string cardNumber, int pinNumber, std::string accountNumber, int money);
    std::pair<bool, std::shared_ptr<ClientInfo>> getClientInfo(std::string &cardNumber, int pinNumber);

private:
    std::unordered_map<std::string, std::shared_ptr<ClientInfo>> clientInfos;
};
