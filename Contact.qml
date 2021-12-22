import QtQuick 2.0

Rectangle {
    id: root

    property string name
    property int representation: 0 // 0 - list, 1 - grid

    signal called

    radius: 10

    border {
        width: 2
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            called()
        }
    }

    Item {
        width: 50
        height: 50

        Text {
            anchors.centerIn: parent

            text: "+"
            font.pointSize: 20
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                favorite = true;
            }
        }
    }

    ContactIcon {
        id: icon
        height: width
    }

    Text {
        id: valueText
        font.pointSize: internal.textSize

        text: root.name
    }

    states: [
        State {
            name: "listViewStatement"
            when: 0 === representation

            PropertyChanges {
                target: icon
                width: root.height
            }
            PropertyChanges {
                target: valueText
                anchors.centerIn: root
            }
        },
        State {
            name: "gridViewStatement"
            when: 1 === representation

            PropertyChanges {
                target: icon
                width: root.height / 1.5
            }
            PropertyChanges {
                target: valueText
                height: root.height - root.height / 1.5
            }
            AnchorChanges {
                target: valueText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
            }
            AnchorChanges {
                target: icon
                anchors.bottom: valueText.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    ]

    QtObject {
        id: internal

        property int textSize: root.height * (representation ? 0.1 : 0.25)
    }
}
