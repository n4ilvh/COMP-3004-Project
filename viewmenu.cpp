#include "viewmenu.h"
#include "ui_ViewMenu.h"
#include "systemdata.h"
#include "menu.h"
#include "menuitem.h"
#include "placeordercontrol.h"
#include <QListWidget>

viewMenu::viewMenu(SystemData &data, Mode mode, PlaceOrderControl *ordering, QWidget *parent) : FeaturePage("Cafe Menu", parent), m_mode(mode), ui(new Ui::viewMenu), m_form(new QWidget), m_data(data), m_ordering(ordering){
    ui->setupUi(m_form);
    contentLayout()->addWidget(m_form);
    ui->addToCart->setVisible(m_mode == Mode::Order);
    ui->checkoutRequest->setVisible(m_mode == Mode::Order);

    connect(ui->checkoutRequest, &QPushButton::clicked, this, &viewMenu::checkoutRequested);

    connect(ui->sandwiches, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->hotBeverages, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->coldBeverages, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(2);});

    if (m_ordering)
        connect(ui->addToCart, &QPushButton::clicked, this, &viewMenu::onAddToCart);

}

void viewMenu::refresh(){
    m_sandwhichItems.clear();
    ui->listWidget->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::SANDWICH)){
        m_sandwhichItems.append(m);
        ui->listWidget->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));
    }

    m_hotBeverages.clear();
    ui->listWidget_2->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::HOT_BEVERAGE)){
        m_hotBeverages.append(m);
        ui->listWidget_2->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));
    }

    m_coldBeverages.clear();
    ui->listWidget_3->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::COLD_BEVERAGE)){
        m_coldBeverages.append(m);
        ui->listWidget_3->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));
    }

}

void viewMenu::onAddToCart(){
    if (!m_ordering) return;

    const QList<const MenuItem *> *items = &m_sandwhichItems;
    QListWidget *list = ui->listWidget;

    switch (ui->stackedWidget->currentIndex()) {
    case 0: items = &m_sandwhichItems; list = ui->listWidget; break;
    case 1: items = &m_hotBeverages; list = ui->listWidget_2; break;
    case 2: items = &m_coldBeverages; list = ui->listWidget_3; break;
    default: return;
    }

    const int row = list->currentRow();
    if (row < 0 || row >= items->size()) return;

    m_ordering->addItem(*items->at(row));
    ui->addToCart->setText(QString("Add to Cart (%1)").arg(m_ordering->cart().size()));
}

viewMenu::~viewMenu(){
    delete ui;
}
