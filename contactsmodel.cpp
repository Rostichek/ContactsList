#include "contactsmodel.h"
#include <QVariant>
#include <QColor>
#include <QDebug>
#include <iostream>

const QHash<int,QByteArray> ContactsModel::rolesDictionary = {
    { Qt::DisplayRole, "display" },
    { Qt::DecorationRole, "background" },
    { ContactIsFavoriteRole, "contactIsFavorite" },
    { ShowOnScreenRole, "showOnScreen" },
    { CallInProgressRole, "callInProgress" }
};

ContactsModel::ContactsModel(const ContactListProvider& provider, QObject *parent) :
    QAbstractListModel{parent},
    provider(provider)
{
    for(const auto& contact : provider.GetContactList()){
        contacts.push_back({contact.id, contact.name});
    }
}

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    return contacts.size();
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    const auto row {static_cast<size_t>(index.row())};
    switch(role) {
    case Qt::DecorationRole:
        if(index == currentCall) {
            return QColor("lightgreen");
        }
        return QColor("white");
    case Qt::DisplayRole:
        return QString::fromStdString(*contacts[row].name.get());
    case ShowOnScreenRole:
        return static_cast<bool>(onlyFavorite ? (contacts[row].is_favorite ? true : false) : true);
    case ContactIsFavoriteRole:
        return static_cast<bool>(contacts[row].is_favorite);
    }
}

QHash<int,QByteArray> ContactsModel::roleNames() const {
    return rolesDictionary;
}

bool ContactsModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    const auto row {static_cast<size_t>(index.row())};
    if(CallInProgressRole == role) {
        provider.call(contacts[row].id);

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
    if(ContactIsFavoriteRole == role) {
        favorites.push_back(row);
        contacts[row].is_favorite = value.value<bool>();
        emit dataChanged(index, index, {ContactIsFavoriteRole, ShowOnScreenRole});
        return true;
    }
}

void ContactsModel::switchOnlyFavoritesMode() {
    onlyFavorite = !onlyFavorite;
    emit dataChanged(createIndex(0, 0),  createIndex(contacts.size(), 0), {ShowOnScreenRole});
}




