#include "viewmenu.h"
#include "ui_ViewMenu.h"
#include "systemdata.h"
#include "menu.h"
#include "menuitem.h"

viewMenu::viewMenu(SystemData &data, QWidget *parent) : FeaturePage("Cafe Menu", parent), ui(new Ui::viewMenu), m_data(data){
    m_form = new QWidget;
    ui->setupUi(m_form);
    contentLayout()->addWidget(m_form);

    connect(ui->sandwhiches, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->hotBeverages, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->coldBeverages, &QPushButton::clicked, this, [this] {ui->stackedWidget->setCurrentIndex(2);});

}

void viewMenu::refresh(){
    ui->listWidget->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::SANDWICH))
        ui->listWidget->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));


    ui->listWidget_2->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::HOT_BEVERAGE))
        ui->listWidget_2->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));

    ui->listWidget_3->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::COLD_BEVERAGE))
        ui->listWidget_3->addItem(QString("%1    $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));

}

viewMenu::~viewMenu(){
    delete ui;
}
