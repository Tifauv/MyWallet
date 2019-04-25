import QtQuick 2.9
import QtQuick.Controls 2.2
import org.kde.kirigami 2.4 as Kirigami

Item {
	id: folder
	implicitWidth: 200
	implicitHeight: folderName.height + accountCount.height
	
	property alias iconCircle: icon
	property alias iconTxt: initial
	property alias folderNameTxt: folderName
	property alias accountCountTxt: accountCount
	property int spacing: Kirigami.Units.largeSpacing

	Rectangle {
		id: icon
		width: Kirigami.Units.iconSizes.medium
		height: width
		radius: width / 2
		anchors.verticalCenter: parent.verticalCenter
		border.width: 0
		anchors.left: parent.left
		
		Label {
			id: initial
			
			text: "Fo"
			
			font.pointSize: 12
			font.bold: true
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			anchors.fill: parent
		}
	}

	Label {
		id: folderName
		text: qsTr("Folder name")
		verticalAlignment: Text.AlignBottom
		anchors.left: icon.right
		anchors.leftMargin: spacing
		anchors.top: parent.top
		anchors.right: parent.right
	}

	SecondaryLabel {
		id: accountCount
		text: qsTr("Empty")
		verticalAlignment: Text.AlignTop
		anchors.left: folderName.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
	}
}
