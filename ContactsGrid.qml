import QtQuick 2.0
import QtQuick.Controls 2.15
import Contacts 1.0


GridView {
    id: root

    property bool isOnlyFavorites: false

    cellWidth: width / 3
    cellHeight: height / 3

    model: ContactsModel

    onIsOnlyFavoritesChanged: {
        foo()
    }

    delegate: Item {
        id: delegateItem

        width: cellWidth
        height: cellHeight

        Contact {
            representation: 1

            anchors.centerIn: parent

            width: (root.width / 3 ) * internal.contactSizeScaleCoefficient
            height: (root.height / 3) * internal.contactSizeScaleCoefficient

            name: display.toString()
            color: background.toString()

            onCalled: {
                call = true;
            }
        }
    }

    QtObject {
        id: internal

        property real contactSizeScaleCoefficient: 0.98
    }
}
