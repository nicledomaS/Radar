import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtCharts 2.0

Window  {
    visible: true
    width: 640
    height: 480
    title: qsTr("Radar")

    Column {
        anchors.fill: parent
        spacing: 2
        TabBar {
            id: bar
            width: parent.width
            TabButton {
                text: qsTr("Radar")
            }
            TabButton {
                text: qsTr("Archive")
            }
        }
        StackLayout {
            currentIndex: bar.currentIndex
            width: parent.width
            height: parent.height - bar.height
            Item {
                id: radar_view_tab
                RadarView {}
            }
            Item {
                id: archive_view_tab
                ArchiveView {}
            }
        }
    }
}