import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

Item {

    property int backplate_height
    property int backplate_width

    Rectangle{
        x:0
        id:numixBack
        color: "#444444"
        width: backplate_width+20
        height: backplate_height
        y:0

    }




}
