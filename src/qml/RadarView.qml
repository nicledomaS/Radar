import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtCharts 2.0

Row {
    spacing: 2
    anchors.fill: parent
    Rectangle {
        id: radar_panel
        width: parent.height
        height: parent.height
        PolarChartView {
            id: chart
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
                target: realtimeViewController
                function onAddSeries(obj) {
                    var myAxisX = chart.axisX(coord);
                    var myAxisY = chart.axisY(coord);
                    var scatter = chart.createSeries(ChartView.SeriesTypeScatter, obj.id, myAxisX, myAxisY);
                    scatter.append(obj.x, obj.y)
                    objectList.model.append({ id: obj.id })
                }

                function onUpdateSeries(obj) {
                    var serise = chart.series(obj.id);
                    var point = serise.at(0)
                    serise.replace(point.x, point.y, obj.x, obj.y)
                }

                function onRemoveSeries(obj) {
                    var serise = chart.series(obj.id);
                    chart.removeSeries(serise)
                    for (var i = 0; i < objectList.model.count; i++) {
                        if(objectList.model.get(i).id == obj.id) {
                            objectList.model.remove(i)
                            break
                        }
                    }
                }
            }
        }
    }
    Rectangle {
        id: filter_panel
        width: parent.width - parent.height
        height: parent.height
        ListView {
            id: objectList
            model: ListModel {}
            delegate: Rectangle {
                anchors.fill: parent
                CheckBox {
                    text: id
                    checked: true
                    nextCheckState: {
                        var serise = chart.series(text);
                        serise.visible = checked
                    }
                }
            }
        }
    }
}