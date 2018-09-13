import QtQuick 2.4

Item {
	width: 440
	height: 32

	property alias nameTxt: accountName
	property alias loginTxt: accountLogin

	Rectangle {
		id: background
		color: "#00000000"
		border.width: 0
		anchors.fill: parent

		Text {
			id: accountName
			y: 8
			text: qsTr("Account name")
			anchors.verticalCenter: parent.verticalCenter
			verticalAlignment: Text.AlignBottom
			font.bold: false
			anchors.left: parent.left
			anchors.leftMargin: 6
			font.pixelSize: 16
		}

		Text {
			id: accountLogin
			y: 11
			color: "#535353"
			text: qsTr("Login")
			anchors.bottomMargin: 1
			verticalAlignment: Text.AlignBottom
			anchors.left: accountName.right
			anchors.leftMargin: 12
			anchors.bottom: accountName.bottom
			font.pixelSize: 12
		}
	}
}
