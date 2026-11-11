#ifndef FEATUREPAGE_H
#define FEATUREPAGE_H

#include <QWidget>

class QVBoxLayout;

// Boundary class: base for feature screens. Each screen gets the same title and
// Back button, and refresh() is called every time the screen is shown.
class FeaturePage : public QWidget {
    Q_OBJECT
public:
    explicit FeaturePage(const QString &title, QWidget *parent = nullptr);

public slots:
    virtual void refresh() = 0;

signals:
    void backRequested();

protected:
    QVBoxLayout *contentLayout() const { return m_content; }
    void showEvent(QShowEvent *event) override;

private:
    QVBoxLayout *m_content;
};

#endif // FEATUREPAGE_H
