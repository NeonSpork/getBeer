import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: beerButton
    width: 200
    height: 200

    Image {
        id: beerButtonIcon
        x: 0
        y: 0
        width: 200
        height: 200
        source: "media/icon/beer_button_off.png"
    }

    MouseArea {
        id: getBeer
        x: 0
        y: 0
        width: 200
        height: 200
    }

    Connections {
        target: beerButton
        onClicked: print("clicked")
    }
}
