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
#ifndef ERRORELEMENTEDITOR_H
#define ERRORELEMENTEDITOR_H

#include "editor.h"
#include "models/element.h"
#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class ErrorElementEditor;
}

class ErrorElementEditor : public Editor {
  Q_OBJECT
  friend class TestErrorElementEditor;

public:
  explicit ErrorElementEditor(Element *e, const QStringList &validQuestionIds,
                              QWidget *parent = nullptr);
  ~ErrorElementEditor();

private slots:
  void onStartTimeChanged(const QDateTime &datetime);
  void onErrorTypeChanged(const QString &errortype);
  void onDiagnosticsChanged(const QString &diagnostics);
  void onSurveyItemChanged(QListWidgetItem *it);
  void onFakeLevelChanged(const QString &fakelevel);
  void onClearAfterChanged(int value);
  void onNotifyAfterChanged(int value);
  void onEfficiencyChanged(double value);
  void onSurveyDelayChanged(int value);
  void onRepeatNotifyChanged(int state);
  void onAllowLateRepairChanged(int state);
  void onLoaChanged(const QString &loa);
  void onLoaDelayChanged(int value);

private:
  Ui::ErrorElementEditor *ui;
  Element *m_element;
};

#endif // ERRORELEMENTEDITOR_H
