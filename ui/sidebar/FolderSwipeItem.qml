import QtQuick 2.9
import QtQuick.Controls 2.2
import ".."

DrawerSwipeDelegate {
	id: delegate

	signal deleteCompleted()

	hoverEnabled: true

	contentItem: FolderItem {
		color: model.color
		text: model.name
		secondText: adaptCount(model.accounts.count)
		hovered: delegate.hovered

		onRemoveClicked: delegate.swipe.open(1.0)
	}

	swipe.left: RemovedSwipeItem {
		width: parent.width
		height: parent.height

		clip: true
		textOpacity: 2 * delegate.swipe.position
		progress: undoTimer.remaining / undoTimer.interval

		SwipeDelegate.onClicked: delegate.swipe.close()
		SwipeDelegate.onPressedChanged: undoTimer.stop()
	}

	TickingTimer {
		id: undoTimer
		interval: 8 * 1000 // ms
		onTriggered: delegate.deleteCompleted()
	}

	swipe.onCompleted: undoTimer.start()
}
