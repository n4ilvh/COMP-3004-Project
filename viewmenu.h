#ifndef VIEWMENU_H
#define VIEWMENU_H

#include "featurepage.h"
#include "systemdata.h"

class SystemData;
class PlaceOrderControl;
namespace Ui {
    class viewMenu;
}

class viewMenu : public FeaturePage{
    Q_OBJECT
signals:
    void checkoutRequested();
public:
    enum class Mode {Browse, Order};
    explicit viewMenu(SystemData &data, Mode mode, PlaceOrderControl *ordering = nullptr, QWidget *parent = nullptr);
    ~viewMenu();

public slots:
    void refresh() override;

private slots:
    void onAddToCart();

private:
    Mode m_mode;
    Ui::viewMenu *ui;
    QWidget *m_form;
    SystemData &m_data;
    PlaceOrderControl *m_ordering = nullptr;
    QList<const MenuItem *> m_sandwhichItems;
    QList<const MenuItem *> m_hotBeverages;
    QList<const MenuItem *> m_coldBeverages;
};

#endif // VIEWMENU_H
