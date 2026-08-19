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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editors/editor.h"
#include "models/elementlist.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onOpenFile();
  void onSaveFile();
  void onSaveAsFile();
  void onNew();
  void onValidateScript();
  void onExit();
  void onDataChanged();
  void onSelectionChanged();
  void onAbout();
  void onRemoveEvent();
  void onDuplicateEvent();
  void onTimeChanged(Element *e);
  void onAddFilterElement();
  void onAddScriptElement();
  void onAddErrorElement();
  void onAddInterfaceElement();
  void onAddAdaptiveElement();
  void onAddCodeElement();
  void onAddDurationElement();
  void onAddControlElement();
  void onAddQuestionElement();
  void onAddAssistanceElement();
  void onAddAccessElement();
  void onAddMessageElement();
  void onAddPopupElement();
  void eventTableContextMenu(QPoint pos);
  void closeEvent(QCloseEvent *event) override;
#ifdef QT_TEST_ENABLED
  void runTests();
#endif

private:
  QStringList validQuestionIds();
  QStringList otherQuestionIds(Element *thiselement);
  void updateActionsAndTitle();
  void saveDataToFile();
  bool m_modified_flag{false};
  bool m_new_flag{true};

  Ui::MainWindow *ui;
  ElementList m_eventlist;
  QString m_filename{""};
  Editor *m_current_widget{nullptr};
  Element *m_current_element{nullptr};

  struct Snapshot {
    QList<Element *> data;
    int selected_row{-1};
    bool modified_flag{false};

    Snapshot() = default;
    Snapshot(const Snapshot &) = delete;
    Snapshot &operator=(const Snapshot &) = delete;

    ~Snapshot() {
        for (auto e : std::as_const(data)) {
            delete e;
        }
      data.clear();
    }
  };

  void takeSnapshot();
  void restoreSnapshot(const Snapshot &sn);
  void resetSnapshots();
  void undo();
  void redo();
  bool canUndo();
  bool canRedo();
  QList<Snapshot *> m_snapshots;
  int m_snapshot_index{-1};
  bool m_in_undoredo_operation{false};
};

#endif // MAINWINDOW_H
