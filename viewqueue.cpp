#include "viewqueue.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

namespace {

enum QueueColumn {
    ColPosition, ColNumber, ColCustomer, ColPlacedAt, ColType, ColItems, ColStatus,
    QueueColumnCount
};

QTableWidgetItem *makeItem(const QString &text)
{
    auto *item = new QTableWidgetItem(text);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    return item;
}

} // namespace

ViewQueue::ViewQueue(OrderQueue &queue, QWidget *parent)
    : FeaturePage("Order Queue", parent),
      m_control(queue)
{
    m_summaryLabel = new QLabel(this);
    m_summaryLabel->setWordWrap(true);

    m_table = new QTableWidget(0, QueueColumnCount, this);
    m_table->setHorizontalHeaderLabels({"Position", "Order #", "Customer Name",
                                        "Order Date and Time", "Type", "Items", "Status"});
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setAlternatingRowColors(true);
    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(ColCustomer, QHeaderView::Stretch);

    m_detailsButton = new QPushButton("View Details", this);
    m_completeButton = new QPushButton("Complete Order", this);

    auto *buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    buttonRow->addWidget(m_detailsButton);
    buttonRow->addWidget(m_completeButton);

    contentLayout()->addWidget(m_summaryLabel);
    contentLayout()->addWidget(m_table, 1);
    contentLayout()->addLayout(buttonRow);

    connect(m_table, &QTableWidget::itemSelectionChanged, this, &ViewQueue::updateButtons);

    auto requestDetails = [this]() {
        const int orderNumber = selectedOrderNumber();
        if (orderNumber >= 0)
            emit viewDetailsRequested(orderNumber);
    };
    connect(m_detailsButton, &QPushButton::clicked, this, requestDetails);
    connect(m_table, &QTableWidget::cellDoubleClicked, this, requestDetails);
    connect(m_completeButton, &QPushButton::clicked, this, [this]() {
        const int orderNumber = selectedOrderNumber();
        if (orderNumber < 0)
            return;
        emit completeOrderRequested(orderNumber);
        refresh();
    });

    updateButtons();
}

int ViewQueue::selectedOrderNumber() const
{
    const QModelIndexList rows = m_table->selectionModel()->selectedRows();
    if (rows.isEmpty())
        return -1;
    const QTableWidgetItem *item = m_table->item(rows.first().row(), ColNumber);
    return item ? item->data(Qt::UserRole).toInt() : -1;
}

void ViewQueue::refresh()
{
    const int previouslySelected = selectedOrderNumber();
    const QList<QueueEntry> entries = m_control.entries();

    m_table->setRowCount(0);
    m_table->setRowCount(entries.size());

    int rowToSelect = entries.isEmpty() ? -1 : 0;
    for (int row = 0; row < entries.size(); ++row) {
        const QueueEntry &entry = entries.at(row);

        auto *numberItem = makeItem(QString::number(entry.orderNumber));
        numberItem->setData(Qt::UserRole, entry.orderNumber);

        m_table->setItem(row, ColPosition, makeItem(QString::number(entry.position)));
        m_table->setItem(row, ColNumber, numberItem);
        m_table->setItem(row, ColCustomer, makeItem(entry.customerName));
        m_table->setItem(row, ColPlacedAt, makeItem(entry.placedAt));
        m_table->setItem(row, ColType, makeItem(entry.type));
        m_table->setItem(row, ColItems, makeItem(QString::number(entry.itemCount)));
        m_table->setItem(row, ColStatus, makeItem(entry.status));

        if (entry.orderNumber == previouslySelected)
            rowToSelect = row;           // keep the same order selected after a refresh
    }
    if (rowToSelect >= 0)
        m_table->selectRow(rowToSelect);

    if (entries.isEmpty())
        m_summaryLabel->setText("The order queue is empty. Paid orders will appear here.");
    else if (entries.size() == 1)
        m_summaryLabel->setText("1 order is waiting to be prepared.");
    else
        m_summaryLabel->setText(QString("%1 orders are waiting to be prepared, oldest first "
                                        "(first in, first out). Position 1 is next.")
                                    .arg(entries.size()));
    updateButtons();
}

void ViewQueue::updateButtons()
{
    const bool hasSelection = selectedOrderNumber() >= 0;
    m_detailsButton->setEnabled(hasSelection);
    m_completeButton->setEnabled(hasSelection);
}
