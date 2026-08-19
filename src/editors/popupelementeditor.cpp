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
#include "popupelementeditor.h"
#include "ui_popupelementeditor.h"
#include <qlineedit.h>

PopupElementEditor::PopupElementEditor(Element *e, QWidget *parent)
    : Editor(parent)
    , m_element{e}
    , ui(new Ui::PopupElementEditor)
{
    ui->setupUi(this);

    ui->timeEdit->setTime(QTime(0, 0, 0).addSecs(m_element->time()));
    if (m_element->parameters().contains("url") && m_element->parameters()["url"].isString()) {
        ui->urlEdit->setText(m_element->parameters()["url"].toString());
    } else {
        onPopupUrlChanged(ui->urlEdit->text());
    }
    if (m_element->parameters().contains("title") && m_element->parameters()["title"].isString()) {
        ui->titleEdit->setText(m_element->parameters()["title"].toString());
    } else {
        onPopupTitleChanged(ui->titleEdit->text());
    }
    connect(ui->urlEdit, &QLineEdit::textChanged, this, &PopupElementEditor::onPopupUrlChanged);
    connect(ui->titleEdit, &QLineEdit::textChanged, this, &PopupElementEditor::onPopupTitleChanged);
    connect(ui->timeEdit,
            &QDateTimeEdit::dateTimeChanged,
            this,
            &PopupElementEditor::onStartTimeChanged);
    emit dataChanged(m_element);
}

PopupElementEditor::~PopupElementEditor() { delete ui; }

void PopupElementEditor::onStartTimeChanged(const QDateTime &datetime) {
  Q_UNUSED(datetime)
  m_element->time(QTime(0, 0, 0).secsTo(ui->timeEdit->time()));
  emit timeChanged(m_element);
}

void PopupElementEditor::onPopupUrlChanged(const QString &url)
{
    m_element->parameters()["url"] = url;
    emit dataChanged(m_element);
}

void PopupElementEditor::onPopupTitleChanged(const QString &title)
{
    m_element->parameters()["title"] = title;
    emit dataChanged(m_element);
}
