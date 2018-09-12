import QtQuick 2.0

ListModel {
	id: wallets

	property int selectedIndex: -1

	ListElement {
		name: "AIFE"
		color: "#2176c7"
		selected: false
	}

	ListElement {
		name: "APHP"
		color: "#738a05"
		selected: false
	}

	ListElement {
		name: "Auxylium"
		color: "#b11c24"
		selected: false
	}

	ListElement {
		name: "CA-TS"
		color: "#738a05"
		selected: false
	}

	ListElement {
		name: "CNOP"
		color: "#738a05"
		selected: false
	}

	ListElement {
		name: "CNRS"
		color: "#259286"
		selected: false
	}

	ListElement {
		name: "Neptune"
		color: "#2176c7"
		selected: false
	}

	ListElement {
		name: "SAIL"
		color: "#c61c6f"
		selected: false
	}

	ListElement {
		name: "Deleted"
		color: "transparent"
		selected: false
	}


	function select(index) {
		if (index !== selectedIndex) {
			wallets.get(index).selected = true;
			if (selectedIndex >= 0 && selectedIndex < wallets.count)
				wallets.get(selectedIndex).selected = false;
			selectedIndex = index;
		}
	}
}
