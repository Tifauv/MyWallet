import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Wallets 1.0

Page {
	id: page

	implicitWidth: 440
	implicitHeight: 480

	property variant folder: undefined

	title: folder !== undefined ? folder.name : qsTr("Folder name")

	Clipboard {
		id: clipboard
	}

	footer: Pane {
		height: accountCount.implicitHeight + topPadding + bottomPadding

		topPadding: 4
		bottomPadding: 4
		leftPadding: 8

		Label {
			id: accountCount
			verticalAlignment: Text.AlignVCenter
			anchors.left: parent.left

			text: adaptCount(folder !== undefined ? folder.count : 0)
		}
	}

	ListView {
		id: list

		anchors.fill: parent
		clip: true

		model: folder !== undefined ? folder : []

		delegate: SwipeDelegate {
			id: delegate
			width: parent.width
			hoverEnabled: true

			contentItem: AccountView {
				name: model.name
				login: model.login
			}

			highlighted: ListView.isCurrentItem
			onClicked: list.currentIndex = model.index

			onDoubleClicked: {
				console.log("Double click: copying password to clipboard")
				clipboard.setTextWithTimer(model.password, 10)
			}

			swipe.right: Rectangle {
				width: parent.width
				height: parent.height

				clip: true
				color: SwipeDelegate.pressed ? "#555" : "#666"

				Label {
					text: delegate.swipe.complete ? "\u2714" : "\u2718"

					padding: 20
					anchors.fill: parent
					horizontalAlignment: Qt.AlignRight
					verticalAlignment: Qt.AlignVCenter

					opacity: 2 * -delegate.swipe.position

					color: Material.color(delegate.swipe.complete ? Material.Green : Material.Red, Material.Shade200)
					Behavior on color { ColorAnimation { } }
				}

				Label {
					text: qsTr("Removed")

					padding: 20
					anchors.fill: parent
					horizontalAlignment: Qt.AlignLeft
					verticalAlignment: Qt.AlignVCenter

					opacity: delegate.swipe.complete ? 1 : 0
					Behavior on opacity { NumberAnimation { } }
				}

				SwipeDelegate.onClicked: delegate.swipe.close()
				SwipeDelegate.onPressedChanged: undoTimer.stop()
			}

			Timer {
				id: undoTimer
				interval: 3600
				onTriggered: folder.deleteAccount(index)
			}

			swipe.onCompleted: undoTimer.start()
		}

		ScrollIndicator.vertical: ScrollIndicator {}
	}

	/**
	 * Adapts the accounts count to the number of elements in the folder.
	 */
	function adaptCount(count) {
		switch (count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(count)
		}
	}
}
