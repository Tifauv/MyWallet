import QtQuick 2.9
import QtQuick.Controls 2.2
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

			onClicked: console.log("New folder requested")
		}
	}

	AccountsPage {
		id: page

		anchors.fill: parent
		anchors.topMargin: windowHeader.height
		anchors.leftMargin: !inPortrait ? sidebar.width : undefined
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
