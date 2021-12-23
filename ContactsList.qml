import QtQuick 2.0
import QtQuick.Controls 2.15
import Contacts 1.0

ListView {
    id: root

    property int entryHeight: 60
    property bool isOnlyFavorites: false

    model: ContactsModel

    onIsOnlyFavoritesChanged: {
        ContactsModel.switchOnlyFavoritesMode()
    }

    delegate: Contact {
        id: contact

        visible: showOnScreen

        width: root.width
        height: visible ? root.entryHeight : 0

        name: display.toString()
        color: background.toString();

        onCalled: {
            callInProgress = true;
        }
    }
}
