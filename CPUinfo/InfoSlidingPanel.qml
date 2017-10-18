import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

Item {
    property int infoSlidingPanel_x
    property int infoSlidingPanel_width
    property int  infoSlidingPanel_y
    property int  infoSlidingPanel_height
    property string  infoSlidingPanel_cpuinfotext
    property int  lastIndex: 100

    x:infoSlidingPanel_x
    y:infoSlidingPanel_y
    height: infoSlidingPanel_height
    width: infoSlidingPanel_width

    Item{
        id:tray
        x:-infoSlidingPanel_width
        y:0
        height: infoSlidingPanel_height
        width: infoSlidingPanel_width

        Rectangle{
            anchors.fill:parent
            color: "black"
            opacity: 0.5
        }
        Label
        {

            id:cpuinfoText
            text: infoSlidingPanel_cpuinfotext
            width: tray.width - 15
            wrapMode: "WordWrap"
            font.pixelSize: 11
            color: "white"
            x:tray.x +10
            y:20

        }



    }
    Rectangle{
        height: infoSlidingPanel_height
        y:0
        x:tray.x+infoSlidingPanel_width
        width: 1
        color: "black"

    }


    PropertyAnimation{
        id:opacityanimation
        target:cpuinfoText
        property: "opacity"
        from:0
        to:1
        duration:1500
        easing.type: Easing.OutQuart
    }

    PropertyAnimation
    {
        id: panelAnimationOPEN
        target: tray
        property: "x"
        from: -infoSlidingPanel_width
        //to:infopanel_x+infopanel_width
        to:0
        duration: 500
        easing.type: Easing.OutQuart



    }
    PropertyAnimation
    {
        id: panelAnimationCLOSE
        target: tray
        property: "x"
        //from:infopanel_x+infopanel_width
        //to:infopanel_x
        from:0
        to:-infoSlidingPanel_width
        duration: 500
        easing.type: Easing.OutQuart

    }


    function infopanel_animatePanel(index)
    {
        if(index==lastIndex)
        {
            panelAnimationCLOSE.start()
            lastIndex =100
        }
        else
        {
            panelAnimationOPEN.start()
            opacityanimation.start()
            lastIndex = index
        }


    }

}
