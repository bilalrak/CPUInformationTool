import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

Item
{

    x:0
    y:0
   // width: window.width
    height: 130
    property int  topMostPlate_width

   // Rectangle{
   //     id:headerBackColor
   //     anchors.fill:parent
   //     color: "black"

   // }


    Rectangle {
        id: rectangle
        x: 0
        y:0
        width: topMostPlate_width
        height: 500
        color: "black"
        //color: "#E91E63"
        LinearGradient {
                anchors.fill: rectangle
                source: rectangle
                start: Qt.point(0, 0)
                end: Qt.point(0, 500)
                //smooth:true
                visible: true
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#151515" }
                    GradientStop { position: 1.0; color: "black" }
                }
        }
    }
    DropShadow{
        radius: 20
        samples: 17
        anchors.fill:rectangle
        color: "black"
        source: rectangle

    }

    Label
    {
        x: 20
        y: 41
        text: "CPU Information Tool"
        font.bold: true
        color: "white"
        font.pixelSize: 20


    }



    Label {
        x: 20
        y: 66
        width: 192
        height: 15
        color: "#FF5722"
        text: "for Linux OS"
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 15
    }

    Rectangle {
        x: 20
        y: 90
        width: topMostPlate_width -40
        height: 1
        //color: "#FF5722"
        color: "#9E9E9E"
    }




}
