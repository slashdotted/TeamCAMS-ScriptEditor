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
#include "durationelementeditor.h"
#include "ui_durationelementeditor.h"

DurationElementEditor::DurationElementEditor(Element *e, QWidget *parent)
    : Editor(parent), m_element{e}, ui(new Ui::DurationElementEditor) {
  ui->setupUi(this);
  if (e->parameters().contains("seconds")) {
    ui->timeEdit->setTime(
        QTime(0, 0, 0).addSecs(e->parameters()["seconds"].toInt()));
  } else {
    m_element->parameters()["seconds"] = 1;
  }
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &DurationElementEditor::onDurationChanged);
}

DurationElementEditor::~DurationElementEditor() { delete ui; }

void DurationElementEditor::onDurationChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  auto newValue = QTime(0, 0, 0).secsTo(ui->timeEdit->time());
  if (m_element->parameters()["seconds"] != newValue) {
    m_element->parameters()["seconds"] = newValue;
    emit timeChanged(m_element);
  }
}
