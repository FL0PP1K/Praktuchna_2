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
class ISubject {
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};
class Store : public ISubject {
private:
    static const int MAX_CUSTOMERS = 10;
    IObserver* observers[MAX_CUSTOMERS];
    int current_count;
    std::string current_promotion;
public:
    Store() : current_count(0) {
        for (int i = 0; i < MAX_CUSTOMERS; ++i) {
            observers[i] = nullptr;
        }
    }
    void attach(IObserver* observer) override {
        if (current_count < MAX_CUSTOMERS) {
            observers[current_count] = observer;
            current_count++;
            std::cout << "Новий підписник доданий до бази.\n";
        }
        else {
            std::cout << "База підписників переповнена.\n";
        }
    }
    void detach(IObserver* observer) override {
        for (int i = 0; i < current_count; ++i) {
            if (observers[i] == observer) {
                for (int j = i; j < current_count - 1; ++j) {
                    observers[j] = observers[j + 1];
                }
                observers[current_count - 1] = nullptr;
                current_count--;
                std::cout << "Клієнт відписався від розсилки.\n";
                return;
            }
        }
    }
    void notify() override {
        for (int i = 0; i < current_count; ++i) {
            if (observers[i] != nullptr) {
                observers[i]->update(current_promotion);
            }
        }
    }
    void createPromotion(const std::string& promotion) {
        current_promotion = promotion;
        std::cout << "\n[Store] Увага! Зміна стану: оголошено нову акцію!\n";
        notify();
    }
};
