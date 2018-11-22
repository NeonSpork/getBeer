import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    width: 1024
    height: 600
    property alias page: page

    BorderImage {
        id: borderImage
        x: 0
        y: 0
        width: 1024
        height: 600
        source: "media/bg/angry_babushka_bg.png"

        Flickable {
            id: flickable
            x: 0
            y: 0
            width: 1024
            height: 600

            Item {
                id: item1
                x: 824
                y: 400
                width: 200
                height: 200

                Image {
                    id: image
                    x: 0
                    y: 0
                    width: 200
                    height: 200
                    source: "media/icon/beer_button_red_off.png"
                }

                MouseArea {
                    id: getBeer
                    x: 0
                    y: 0
                    width: 200
                    height: 200
                }
            }
        }
    }

    Connections {
        target: getBeer
        onPressAndHold: normalValve.on()
        onReleased: normalValve.off()
    }

    Connections {
        target: flickable
        onFlickEnded: {
            Page4Form.visible = false
            Page1Form.visible = true
        }
    }

    states: [
        State {
            name: "DispesningBeer"

            PropertyChanges {
                target: image
                source: "media/icon/beer_button_red_on.png"
            }
        }
    ]
}
