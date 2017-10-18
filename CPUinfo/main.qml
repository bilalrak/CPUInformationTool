import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0



ApplicationWindow {
    id: window
    visible: true
    width: 1020
    height: 650
    title: qsTr("CPU Information")
    color:"#444444"
   // color: "white"
    flags: Qt.WindowCloseButtonHint + Qt.WindowMinimizeButtonHint



    InfoSlidingPanel
    {
        id:myinfoSlidingPanel
        infoSlidingPanel_x:myBackPlate.backplate_width+20
        infoSlidingPanel_width:420
        infoSlidingPanel_y: 0
        infoSlidingPanel_height: window.height
    }





    BackPlate
    {
        id:myBackPlate
        backplate_height: parent.height
        backplate_width: cpuContainer.x+ cpuContainer.width+10

    }
    TopMostPlate{
        topMostPlate_width: myBackPlate.backplate_width
        }



    Connections
    {
        target: procfs
        onCpuInfoText:myinfoSlidingPanel.infoSlidingPanel_cpuinfotext = details
    }




    Grid
    {
        id: cpuContainer
        property int count:procfs.numOfCPUs
        columns: count/2
        spacing: 10
        x: 180
        y:175
        Repeater
        {
            model:cpuContainer.count
            Button
            {
                width:300/cpuContainer.columns; height: 150
                text: "CPU" + index
                onClicked:
                {
                    procfs.onRequestDetails(index)
                    myinfoSlidingPanel.infopanel_animatePanel(index)
                }

            }
        }
    }




    Label
    {
        id: cpuMarginlabel
        x: 5
        y: 175
        width: 159
        height: 32
        text: "CPUs found on this Machine\n\nSelect a CPU to view the information"
        horizontalAlignment: Text.AlignRight
        wrapMode: "WordWrap"
        color: "white"
        font.pixelSize: 12
    }



    Rectangle
    {
        id: rectangle
        x: 170
        y: 175
        width: 1
        height: 310
        color: "#444444"
    }

    Rectangle
    {
        id: rectangle1
        x: 170
        y: 175
        width: 10
        height: 1
        color: "#444444"
    }

    Rectangle
    {
        id: rectangle2
        x: 170
        y: 485
        width: 10
        height: 1
        color: "#444444"
    }




}
