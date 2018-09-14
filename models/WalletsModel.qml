import QtQuick 2.0

ListModel {
	id: wallets

	property int selectedIndex: -1

	ListElement {
		name: "AIFE"
		color: "#2176c7"
		selected: false
		accounts: [
			ListElement {
				name: "PPR"
				login: "domain\\username"
			},
			ListElement {
				name: "PRD"
				login: "domain\\username"
			}
		]
	}

	ListElement {
		name: "CA-TS"
		color: "#738a05"
		selected: false
		accounts: [
			ListElement {
				name: "Standard"
				login: "domain\\username"
			}
		]
	}

	ListElement {
		name: "CNRS"
		color: "#259286"
		selected: false
		accounts: [
			ListElement {
				name: "CyberArk"
				login: "AD-BS\\A454593"
			},
			ListElement {
				name: "PMAD"
				login: "OUTSOURCING\\A454593"
			},
			ListElement {
				name: "SAaCon - iam"
				login: "A454593"
			}
		]
	}

	ListElement {
		name: "SAIL"
		color: "#c61c6f"
		selected: false
		accounts: []
	}

	ListElement {
		name: "Deleted"
		color: "transparent"
		selected: false
		accounts: []
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
