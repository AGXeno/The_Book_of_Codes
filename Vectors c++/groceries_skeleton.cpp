// groceries_template.cpp: Stores Orders in a list.

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>
#include "split.h"
using namespace std;

//////////////////
// Customer code /
//////////////////
struct Customer {
    int cust_id;
    string name;
    string street;
    string city;
    string state;
    string zip;
    string phone;
    string email;
    Customer(int id, const string& name, const string& street, const string& city,
             const string& state, const string& zip, const string& phone, const string& email)
        : name(name), street(street), city(city), state(state), zip(zip), phone(phone), email(email) 
    {
        cust_id = id;
    }
    string print_detail() const {
        // TODO
    }
};
vector<Customer> customers;

void read_customers(const string& fname) {
    ifstream read_customer_file("customers.txt"); //opens file
    string line;
    while(getline(read_customer_file, line)){
        auto info = split(line, ',');
        Customer cst(stoi(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7]));
        customers.push_back(cst);
    }
}

int find_cust_idx(int cust_id) {
    for (int i = 0; i < customers.size(); ++i)
        if (cust_id == customers[i].cust_id)
            return i;
    throw runtime_error("Customer not found");
}

//////////////
// Item code /
//////////////
struct Item {
    int item_id;
    string description;
    double price;
    Item(int id, const string& desc, double pric) : description(desc) {
        item_id = id;
        price = pric;
    }
};
vector<Item> items;

void read_items(const string& fname) {
    // TODO
}

int find_item_idx(int item_id) {
    for (int i = 0; i < items.size(); ++i)
        if (item_id == items[i].item_id)
            return i;
    throw runtime_error("Item not found");
}

class LineItem {
    int item_id;
    int qty;
    friend class Order;
public:
    LineItem(int id, int q) {
        item_id = id;
        qty = q;
    }
    double sub_total() const {
        int idx = find_item_idx(item_id);
        return items[idx].price * qty;
    }
    friend bool operator<(const LineItem& item1, const LineItem& item2) {
        return item1.item_id < item2.item_id;
    }
};

/////////////////
// Payment code /
/////////////////
class Payment {
    double amount = 0.0;
    friend class Order;
public:
    Payment() = default;
    virtual ~Payment() = default;
    virtual string print_detail() const = 0;
};

class Credit : public Payment {
    // TODO
};

class Paypal : public Payment {
    // TODO
};

class WireTransfer : public Payment {
    // TODO
};

///////////////
// Order code /
///////////////
class Order {
    int order_id;
    string order_date;
    int cust_id;
    vector<LineItem> line_items;
    Payment* payment;
public:
    Order(int id, const string& date, int c_id, const vector<LineItem>& items, Payment* p) 
    : order_date(date), line_items(items) {
        order_id = id;
        cust_id = c_id;
        payment = p;
        sort(line_items.begin(), line_items.end());
        // Compute order_total: TODO
    }
    ~Order() {
        delete payment;
    }
    double total() const {
        return payment->amount;
    }
    string print_order() const {
        // TODO
    }
};
list<Order> orders;

void read_orders(const string& fname) {
    ifstream orderf(fname);
    string line;
    while (getline(orderf, line)) {
        // split line

        // Extract cust_id, order_id, and date

        // Create line item vector
        vector<LineItem> line_items;
        // TODO

        sort(begin(line_items), end(line_items));

        // Read payment method (by reading/splitting next line in file)
        // TODO
        // 
        // Create concrete Payment object on heap (pmt)
        Payment* pmt;
        // TODO
        
        orders.emplace_back(order_id, date, cust_id, line_items, pmt);
    }
}

int main() {
    read_customers("customers.txt");
    read_items("items.txt");
    read_orders("orders.txt");

    ofstream ofs("order_report.txt");
    for (const Order& order: orders)
        ofs << order.print_order() << endl;
}
