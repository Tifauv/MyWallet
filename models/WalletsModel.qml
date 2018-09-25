import QtQuick 2.0

ListModel {
	id: wallets

	ListElement {
		name: "AIFE"
		color: "#2176c7"
		accounts: [
			ListElement {
				name: "PPR"
				login: "domain\\username"
				password: "AIFE-PPR-PWD"
			},
			ListElement {
				name: "PRD"
				login: "domain\\username"
				password: "AIFE-PRD-PWD"
			}
		]
	}

	ListElement {
		name: "CA-TS"
		color: "#738a05"
		accounts: [
			ListElement {
				name: "Standard"
				login: "domain\\username"
				password: "CA--TS-Standard-PWD"
			}
		]
	}

	ListElement {
		name: "CNRS"
		color: "#259286"
		accounts: [
			ListElement {
				name: "CyberArk"
				login: "AD-BS\\A454593"
				password: "CNRS-CyberArk-PWD"
			},
			ListElement {
				name: "PMAD"
				login: "OUTSOURCING\\A454593"
				password: "CNRS-PMAD-PWD"
			},
			ListElement {
				name: "SAaCon - iam"
				login: "A454593"
				password: "CNRS-SAaCon-PWD"
			}
		]
	}

	ListElement {
		name: "SAIL"
		color: "#c61c6f"
		accounts: []
	}

	ListElement {
		name: "Deleted"
		color: "transparent"
		accounts: []
	}
}
