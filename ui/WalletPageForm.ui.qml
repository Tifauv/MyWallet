import QtQuick 2.4
import "widgets"
import QtQuick.Controls 2.2

Page {
	id: page
	width: 440
	height: 480
	title: "Page Title"
	background: Rectangle {
		color: "#fdf6e3"
	}

	header: PageHeader {
		id: headerbar
		mainText: page.title
	}

	property alias menuButton: headerbar.button
	property alias accounts: list

	ListView {
		id: list
		clip: true
		anchors.fill: parent
		delegate: AccountView {
			anchors.left: parent.left
			anchors.right: parent.right

			name: model.name
			login: model.login
		}
	}
}
