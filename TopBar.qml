import QtQuick 2.0

Rectangle {
    signal favorites

    color: "lightgray"

    Rectangle{
        radius: 10

        anchors.fill: parent
        anchors.topMargin: 2
        anchors.bottomMargin: 2

        color: "gray"

        Rectangle{
            width: parent.width / 2
            height: parent.height
            radius: 10

            anchors.right: parent.right

            color: "lightblue"

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    favorites()
                }
            }
        }
    }


}
