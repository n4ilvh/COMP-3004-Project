#include "featurepage.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

FeaturePage::FeaturePage(const QString &title, QWidget *parent) : QWidget(parent)
{
    auto *titleLabel = new QLabel(title, this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    auto *backButton = new QPushButton("Back", this);
    backButton->setToolTip("Return to the home screen");
    connect(backButton, &QPushButton::clicked, this, &FeaturePage::backRequested);

    auto *header = new QHBoxLayout;
    header->addWidget(titleLabel);
    header->addStretch();
    header->addWidget(backButton, 0, Qt::AlignTop);

    m_content = new QVBoxLayout;

    auto *main = new QVBoxLayout(this);
    main->addLayout(header);
    main->addLayout(m_content, 1);
}

void FeaturePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    refresh();
}
