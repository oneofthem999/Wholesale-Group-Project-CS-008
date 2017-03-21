#ifndef MEMBER_H
#define MEMBER_H
#include <string>

class member
{
    public:
        // MEMBER CONSTANT
        static const double SALES_TAX_RATE = .0875;
        static const double REBATE_RATE = 0.05;
        // CONSTRUCTORS
        member();
        member(const member& other);
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(std::string first, std::string last);
        bool setMembershipNumber(std::string number);
        bool setMembershipType(std::string type = "Basic");
        bool setExpirationDate(int month, int day, int year);
        bool enterPurchase(int m, int d, int y, std::string item,
                           double price, double quantity);
        bool setTotalAmountSpent(double amountToAdd);
        bool setRebateAmount();
        // CONSTANT MEMBER FUNCTIONS
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getID() const;
        std::string getMembershipType() const;
        std::string getExpirationDate() const;
        double getAmountSpent() const;
        double getRebateAmount() const;
        bool shouldUpgradeOrDowngrade() const;

    private:
        std::string firstName;
        std::string lastName;
        std::string membershipNumber;
        std::string membershipType;
        int expMonth;
        int expDay;
        int expYear;
        double totalAmountSpent;
        double rebateAmount;
        struct purchase
        {
            int month;
            int day;
            int year;
            std::string itemName;
            double itemPrice;
            double itemQuantity;
            double subtotal;
            double tax;
            double total;
        };
        purchase* purchaseHistory;
};

#endif // MEMBER_H
