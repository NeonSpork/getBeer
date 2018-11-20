import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: item1
    width: 300
    height: 150
    
    Image {
        id: image
        x: 0
        y: 0
        width: 300
        height: 150
        source: "media/icon/default_icon.png"
        
        MouseArea {
            id: default_background
            x: 0
            y: 0
            width: 300
            height: 150
        }
    }
}
