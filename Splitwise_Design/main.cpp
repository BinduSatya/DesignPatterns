/*
Requirements:
1. User has name, emailId , id
2. User can createExpense, join groups, createRequest, acceptRequest
3. There should be a group where users can join
4. Expense can be group based/non group based
5. To create a expense, user need amount, paid by users, split among users, canbe group/cannot be
6. Split can be equal, amount based or percentagebased
7. Can between who owes whom between users
8. Simplify balances to minimize transactions
9. Each user can have history of expenses
*/

#include <bits/stdc++.h>
using namespace std;

class User;
class Expense;

class Split
{
public:
    User *user;
    double amount;

    Split(User *user, double amount) : user(user), amount(amount) {}
};

class User
{
public:
    static int nxtId;
    string id;
    string name;
    string email;

    unordered_map<string, double> balances;

    User(string name, string email)
    {
        id = "User_" + to_string(++nxtId);
        this->name = name;
        this->email = email;
    }

    void updateBalance(User *user, double amount)
    {
        balances[user->name] += amount;
    }

    double getTotalOwed()
    {
        double sum = 0;
        for (auto &it : balances)
            if (it.second > 0)
                sum += it.second;
        return sum;
    }

    double getTotalOwing()
    {
        double sum = 0;
        for (auto &it : balances)
            if (it.second < 0)
                sum += it.second;
        return sum;
    }
};

int User::nxtId = 0;

class SplitType
{
public:
    virtual vector<Split *> split(
        vector<User *> users,
        double amount,
        vector<double> meta) = 0;

    virtual ~SplitType() {}
};

class EqualSplitType : public SplitType
{
public:
    vector<Split *> split(vector<User *> users, double amount, vector<double>) override
    {
        vector<Split *> res;
        double each = amount / users.size();
        for (auto *u : users)
            res.push_back(new Split(u, each));
        return res;
    }
};

class ExactSplitType : public SplitType
{
public:
    vector<Split *> split(vector<User *> users, double, vector<double> meta) override
    {
        vector<Split *> res;
        if (users.size() != meta.size())
            return {};
        for (int i = 0; i < users.size(); i++)
            res.push_back(new Split(users[i], meta[i]));
        return res;
    }
};

class PercentSplitType : public SplitType
{
public:
    vector<Split *> split(vector<User *> users, double amount, vector<double> meta) override
    {
        vector<Split *> res;
        if (users.size() != meta.size())
            return {};
        for (int i = 0; i < users.size(); i++)
            res.push_back(new Split(users[i], amount * meta[i] / 100.0));
        return res;
    }
};

class Expense
{
public:
    static int nxtId;
    string id;
    string description;
    User *paidBy;
    double amount;
    vector<Split *> splits;
    string groupId;
    bool settled;

    Expense(
        string description,
        User *paidBy,
        double amount,
        vector<Split *> splits,
        string groupId = "")
    {
        id = "Expense_" + to_string(++nxtId);
        this->description = description;
        this->paidBy = paidBy;
        this->amount = amount;
        this->splits = splits;
        this->groupId = groupId;
        this->settled = false;
    }
};

int Expense::nxtId = 0;

class Group
{
public:
    static int nxtId;
    string id;
    string name;
    User *admin;

    vector<User *> users;
    vector<Expense *> expenses;

    unordered_map<User *, unordered_map<User *, double>> balances;

    Group(string name, User *admin)
    {
        id = "Group_" + to_string(++nxtId);
        this->name = name;
        this->admin = admin;
        users.push_back(admin);
    }

    string getGroupId() { return id; }

    void addMember(User *user)
    {
        users.push_back(user);
    }

    void removeMember(User *user)
    {
        users.erase(
            remove(users.begin(), users.end(), user),
            users.end());
        balances.erase(user);
    }

    void addExpense(
        string desc,
        double paidAmount,
        User *paidBy,
        vector<User *> involvedUsers,
        SplitType *splitType,
        vector<double> meta = {})
    {
        vector<Split *> splits = splitType->split(involvedUsers, paidAmount, meta);
        Expense *e = new Expense(desc, paidBy, paidAmount, splits, id);
        expenses.push_back(e);

        for (auto *s : splits)
        {
            if (s->user == paidBy)
                continue;

            balances[paidBy][s->user] += s->amount;
            balances[s->user][paidBy] -= s->amount;

            paidBy->updateBalance(s->user, s->amount);
            s->user->updateBalance(paidBy, -s->amount);
        }
    }

