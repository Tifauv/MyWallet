import QtQuick 2.0

Item {
	id: widget

	property int interval: 10000 // ms
	property alias precision: timer.interval
	property int remaining: 10000 // ms
	property alias running: timer.running
	property alias triggeredOnStart: timer.triggeredOnStart

	signal triggered()

	Timer {
		id: timer

		interval: 64
		repeat: true
		running: false

		onTriggered: {
			widget.remaining -= timer.interval
			console.log("Timer triggered, remaining " + widget.remaining + " ms");
			if (widget.remaining <= 0) {
				timer.stop();
				widget.triggered();
			}
		}
	}


	function start() {
		widget.remaining = widget.interval;
		timer.start();
	}


	function stop() {
		timer.stop();
	}


	function restart() {
		widget.remaining = widget.interval;
		timer.restart();
	}
}
