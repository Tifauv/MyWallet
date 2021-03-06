/*
 *  SPDX-FileCopyrightText: 2019 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0

Kirigami.ScrollablePage {
	id: page
	title: qsTr("Folders")

	property alias model: list.model
	property variant createDlg
	readonly property alias selectedFolder: list.currentFolder
	
	signal edit(int p_index)
	signal confirmDelete(int p_index)

	mainAction: Kirigami.Action {
		text: qsTr("Create folder")
		iconName: "folder-new"
		onTriggered: {
			createDlg.open()
		}
	}

	mainItem: ListView {
		id: list

		clip: true
		
		property variant currentFolder: undefined

		onCurrentIndexChanged: currentFolder = (currentIndex > -1 ? wallet.get(currentIndex) : undefined);

		delegate: Kirigami.SwipeListItem {
			id: delegate
			
			separatorVisible: false

			actions: [
				 Kirigami.Action {
					text: qsTr("Edit this folder")
					iconName: "document-edit"
					onTriggered: page.edit(model.index)
				 },
				 Kirigami.Action {
					text: qsTr("Delete this folder")
					iconName: "edit-delete"
					onTriggered: page.confirmDelete(model.index)
				 }
			]

			contentItem: FolderItem {
				iconColor: model.color
				folderName: model.name
				folderNameColor: delegate.textColor
				accountCount: adaptCount(model.accounts.count)
				accountCountColor: Qt.lighter(delegate.textColor, 1.8)
				
				spacing: delegate.leftPadding
			}

			highlighted: ListView.isCurrentItem
			onClicked: list.currentIndex = model.index
		}
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


	function selectFolder(p_index) {
		list.currentIndex = (p_index > -1 ? p_index : 0)
	}
}
