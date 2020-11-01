/*
 *  SPDX-FileCopyrightText: 2019 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

import QtQuick 2.12
import QtQuick.Controls 2.5

GridView {
	id: selector

	implicitHeight: cellHeight * rows
	implicitWidth: cellWidth * (model.count / rows)

	property int rows: 2
	property int padSize: 32
	property int padding: 2
	property string selectedColor: currentIndex >= 0 ? model.get(currentIndex).colorCode : "white"

	cellWidth: padSize + 2 * padding
	cellHeight: padSize + 2 * padding

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
