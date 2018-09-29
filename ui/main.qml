import QtQuick 2.9
import QtQuick.Controls 2.2
//import QtQuick.Controls.Material 2.2
import Wallets 1.0

ApplicationWindow {
	id: window
	visible: true
	width: 640
	height: 480
	title: qsTr("Wallets")

	readonly property bool inPortrait: window.width < window.height

	Wallet {
		id: wallet
	}

	TitleBar {
		id: windowHeader

		z: 1
		width: parent.width
		parent: window.overlay
		implicitHeight: Math.max(appName.height, menuBtn.height)

		Label {
			id: appName

			anchors.left: parent.left
			anchors.leftMargin: 8
			anchors.verticalCenter: parent.verticalCenter

			text: qsTr("Wallets / %1").arg(page.title)
			font.letterSpacing: 2
			font.weight: Font.Thin
			font.pixelSize: 22

		}

		ToolButton {
			id: menuBtn

			anchors.right: parent.right
			anchors.verticalCenter: parent.verticalCenter

			text: "\u2630"
			font.pixelSize: Qt.application.font.pixelSize * 1.6

			onClicked: menu.open()

			Menu {
				id: menu
				y: menuBtn.height

				MenuItem { text: "Export wallet..." }
				MenuItem { text: "Import wallet..." }
				MenuItem { text: "Delete wallet"    }
				MenuSeparator { }
				MenuItem { text: "Settings"         }
			}
		}
	}

	Drawer {
		id: sidebar

		y: windowHeader.height
		width: 180
		height: window.height - windowHeader.height

		modal: inPortrait
		interactive: inPortrait
		position: inPortrait ? 0 : 1
		visible: !inPortrait

		contentItem: ListView {
			id: folderList

			anchors.fill: parent
			clip: true

			model: wallet

			delegate: ItemDelegate {
				id: delegate
				width: parent.width
				hoverEnabled: true

				contentItem: FolderItem {
					color: model.color
					text: model.name
				}

				highlighted: ListView.isCurrentItem
				onClicked: {
					loadFolder(model.index)
					folderList.currentIndex = model.index
				}

				/*swipe.right: Rectangle {
					width: parent.width
					height: parent.height

					clip: true
					color: SwipeDelegate.pressed ? "#555" : "#666"

					Label {
						//font.family: "Fontello"
						text: delegate.swipe.complete ? "\ue805" // icon-cw-circled
													: "\ue801" // icon-cancel-circled-1

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
						color: "white"

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
					onTriggered: wallet.removeFolder(index)
				}

				swipe.onCompleted: undoTimer.start()
				*/
			}

			ScrollIndicator.vertical: ScrollIndicator { }
		}

		RoundButton {
			id: newFolderBtn
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 4
			anchors.horizontalCenter: parent.horizontalCenter

			hoverEnabled: true
			text: "+"

			onClicked: createFolderDlg.open()
		}
	}

	AccountsPage {
		id: page

		anchors.fill: parent
		anchors.topMargin: windowHeader.height
		anchors.leftMargin: !inPortrait ? sidebar.width : undefined
	}

	CreateFolderDialog {
		id: createFolderDlg

		modal: true
		focus: true

		width: 220
		height: 200

		x: (parent.width - width) / 2
		y: (parent.height - height) / 2

		onAccepted: {
			console.log("Creating folder '" + name + "' with color '" + tagColor + "'")
			wallet.createFolder(name, tagColor);
		}
	}

	// Autoselect the first folder
	Component.onCompleted: loadFolder(0)


	/**
	 * Selects the folder at the given index in the model.
	 * If the model is empty, or the index is outside [0, model.count[, nothing is done.
	 *
	 * @param index  the index of the folder to select
	 */
	function loadFolder(index) {
		if (wallet.count > 0 && index >= 0 && index < wallet.count)
			page.folder = wallet.get(index)
	}
}
