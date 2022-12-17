// groceries_template.cpp: Stores Orders in a list.
#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "split.h"
using namespace std;

//////////////////
// Customer code /
//////////////////
struct Customer {
    //attributes
    int cust_id;
    string name;
    string street;
    string city;
    string state;
    string zip;
    string phone;
    string email;

    //customer data in a single text line
    // this is the constructor
    Customer(int id, const string& name, const string& street, const string& city,
             const string& state, const string& zip, const string& phone, const string& email)
            : name(name), street(street), city(city), state(state), zip(zip), phone(phone), email(email)
    {
        cust_id = id;
    }
    //create a string, return a string, not cout
    string print_detail() const {
        // TODO
        ostringstream os;
        os << "Customer ID #"<< cust_id << ": " << endl
        << name << ", "
        << "ph. " << phone << ", "
        << "email: " << email << endl
        << street << endl
        << city << ", " << state << " " << zip << endl;
        return os.str();
    }
};
vector<Customer> customers; // structure variable, you initialize the struct from here

//read in the customer file, parse it and puts it into the customer vector,
void read_customers(const string& fname) {
    ifstream read_customer_file(fname); //opens file
    string line;
    while(getline(read_customer_file, line)){ // while reading the file...
        // assign the content of file into a variable, with comma
        //as delimiter
        auto info = split(line, ',');

        //assign info and store into a customer object
        Customer store_info(stoi(info[0]), info[1], info[2], info[3],
                     info[4], info[5], info[6], info[7]);
        //store object into vector
        customers.push_back(store_info);
        }
}
//find the customer
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

//read in the file?
void read_items(const string& fname) {
    ifstream read_item_file (fname);
    string line;
    while(getline(read_item_file, line)) {
        auto info = split(line, ',');
        Item store_info (stoi(info[0]), info[1], stod(info[2]));
        items.push_back(store_info);
    }
}

//find the item
int find_item_idx(int item_id) {
    for (int i = 0; i < items.size(); ++i)
        if (item_id == items[i].item_id)
            return i;
    throw runtime_error("Item not found");
}

//
class LineItem {
    int item_id;
    int qty;
    friend class Order;
public:
    LineItem(int id, int q) {
        item_id = id;
        qty = q;
    }
    string print_out_item (){
        ostringstream os;
        Item myItem = items.at(find_item_idx(item_id));
        os << "Item " << item_id << ":" << "\"" << myItem.description << "\", " << qty << "@ " << myItem.price << endl;
        return os.str();
    }

    double sub_total() const {
        int idx = find_item_idx(item_id);
        return items[idx].price * qty;
    }
    friend bool operator<(const LineItem& item1, const LineItem& item2) {
        return item1.item_id < item2.item_id;
    }
};

///////////////
// Payment code /
///////////////
class Payment {
    double amount = 0.0;
    friend class Order;
public:
    Payment() = default;
    virtual ~Payment() = default; // destructor
    virtual string print_detail() const = 0;
};

class Credit : public Payment {
    string card_number;
    string expiration;
public:

    Credit(string card_num, string expire){
        card_number = card_num;
        expiration = expire;
    }

    string print_detail () const override {

        ostringstream os;
        os << "Paid by Credit Card " << card_number << ", " << "exp. "<< expiration << endl;
        return os.str();
    }
};

class Paypal : public Payment {
    string paypal_id;
public:
    Paypal(string id) {
        paypal_id = id;
    }
    string print_detail() const override {
        ostringstream os;
        os << "Paid by PayPal " << paypal_id << endl;
        return os.str();
    }
};

class WireTransfer : public Payment {
    string bank_id;
    string account_id;
public:
    WireTransfer(string bank, string account){
        bank_id = bank;
        account_id = account;
    }
    string print_detail() const override {
        ostringstream os;
        os << "Paid by wire transfer " << bank_id << ", " << account_id << endl;
        return os.str();
    }
};

/////////////
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
        double order_total;

        //orders pull up items list
        for (int i = 0; i < line_items.size(); i++){
        //orders looks through item list that matches what customer bought
            order_total += line_items[i].sub_total();
        }
        payment->amount = order_total;
    }
    ~Order() {
        delete payment;
    }
    double total() const {
        return payment->amount;
    }
    string print_order() const {
        ostringstream os;

        os << "=========================================" << endl;
        os << "Order #" << order_id << ", " << "Date: " << order_date << endl;

        //include payment and payment info
        os << "Amount: $" << payment->amount << ", " << payment->print_detail() << endl;

        int customer_index = find_cust_idx(cust_id); //find the customer number
        os << customers.at(customer_index).print_detail() << endl; // this gives me the customer I want, then output
        //print order detail
        os << "Order Detail: " << endl;

        //print item_id, then description, then quantity, then price. Look at the end of the calls.
        for (int i = 0; i < line_items.size(); i++) {
            //grab the information from items vector, use the find_item_idx function to find the item id
            auto grab_info = items.at(find_item_idx(line_items.at(i).item_id));

            // grab the attributes
            int item_id = grab_info.item_id;
            string item_description = grab_info.description;

            //grab the quantity from line_items vector
            int quantity = line_items.at(i).qty;
            double price = grab_info.price;

            os << "\t" << "Item " << item_id <<": \""<< item_description << "\", " << quantity << " @ " <<
            price << endl;
        }
        return os.str();
    }
};
list<Order> orders;

void read_orders(const string& fname) {
    ifstream orderf(fname);
    string line;
    int order_id;
    string date;
    int cust_id;
    while (getline(orderf, line)) {
        // split line
        auto info = split(line, ',');
        // Extract cust_id, order_id, and date
        cust_id = stoi(info[0]);
        order_id = stoi(info[1]);
        date = info[2];

        // Create line item vector
        vector<LineItem> line_items;
        vector<string> string_holder;

        // grab items after the date
        for (int i = 3; i < info.size(); i++ ){
           string_holder = split(info.at(i), '-');
           LineItem blah (stoi(string_holder.at(0)), stoi(string_holder.at(1)));
           line_items.push_back(blah);
        }
        sort(begin(line_items), end(line_items));

        getline(orderf, line); // move to next line

        info = split(line, ',');
        // Read payment method (by reading/splitting next line in file)
        Payment* pmt;
        if (info[0] == "1") {
            //credit card
            pmt = new Credit(info[1], info[2]);
        }
        else if (info[0] == "2") {
            // Paypal
            pmt = new Paypal(info[1]);
        }

        else if (info[0] == "3") {
            // wire transfer
            pmt = new WireTransfer(info[1], info[2]);
            }

        orders.emplace_back(order_id, date, cust_id, line_items, pmt);
        }

    }

int main() {
    read_customers("customers.txt");
    read_items("items.txt");
    read_orders("orders.txt");

    //ofstream represents the output file stream and is used to create files and to write information to files.
    ofstream ofs("order_report.txt");
    for (const Order& order: orders) // running a for range loop, "for order in orders" (in python-ese)
        ofs << order.print_order() << endl;
}
