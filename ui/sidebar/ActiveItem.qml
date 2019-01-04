import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import ".."

ItemDelegate {
	id: delegate

	height: 48
	width: 199

	property var visualItem
	property var swipeLeft
	property var swipeRight
	property var actionsItem

	contentItem: Rectangle {
		color: "#f2de09"
	}

	Rectangle {
		id: itemBackground

		anchors.fill: parent
		color: Material.dialogColor

		Binding {
			target: contentItem
			property: "anchors.fill"
			value: itemBackground
		}
		Binding {
			target: contentItem
			property: "anchors.leftMargin"
			value: 10
		}
		Binding {
			target: contentItem
			property: "anchors.rightMargin"
			value: 10
		}
		Binding {
			target: contentItem
			property: "anchors.topMargin"
			value: 8
		}
		Binding {
			target: contentItem
			property: "anchors.bottomMargin"
			value: 8
		}
	}
}
