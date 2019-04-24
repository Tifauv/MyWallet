import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: account
    implicitWidth: 440
    implicitHeight: 48

    property alias nameTxt: accountName
    property alias loginTxt: accountLogin

    Label {
        id: accountName
        text: qsTr("Account name")
        font.pixelSize: 16

        verticalAlignment: Text.AlignVCenter

        anchors.topMargin: 6
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 6
    }

    SecondaryLabel {
        id: accountLogin
        text: qsTr("Login")

        verticalAlignment: Text.AlignVCenter

        anchors.top: accountName.bottom
        anchors.topMargin: 2
        anchors.bottomMargin: 6
        anchors.bottom: parent.bottom
        anchors.left: accountName.left
        anchors.leftMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 6
    }
}
