import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: item2
    width: 150
    height: 150
    
    Image {
        id: image2
        x: 0
        y: 0
        width: 150
        height: 150
        source: "media/icon/tropical_thunder_icon.png"
        
        MouseArea {
            id: tropical_thunder
            x: 0
            y: 0
            width: 150
            height: 150
        }
    }
}
