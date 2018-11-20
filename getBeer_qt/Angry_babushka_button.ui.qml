import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: item3
    width: 150
    height: 150
    
    Image {
        id: image1
        x: 0
        y: 0
        width: 150
        height: 150
        source: "media/icon/angry_babushka_icon.png"
        
        MouseArea {
            id: angry_babushka
            x: 0
            y: 0
            width: 150
            height: 150
        }
    }
}
