import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 1024
    height: 600

    BorderImage {
        id: borderImage
        x: 0
        y: 0
        width: 1024
        height: 600
        source: "media/bg/default_background.png"

        Flickable {
            id: flickable_left
            x: 0
            y: 0
            width: 1024
            height: 600

            SecretActivationButton {
                id: secretActivationButton
                x: 564
                y: 25
            }

            Item {
                id: beerButton
                x: 824
                y: 400
                width: 200
                height: 200

                Image {
                    id: buttonIcon
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
            }
        }
    }

    Connections {
        target: secretActivationButton
        onPressAndHold: secretValve.on()
        onReleased: secretValve.off()
    }

    Connections {
        target: beerButton
        onPressAndHold: normalValve.on()
        onReleased: normalValve.off()
    }

    Connections {
        target: flickable_left
        onFlickEnded: {
            Page2Form.visible = false
            Page1Form.visible = true
        }
    }
    states: [
        State {
            name: "DispesningBeer"

            PropertyChanges {
                target: buttonIcon
                source: "media/icon/beer_button_on.png"
            }
        }
    ]
}
