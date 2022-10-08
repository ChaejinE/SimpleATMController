#include <server.hpp>

class SimpleATMController
{
public:
    SimpleATMController();
    ~SimpleATMController();

    void queryCardNumberToUser();
    void queryPinNumberToUser();
    bool queryAccountNumberToUser();
    bool queryProcessNumberToUser();

    void setCurrentCardNumber(std::string cardNumber);
    void setCurrentPinNumber(int pinNumber);
    void setAccountNumber(std::string accountNumber);

    void operate();
    bool isProcessAgain();

private:
    std::shared_ptr<BankAPI> api;

    std::string currentCardNumber;
    std::string currentAccountNumber;
    int currentPinNumber;

    std::pair<bool, std::vector<std::string>> requestAccountNumbers();
    std::pair<bool, int> requestBalanceToServer();
    std::pair<bool, int> requestDepositToServer(int money);
    std::pair<bool, int> requestWithdrawToServer(int money);

    std::vector<bool (*)()> workFlow;
};
