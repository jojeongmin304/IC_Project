import QtQuick 2.15

Item {
    width: 1920
    height: 1080

    property real actualSpeed: speedController.speed
    property real actualCapacity: 1000

    Image {
        id: backGround
        //x: 0
        //y: 0
        //width: 1920
        //height: 1080

        source: "qrc:/asset/BackGround.png"
        anchors.fill: parent
        //sourceSize.height: 1080
        //sourceSize.width: 1920
        fillMode: Image.PreserveAspectFit
    }
    LeftCluster {
        id: leftCluster
        x: 70
        y: 205

        //leftCluster의 speed 프로퍼티에 실제 속도 값을 전달
        speed: actualSpeed
    }

    RightCluster {
        id: rightCluster
        x: 1027
        y: 205

        //rightCluster의 Capacity 프로퍼티에 실제 배터리 값을 전달
        capacity: actualCapacity
    }
}


