#include <simpleATM.hpp>

int main()
{
    std::shared_ptr<SimpleATMController> atm = std::make_shared<SimpleATMController>();
    atm->operate();
}