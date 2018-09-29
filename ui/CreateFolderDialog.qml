import QtQuick 2.9
import QtQuick.Controls 2.2

Dialog {
	id: dialog

	implicitWidth: 220
	implicitHeight: nameTxt.height + padding + colorSelector.implicitHeight

	standardButtons: Dialog.Save | Dialog.Cancel
	closePolicy: Dialog.CloseOnEscape | Dialog.CloseOnPressOutside

	property alias name: nameTxt.text
	property alias tagColor: colorSelector.selectedColor

	TextField {
		id: nameTxt
		width: parent.width

		text: name
		placeholderText: qsTr("Folder name")
		focus: true
	}

	ColorSelector {
		id: colorSelector

		anchors.top: nameTxt.bottom
		anchors.topMargin: 4

		anchors.right: parent.right
		anchors.left: parent.left

		model: SolarizedPalette {}
	}
	
	function reset() {
		name = "";
		nameTxt.focus = true;
	}
}
