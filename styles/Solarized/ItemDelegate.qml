import QtQuick 2.9
import QtQuick.Templates 2.2 as T

T.ItemDelegate {
	id: control

	implicitWidth: Math.max(background ? background.implicitWidth : 0,
							contentItem.implicitWidth + leftPadding + rightPadding)
	implicitHeight: Math.max(background ? background.implicitHeight : 0,
										Math.max(contentItem.implicitHeight,
									  indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
	baselineOffset: contentItem.y + contentItem.baselineOffset

	background: Rectangle {
		implicitWidth: 200
		implicitHeight: 32
		visible: control.down || control.highlighted || control.visualFocus || control.hovered
		color: control.hovered ? "#30525b" : "#073642"
	}
}
