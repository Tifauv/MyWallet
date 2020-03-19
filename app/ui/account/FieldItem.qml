import QtQuick 2.12
import QtQuick.Controls 2.5
import org.kde.kirigami 2.8 as Kirigami

FieldItemForm {
	id: view
	
	property string name: "Field name"
	property string value: "Field value"
	
	property bool showRevealAction: false
    property bool showCopyAction: true

    property bool passwordVisible: false
	
	signal copyValue(string p_value)
	
	nameTxt.text: name
	valueTxt.sourceComponent: labelValue
	
	revealBtn.visible: showRevealAction
	revealBtn.onPressed: passwordVisible = !passwordVisible
	revealBtn.text: passwordVisible ? qsTr("Hide password") : qsTr("Reveal password")
	revealBtn.icon.name: passwordVisible ? "password-show-off" : "password-show-on"
	
	copyBtn.visible: showCopyAction
	copyBtn.onPressed: view.copyValue(value)
	
	visible: value.length > 0
	
	Component {
		id: labelValue
		
		Label {
			text: !showRevealAction || passwordVisible ? value : "\u25cf".repeat(value.length)
			leftPadding: Kirigami.Units.largeSpacing
		}
	}
	
	Component {
		id: linkValue
		
		Kirigami.UrlButton {
			url: value
			horizontalAlignment: Text.AlignHLeft
			leftPadding: Kirigami.Units.largeSpacing
		}
	}
	
	states: [
		State {
			name: "UrlValue"
			when: value.startsWith("http://") || value.startsWith("https://")
			
			PropertyChanges {
				target: valueTxt
				sourceComponent: linkValue
			}
		}
	]
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
