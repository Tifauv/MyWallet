import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0

Kirigami.ApplicationWindow {
	id: window
	visible: true
	width: 640
	height: 480
	title: wallet.name

	readonly property int defaultSidebarWidth: Kirigami.Units.gridUnit * 12
	readonly property int defaultContextDrawerWidth: Kirigami.Units.gridUnit * 17

	Wallet {
		id: wallet
	}

	globalDrawer: Kirigami.GlobalDrawer {
		title: wallet.name
		titleIcon: "kwalletmanager"
		
		actions: [
			Kirigami.Action {
				text: "Wallet"
				iconName: "view-list-icons"
				Kirigami.Action {
					text: "Export"
					iconName: "folder-sync"
				}
				Kirigami.Action {
					text: "Import"
					iconName: "folder-sync"
				}
				Kirigami.Action {
					text: "Delete"
					iconName: "folder-sync"
				}
			},
			Kirigami.Action {
				text: "Settings"
				iconName: "folder-sync"
			}
		]
	}
	
	contextDrawer: Kirigami.ContextDrawer {
		id: contextDrawer
	}
	
	pageStack.defaultColumnWidth: defaultSidebarWidth
	pageStack.initialPage: [foldersPage, accountsPage]


	FoldersPage {
		id: foldersPage
		
		model: wallet
		createDlg: createFolderDlg
	}


	AccountsPage {
		id: accountsPage
		
		model: foldersPage.selectedFolder
		createDlg: createAccountDlg
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
			wallet.createFolder(name, tagColor);
			reset();
		}
		onRejected: reset()
	}


	CreateAccountDialog {
		id: createAccountDlg

		modal: true
		focus: true

		width: 220
		height: 200

		x: (parent.width - width) / 2
		y: (parent.height - height) / 2

		onAccepted: {
			folder.createAccount(name, login, password);
			reset();
		}
		onRejected: reset()
	}


	// Restore the previous state
	Component.onCompleted: {
		window.width  = config.previousWidth;
		window.height = config.previousHeight;

		// Select the previous folder, or the first one
		var index = wallet.find(config.previousFolder);
		foldersPage.selectFolder(index);

		// If the wallet is empty, show the folder creation dialog
		if (wallet.count === 0)
			createFolderDlg.open();
	}

	// Sync the config object on closing
	onClosing: {
		config.previousWidth  = window.width;
		console.log("Saved previous window width: " + config.previousWidth);
		config.previousHeight = window.height;
		console.log("Saving previous window height: " + config.previousHeight);
		config.previousFolder = foldersPage.selectedFolder.name;
		console.log("Saving previous folder: " + config.previousFolder);
	}
}
