import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 1024
    height: 600
    property alias mouseArea3: mouseArea3
    property alias angry_babushka: angry_babushka
    property alias tropical_thunder: tropical_thunder
    property alias default_background: default_background
    property alias flickable: flickable

    BorderImage {
        id: borderImage
        x: 0
        y: 0
        width: 1024
        height: 600
        source: "media/bg/brick_wall.png"

        Flickable {
            id: flickable
            x: 0
            y: 0
            width: 1024
            height: 600

            Default_selection {
                id: defaultSelection
                x: 362
                y: 37
            }

            Tropical_thunder_button {
                id: tropicalThunder
                x: 227
                y: 225
            }

            Angry_babushka_button {
                id: angryBabushka
                x: 437
                y: 225
            }

            Coming_soon {
                id: comingSoon
                x: 651
                y: 225
            }

            Coming_soon {
                id: comingSoon1
                x: 227
                y: 413
            }

            Coming_soon {
                id: comingSoon2
                x: 437
                y: 413
            }

            Coming_soon {
                id: comingSoon3
                x: 651
                y: 413
            }
        }
    }

    Connections {
        target: tropicalThunder
        onClicked: {
            Page1Form.visible = false
            Page3Form.visible = true
        }
    }

    Connections {
        target: angryBabushka
        onClicked: {
            Page1Form.visible = false
            Page4Form.visible = true
        }
    }

    Connections {
        target: comingSoon
        onClicked: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }

    Connections {
        target: comingSoon1
        onClicked: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }

    Connections {
        target: comingSoon2
        onClicked: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }

    Connections {
        target: comingSoon3
        onClicked: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }

    Connections {
        target: defaultSelection
        onClicked: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }

    Connections {
        target: flickable
        onFlickEnded: {
            Page1Form.visible = false
            Page2Form.visible = true
        }
    }
}
