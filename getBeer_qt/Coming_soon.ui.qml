import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: comingSoon
    width: 150
    height: 150
    
    Image {
        id: comingSoonIcon
        x: 0
        y: 0
        width: 150
        height: 150
        source: "media/icon/coming_soon_icon.png"
        
        ComingSoon {
            id: mouseArea3
            x: 0
            y: 0
        }
    }
}
