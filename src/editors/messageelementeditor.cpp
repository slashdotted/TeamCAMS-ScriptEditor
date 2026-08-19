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
#include "messageelementeditor.h"
#include "ui_messageelementeditor.h"

MessageElementEditor::MessageElementEditor(Element *e, QWidget *parent)
    : Editor(parent), ui(new Ui::MessageElementEditor), m_element{e} {
  ui->setupUi(this);
  ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));

  if (m_element->parameters().contains("from")) {
    ui->senderEdit->setText(m_element->parameters()["from"].toString());
  }
  if (m_element->parameters().contains("to")) {
    ui->recipientEdit->setText(m_element->parameters()["to"].toString());
  }
  if (m_element->parameters().contains("text")) {
    ui->messageEdit->setText(m_element->parameters()["text"].toString());
  }
  connect(ui->timeEdit, &QDateTimeEdit::dateTimeChanged, this,
          &MessageElementEditor::onStartTimeChanged);
  connect(ui->senderEdit, &QLineEdit::textChanged, this,
          &MessageElementEditor::onSenderChanged);
  connect(ui->recipientEdit, &QLineEdit::textChanged, this,
          &MessageElementEditor::onRecipientChanged);
  connect(ui->messageEdit, &QLineEdit::textChanged, this,
          &MessageElementEditor::onMessageChanged);
}

MessageElementEditor::~MessageElementEditor() { delete ui; }

void MessageElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void MessageElementEditor::onSenderChanged() {
  m_element->parameters()["from"] = ui->senderEdit->text().toHtmlEscaped();
  emit dataChanged(m_element);
}

void MessageElementEditor::onRecipientChanged() {
  m_element->parameters()["to"] = ui->recipientEdit->text().toHtmlEscaped();
  emit dataChanged(m_element);
}

void MessageElementEditor::onMessageChanged() {
  m_element->parameters()["text"] = ui->messageEdit->text().toHtmlEscaped();
  emit dataChanged(m_element);
}
