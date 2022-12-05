import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtCharts 2.0

Row {
    spacing: 2
    anchors.fill: parent
    Rectangle {
        id: archive_panel
        width: parent.height
        height: parent.height
        PolarChartView {
            id: archive_chart
            anchors.fill: parent
            theme: ChartView.ChartThemeDark
            legend.visible: false
            antialiasing: true

            ValueAxis {
                id: axisAngular
                min: 0
                max: 360
            }

            ValueAxis {
                id: axisRadial
                min: 0
                max: 100
            }

            LineSeries {
                id: coord
                axisAngular: axisAngular
                axisRadial: axisRadial
            }

            Connections {
                target: archiveTrackModel
                function onAddArchiveSeries(objects) {
                    if(objects.empty)
                        return
                    
                    var myAxisX = archive_chart.axisX(coord)
                    var myAxisY = archive_chart.axisY(coord)
                    var scatter = archive_chart.createSeries(ChartView.SeriesTypeScatter, "Track_" + objects[0].id, myAxisX, myAxisY)
                    for (var i = 0; i < objects.length; i++) {
                        scatter.append(objects[i].x, objects[i].y)
                    }
                    objectList.model.append({ id: "Track_" + objects[0].id })
                }
            }
        }
    }
    Column {
        width: parent.width - parent.height
        height: parent.height
        spacing: 2
        DatePikerField {
            id: start_time
            someString: qsTr("Start time")
        }
        DatePikerField {
            id: end_time
            someString: qsTr("End time  ")
        }
        Button {
            text: qsTr("Load")
            onClicked: {
                archive_chart.removeAllSeries()
                objectList.model.clear()
                archiveTrackModel.update(start_time.getDateStr(), end_time.getDateStr())
            }
        }
        Rectangle {
            id: filter_panel
            width: parent.width - parent.height
            height: parent.height
            ListView {
                id: objectList
                anchors.fill: parent
                model: ListModel {}
                delegate: Rectangle {
                    height: 20
                    CheckBox {
                        text: id
                        checked: true
                        nextCheckState: {
                            var serise = archive_chart.series(text);
                            serise.visible = checked
                        }
                    }
                }
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true
            }
        }
    }
}