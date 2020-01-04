import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
	id: page
	title: qsTr("Wallet")
	
	property variant model
	property string walletName: "Wallets"
	
	signal retryOpenWallet(string name)
	
	Column {
		id: column
		anchors.fill: parent
		
		spacing: Kirigami.Units.largeSpacing
		
		Label {
			id: message
			text: qsTr("Opening wallet '%1'...").arg(walletName)
			anchors.horizontalCenter: parent.horizontalCenter
		}
		
		Button {
			id: action
			text: "Retry"
			anchors.horizontalCenter: parent.horizontalCenter
			
			visible: false
			enabled: false
			
			focus: true
			
			onClicked: retryOpenWallet(walletName)
		}
	}
	
	states: [
		State {
			name: "Retry"
			
			PropertyChanges {
				target: message
				text: qsTr("Failed to open wallet '%1'.").arg(walletName)
			}
			
			PropertyChanges {
				target: action
				visible: true
				enabled: true
			}
		},
		State {
			name: "Success"
			
			PropertyChanges {
				target: message
				text: qsTr("Wallet '%1' opened.").arg(walletName)
			}
		}
	]
}
