#include "defaultdata.h"
#include "systemdata.h"
#include "customer.h"
#include "staff.h"

#include <vector>

namespace {

// ---------- Menu ----------
void loadMenu(Menu &menu)
{
    auto add = [&menu](const QString &name, const QString &cat, double price,
                       std::initializer_list<IngredientRequirement> ings) {
        MenuItem item(name, cat, price);
        for (const IngredientRequirement &i : ings)
            item.addIngredient(i.ingredient, i.quantity, i.unit);
        menu.addItem(item);
    };

    // Sandwiches
    add("Dragon Club", Menu::SANDWICH, 9.50,
        {{"Bread", 3, "slices"}, {"Turkey", 80, "g"}, {"Bacon", 2, "strips"},
         {"Lettuce", 20, "g"}, {"Tomato", 2, "slices"}});
    add("Hobbit Melt", Menu::SANDWICH, 8.75,
        {{"Bread", 2, "slices"}, {"Cheddar Cheese", 60, "g"}, {"Ham", 50, "g"}, {"Butter", 10, "g"}});
    add("Sorcerer's Veggie Wrap", Menu::SANDWICH, 8.25,
        {{"Tortilla", 1, "piece"}, {"Hummus", 40, "g"}, {"Lettuce", 20, "g"},
         {"Cucumber", 30, "g"}, {"Tomato", 2, "slices"}});

    // Hot beverages
    add("Dragon Fire Espresso", Menu::HOT_BEVERAGE, 3.25,
        {{"Coffee Beans", 18, "g"}, {"Water", 60, "ml"}});
    add("Mount Doom Mocha", Menu::HOT_BEVERAGE, 4.75,
        {{"Coffee Beans", 18, "g"}, {"Milk", 200, "ml"}, {"Chocolate Syrup", 30, "ml"}});
    add("Harold's Hot Chocolate", Menu::HOT_BEVERAGE, 4.25,
        {{"Milk", 250, "ml"}, {"Chocolate Syrup", 40, "ml"}});
    add("Timmy's Chai Latte", Menu::HOT_BEVERAGE, 4.50,
        {{"Chai Concentrate", 80, "ml"}, {"Milk", 200, "ml"}});

    // Cold beverages
    add("Iced Dorc Tea", Menu::COLD_BEVERAGE, 3.75,
        {{"Tea Bags", 2, "bags"}, {"Ice", 150, "g"}, {"Water", 250, "ml"}});
    add("Frosty Dragon Cold Brew", Menu::COLD_BEVERAGE, 4.50,
        {{"Cold Brew Concentrate", 120, "ml"}, {"Ice", 150, "g"}, {"Water", 100, "ml"}});
    add("Lemon Elixir", Menu::COLD_BEVERAGE, 3.95,
        {{"Lemon Juice", 60, "ml"}, {"Sugar", 15, "g"}, {"Ice", 150, "g"}, {"Water", 250, "ml"}});
}

// ---------- Customers + order history ----------
struct Line { const char *name; int qty; };
struct OrderSpec {
    std::vector<Line> lines;
    int points;
    double credit;
    OrderStatus status;
    OrderType type;
};
struct CustomerSpec {
    const char *name, *username, *loyaltyNumber, *email, *address;
    int openingPoints;
    double openingCredit;
    std::vector<OrderSpec> orders;   // oldest first
};

const OrderStatus PU = OrderStatus::PickedUp;
const OrderStatus CX = OrderStatus::Cancelled;
const OrderType ON = OrderType::Online;
const OrderType IP = OrderType::InPerson;

std::vector<CustomerSpec> customerSpecs()
{
    return {
        {"Alice Archer", "aarcher", "LP-100001", "alice.archer@hintonville.ca",
         "12 Elm Lane, Hintonville", 10, 5.00, {
            {{{"Dragon Club",1},{"Dragon Fire Espresso",1}}, 0, 0.0, PU, IP},
            {{{"Hobbit Melt",2},{"Iced Dorc Tea",1}},        5, 0.0, PU, ON},
            {{{"Mount Doom Mocha",2}},                       0, 3.0, PU, ON},
            {{{"Sorcerer's Veggie Wrap",1},{"Lemon Elixir",1}}, 4, 2.0, CX, ON},  // cancelled: points + credit
            {{{"Timmy's Chai Latte",1}},                     0, 0.0, PU, ON}}},

        {"Bruno Brightblade", "bbrightblade", "LP-100002", "bruno.b@hintonville.ca",
         "48 Orchard Road, Hintonville", 15, 8.00, {
            {{{"Mount Doom Mocha",2}},                       0, 0.0, PU, IP},
            {{{"Dragon Club",2}},                            8, 0.0, PU, ON},
            {{{"Frosty Dragon Cold Brew",1},{"Lemon Elixir",1}}, 0, 4.0, PU, ON},
            {{{"Hobbit Melt",1}},                            0, 0.0, CX, ON},
            {{{"Timmy's Chai Latte",2},{"Sorcerer's Veggie Wrap",1}}, 0, 0.0, PU, IP}}},

        {"Cora Wells", "cwells", "LP-100003", "cora.wells@hintonville.ca",
         "7 Mill Street, Hintonville", 12, 6.00, {
            {{{"Sorcerer's Veggie Wrap",1},{"Dragon Fire Espresso",1}}, 0, 0.0, PU, ON},
            {{{"Iced Dorc Tea",3}},                          5, 0.0, CX, ON},     // cancelled: points
            {{{"Dragon Club",1},{"Harold's Hot Chocolate",1}}, 0, 2.5, PU, ON},
            {{{"Mount Doom Mocha",1},{"Lemon Elixir",1}},    3, 0.0, PU, ON},
            {{{"Hobbit Melt",2}},                            0, 0.0, PU, IP}}},

        {"Dmitri Stone", "dstone", "LP-100004", "d.stone@hintonville.ca",
         "301 Quarry Way, Hintonville", 8, 10.00, {
            {{{"Hobbit Melt",1},{"Frosty Dragon Cold Brew",1}}, 0, 0.0, PU, IP},
            {{{"Timmy's Chai Latte",1},{"Dragon Fire Espresso",1}}, 0, 3.0, PU, ON},
            {{{"Dragon Club",1},{"Sorcerer's Veggie Wrap",1}}, 6, 4.0, CX, ON},  // cancelled: points + credit
            {{{"Lemon Elixir",2}},                           0, 0.0, PU, ON},
            {{{"Harold's Hot Chocolate",1},{"Iced Dorc Tea",1}}, 2, 0.0, PU, ON}}},

        {"Elena Frost", "efrost", "LP-100005", "elena.frost@hintonville.ca",
         "90 Glacier Court, Hintonville", 5, 12.00, {
            {{{"Dragon Club",2},{"Mount Doom Mocha",1}},     0, 0.0, PU, ON},
            {{{"Sorcerer's Veggie Wrap",1}},                 0, 5.0, PU, ON},
            {{{"Dragon Fire Espresso",2}},                   0, 0.0, PU, IP},
            {{{"Frosty Dragon Cold Brew",2}},                0, 2.5, CX, ON},
            {{{"Hobbit Melt",1},{"Lemon Elixir",1}},         4, 0.0, PU, ON}}},
    };
}

void loadCustomers(SystemData &data)
{
    const QDateTime base(QDate(2026, 9, 1), QTime(9, 0));
    int customerIndex = 0;

    for (const CustomerSpec &cs : customerSpecs()) {
        auto customer = std::make_unique<Customer>(cs.name, cs.username, cs.loyaltyNumber,
                                                   cs.email, cs.address,
                                                   cs.openingPoints, cs.openingCredit);
        int orderIndex = 0;
        for (const OrderSpec &os : cs.orders) {
            QDateTime when = base.addDays(orderIndex * 4 + customerIndex).addSecs(orderIndex * 1800);
            Order order(data.nextOrderNumber(), cs.username, cs.name, os.type, when);
            for (const Line &l : os.lines) {
                const MenuItem *mi = data.menu().find(l.name);
                if (mi)
                    order.addLine(mi->name(), l.qty, mi->price());
            }
            order.applyPayment(os.points, os.credit);
            order.setStatus(os.status);
            if (os.status == OrderStatus::Cancelled)
                order.setLoyaltyPointsEarned(0);       // earned points are removed on cancel

            // Updates the balances so they are consistent with the order history.
            customer->recordHistoricalOrder(order);
            ++orderIndex;
        }
        data.addUser(std::move(customer));
        ++customerIndex;
    }
}

// ---------- Staff ----------
void loadStaff(SystemData &data)
{
    data.addUser(std::make_unique<Kitchen>("Timmy Tortoise", "ttortoise", "K-001"));
    data.addUser(std::make_unique<Kitchen>("Kira Kettle", "kkettle", "K-002"));
    data.addUser(std::make_unique<Cashier>("Harold Hare", "hhare", "C-001"));
    data.addUser(std::make_unique<Cashier>("Rosa Rapid", "rrapid", "C-002"));
    data.addUser(std::make_unique<Manager>("Magnus Moss", "mmoss", "M-001"));
    data.addUser(std::make_unique<Admin>("Sage Sysop", "ssysop", "A-001"));
}

} // namespace

void DefaultData::load(SystemData &data)
{
    loadMenu(data.menu());
    loadCustomers(data);
    loadStaff(data);
    // The kitchen order queue is intentionally left empty.
}
