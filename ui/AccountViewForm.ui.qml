import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
	id: account
	implicitWidth: 440
	implicitHeight: 48

	property alias nameTxt: accountName
	property alias loginTxt: accountLogin
	property alias deleteBtn: deleteBtn

	Label {
		id: accountName
		text: qsTr("Account name")
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
		text: qsTr("Login")
		anchors.top: accountName.bottom
		anchors.topMargin: 2
		anchors.bottomMargin: 6
		anchors.bottom: parent.bottom
		anchors.leftMargin: 12
		verticalAlignment: Text.AlignVCenter
		anchors.left: accountName.left
		font.pixelSize: 12
	}

	ToolButton {
		id: deleteBtn
		text: qsTr("\u2716")
		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
	}
}
