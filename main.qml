import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root

    width: 600
    height: 200
    visible: true
    title: qsTr("Contact List Viwer")

    color: "lightgray"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Only favorites")
                onClicked: {
                    loader.item.isOnlyFavorites = !loader.item.isOnlyFavorites
                }
            }
        }
    }

    Loader {
        id: loader

        anchors.fill: parent

        source: (parent.width<500) ? "ContactsList.qml" : "ContactsGrid.qml"
    }

}
