import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
	id: walletItem
	width: 200
	height: 32

	property alias color: icon.color
	property alias text: label.text

	Rectangle {
		id: icon
		width: 16
		height: 16
		radius: 4
		anchors.verticalCenter: parent.verticalCenter
		border.width: 0
		anchors.left: parent.left
		anchors.leftMargin: 8
	}

	Label {
		id: label
		text: "Wallet name"
		anchors.verticalCenter: icon.verticalCenter
		verticalAlignment: Text.AlignVCenter
		anchors.left: icon.right
		anchors.leftMargin: 10
		anchors.right: parent.right
		anchors.rightMargin: 8
	}
}
