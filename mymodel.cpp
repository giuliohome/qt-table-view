#include "mymodel.h"
#include <QDebug>
#include <QFont>
#include <QBrush>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int myRows = 2;
QColor myColor = Qt::red;

void MyModel::setCount(int i)
{
  myRows = i;
  QModelIndex topLeft = index(i-1, 0);
  QModelIndex bottomRight = index(i-1,2);
  emit dataChanged(topLeft, bottomRight);
  emit layoutChanged();
}

void MyModel::setColor(QColor color) {
    myColor = color;
    emit layoutChanged();
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return myRows;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    /*
     * qDebug() << QString("row %1, col%2, role %3")
     *      .arg(row).arg(col).arg(role);
     */

    switch (role) {
    case Qt::DisplayRole:
        if (row % 2 == 0 && col == 1) return QString("<--left");
        if (row % 2 == 1 && col == 1) return QString("right-->");

        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col +1);
    case Qt::FontRole:
        if (row % 2 == 0 && col == 0) { //change font only for cell(0,0)
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:
        if (row % 2 == 1 && col == 2)  //change background only for cell(1,2)
            return QBrush(myColor);
        break;
    case Qt::TextAlignmentRole:
        if (row % 2 == 1 && col == 1) //change text alignment only for cell(1,1)
            return int(Qt::AlignRight | Qt::AlignVCenter);
        break;
    case Qt::CheckStateRole:
        if (row % 2 == 1 && col == 0) //add a checkbox to cell(1,0)
            return Qt::Checked;
        break;
    }
    return QVariant();
}
