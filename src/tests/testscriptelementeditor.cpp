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
#include "testscriptelementeditor.h"
#include "../editors/ui_scriptelementeditor.h"
#include "editors/scriptelementeditor.h"
#include <QTest>

TestScriptElementEditor::TestScriptElementEditor(QObject *parent)
    : QObject(parent) {}

void TestScriptElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["adaptive"] = true;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["adaptiveControl"] = "transmission";
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "transmission");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["adaptiveControlMaxChange"] = 3;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 3);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactionbaselinetransmission"] = 2355;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 2355);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactionbaselinetransmissionDuringFault"] = 3333;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 3333);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactionbaselinelogging"] = 1234;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 1234);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactionbaselineloggingduringfault"] = 4321;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 4321);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimetransmissionpredefinedintervals_a"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 42);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimetransmissionpredefinedintervals_b"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 42);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimetransmissionpredefinedintervals_c"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 42);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimetransmissionpredefinedintervals_d"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 42);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimetransmissionpredefinedintervals_e"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 42);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimeloggingpredefinedintervals_a"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 42);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimeloggingpredefinedintervals_b"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 42);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimeloggingpredefinedintervals_c"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 42);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimeloggingpredefinedintervals_d"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 42);
    QVERIFY(editor.ui->logE->value() == 0);
  }
  {
    QJsonObject parameters;
    parameters["reactiontimeloggingpredefinedintervals_e"] = 42;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    QVERIFY(!editor.ui->adaptiveControlEnabled->isChecked());
    QVERIFY(editor.ui->adaptiveControlType->currentText() == "none");
    QVERIFY(editor.ui->maxLOAChange->value() == 0);
    QVERIFY(editor.ui->txBaseline->value() == 0);
    QVERIFY(editor.ui->txBaselineFault->value() == 0);
    QVERIFY(editor.ui->logBaseline->value() == 0);
    QVERIFY(editor.ui->logBaselineFault->value() == 0);
    QVERIFY(editor.ui->txA->value() == 0);
    QVERIFY(editor.ui->txB->value() == 0);
    QVERIFY(editor.ui->txC->value() == 0);
    QVERIFY(editor.ui->txD->value() == 0);
    QVERIFY(editor.ui->txE->value() == 0);
    QVERIFY(editor.ui->logA->value() == 0);
    QVERIFY(editor.ui->logB->value() == 0);
    QVERIFY(editor.ui->logC->value() == 0);
    QVERIFY(editor.ui->logD->value() == 0);
    QVERIFY(editor.ui->logE->value() == 42);
  }
}

void TestScriptElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->adaptiveControlEnabled->setChecked(true);
    QVERIFY(e.parameters()["adaptive"].toBool());
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->adaptiveControlType->setCurrentText("logging");
    QVERIFY(e.parameters()["adaptiveControl"] == "logging");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->maxLOAChange->setValue(2);
    QVERIFY(e.parameters()["adaptiveControlMaxChange"] == 2);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txBaseline->setValue(1234);
    QVERIFY(e.parameters()["reactionbaselinetransmission"] == 1234);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logBaseline->setValue(1234);
    QVERIFY(e.parameters()["reactionbaselinelogging"] == 1234);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txBaselineFault->setValue(1234);
    QVERIFY(e.parameters()["reactionbaselinetransmissionDuringFault"] == 1234);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logBaselineFault->setValue(1234);
    QVERIFY(e.parameters()["reactionbaselineloggingduringfault"] == 1234);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txA->setValue(5678);
    QVERIFY(e.parameters()["reactiontimetransmissionpredefinedintervals_a"] ==
            5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txB->setValue(5678);
    QVERIFY(e.parameters()["reactiontimetransmissionpredefinedintervals_b"] ==
            5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txC->setValue(5678);
    QVERIFY(e.parameters()["reactiontimetransmissionpredefinedintervals_c"] ==
            5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txD->setValue(5678);
    QVERIFY(e.parameters()["reactiontimetransmissionpredefinedintervals_d"] ==
            5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->txE->setValue(5678);
    QVERIFY(e.parameters()["reactiontimetransmissionpredefinedintervals_e"] ==
            5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logA->setValue(5678);
    QVERIFY(e.parameters()["reactiontimeloggingpredefinedintervals_a"] == 5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logB->setValue(5678);
    QVERIFY(e.parameters()["reactiontimeloggingpredefinedintervals_b"] == 5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logC->setValue(5678);
    QVERIFY(e.parameters()["reactiontimeloggingpredefinedintervals_c"] == 5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logD->setValue(5678);
    QVERIFY(e.parameters()["reactiontimeloggingpredefinedintervals_d"] == 5678);
  }
  {
    QJsonObject parameters;
    Element e{ElementType::ScriptElementType, 0, parameters};
    ScriptElementEditor editor{&e};
    editor.ui->logE->setValue(5678);
    QVERIFY(e.parameters()["reactiontimeloggingpredefinedintervals_e"] == 5678);
  }
}
