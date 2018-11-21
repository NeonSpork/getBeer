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

            BeerButton {
                id: beerButton
                x: 824
                y: 400
            }
        }
    }
    states: [
        State {
            name: "DispesningBeer"

            PropertyChanges {
                target: beerButtonIcon
                source: "media/icon/beer_button_on.png"
            }
        }
    ]
}
