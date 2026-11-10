#include "viewmenu.h"
#include "ui_ViewMenu.h"
#include "systemdata.h"
#include "menu.h"
#include "menuitem.h"

viewMenu::viewMenu(SystemData &data, QWidget *parent) : QWidget(parent), ui(new Ui::viewMenu), m_data(data)
{
    ui->setupUi(this);
    ui->listWidget->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::SANDWICH))
        ui->listWidget->addItem(QString("%1   $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));

    ui->listWidget_2->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::HOT_BEVERAGE))
        ui->listWidget_2->addItem(QString("%1   $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));

    ui->listWidget_3->clear();
    for (const MenuItem *m : m_data.menu().itemsInCategory(Menu::COLD_BEVERAGE))
        ui->listWidget_3->addItem(QString("%1   $%2").arg(m->name()).arg(m->price(), 0, 'f', 2));
}

viewMenu::~viewMenu()
{
    delete ui;
}
