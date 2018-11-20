import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 1024
    height: 600
    title: qsTr("getBeer")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex:

        Page1Form {
            Flickable: right

        }

        Page2Form {
            Flickable: left
        }

        Page3Form {
            Flickable: left
        }

        Page4Form {
            Flickable: left
        }
    }
    }
