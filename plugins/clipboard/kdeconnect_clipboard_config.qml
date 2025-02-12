/**
 * SPDX-FileCopyrightText: 2022 Yuchen Shi <bolshaya_schists@mail.gravitide.co>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import org.kde.kirigami 2.5 as Kirigami
import org.kde.kdeconnect 1.0

Kirigami.FormLayout {

    property string device

    KdeConnectPluginConfig {
        id: config
        deviceId: device
        pluginName: "kdeconnect_clipboard"
    }

    Component.onCompleted: {
        unknown.checked = config.get("sendUnknown", true)
        password.checked = config.get("sendPassword", true)
    }

    CheckBox {
        id: password
        text: i18n("Passwords (as marked by password managers)")
        onClicked: config.set("sendPassword", checked)
    }

    CheckBox {
        id: unknown
        text: i18n("Anything else")
        onClicked: config.set("sendUnknown", checked)
    }
}
