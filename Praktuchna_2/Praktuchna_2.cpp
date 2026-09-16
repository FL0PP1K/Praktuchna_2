#include <iostream>
#include <string>
class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const std::string& message) = 0;
};
class Customer : public IObserver {
private:
    std::string name;
public:
    Customer(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Клієнт [" << name << "] отримав повідомлення: " << message << "\n";
    }
};
