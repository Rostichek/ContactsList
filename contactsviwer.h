#pragma once
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QJSEngine>
#include <vector>
#include <string>

class ContactsViwer : public QAbstractListModel
{
    Q_ENUMS(Roles)
public:
    enum Roles {
            CallRole = Qt::UserRole + 1,
            FavoriteRole,
            FavoriteViewRole,
        };

    ContactsViwer(QObject *parent = nullptr);

    struct Contact {
        std::string name;
        bool is_favorite = false;
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE void foo();

private:
    std::vector<Contact> contacts = {
        {"Kevin Green"},
        {"John Bob"},
        {"John Bob"},
        {"John Bob"},
        {"John Bob"},
        {"John Bob"},
        {"John Bob"},
        {"John Bob"},
        {"Kevin Green"},
        {"Kevin Green"},
        {"Kevin Green"},
        {"Kevin Green"},
        {"John Bob"},
        {"John Bob"},};

    std::vector<size_t> favorites;

    bool onlyFavorite = false;

    QModelIndex currentCall;
};

static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    ContactsViwer *contactsViwer = new ContactsViwer();
    return contactsViwer;
}
