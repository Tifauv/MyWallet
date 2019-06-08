import QtQuick 2.9
import org.kde.kirigami 2.4 as Kirigami

FolderItemForm {
	id: idem
	
	property color iconColor: icon.color
	property string folderName: qsTr("Folder name")
	property color folderNameColor
	property string accountCount: qsTr("Empty")
	property color accountCountColor

	iconCircle.color: iconColor
	iconTxt.text: folderName.charAt(0).toUpperCase() + folderName.charAt(1).toLowerCase()
	iconTxt.color: Qt.lighter(iconColor, 1.6)
	folderNameTxt.text: folderName
	folderNameTxt.color: folderNameColor
	accountCountTxt.text: accountCount
	accountCountTxt.color: accountCountColor
}
