#pragma once
#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QQmlEngine>
#include <QJSEngine>
#include <vector>
#include <string>
#include <string_view>
#include "contactlistprovider.h"

class ContactsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        CallInProgressRole = Qt::UserRole + 1,
        ContactIsFavoriteRole,
        ShowOnScreenRole,
    };

    struct ContactProperties {
        size_t id;
        std::shared_ptr<std::string> name;
        bool is_favorite = false;
    };


    ContactsModel(const ContactListProvider& provider, QObject *parent = nullptr);

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE void switchOnlyFavoritesMode();

private:
    const ContactListProvider& provider;

    std::vector<ContactProperties> contacts;

    std::vector<size_t> favorites;

    bool onlyFavorite = false;

    QModelIndex currentCall;

    const static QHash<int,QByteArray> rolesDictionary;
};

static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    ContactsModel *contactsModel = new ContactsModel(ContactListProvider{});
    return contactsModel;
}
