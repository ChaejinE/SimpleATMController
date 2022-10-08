#include <simpleATM.hpp>
#include <iostream>
#include <string>
#include <algorithm>

SimpleATMController::SimpleATMController() : api(std::make_shared<BankAPI>()) {}
SimpleATMController::~SimpleATMController() {}

void SimpleATMController::queryCardNumberToUser()
{
    std::cout << "Please insert your card. Ex) 0000 0000 0000 0000" << std::endl;
    std::string cardNumberStr;
    std::getline(std::cin, cardNumberStr);

    this->setCurrentCardNumber(cardNumberStr);
}

void SimpleATMController::queryPinNumberToUser()
{
    std::cout << "Please enter your PIN number. Ex) 0000" << std::endl;
    std::string pinNumberStr;
    std::getline(std::cin, pinNumberStr);
    pinNumberStr.erase(std::remove(pinNumberStr.begin(), pinNumberStr.end(), ' '), pinNumberStr.end());

    this->setCurrentPinNumber(std::stoi(pinNumberStr));
}

bool SimpleATMController::queryAccountNumberToUser()
{
    auto resultAccountNumbers = this->requestAccountNumbers();
    if (resultAccountNumbers.first)
    {
        std::cout << "Please select your account that want to process. Ex) 1" << std::endl;
        std::string accountNumberStr;

        for (int i = 1; i <= resultAccountNumbers.second.size(); ++i)
        {
            std::cout << i << ": ";
            std::cout << resultAccountNumbers.second[i - 1] << std::endl;
        }

        std::string selectNumber;
        std::getline(std::cin, selectNumber);
        selectNumber.erase(std::remove(selectNumber.begin(), selectNumber.end(), ' '), selectNumber.end());
        this->setAccountNumber(resultAccountNumbers.second[std::stoi(selectNumber) - 1]);

        return true;
    }
    else
    {
        std::cerr << "[ATM Error] Request account numbers fail" << std::endl;
    }

    return false;
}

bool SimpleATMController::queryProcessNumberToUser()
{
    std::cout << "Please select your process that you need Ex) 1" << std::endl;
    std::cout << "1: See Balance" << std::endl;
    std::cout << "2: Deposit" << std::endl;
    std::cout << "3: Withdraw" << std::endl;

    std::string selectNumber;
    std::getline(std::cin, selectNumber);
    selectNumber.erase(std::remove(selectNumber.begin(), selectNumber.end(), ' '), selectNumber.end());

    bool processResult;
    switch (std::stoi(selectNumber))
    {
    case 1:
    {
        auto result = this->requestBalanceToServer();
        if (result.first)
        {
            std::cout << "Balance : $" << result.second << std::endl;
            processResult = true;
        }
        else
        {
            std::cerr << "[ATM Error] Request balance fail" << std::endl;
            processResult = false;
        }

        break;
    }

    case 2:
    {
        std::cout << "Please enter amount of money that want to deposit" << std::endl;
        std::cout << "Ex) 15  -> this means 15 dollars deposit" << std::endl;
        std::string money;
        std::getline(std::cin, money);
        money.erase(std::remove(money.begin(), money.end(), ' '), money.end());

        auto result = this->requestDepositToServer(std::stoi(money));
        if (result.first)
        {
            std::cout << "Atfter deposit, current balance : $" << result.second << std::endl;
            processResult = true;
        }
        else
        {
            std::cerr << "[ATM Error] Request deposit fail" << std::endl;
            processResult = false;
        }

        break;
    }
    case 3:
    {
        std::cout << "Please enter amount of money that want to withdraw" << std::endl;
        std::cout << "Ex) 15  -> this means 15 dollars withdraw" << std::endl;
        std::string money;
        std::getline(std::cin, money);
        money.erase(std::remove(money.begin(), money.end(), ' '), money.end());
        if (money == "")
            money = "0";

        auto result = this->requestWithdrawToServer(std::stoi(money));
        if (result.first)
        {
            std::cout << "Atfter withdraw, current balance : $" << result.second << std::endl;
            processResult = true;
        }
        else
        {
            std::cerr << "[ATM Error] Request withdraw fail" << std::endl;
            processResult = false;
        }

        break;
    }
    default:
        std::cout << "Not Defined Process Number" << std::endl;
        processResult = false;

        break;
    }

    return processResult;
}

void SimpleATMController::setCurrentCardNumber(std::string cardNumber)
{
    this->currentCardNumber = cardNumber;
}

void SimpleATMController::setCurrentPinNumber(int pinNumber)
{
    this->currentPinNumber = pinNumber;
}

void SimpleATMController::setAccountNumber(std::string accountNumber)
{
    this->currentAccountNumber = accountNumber;
}

void SimpleATMController::operate()
{
    bool result = true;
    while (result)
    {
        this->queryCardNumberToUser();
        this->queryPinNumberToUser();

        result = this->queryAccountNumberToUser();
        if (!(result))
        {
            result = this->isProcessAgain();
            if (!result)
                break;
        }

        result = this->queryProcessNumberToUser();
        if (!(result))
        {
            result = this->isProcessAgain();
            if (!result)
                break;
        }

        result = this->isProcessAgain();
    }
}

bool SimpleATMController::isProcessAgain()
{
    std::cout << "Could you process again ? [y/n]" << std::endl;

    std::string again;
    std::getline(std::cin, again);
    again.erase(std::remove(again.begin(), again.end(), ' '), again.end());

    if ((again == "y") || (again == "Y"))
        return true;
    else
        return false;
}

std::pair<bool, std::vector<std::string>> SimpleATMController::requestAccountNumbers()
{
    auto resultAccountNumbers = this->api->responseAccountNumbers(this->currentCardNumber, this->currentPinNumber);

    if (resultAccountNumbers.first)
    {
        return std::make_pair(true, resultAccountNumbers.second);
    }

    return std::make_pair(false, resultAccountNumbers.second);
}

std::pair<bool, int> SimpleATMController::requestBalanceToServer()
{
    auto resultBalance = this->api->responseBalance(this->currentCardNumber, this->currentPinNumber, this->currentAccountNumber);

    if (resultBalance.first)
    {
        return std::make_pair(true, resultBalance.second);
    }

    return std::make_pair(false, resultBalance.second);
}

std::pair<bool, int> SimpleATMController::requestDepositToServer(int money)
{
    auto resultDeposit = this->api->responseDeposit(this->currentCardNumber, this->currentPinNumber, this->currentAccountNumber, money);

    if (resultDeposit.first)
    {
        return std::make_pair(true, resultDeposit.second);
    }

    return std::make_pair(false, resultDeposit.second);
}

std::pair<bool, int> SimpleATMController::requestWithdrawToServer(int money)
{
    auto resultWithdraw = this->api->responseWithdraw(this->currentCardNumber, this->currentPinNumber, this->currentAccountNumber, money);

    if (resultWithdraw.first)
    {
        return std::make_pair(true, resultWithdraw.second);
    }

    return std::make_pair(false, resultWithdraw.second);
}
