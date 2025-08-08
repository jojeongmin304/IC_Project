import QtQuick 2.15


//이 컴포넌트는 독립적으로 존재, 절대좌표를 사용하지 않는다.
Item {
    id: leftcluster
    width: leftOutCircle.width
    height: leftOutCircle.height
    visible: true

    property real speed: 0

    // 바깥 음영 원
    Image {
        id: leftOutCircle
        //x: 0
        //y: 0
        width: 800
        height: 750
        anchors.fill: parent
        source: "qrc:/asset/LeftOutCircle.png"
        fillMode: Image.PreserveAspectFit

    // 게이지나 바늘 이미지 추가할 예정
    }

    //  중앙 파란 원
    Image {
        id: leftCircle
        //x: 155
        //y: 133
        width: 490
        height: 485
        //anchors.fill: parent
        anchors.centerIn: leftOutCircle  //바깥 원 중앙에 배치
        source: "qrc:/asset/LeftCircle.png"
        fillMode: Image.PreserveAspectFit
    }

    // -----텍스트 요소들------
    //실제 속도 값 표시 텍스트
    Text {
        //x: 310
        //y: 315
        //width: 180
        //height: 120
        anchors.centerIn: parent
        color: "#ffffff"
        //text: qsTr("72")
        font.pixelSize: 75
        text: Math.round(speed)  //반올림 해서 바인딩
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
    }
    //단위(km/h) 표시 텍스트
    Text {
        x: 353
        y: 398
        width: 100
        height: 60
        color: "#d7d8d9"
        text: qsTr("km/h")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
