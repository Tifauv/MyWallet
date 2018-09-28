import QtQuick 2.9
import QtQuick.Controls 2.2

GridView {
	id: selector

	implicitHeight: cellHeight * Math.ceil( (model.count * cellWidth) / width )

	onWidthChanged: console.log("width: " + width)
	onImplicitHeightChanged: console.log("implicit height: " + implicitHeight)

	property int padSize: 32
	property int padding: 2
	property string selectedColor: currentIndex >= 0 ? model.get(currentIndex).colorCode : "white"

	cellWidth: padSize + 2 * padding
	cellHeight: padSize + 2 * padding
	onCellWidthChanged: console.log("cell width: " + cellWidth)
	onCellHeightChanged: console.log("cell height: " + cellHeight)

	delegate: ItemDelegate {
		id: colorTag
		hoverEnabled: true

		implicitWidth: cellWidth
		implicitHeight: cellHeight

		Rectangle {
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter

			width: padSize
			height: padSize
			radius: height  / 2

			color: model.colorCode
		}

		highlighted: GridView.isCurrentItem
		onClicked: selector.currentIndex = model.index
	}

	ScrollIndicator.vertical: ScrollIndicator {}
}
