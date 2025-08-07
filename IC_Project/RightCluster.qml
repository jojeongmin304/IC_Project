import QtQuick 2.15

Item {
    id: rightcluster
    width: rightOutCircle.width
    height: rightOutCircle.height

    property real capacity: 0

    //중앙 파란 원
    Image {
        id: rightCircle
        //x: 295
        //y: 78
        width: 490
        height: 485
        anchors.centerIn: rightOutCircle
        source: ":/assets/RightCircle.png"
        fillMode: Image.PreserveAspectFit
    }
    //바깥 음영 원
    Image {
        id: rightOutCircle
        //x: 140
        //y: -54
        width: 800
        height: 750
        anchors.fill: parent
        source: ":/assets/RightOutCircle.png"
        fillMode: Image.PreserveAspectFit

    }

    Text {
        //x: 332
        //y: 341
        anchors.centerIn: parent
        color: "#ffffff"
        text: Math.round(capacity)
        font.pixelSize: 60
        font.bold: true
    }

    Text {
        x: 363
        y: 415
        color: "#d8d8d8"
        text: qsTr("mAh")
        font.pixelSize: 35
    }

    //배터리 게이지나 바늘 이미지 추가할 예정

}
