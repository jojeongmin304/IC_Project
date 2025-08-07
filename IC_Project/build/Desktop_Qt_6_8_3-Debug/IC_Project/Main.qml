import QtQuick 2.15

Window {
    id: instrumentcluster
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Instrument Cluster")

    InstrumentCluster {
        id: instrumentCluster
        //x: 0
        //y: 0
        anchors.centerIn: parent
    }
}
