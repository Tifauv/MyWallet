import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
	width: 440
	implicitHeight: 48

	property alias nameTxt: accountName
	property alias loginTxt: accountLogin

	Rectangle {
		id: background
		color: "#00000000"
		border.width: 0
		anchors.fill: parent

		Label {
			id: accountName
			text: qsTr("Account name")
			anchors.bottom: accountLogin.top
			anchors.bottomMargin: 2
			anchors.topMargin: 6
			anchors.top: parent.top
			verticalAlignment: Text.AlignVCenter
			font.bold: false
			anchors.left: parent.left
			anchors.leftMargin: 8
			font.pixelSize: 16
		}

		Label {
			id: accountLogin
			y: 11
			color: "#93a1a1"
			text: qsTr("Login")
			anchors.bottomMargin: 6
			anchors.bottom: parent.bottom
			anchors.leftMargin: 12
			verticalAlignment: Text.AlignVCenter
			anchors.left: accountName.left
			font.pixelSize: 12
		}
	}
}
