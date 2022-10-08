#include <storage.hpp>
#include <iostream>

Account::Account(int _balance) : balance(_balance){};
Account::Account() : balance(0){};
Account::~Account(){};

bool Account::deposit(int money)
{
    if (money < 0)
    {
        std::cerr << "[Account Error] money is not negative" << std::endl;
        return false;
    }
    else
    {
        this->balance += money;
        return true;
    }
}

bool Account::withdraw(int money)
{
    if (money < 0)
    {
        std::cerr << "[Account Error] money is not negative" << std::endl;
        return false;
    }
    else if ((this->balance - money) < 0)
    {
        std::cerr << "[Account Error] Insufficient balance" << std::endl;
        return false;
    }
    else
    {
        this->balance -= money;
        return true;
    }
}

int Account::getBalance()
{
    return this->balance;
}

ClientInfo::ClientInfo(int _pinNumber) : pinNumber(_pinNumber){};                                      // pinNumber만 등록한 경우
ClientInfo::ClientInfo(int _pinNumber, std::string _accountNumber, int _money) : pinNumber(_pinNumber) // pinNumber 등록 및 초기 계좌 등록한 경우
{
    this->openAccount(_accountNumber, _money);
}
ClientInfo::ClientInfo() : pinNumber(-1){}; // 명의만 등록한 경우
ClientInfo::~ClientInfo(){};

bool ClientInfo::validPinNumber(int pinNumber)
{
    if ((this->pinNumber == pinNumber) && (pinNumber != -1))
    {
        return true;
    }
    else
    {
        std::cerr << "[ClientInfo Error] PIN number is Not valid" << std::endl;
        return false;
    }
}

std::pair<bool, std::shared_ptr<Account>> ClientInfo::getAccount(std::string accountNumber)
{
    std::shared_ptr<Account> dummy = std::make_shared<Account>(-1);
    if (this->accounts.empty())
    {
        std::cerr << "[ClientInfo Error] Accounts is empty" << std::endl;
        return std::make_pair(false, dummy);
    }
    else
    {
        if (this->accounts.find(accountNumber) == this->accounts.end())
        {
            std::cerr << "[ClientInfo Error] Account nubmer is not Exist" << std::endl;
            return std::make_pair(false, dummy);
        }

        return std::make_pair(true, this->accounts[accountNumber]);
    }
}

std::pair<bool, std::vector<std::string>> ClientInfo::getAccountNumbers()
{
    if (this->accounts.empty())
    {
        std::cerr << "[ClientInfo Error] Accounts is empty" << std::endl;
        return std::make_pair(false, std::vector<std::string>());
    }
    else
    {
        std::vector<std::string> accountNumbers;
        accountNumbers.reserve(this->accounts.size());
        for (auto &kv : this->accounts)
            accountNumbers.emplace_back(kv.first);

        return std::make_pair(true, accountNumbers);
    }
}

bool ClientInfo::openAccount(std::string accountNumber, int money = 0)
{

    if ((this->accounts.empty()) || (this->accounts.find(accountNumber) == this->accounts.end()))
    {
        this->accounts[accountNumber] = std::make_shared<Account>(money);
        return true;
    }
    else if (this->accounts.find(accountNumber) != this->accounts.end())
    {
        std::cerr << "[ClientInfo Error] Account is already exist" << std::endl;
        return false;
    }
    else
    {
        std::cerr << "[ClientInfo Error] Open account error" << std::endl;
        return false;
    }
}

Storage::Storage(){};
Storage::~Storage(){};

bool Storage::enrollClient(std::string cardNumber, int pinNumber, std::string accountNumber = "", int money = 0)
{
    if ((this->clientInfos.empty()) || (this->clientInfos.find(accountNumber) == this->clientInfos.end()))
    {
        if (accountNumber != "")
            this->clientInfos[cardNumber] = std::make_shared<ClientInfo>(pinNumber, accountNumber, money);
        else
            this->clientInfos[cardNumber] = std::make_shared<ClientInfo>(pinNumber);
        return true;
    }
    else
    {
        std::cerr << "[Storage Error] Enroll client error" << std::endl;
        return false;
    }
}

bool Storage::addAccount(std::string cardNumber, int pinNumber, std::string accountNumber, int money = 0)
{
    if (this->clientInfos.find(cardNumber) != this->clientInfos.end())
    {
        auto &clientInfo = this->clientInfos[cardNumber];
        if (clientInfo->validPinNumber(pinNumber))
        {
            clientInfo->openAccount(accountNumber, money);
            return true;
        }
        else
        {
            std::cerr << "[Storage Error] Client PIN number is not valid" << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "[Storage Error] Add account error" << std::endl;
        return false;
    }
}

std::pair<bool, std::shared_ptr<ClientInfo>> Storage::getClientInfo(std::string &cardNumber, int pinNumber)
{
    if (this->clientInfos.find(cardNumber) != this->clientInfos.end())
    {
        auto &clientInfo = this->clientInfos[cardNumber];
        if (clientInfo->validPinNumber(pinNumber))
        {
            return std::make_pair(true, this->clientInfos[cardNumber]);
        }
        else
        {
            std::cerr << "[Storage Error] Client PIN number is not valid" << std::endl;
            return std::make_pair(false, std::make_shared<ClientInfo>());
        }
    }
    else
    {
        std::cerr << "[Storage Error] Get client info error" << std::endl;
        return std::make_pair(false, std::make_shared<ClientInfo>());
    }
}