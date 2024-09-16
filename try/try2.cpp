#include <bits/stdc++.h>
using namespace std;

// functional requirements
// Based on use cases, customers can opt for payment via card / upi / net banking etc. Below is the general runbook for making a payment.

// Select a pay mode
// Enter details
// For netbanking - enter username and password
// For credit / debit card - enter card details ( number, expiry, cvv etc )
// UPI - enter vpa
// Implement a payments gateway which help facilitate a payment for its client, below points should be kept in mind while implementation

// addClient() - add a client in PG
// removeClient() - remove client from PG
// hasClient() - does a client exist in the PG?
// listSupportedPaymodes() - show paymodes support by PG. if a client is passed as parameter, all supported paymodes for the clients should be shown.
// addSupportForPaymode() - add paymodes support in the PG. If a client is passed as parameter, add paymode for the clients.
// removePaymode() - remove paymode ( both from PG or client basis parameter)
// showDistribution() - show active distribution percentage of router
// makePayment( //necessary payment details )

// Customer, Bank(abstract)-- HDFCBank,AxisBank,SBIBank, Organisation(Client) , BankAccount, Payment(Abstract)- NetBankingPayment, CreditCardPayment, DebitCardPayment,UPIPayment
enum BankName
{
    AXIS,
    HDFC,
    ICICI
};

enum PaymentMethod
{
    CREDIT,
    DEBIT,
    NETBANKING,
    UPI
};

class Card
{
private:
    string cardNumber, CVV;

public:
    Card(string cardNum, string CVV)
    {
        this->cardNumber = cardNum;
        this->CVV = CVV;
    }
};

class BankAccount
{
private:
    string accNo, IFSCcode, mobileNumber, bankName;

public:
    BankAccount(string bankName, string accNo, string IFSC, string mobile)
    {
        this->bankName = bankName;
        this->accNo = accNo;
        this->IFSCcode = IFSC;
        this->mobileNumber = mobile;
    }
    BankAccount() {}
    string getMobile()
    {
        return mobileNumber;
    }
};

class Bank //
{
public:
    virtual bool makeCreditPayment(Card card, BankAccount acc, double amount) = 0;
    virtual bool makeDebitPayment(Card card, BankAccount acc, double amount) = 0;
    virtual string makeNetBankingPayment(string username, string password, BankAccount acc, double amount) = 0;
    virtual BankAccount fetchAccountDetails(string mobile) = 0;
    static bool makeUPIPayment(string reciepientVPA, string senderVPA, double amount)
    {
        // make a call to NPCI
        return true;
    }
};
class AxisBank : public Bank
{
public:
    bool makeCreditPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    bool makeDebitPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    string makeNetBankingPayment(string username, string password, BankAccount acc, double amount)
    {
        return "axis";
    }
    BankAccount fetchAccountDetails(string mobile)
    {
        return BankAccount("", "", "", "");
    }
};

class ICICIBank : public Bank
{
public:
    bool makeCreditPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    bool makeDebitPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    string makeNetBankingPayment(string username, string password, BankAccount acc, double amount)
    {
        return "ICICI";
    }
    BankAccount fetchAccountDetails(string mobile)
    {
        return BankAccount("", "", "", "");
    }
};

class HDFCBank : public Bank
{
public:
    bool makeCreditPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    bool makeDebitPayment(Card card, BankAccount acc, double amount)
    {
        return true;
    }
    string makeNetBankingPayment(string username, string password, BankAccount acc, double amount)
    {
        return "HDFC";
    }
    BankAccount fetchAccountDetails(string mobile)
    {
        return BankAccount("", "", "", "");
    }
};

class Customer
{
private:
    string name, mobile, vendorId;
    BankAccount account;

public:
    Customer(string name, string mobile, string bankName, string vendorId) : name(name), mobile(mobile), vendorId(vendorId), account(getBank(bankName)->fetchAccountDetails(mobile)) {}

    static Bank *getBank(string bankName) // simple factory
    {
        if (bankName == "HDFC")
            return new HDFCBank();
        else if (bankName == "Axis")
            return new AxisBank();
        else
            return new ICICIBank();
    }
};

class Vendor
{
private:
    BankAccount account;
    string vendorId;
    vector<Customer> customers;
    unordered_set<PaymentMethod> allowedMethods;

public:
    Vendor(BankAccount bankAccount)
    {
        this->account = bankAccount;
        this->vendorId = "VENDOR" + bankAccount.getMobile();
    }
    Vendor() {}
    string getId()
    {
        return vendorId;
    }
    void addPaymentMethod(PaymentMethod method)
    {
        (this->allowedMethods).insert(method);
    }
    void removePaymentMethod(PaymentMethod method)
    {
        (this->allowedMethods).erase(method);
    }

    unordered_set<PaymentMethod> getAllowedMethods()
    {
        return this->allowedMethods;
    }
};

class Payment
{
private:
    string id;
    double amount;
    string vendorId;
    bool isSuccessful;

public:
    Payment(double amount, string vendorId)
    {
        this->amount = amount;
        this->vendorId = vendorId;
    }
};

class PaymentGateway
{
private:
    unordered_map<string, Vendor> vendors;
    unordered_set<PaymentMethod> paymentMethods;

public:
    void addClient(Vendor vendor)
    {
        vendors[vendor.getId()] = vendor;
    }
    void removeClient(string id)
    {
        vendors.erase(id);
    }
    bool hasClient(string id)
    {
        if (vendors.find(id) == vendors.end())
            return false;
        return true;
    }
    unordered_set<PaymentMethod> listSupportedPaymodes(string vendorId)
    {
        return (vendors[vendorId]).getAllowedMethods();
    }
    void addSupportForPaymode(PaymentMethod method)
    {
        (this->paymentMethods).insert(method);
    }
    void addSupportForPaymode(PaymentMethod method, string vendorId)
    {
        (vendors[vendorId]).addPaymentMethod(method);
    }
    void removePaymode(PaymentMethod method)
    {
        (this->paymentMethods).erase(method);
    }
    void removePaymode(PaymentMethod method, string vendorId)
    {
        (vendors[vendorId]).removePaymentMethod(method);
    }
    showDistribution()
    {
    }
    bool makePayment(PaymentMethod paymentMethod, double amount)
};

class Router // 2 strategies can be configured - either based on
{
public:
}

int
main()
{
    // BankAccount flipkartAccount=new BankAccount();
    cout << 1 << endl;
}