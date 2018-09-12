import QtQuick 2.0

WalletButtonForm {
	id: walletButton

	property color color
	property string name
	property bool selected
	signal clicked()

	icon.color: color
	label.text: name


	button.onClicked: {
		clicked()
	}

	states: [
		State {
			name: "Highlighted"
			when: button.containsMouse && !walletButton.selected

			PropertyChanges {
				target: background
				color: "#073642"
			}

			PropertyChanges {
				target: label
				color: "#93a1a1"
			}
		},
		State {
			name: "Selected"
			when: walletButton.selected

			PropertyChanges {
				target: background
				color: "#073642"
			}

			PropertyChanges {
				target: label
				color: Qt.colorEqual(walletButton.color, "#00000000") ? "#93a1a1" : walletButton.color
			}
		}
	]
}
