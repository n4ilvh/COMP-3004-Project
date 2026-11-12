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
    enum class Mode {Browse, Order};
    explicit viewMenu(SystemData &data, Mode mode, QWidget *parent = nullptr);
    ~viewMenu();

public slots:
    void refresh() override;

private:
    Mode m_mode;
    Ui::viewMenu *ui;
    QWidget *m_form;
    SystemData &m_data;
    QList<const MenuItem *> m_sandwhichItems;
    QList<const MenuItem *> m_hotBeverages;
    QList<const MenuItem *> m_coldBeverages;
};

#endif // VIEWMENU_H
