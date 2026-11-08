#include "loginwidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    auto *title = new QLabel("Dragon's End Café", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 26px; font-weight: bold;");

    auto *subtitle = new QLabel("DragonEndPOS - Please identify yourself", this);
    subtitle->setAlignment(Qt::AlignCenter);

    m_input = new QLineEdit(this);
    m_input->setPlaceholderText("Enter your name or username");
    m_input->setMinimumWidth(280);
    m_input->setAccessibleName("Name or username");

    m_loginButton = new QPushButton("Log In", this);
    m_loginButton->setDefault(true);

    m_error = new QLabel(this);
    m_error->setAlignment(Qt::AlignCenter);
    m_error->setStyleSheet("color: #b00020; font-weight: bold;");

    auto *inner = new QVBoxLayout;
    inner->addWidget(title);
    inner->addWidget(subtitle);
    inner->addSpacing(12);
    inner->addWidget(m_input);
    inner->addWidget(m_loginButton);
    inner->addWidget(m_error);

    // centre the form in the window
    auto *outer = new QVBoxLayout(this);
    outer->addStretch();
    auto *row = new QHBoxLayout;
    row->addStretch();
    row->addLayout(inner);
    row->addStretch();
    outer->addLayout(row);
    outer->addStretch();

    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(m_input, &QLineEdit::returnPressed, this, &LoginWidget::onLoginClicked);
}

void LoginWidget::onLoginClicked()
{
    m_error->clear();
    emit loginRequested(m_input->text());
}

void LoginWidget::showError(const QString &message)
{
    m_error->setText(message);
    m_input->selectAll();
    m_input->setFocus();
}

void LoginWidget::reset()
{
    m_input->clear();
    m_error->clear();
    m_input->setFocus();
}
