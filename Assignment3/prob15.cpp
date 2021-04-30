#include<iostream>

using namespace std;

class BALANCE;

class Date
{
    int dd;
    int mm;
    int yy;

public:
    Date(int d, int m, int y)
    {
        dd = d;
        mm = m;
        yy = y;
    }
    Date()
    {
        dd = 1;
        mm = 1;
        yy = 2000;
    }

    friend class BALANCE;
};

class TRANSACTION;

class BALANCE
{
    int acno;
    float balance;
    Date last_update;

public:
    BALANCE(int acn, float b, Date dt)
    {
        acno = acn;
        balance = b;
        last_update = dt;
    }

    void print_balance()
    {
        cout << "Account No.: " << acno << "\nBalance: " << balance << "\nDate of Last Update: " << last_update.dd << "." << last_update.mm << "." << last_update.yy << endl;
    }

    friend class TRANSACTION;
};

class TRANSACTION
{
    int acno;
    Date transac_date;
    float amt;
    char type;

public:
    TRANSACTION(int acn, Date dt, float amount, char typ, BALANCE &balance)
    {
        int f = 0;
        if (typ == 'W')
        {
            if (balance.balance - amount < 0)
            {
                printf("Insufficient Balance to make transaction!");
                f = 1;
            }
            else
            {
                acno = acn;
                transac_date = dt;
                amt = amount;
                type = typ;

                balance.balance -= amount;
                balance.last_update = dt;
            }
        }
        else
        {
            acno = acn;
            transac_date = dt;
            amt = amount;
            type = typ;

            balance.balance += amount;
            balance.last_update = dt;
        }
    }
};

int main()
{
    Date date = Date(30, 10, 2000);
    BALANCE balance = BALANCE(100, 200, date);
    date = Date(30, 11, 2001);
    TRANSACTION(100, date, 100, 'W', balance);
    balance.print_balance();
    TRANSACTION(100, date, 100, 'D', balance);
    balance.print_balance();
}