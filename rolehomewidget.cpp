#include "rolehomewidget.h"
#include "user.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

RoleHomeWidget::RoleHomeWidget(User *user, QWidget *parent)
    : QWidget(parent), m_user(user)
{
    auto *typeLabel = new QLabel(user->userType() + " Interface", this);
    typeLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    auto *nameLabel = new QLabel("Logged in as: " + user->name(), this);

    auto *titleCol = new QVBoxLayout;
    titleCol->addWidget(typeLabel);
    titleCol->addWidget(nameLabel);

    auto *exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &RoleHomeWidget::exitRequested);

    auto *header = new QHBoxLayout;
    header->addLayout(titleCol);
    header->addStretch();
    header->addWidget(exitButton, 0, Qt::AlignTop);

    m_featureLayout = new QVBoxLayout;

    auto *main = new QVBoxLayout(this);
    main->addLayout(header);
    main->addLayout(m_featureLayout);
    main->addStretch();
}
