import QtQuick 2.4
//import Qt5Compat.GraphicalEffects
import QtGraphicalEffects 1.15

Item {
    id: root
    Rectangle {
        id: mask

        width: root.width * internal.imageSizeScaleCoefficient
        height: root.width * internal.imageSizeScaleCoefficient
        anchors.centerIn: parent
        radius: height

        visible: false
    }

    Image {
        id: valueImage

        anchors.fill: mask

        source: "pics/cat.jpg"
        fillMode: Image.PreserveAspectCrop
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: mask
        }
    }

    QtObject {
        id: internal

        property real imageSizeScaleCoefficient: 0.7
    }
}
