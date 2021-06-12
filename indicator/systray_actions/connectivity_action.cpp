/*
 * SPDX-FileCopyrightText: 2016 Aleix Pol Gonzalez <aleixpol@kde.org>
 * SPDX-FileCopyrightText: 2020 Piyush Aggarwal <piyushaggarwal002@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#include "connectivity_action.h"

ConnectivityAction::ConnectivityAction(DeviceDbusInterface* device)
    : QAction(nullptr)
    , m_connectivityiface(device->id())
{
    setCellularNetworkStrength(m_connectivityiface.cellularNetworkStrength());
    setCellularNetworkType(m_connectivityiface.cellularNetworkType());

    connect(&m_connectivityiface, &ConnectivityReportDbusInterface::refreshedProxy, this, [this]{
        setCellularNetworkStrength(m_connectivityiface.cellularNetworkStrength());
        setCellularNetworkType(m_connectivityiface.cellularNetworkType());
    });

    setIcon(QIcon::fromTheme(QStringLiteral("network-wireless")));

    ConnectivityAction::update();
}

void ConnectivityAction::update()
{
    if (m_cellularNetworkStrength < 0) {
        setText(i18nc("The fallback text to display in case the remote device does not have a cellular connection", "No Cellular Connectivity"));
    } else {
        setText(i18nc("Display the cellular connection type and an approximate percentage of signal strength","%1  | ~%2%", m_cellularNetworkType, m_cellularNetworkStrength * 25));
    }

    // set icon name

    QString iconName = QStringLiteral("network-mobile");

    if (m_cellularNetworkStrength < 0) {
        iconName += QStringLiteral("-off");
    } else {
        int signalStrength;
        switch (m_cellularNetworkStrength)
        {
            case 0 : signalStrength = 0; break;
            case 1 : signalStrength = 20; break;
            case 2 : signalStrength = 60; break;
            case 3 : signalStrength = 80; break;
            default : signalStrength = 100; break;
        }
        iconName += QStringLiteral("-") + QString::number(signalStrength);
    }

    if (m_cellularNetworkType == QStringLiteral("5G")) {
        // No icon for this case!
        iconName += QStringLiteral("-");
    } else if (m_cellularNetworkType == QStringLiteral("LTE")) {
        iconName += QStringLiteral("-lte");
    } else if (m_cellularNetworkType == QStringLiteral("HSPA")) {
        iconName += QStringLiteral("-hspa");
    } else if (m_cellularNetworkType == QStringLiteral("UMTS")) {
        iconName += QStringLiteral("-umts");
    } else if (m_cellularNetworkType == QStringLiteral("CDMA2000")) {
        // GSconnect just uses the 3g icon
        // No icon for this case!
        iconName += QStringLiteral("");
    } else if (m_cellularNetworkType == QStringLiteral("EDGE")) {
        iconName += QStringLiteral("-edge");
    } else if (m_cellularNetworkType == QStringLiteral("GPRS")) {
        iconName += QStringLiteral("-gprs");
    } else if (m_cellularNetworkType == QStringLiteral("GSM")) {
        // GSconnect just uses the 2g icon
        // No icon for this case!
        iconName += QStringLiteral("");
    } else if (m_cellularNetworkType == QStringLiteral("CDMA")) {
        // GSconnect just uses the 2g icon
        // No icon for this case!
        iconName += QStringLiteral("");
    } else if (m_cellularNetworkType == QStringLiteral("iDEN")) {
        // GSconnect just uses the 2g icon
        // No icon for this case!
        iconName += QStringLiteral("");
    } else {
        // We didn't recognize the network type. Don't append anything.
        iconName += QStringLiteral("");
    }
    qDebug() << "iconName ="<< iconName;

    setIcon(QIcon::fromTheme(iconName));

}

void ConnectivityAction::setCellularNetworkStrength(int cellularNetworkStrength)
{
    m_cellularNetworkStrength = cellularNetworkStrength;
    update();
}

void ConnectivityAction::setCellularNetworkType(QString cellularNetworkType)
{
    m_cellularNetworkType = cellularNetworkType;
    update();
}