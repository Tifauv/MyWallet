import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.plasma.core 2.1 as PlasmaCore

Item {
	id: account
	implicitWidth: 440
	implicitHeight: 48

	property alias nameTxt: accountName
	property alias loginTxt: accountLogin
	property alias revealBtn: viewBtn
	property alias removeBtn: deleteBtn
	property bool hovered: false

	Label {
		id: accountName
		text: qsTr("Account name")
		font.pixelSize: 16

		verticalAlignment: Text.AlignVCenter

		anchors.topMargin: 6
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.leftMargin: 8
		anchors.right: viewBtn.left
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
		anchors.right: viewBtn.left
		anchors.rightMargin: 6
	}

	Button {
		id: viewBtn

		width: height

		anchors.right: deleteBtn.left

		flat: true
		visible: account.hovered

		PlasmaCore.IconItem {
			source: "quickview"

			anchors.centerIn: parent
		}
	}

	Button {
		id: deleteBtn

		width: height

		anchors.right: parent.right

		flat: true
		visible: account.hovered

		PlasmaCore.IconItem {
			source: "edit-delete"

			anchors.centerIn: parent
		}
	}
}
