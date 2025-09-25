#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class HCS {
private:
    string district;        
    int number;           
    int countPeople;          
    double payment;       
    int countPay;      

    void validate(int num, int people, double pay, int paid) {
        if (num <= 0) throw invalid_argument("Номер ЖЭС отрицательный");
        if (num > pow(10, 6)) throw invalid_argument("Номер ЖЭС слишком большой");
        if (people <= 0) throw invalid_argument("Число жильцов отрицательно");
        if (people > pow(10, 6)) throw invalid_argument("Число жильцов слишком большое");
        if (pay < 0) throw invalid_argument("Оплата за месяц отрицательна");
        if (paid < 0 || paid > people) throw invalid_argument("Число оплативших жильцов отрицательно или больше числа жильцов");
    }

public:
    
    HCS(const string& District, int Number, int CountPeople, double Payment, int CountPay = 0) {
        validate(Number, CountPeople, Payment, CountPay);  
        district = District;
        number = Number;
        countPeople = CountPeople;
        payment = Payment;
        countPay = CountPay;
    }

    
    HCS() : district("Не указан"), number(0), countPeople(0), payment(0.0), countPay(0) {}

    
    string getDistrict() const { return district; }
    int getNumber() const { return number; }
    int getCountPeople() const { return countPeople; }
    double getMonthlyPayment() const { return payment; }  
    int getCountPay() const { return countPay; }

    
    void setCountPay(int paidCount) {
        if (paidCount < 0 || paidCount > countPeople) {
            throw invalid_argument("Некорректное число оплативших жильцов");
        }
        countPay = paidCount;
    }

    // задолженность
    double calculateMust() const {
        int mustCount = countPeople - countPay;
        return mustCount * payment;
    }

    // процент оплативших 
    double getPaymentPercentage() const {  
        if (countPeople == 0) return 0.0;
        return (static_cast<double>(countPay) / countPeople) * 100.0;
    }

    // добавление оплаты от одного жильца
    void addPayment() {
        if (countPay < countPeople) {
            countPay++;
        }
        else {
            throw logic_error("Все жильцы уже оплатили");
        }
    }

    // добавление оплаты от нескольких жильцов
    void addPayments(int count) {
        if (countPay + count <= countPeople && count > 0) {
            countPay += count;
        }
        else {
            throw invalid_argument("Некорректное число оплативших");
        }
    }

    
    void info() const {
        cout << "-------------------------" << endl;
        cout << "Информация о ЖЭС" << endl;
        cout << "Район: " << district << endl;
        cout << "Номер ЖЭС: " << number << endl;
        cout << "Число жильцов: " << countPeople << endl;
        cout << "Ежемесячная оплата: " << payment << " руб." << endl;
        cout << "Оплатили: " << countPay << " жильцов" << endl;
        cout << "Задолженность: " << calculateMust() << " руб." << endl;
        cout << "Процент оплаты: " << getPaymentPercentage() << "%" << endl;  
        cout << "-------------------------" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    try {
        HCS hes("Центральный район", 15, 5000000, 2500.0, 450);
        hes.info();

        cout << "\nПосле дополнительных оплат:" << endl;
        hes.setCountPay(487);
        hes.info();

        hes.addPayment();
        cout << "\nПосле добавления одной оплаты:" << endl;
        cout << "Оплатили: " << hes.getCountPay() << " жильцов" << endl;
        cout << "Задолженность: " << hes.calculateMust() << " руб." << endl;

        cout << "\nВторой ЖЭС:" << endl;
        HCS hes2("Северный район", 8, 300, 1800.0);
        hes2.info();
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}