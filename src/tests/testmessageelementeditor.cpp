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
#include "testmessageelementeditor.h"
#include "../editors/ui_messageelementeditor.h"
#include "editors/messageelementeditor.h"
#include <QTest>

TestMessageElementEditor::TestMessageElementEditor(QObject *parent)
    : QObject(parent) {}

void TestMessageElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->senderEdit->text().isEmpty());
    QVERIFY(editor.ui->recipientEdit->text().isEmpty());
    QVERIFY(editor.ui->messageEdit->text().isEmpty());
  }
  {
    QJsonObject parameters;
    parameters["from"] = "foo";
    parameters["to"] = "bar";
    parameters["text"] = "hello";
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    QVERIFY(QTime(0, 0, 0).secsTo(editor.ui->timeEdit->time()) == 0);
    QVERIFY(editor.ui->senderEdit->text() == "foo");
    QVERIFY(editor.ui->recipientEdit->text() == "bar");
    QVERIFY(editor.ui->messageEdit->text() == "hello");
  }
}

void TestMessageElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    editor.ui->timeEdit->setTime(QTime{0, 0, 44});
    QVERIFY(e.time() == 44);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    editor.ui->senderEdit->setText("ducky");
    QVERIFY(e.parameters()["from"] == "ducky");
    QVERIFY(editor.ui->recipientEdit->text().isEmpty());
    QVERIFY(editor.ui->messageEdit->text().isEmpty());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    editor.ui->recipientEdit->setText("dacky");
    QVERIFY(e.parameters()["to"] == "dacky");
    QVERIFY(editor.ui->senderEdit->text().isEmpty());
    QVERIFY(editor.ui->messageEdit->text().isEmpty());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::MessageElementType, 0, parameters};
    MessageElementEditor editor{&e};
    editor.ui->messageEdit->setText("docky");
    QVERIFY(e.parameters()["text"] == "docky");
    QVERIFY(editor.ui->recipientEdit->text().isEmpty());
    QVERIFY(editor.ui->senderEdit->text().isEmpty());
  }
}
