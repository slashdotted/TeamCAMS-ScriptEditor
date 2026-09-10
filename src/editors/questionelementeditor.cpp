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
#include "questionelementeditor.h"
#include "ui_questionelementeditor.h"
#include <QLineEdit>

QuestionElementEditor::QuestionElementEditor(
    Element *e, const QStringList &existingquestionids, QWidget *parent)
    : Editor(parent), m_existingquestionids{existingquestionids}, m_element{e},
      ui(new Ui::QuestionElementEditor) {
  ui->setupUi(this);

  ui->duplicateErrorLabel->setVisible(false);
  if (m_element->parameters().contains("id")) {
      QString qid{m_element->parameters()["id"].toString().toLower()};
      ui->qid_edit->setText(qid);
      if (!qid.isEmpty() && m_existingquestionids.contains(qid)) {
          ui->duplicateErrorLabel->setVisible(true);
      }
  }

  if (m_element->parameters().contains("text")) {
    ui->text_edit->setText(m_element->parameters()["text"].toString());
  }

  connect(ui->qid_edit, &QLineEdit::textChanged, this,
          &QuestionElementEditor::onQuestionIdChanged);
  connect(ui->text_edit, &QLineEdit::textChanged, this,
          &QuestionElementEditor::onQuestionTextChanged);
}

QuestionElementEditor::~QuestionElementEditor() { delete ui; }

void QuestionElementEditor::onQuestionIdChanged(const QString &qid) {
  if (qid.trimmed().isEmpty()) {
    m_element->parameters().remove("id");
    emit dataChanged(m_element);
  } else {
      auto questionId{qid.toLower()};
      m_element->parameters()["id"] = questionId;
      if (m_existingquestionids.contains(questionId)) {
          ui->duplicateErrorLabel->setVisible(true);
      } else {
          ui->duplicateErrorLabel->setVisible(false);
          m_element->parameters()["id"] = questionId;
          emit dataChanged(m_element);
      }
  }
}

void QuestionElementEditor::onQuestionTextChanged(const QString &text) {

  if (text.trimmed().isEmpty()) {
    m_element->parameters().remove("text");
  } else {
    m_element->parameters()["text"] = text;
  }
  emit dataChanged(m_element);
}
