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

            Item {
                id: item2
                x: 564
                y: 25
                width: 272
                height: 132

                MouseArea {
                    id: mouseArea
                    x: 6
                    y: 0
                    width: 266
                    height: 132
                }
            }

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
    states: [
        State {
            name: "DispesningBeer"

            PropertyChanges {
                target: image
                source: "media/icon/beer_button_on.png"
            }
        }
    ]
}
