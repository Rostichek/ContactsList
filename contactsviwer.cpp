#include "contactsviwer.h"
#include <QVariant>
#include <QColor>
#include <QDebug>
#include <iostream>

ContactsViwer::ContactsViwer(QObject *parent) :
    QAbstractListModel{parent}
{}

int ContactsViwer::rowCount(const QModelIndex &parent) const
{
    return onlyFavorite ?  favorites.size() : contacts.size();
}

QVariant ContactsViwer::data(const QModelIndex &index, int role) const
{
    const auto row {static_cast<size_t>(index.row())};
    if(Qt::DecorationRole == role) {
        if(index == currentCall) {
            return QColor("lightgreen");
        }
        return QColor("white");
    }
    if(Qt::DisplayRole == role) {
        return QString::fromStdString(onlyFavorite ? contacts[favorites[row]].name : contacts[row].name);
    }
}

QHash<int,QByteArray> ContactsViwer::roleNames() const {
    return { { CallRole, "call" },
        { Qt::DisplayRole, "display" },
        { Qt::DecorationRole, "background" },
        { FavoriteRole, "favorite" },
        { FavoriteViewRole, "isOnlyFavoriteMode" }};
}

bool ContactsViwer::setData(const QModelIndex &index, const QVariant &value, int role) {
    const auto row {static_cast<size_t>(index.row())};
    if(Roles::CallRole == role) {
        const auto prev = currentCall;
        if(index == prev) {
            currentCall = createIndex(contacts.size(), 0);
        }
        else {
            currentCall = index;
        }
        emit dataChanged(prev, prev, {Qt::DecorationRole});
        emit dataChanged(currentCall, currentCall, {Qt::DecorationRole});
        return true;
    }
    if(Roles::FavoriteRole == role) {
        favorites.push_back(row);
        contacts[row].is_favorite = true;
        return true;
    }
    if(Roles::FavoriteViewRole == role) {
        onlyFavorite = !onlyFavorite;
        emit dataChanged(createIndex(0,0), createIndex(rowCount(), 0), {Qt::DecorationRole});
        return true;
    }
}

void ContactsViwer::foo(){
    qDebug() << "asdasd";
}



