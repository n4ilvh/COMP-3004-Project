#ifndef VIEWMENU_H
#define VIEWMENU_H

#include "featurepage.h"
#include "systemdata.h"

class SystemData;
namespace Ui {
    class viewMenu;
}

class viewMenu : public FeaturePage{
    Q_OBJECT
public:
    explicit viewMenu(SystemData &data, QWidget *parent = nullptr);
    ~viewMenu();

public slots:
    void refresh() override;

private:
    Ui::viewMenu *ui;
    QWidget *m_form;
    SystemData &m_data;
};

#endif // VIEWMENU_H
