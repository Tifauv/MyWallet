import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.4 as Kirigami
import Wallets 1.0
import "folder"
import "account"

Kirigami.ApplicationWindow {
	id: window
	visible: true
	width: 640
	height: 480
	title: qsTr("MyWallet")

	readonly property int defaultSidebarWidth: Kirigami.Units.gridUnit * 14
	property int copyTimeout: 10 // seconds

	globalDrawer: Kirigami.GlobalDrawer {
		title: qsTr("MyWallet")
		titleIcon: "kwalletmanager"
		
		actions: [
			Kirigami.Action {
				text: qsTr("Quit")
				iconName: "application-exit"
				shortcut: StandardKey.Quit
				onTriggered: Qt.quit()
			}
		]
	}
	
	pageStack.defaultColumnWidth: defaultSidebarWidth
	pageStack.initialPage: walletPage

	WalletPage {
		id: walletPage
		
		walletName: wallet.name
		
		onRetryOpenWallet: {
			wallet.loadKWallet(config.previousWallet.length > 0 ? config.previousWallet : "Wallets")
		}
	}
	
	FoldersPage {
		id: foldersPage
		
		model: wallet
		createDlg: createFolderDlg
		
		onEdit: window.showPassiveNotification(
					qsTr("Folder edition not yet implemented."),
					"short")
		
		onConfirmDelete: window.showPassiveNotification(
							 qsTr("Delete folder \"%1\"?").arg(wallet.get(p_index).name),
							 "long",
							 qsTr("Delete"),
							 function(){wallet.deleteFolder(p_index)});
	}

	AccountsPage {
		id: accountsPage
		
		model: foldersPage.selectedFolder
		createDlg: createAccountDlg
	}

	AccountViewPage {
		id: accountViewPage
		
		model: accountsPage.selectedAccount
		editDlg: editAccountDlg

		onCopyString: clipboard.setText(p_string)
		onCopyPassword: {
			clipboard.setSecretTextWithTimer(p_password, copyTimeout);
			window.showPassiveNotification(
					qsTr("Password for \"%1\" copied to clipboard.").arg(model.name),
					copyTimeout * 1000 /* milliseconds */)
		}

		onConfirmDelete: window.showPassiveNotification(
							qsTr("Delete account \"%1\"?").arg(model.name),
							"long",
							qsTr("Delete"),
							function(){accountsPage.model.deleteAccount(accountsPage.selectedIndex)})
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

	AccountCreationSheet {
		id: createAccountDlg
		
		folderModel: accountsPage.model
	}
	
	AccountEditionSheet {
		id: editAccountDlg
		
		onModifyAccount: accountsPage.model.modifyAccount(accountsPage.selectedIndex, login, website, notes)
	}

	Config {
		id: config
	}

	Wallet {
		id: wallet
		
		onOpened: {
			walletPage.state = "Success";
			pageStack.pop();
			pageStack.push(foldersPage)
			pageStack.push(accountsPage)
			pageStack.push(accountViewPage)
		}
		
		onOpenFailed: {
			walletPage.state = "Retry"
		}
		
		onLoaded: {
			// Select the previous folder, or the first one
			var index = wallet.find(config.previousFolder);
			foldersPage.selectFolder(index);
	
			// If the wallet is empty, show the folder creation dialog
			if (wallet.count === 0)
				createFolderDlg.open();
		}
	}

	Clipboard {
		id: clipboard
	}


	// Restore the previous state
	Component.onCompleted: {
		window.width  = config.previousWidth;
		window.height = config.previousHeight;

		// Load the previous wallet, or default to "Wallets"
		wallet.name = config.previousWallet.length > 0 ? config.previousWallet : "Wallets";
	}

	// Sync the config object on closing
	onClosing: {
		config.previousWidth  = window.width;
		console.log("Saved previous window width: " + config.previousWidth);
		config.previousHeight = window.height;
		console.log("Saving previous window height: " + config.previousHeight);
		config.previousWallet = wallet.name;
		console.log("Saving previous wallet: " + config.previousWallet);
		config.previousFolder = foldersPage.selectedFolder.name;
		console.log("Saving previous folder: " + config.previousFolder);
	}
}
