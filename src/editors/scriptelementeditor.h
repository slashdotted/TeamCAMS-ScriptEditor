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
#ifndef SCRIPTELEMENTEDITOR_H
#define SCRIPTELEMENTEDITOR_H

#include "editor.h"
#include "models/element.h"
#include <QWidget>

namespace Ui {
class ScriptElementEditor;
}

class ScriptElementEditor : public Editor {
  Q_OBJECT
  friend class TestScriptElementEditor;

public:
  explicit ScriptElementEditor(Element *e, QWidget *parent = nullptr);
  ~ScriptElementEditor();

private slots:
  void onAdaptiveControlEnabledChanged();
  void onAdaptiveControlTypeChanged();
  void onMaxLOAChangeChanged();
  void onTxBaselineChanged();
  void onTxBaselineFaultChanged();
  void onLogBaselineChanged();
  void onLogBaselineFaultChanged();
  void onTxAChanged();
  void onTxBChanged();
  void onTxCChanged();
  void onTxDChanged();
  void onTxEChanged();
  void onLogAChanged();
  void onLogBChanged();
  void onLogCChanged();
  void onLogDChanged();
  void onLogEChanged();

private:
  Ui::ScriptElementEditor *ui;
  Element *m_element;
};

#endif // SCRIPTELEMENTEDITOR_H
