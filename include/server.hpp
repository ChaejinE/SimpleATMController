#include <storage.hpp>

class BankAPI
{
public:
    BankAPI();
    ~BankAPI();

    std::pair<bool, std::vector<std::string>> responseAccountNumbers(std::string cardNumber, int pinNumber);
    std::pair<bool, int> responseBalance(std::string cardNumber, int pinNumber, std::string accountNumber);
    std::pair<bool, int> responseDeposit(std::string cardNumber, int pinNumber, std::string accountNumber, int money);
    std::pair<bool, int> responseWithdraw(std::string cardNumber, int pinNumber, std::string accountNumber, int money);

private:
    std::shared_ptr<Storage> storage;
    std::string s;
};
