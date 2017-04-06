#ifndef MEMBER_H
#define MEMBER_H
#include <string>
<<<<<<< HEAD
=======
#include <iostream>
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
#include "purchase.h"

const double REBATE_RATE = 0.05;
const double BASIC_DUES = 60.00;
const double PREFERRED_DUES = 75.00;
<<<<<<< HEAD

=======
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
static purchaseHistory history = purchaseHistory();

class member
{
    friend class purchaseHistory;
<<<<<<< HEAD
public:
    // CONSTRUCTORS AND DESTRUCTOR
    member();
    member(const member& other);
    ~member();
    // MODIFICATION MEMBER FUNCTIONS
    void setName(std::string first, std::string last);
    void setMembershipNumber(std::string number);
    bool setMembershipType(std::string type = "Basic");
    void setExpirationDate(std::string date);
    void enterPurchase(std::string date, Item item);
    void setAmountSpent(double amountToAdd);
    void setRebateAmount();
    memberPurchase* getMemberPurchase() { return memberPurchases; }

    // CONSTANT MEMBER FUNCTIONS
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getID() const { return membershipNumber; }
    std::string getMembershipType() const { return membershipType; }
    std::string getExpirationDate() const { return expirationDate; }
    double getAmountSpent() const { return totalAmountSpent; }
    double getRebateAmount() const { return rebateAmount; }
    bool shouldUpgradeOrDowngrade() const;

    bool operator>(const member& RHS);
    bool operator<(const member& RHS);
    bool operator>=(const member& RHS);
    bool operator<=(const member& RHS);
    bool operator==(const member& RHS);
    bool operator!=(const member& RHS);

private:
    std::string firstName;
    std::string lastName;
    std::string membershipNumber;
    std::string membershipType;
    std::string expirationDate;
    double totalAmountSpent;
    double rebateAmount;
    memberPurchase* memberPurchases;
=======
    public:
        // CONSTRUCTORS AND DESTRUCTOR
        member();
        member(std::string first, std::string last, std::string id,
               std::string type, std::string date);
        member(const member& other);
        member& operator=(const member& other);
        ~member();
        // MODIFICATION MEMBER FUNCTIONS
        bool setName(std::string first, std::string last);
        bool setMembershipNumber(std::string number);
        bool setMembershipType(std::string type = "Basic");
        bool setExpirationDate(std::string date);
        void enterPurchase(std::string date, Item item);
        void setAmountSpent(double amountToAdd);
        void setRebateAmount();

        // CONSTANT MEMBER FUNCTIONS
        std::string getFirstName() const      {return firstName;}
        std::string getLastName() const       {return lastName;}
        std::string getFullName() const       {return firstName + " " + lastName;}
        std::string getID() const             {return membershipNumber;}
        std::string getMembershipType() const {return membershipType;}
        std::string getExpirationDate() const {return expirationDate;}
        double getAmountSpent() const         {return totalAmountSpent;}
        double getRebateAmount() const        {return rebateAmount;}
        memberPurchase* getMemberPurchase()   { return memberPurchases; }
        bool shouldUpgradeOrDowngrade() const;

        bool operator>(const member& RHS);
        bool operator<(const member& RHS);
        bool operator>=(const member& RHS);
        bool operator<=(const member& RHS);
        bool operator==(const member& RHS);
        bool operator!=(const member& RHS);

        friend ostream& operator<<(ostream& out, member& x);

    private:
        std::string firstName;
        std::string lastName;
        std::string membershipNumber;
        std::string membershipType;
        std::string expirationDate;
        double totalAmountSpent;
        double rebateAmount;
        memberPurchase* memberPurchases;
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
};

class memberList
{
    friend class member;
<<<<<<< HEAD
public:
    memberList();
    void addMember(member mem);
    void deleteMember(string firstName, string LastName);
    void deleteMember(string id);
    memberPurchase* memberPurchaseSearch(string firstName, string LastName);
    memberPurchase* memberPurchaseSearch(string id);
private:
    List<member> allMembers;
=======
    public:
        memberList();
        void addMember(member mem);
        void deleteMember(string firstName, string LastName);
        void deleteMember(string id);
        node<member>* search(string id);
        memberPurchase* memberPurchaseSearch(string firstName, string LastName);
        memberPurchase* memberPurchaseSearch(string id);
        void updateMemberName(member &updated, std::string first, std::string last);
        bool readMemberFile(std::string filename);
        bool readSalesFile(std::string filename);
        purchaseHistory getAllPurchases() const {return history;}
        List<member>& getMembers() {return allMembers;}
        int size() {return numberOfMembers;}
        friend ostream& operator<<(ostream& out, memberList& x);

    private:
        List<member> allMembers;
        int numberOfMembers;
>>>>>>> 0a42db703a0f5d93767bd7117a704ee57cec3a92
};

#endif // MEMBER_H
