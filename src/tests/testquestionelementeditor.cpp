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
#include "testquestionelementeditor.h"
#include "../editors/ui_questionelementeditor.h"
#include "editors/questionelementeditor.h"
#include <QTest>

TestQuestionElementEditor::TestQuestionElementEditor(QObject *parent)
    : QObject(parent) {}

void TestQuestionElementEditor::testLoad() {
  {
    QJsonObject parameters;
    Element e{ElementType::QuestionElementType, 0, parameters};
    QuestionElementEditor editor{&e, {}};
    QVERIFY(editor.ui->qid_edit->text().isEmpty());
    QVERIFY(editor.ui->text_edit->text().isEmpty());
  }
  {
    QJsonObject parameters;
    parameters["id"] = "questionid";
    parameters["text"] = "thequestion";
    Element e{ElementType::QuestionElementType, 0, parameters};
    QuestionElementEditor editor{&e, {}};
    QVERIFY(editor.ui->qid_edit->text() == "questionid");
    QVERIFY(editor.ui->text_edit->text() == "thequestion");
  }
}

void TestQuestionElementEditor::testChange() {
  {
    QJsonObject parameters;
    Element e{ElementType::QuestionElementType, 0, parameters};
    QuestionElementEditor editor{&e, {}};
    editor.ui->qid_edit->setText("alpha");
    QVERIFY(e.parameters()["id"].toString() == "alpha");
  }
  {
    QJsonObject parameters;
    Element e{ElementType::QuestionElementType, 0, parameters};
    QuestionElementEditor editor{&e, {}};
    editor.ui->text_edit->setText("beta");
    QVERIFY(e.parameters()["text"] == "beta");
  }
}
