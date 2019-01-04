import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import ".."

Drawer {
	id: sidebar

	property alias model: list.model
	property variant createDlg
	signal folderSelected(int index)

	ListView {
		id: list

		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: newFolderBtn.top

		clip: true

		delegate: FolderSwipeItem {
			id: delegate
			width: parent.width

			highlighted: ListView.isCurrentItem
			onClicked: selectFolder(model.index)

			onDeleteCompleted: wallet.deleteFolder(model.index)
		}

		ScrollIndicator.vertical: ScrollIndicator { }
	}

	ToolButton {
		id: newFolderBtn
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		height: 32

		text: qsTr("New Folder...")
		flat: true
		hoverEnabled: true

		onClicked: createDlg.open()
	}

	/**
	 * Adapts the accounts count to the number of elements in the folder.
	 */
	function adaptCount(p_count) {
		switch (p_count) {
		    case 0: return qsTr("Empty");
			case 1: return qsTr("1 account");
			default: return qsTr("%1 accounts").arg(p_count)
		}
	}

	/**
	 * Changes the list's selected index then emits the folderSelected signal.
	 */
	function selectFolder(p_index) {
		list.currentIndex = p_index;
		folderSelected(p_index);
	}
}
