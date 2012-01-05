/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Item {
    id: flipableelementtest
    anchors.fill: parent
    property string testtext: ""

    Flipable {
        id: flipableelement
        height: 250; width: 250
        anchors.centerIn: parent
        front: Rectangle { color: "green"; anchors.fill: parent; border.color: "gray"; border.width: 3; opacity: .9; radius: 20; clip: true }
        back: Rectangle { color: "red"; anchors.fill: parent; border.color: "gray"; border.width: 3; opacity: .9; radius: 20; clip: true }
        transform: Rotation {
            id: rotation
            origin.x: flipableelement.width/2
            origin.y: flipableelement.height/2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

    }
    transitions: Transition {
         NumberAnimation { target: rotation; property: "angle"; duration: 2000 }
     }

    SystemTestHelp { id: helpbubble; visible: statenum != 0
        anchors { top: parent.top; horizontalCenter: parent.horizontalCenter; topMargin: 50 }
    }
    BugPanel { id: bugpanel }

    states: [
        State { name: "start"; when: statenum == 1
            PropertyChanges { target: flipableelementtest
                testtext: "This is a Flipable element. At present it should be showing a green rectangle.\n"+
                "Next, let's flip the Flipable horizontally to show the back" }
        },
        State { name: "back"; when: statenum == 2
            PropertyChanges { target: rotation; angle: 180 }
            //FIXED PropertyChanges { target: bugpanel; bugnumber: "19901" }
            PropertyChanges { target: flipableelementtest
                testtext: "Flipable should now be showing a red rectangle.\n"+
                "Next, let's flip the Flipable to again show the front." }
        },
        State { name: "front"; when: statenum == 3
            PropertyChanges { target: flipableelementtest
                testtext: "Flipable should have flipped and now be showing a green rectangle.\n"+
                "Next, let's flip vertically." }
        },
        State { name: "backvertical"; when: statenum == 4
            PropertyChanges { target: rotation; axis.y: 0; axis.x: 1; angle: 180 }
            //FIXED PropertyChanges { target: bugpanel; bugnumber: "19901" }
            PropertyChanges { target: flipableelementtest
                testtext: "Flipable should have flipped vertically and now be showing a red rectangle.\n"+
                "Next, let's flip back." }
        },
        State { name: "frontvertical"; when: statenum == 5
            PropertyChanges { target: rotation; axis.y: 0; axis.x: 1; angle: 0 }
            PropertyChanges { target: flipableelementtest
                testtext: "Flipable should have flipped vertically and now be showing a green rectangle.\n"+
                "Next, let's restart the test." }
        }
    ]
}
