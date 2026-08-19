// TeamCAMS - reborn Cabin Air Management System
// Copyright (C) 2015-2026  Amos Brocco,
//                          Cognitive Ergonomics and Work Psychology Team,
//                          Psychology Department of Fribourg University,
//                          Switzerland / Department of Innovative Technologies
//                          University of Applied Sciences and Arts of Southern
//                          Switzerland, Contact: amos.brocco@supsi.ch
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
#include "testinterfaceelementeditor.h"
#include "../editors/ui_interfaceelementeditor.h"
#include "editors/interfaceelementeditor.h"
#include <QTest>

TestInterfaceElementEditor::TestInterfaceElementEditor(QObject *parent)
    : QObject(parent) {}

void TestInterfaceElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenscope");
    QVERIFY(editor.ui->users->text().isEmpty());
    QVERIFY(!editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->enabledCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isChecked());
    QVERIFY(editor.ui->visibleCheck->isEnabled());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 32, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 32);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenscope");
    QVERIFY(editor.ui->users->text().isEmpty());
    QVERIFY(!editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->enabledCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isChecked());
    QVERIFY(editor.ui->visibleCheck->isEnabled());
  }
  {
    QJsonObject parameters;
    parameters["display"] = "oxygenpanel";
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenpanel");
    QVERIFY(editor.ui->users->text().isEmpty());
    QVERIFY(editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->enabledCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isEnabled());
  }
  {
    QJsonObject parameters;
    parameters["users"] = "anuser";
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenscope");
    QVERIFY(editor.ui->users->text() == "anuser");
    QVERIFY(!editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->enabledCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isChecked());
    QVERIFY(editor.ui->visibleCheck->isEnabled());
  }
  {
    QJsonObject parameters;
    parameters["enabled"] = true;
    parameters["display"] = "oxygenpanel";
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenpanel");
    QVERIFY(editor.ui->users->text().isEmpty());
    QVERIFY(editor.ui->enabledCheck->isEnabled());
    QVERIFY(editor.ui->enabledCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isChecked());
    QVERIFY(!editor.ui->visibleCheck->isEnabled());
  }
  {
    QJsonObject parameters;
    parameters["visible"] = true;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->interfaceElement->currentText() == "oxygenscope");
    QVERIFY(editor.ui->users->text().isEmpty());
    QVERIFY(!editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->enabledCheck->isChecked());
    QVERIFY(editor.ui->visibleCheck->isChecked());
    QVERIFY(editor.ui->visibleCheck->isEnabled());
  }
}

void TestInterfaceElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    editor.ui->timeEdit->setTime(QTime{0, 0, 56});
    QVERIFY(e.time() == 56);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    editor.ui->interfaceElement->setCurrentText("oxygenpanel");
    QVERIFY(editor.ui->enabledCheck->isEnabled());
    QVERIFY(!editor.ui->visibleCheck->isEnabled());
    QVERIFY(e.parameters()["display"] == "oxygenpanel");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    editor.ui->users->setText("someuser");
    QVERIFY(e.parameters()["users"] == "someuser");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    editor.ui->visibleCheck->setChecked(true);
    QVERIFY(e.parameters()["visible"].toBool());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::InterfaceElementType, 0, parameters};
    InterfaceElementEditor editor{&e};
    editor.ui->interfaceElement->setCurrentText("oxygenpanel");
    editor.ui->enabledCheck->setChecked(true);
    QVERIFY(e.parameters()["enabled"].toBool());
  }
}
