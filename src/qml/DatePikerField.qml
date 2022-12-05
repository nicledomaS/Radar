
import QtQuick 2.15
import QtQuick.Controls

Row {
    property string someString
    spacing: 2
    width: parent.width
    Text { 
        text: someString
        anchors.bottom: parent.bottom
    }
    TextField  {
        id: date_field
        focus: true
        validator: RegularExpressionValidator { regularExpression: /^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$/ }
    }

    function getDateStr() {
        return date_field.text
    }
}