/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Lars Uebernickel <lars.uebernickel@canonical.com>
 */


#include "plugin.h"
#include "gsettings-qml.h"

void GSettingsQmlPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<GSettingsQml>(uri, 1, 0, "GSettings");
    qmlRegisterUncreatableType<GSettingsSchemaQml>(uri, 1, 0, "GSettingsSchema",
                                                   QStringLiteral("GSettingsSchema can only be used inside of a GSettings component"));
}
