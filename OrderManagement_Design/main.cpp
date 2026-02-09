/*
Requirement:
1. User can order items from restuarant to cart
2. User can add/remove items from cart
3. User can checkOut(pay)
4. Each item can be from different restaurants
5. During checkout, user should pay the amount and
*/

#include <bits/stdc++.h>
using namespace std;

enum class OrderStatus
{
    PENDING,
    PREPARING,
    DISPATCHED,
    COMPLETED
};
enum class OrderItemStatus
{
    PENDING,
    READY
};

class Restaurant;
class Order;

class Item
{
    string name;
    double price;
    Restaurant *restaurant;

public:
    Item(string name, double price, Restaurant *restaurant)
        : name(name), price(price), restaurant(restaurant) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    Restaurant *getRestaurant() const { return restaurant; }
};

class OrderItem
{
    Item *item;
    OrderItemStatus status;

public:
    OrderItem(Item *item) : item(item), status(OrderItemStatus::PENDING) {}

    Item *getItem() const { return item; }

    void markReady() { status = OrderItemStatus::READY; }
    bool isReady() const { return status == OrderItemStatus::READY; }
};

class PaymentMethod
{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentMethod() = default;
};

class UPIPayment : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paid " << amount << " via UPI\n";
    }
};

class CardPayment : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paid " << amount << " via Card\n";
    }
};

/* ===================== Order ===================== */

class Order
{
    static int NEXT_ID;
    int id;
    vector<OrderItem> orderItems;
    OrderStatus status;

public:
    Order(vector<Item *> &items) : id(++NEXT_ID), status(OrderStatus::PENDING)
    {
        for (auto *item : items)
            orderItems.emplace_back(item);
    }

    int getId() const { return id; }
    OrderStatus getStatus() const { return status; }

    vector<OrderItem> &getOrderItems() { return orderItems; }

    void updateStatus(OrderStatus newStatus)
    {
        status = newStatus;
    }

    double totalAmount() const
    {
        double total = 0;
        for (auto &oi : orderItems)
            total += oi.getItem()->getPrice();
        return total;
    }
};

int Order::NEXT_ID = 0;

/* ===================== Observer Interface ===================== */

class OrderObserver
{
public:
    virtual void onOrderPlaced(Order *order) = 0;
};

/* ===================== Restaurant ===================== */

class Restaurant : public OrderObserver
{
    string name;
    map<int, vector<OrderItem *>> activeOrders;

public:
    Restaurant(string name) : name(name) {}

    string getName() const { return name; }

    void onOrderPlaced(Order *order) override
    {
        for (auto &oi : order->getOrderItems())
        {
            if (oi.getItem()->getRestaurant() == this)
            {
                activeOrders[order->getId()].push_back(&oi);
            }
        }
        if (!activeOrders[order->getId()].empty())
            cout << "Restaurant " << name << " received Order #" << order->getId() << "\n";
    }

    void prepareOrder(int orderId)
    {
        for (auto *oi : activeOrders[orderId])
            oi->markReady();

        cout << "Restaurant " << name << " prepared items for Order #" << orderId << "\n";
    }
};

/* ===================== Cart ===================== */

class Cart
{
    vector<Item *> items;

public:
    void addItem(Item *item)
    {
        items.push_back(item);
    }

    void removeItem(Item *item)
    {
        items.erase(remove(items.begin(), items.end(), item), items.end());
    }

    vector<Item *> &getItems() { return items; }

    void clear() { items.clear(); }
};

/* ===================== User ===================== */

class User
{
    string name;
    string address;
    Cart cart;
    vector<Order *> orderHistory;

public:
    User(string name, string address) : name(name), address(address) {}

    Cart &getCart() { return cart; }

    void addOrder(Order *order)
    {
        orderHistory.push_back(order);
    }

    void showOrderHistory()
    {
        cout << "\nOrder History for " << name << ":\n";
        for (auto *o : orderHistory)
            cout << "Order #" << o->getId() << "\n";
    }
};

/* ===================== Order Service ===================== */

class OrderService
{
    vector<OrderObserver *> observers;

public:
    void registerObserver(OrderObserver *obs)
    {
        observers.push_back(obs);
    }

    Order *checkout(User &user, PaymentMethod *payment)
    {
        auto &items = user.getCart().getItems();
        Order *order = new Order(items);

        payment->pay(order->totalAmount());

        for (auto *obs : observers)
            obs->onOrderPlaced(order);

        user.addOrder(order);
        user.getCart().clear();

        return order;
    }
};

/* ===================== MAIN ===================== */

int main()
{
    Restaurant r1("Indian Kitchen");
    Restaurant r2("Italian Bistro");

    Item naan("Naan", 20, &r1);
    Item paneer("Paneer", 150, &r1);
    Item pizza("Pizza", 300, &r2);

    User user("Yeswanth", "Bangalore");

    user.getCart().addItem(&naan);
    user.getCart().addItem(&pizza);
    user.getCart().addItem(&paneer);

    OrderService orderService;
    orderService.registerObserver(&r1);
    orderService.registerObserver(&r2);

    PaymentMethod *payment = new UPIPayment();
    Order *order = orderService.checkout(user, payment);

    r1.prepareOrder(order->getId());
    r2.prepareOrder(order->getId());

    user.showOrderHistory();
}