    void showGroupBalances()
    {
        cout << "\nGroup Balances:\n";
        for (auto &u : balances)
        {
            for (auto &v : u.second)
            {
                if (v.second > 0)
                    cout << v.first->name << " owes "
                         << u.first->name << " : "
                         << v.second << "\n";
            }
        }
    }

    void simplifyGroupDebts()
    {
        unordered_map<User *, double> netBalance;
        for (auto &u : balances)
        {
            for (auto &v : u.second)
            {
                netBalance[u.first] += v.second;
            }
        }

        vector<pair<User *, double>> debtors;
        vector<pair<User *, double>> creditors;

        for (auto &it : netBalance)
        {
            if (it.second < -0.01)
                debtors.push_back(it);
            else if (it.second > 0.01)
                creditors.push_back(it);
        }

        int i = 0, j = 0;

        cout << "\nSimplified Transactions:\n";

        while (i < debtors.size() && j < creditors.size())
        {
            double settleAmount = min(
                -debtors[i].second,
                creditors[j].second);

            cout << debtors[i].first->name
                 << " pays "
                 << creditors[j].first->name
                 << " : "
                 << settleAmount << endl;

            debtors[i].second += settleAmount;
            creditors[j].second -= settleAmount;

            if (abs(debtors[i].second) < 0.01)
                i++;
            if (abs(creditors[j].second) < 0.01)
                j++;
        }
    }
};

int Group::nxtId = 0;

class SplitWise
{
private:
    static SplitWise *instance;
    SplitWise() {}

public:
    unordered_map<string, User *> users;
    unordered_map<string, Group *> groups;

    static SplitWise *getInstance()
    {
        if (!instance)
            instance = new SplitWise();
        return instance;
    }

    User *createUser(string name, string email)
    {
        User *user = new User(name, email);
        users[user->id] = user;
        return user;
    }

    User *getUser(string userId)
    {
        if (users.count(userId))
            return users[userId];
        return nullptr;
    }

    Group *createGroup(string name, User *admin)
    {
        Group *group = new Group(name, admin);
        groups[group->getGroupId()] = group;
        return group;
    }

    Group *getGroup(string groupId)
    {
        if (groups.count(groupId))
            return groups[groupId];
        return nullptr;
    }

    void addUserToGroup(User *user, Group *group)
    {
        group->addMember(user);
    }

    void showUserBalance(User *user)
    {
        cout << "\nBalance Sheet for " << user->name << ":\n";
        for (auto &it : user->balances)
        {
            if (it.second > 0)
                cout << it.first << " owes " << it.second << "\n";
            else if (it.second < 0)
                cout << "Owes " << it.first << " : " << -it.second << "\n";
        }
    }

    void showGroupBalances(Group *group)
    {
        group->showGroupBalances();
    }
};

SplitWise *SplitWise::instance = nullptr;

int main()
{
    SplitWise *app = SplitWise::getInstance();

    User *u1 = app->createUser("Prabhas", "alice@gmail.com");
    User *u2 = app->createUser("Bob", "bob@gmail.com");
    User *u3 = app->createUser("Allu", "charlie@gmail.com");

    Group *trip = app->createGroup("Goa Trip", u1);

    app->addUserToGroup(u2, trip);
    app->addUserToGroup(u3, trip);

    SplitType *equalSplit = new EqualSplitType();

    trip->addExpense(
        "Hotel",
        3000,
        u1,
        {u1, u2, u3},
        equalSplit);

    app->showUserBalance(u1);
    app->showUserBalance(u2);
    app->showUserBalance(u3);

    SplitType *percentSplit = new PercentSplitType();
    trip->addExpense("Bus", 4500, u2, {u1, u2, u3}, percentSplit, {30, 40, 30});

    app->showUserBalance(u1);
    app->showUserBalance(u2);
    app->showUserBalance(u3);
    trip->simplifyGroupDebts();
    // app->showGroupBalances(trip);
    return 0;
}
