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
#include "codeelementeditor.h"
#include "ui_codeelementeditor.h"

CodeElementEditor::CodeElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::CodeElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  if (m_element->parameters().contains("code")) {
    ui->code_textEdit->setText(m_element->parameters()["code"].toString());
  }
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &CodeElementEditor::onStartTimeChanged);
  connect(ui->code_textEdit, &QTextEdit::textChanged, this,
          &CodeElementEditor::onCodeChanged);
}

CodeElementEditor::~CodeElementEditor() { delete ui; }

void CodeElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void CodeElementEditor::onCodeChanged() {
  m_element->parameters()["code"] = ui->code_textEdit->toPlainText();
  emit dataChanged(m_element);
}
