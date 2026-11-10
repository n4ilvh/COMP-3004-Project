#ifndef VIEWMENU_H
#define VIEWMENU_H

#include <QWidget>

class SystemData;
namespace Ui {
    class viewMenu;
}

class viewMenu : public QWidget{
    Q_OBJECT
public:
    explicit viewMenu(SystemData &data, QWidget *parent = nullptr);
    ~viewMenu();
private:
    Ui::viewMenu *ui;
    SystemData &m_data;
};

#endif // VIEWMENU_H
