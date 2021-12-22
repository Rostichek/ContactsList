import QtQuick 2.0
import QtQuick.Controls 2.15
import Contacts 1.0

ListView {
    id: root

    property int entryHeight: 60

    spacing: 2

    model: ContactsModel

    delegate: Contact {
        id: contact

        width: root.width
        height: root.entryHeight

        name: display.toString()
        color: background.toString();

        onCalled: {
            call = true;
        }
    }
}
