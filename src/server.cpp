#include <server.hpp>
#include <iostream>

BankAPI::BankAPI() : storage(std::make_shared<Storage>())
{
    bool result;
    result = storage->enrollClient("1111 1111 1111 1111", 1588, "123-456-789", 5);
    result = storage->enrollClient("2222 2222 2222 2222", 3082, "135-791-113", 20);
    result = storage->addAccount("2222 2222 2222 2222", 1688, "246-810-121", 100);
    result = storage->enrollClient("3333 3333 3333 3333", 5700, "", 0);
};

BankAPI::~BankAPI(){};

std::pair<bool, std::vector<std::string>> BankAPI::responseAccountNumbers(std::string cardNumber, int pinNumber)
{
    auto resultClientInfo = this->storage->getClientInfo(cardNumber, pinNumber);
    std::pair<bool, std::shared_ptr<Account>> resultAccount;

    if (resultClientInfo.first)
    {
        auto resultAccountNumbers = resultClientInfo.second->getAccountNumbers();
        if (resultAccountNumbers.first)
        {
            return std::make_pair(true, resultAccountNumbers.second);
        }
        else
        {
            std::cerr << "[BankAPI Warn] Get account numbers fail" << std::endl;
        }
    }
    else
    {
        std::cerr << "[BankAPI Warn] Get client info fail" << std::endl;
    }

    return std::make_pair(false, std::vector<std::string>());
}

std::pair<bool, int> BankAPI::responseBalance(std::string cardNumber, int pinNumber, std::string accountNumber)
{
    auto resultClientInfo = this->storage->getClientInfo(cardNumber, pinNumber);
    std::pair<bool, std::shared_ptr<Account>> resultAccount;

    if (resultClientInfo.first)
    {
        auto resultAccount = resultClientInfo.second->getAccount(accountNumber);
        if (resultAccount.first)
        {
            return std::make_pair(true, resultAccount.second->getBalance());
        }
        else
        {
            std::cerr << "[BankAPI Warn] Get account fail" << std::endl;
        }
    }
    else
    {
        std::cerr << "[BankAPI Warn] Get client info fail" << std::endl;
    }

    return std::make_pair(false, resultAccount.second->getBalance());
}

std::pair<bool, int> BankAPI::responseDeposit(std::string cardNumber, int pinNumber, std::string accountNumber, int money)
{
    auto resultClientInfo = this->storage->getClientInfo(cardNumber, pinNumber);
    std::pair<bool, std::shared_ptr<Account>> resultAccount;

    if (resultClientInfo.first)
    {
        auto resultAccount = resultClientInfo.second->getAccount(accountNumber);
        if (resultAccount.first)
        {
            resultAccount.second->deposit(money);
            return std::make_pair(true, resultAccount.second->getBalance());
        }
        else
        {
            std::cerr << "[BankAPI Warn] Get account fail" << std::endl;
        }
    }
    else
    {
        std::cerr << "[BankAPI Warn] Get client info fail" << std::endl;
    }

    return std::make_pair(false, resultAccount.second->getBalance());
}

std::pair<bool, int> BankAPI::responseWithdraw(std::string cardNumber, int pinNumber, std::string accountNumber, int money)
{
    auto resultClientInfo = this->storage->getClientInfo(cardNumber, pinNumber);
    std::pair<bool, std::shared_ptr<Account>> resultAccount;

    if (resultClientInfo.first)
    {
        auto resultAccount = resultClientInfo.second->getAccount(accountNumber);
        if (resultAccount.first)
        {
            resultAccount.second->withdraw(money);
            return std::make_pair(true, resultAccount.second->getBalance());
        }
        else
        {
            std::cerr << "[BankAPI Warn] Get account fail" << std::endl;
        }
    }
    else
    {
        std::cerr << "[BankAPI Warn] Get client info fail" << std::endl;
    }

    return std::make_pair(false, resultAccount.second->getBalance());
}