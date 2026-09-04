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
#include "mainwindow.h"
#include "editors/accesselementeditor.h"
#include "editors/adaptiveelementeditor.h"
#include "editors/assistanceelementeditor.h"
#include "editors/codeelementeditor.h"
#include "editors/controlelementeditor.h"
#include "editors/durationelementeditor.h"
#include "editors/errorelementeditor.h"
#include "editors/filterelementeditor.h"
#include "editors/interfaceelementeditor.h"
#include "editors/messageelementeditor.h"
#include "editors/popupelementeditor.h"
#include "editors/questionelementeditor.h"
#include "editors/scriptelementeditor.h"
#include "gui/timelinewidget.h"
#include "io/xmlconfigwriter.h"
#ifdef QT_TEST_ENABLED
#include "tests/testaccesselementeditor.h"
#include "tests/testadaptiveelementeditor.h"
#include "tests/testassistanceelementeditor.h"
#include "tests/testcodeelementeditor.h"
#include "tests/testcontrolelementeditor.h"
#include "tests/testerrorelementeditor.h"
#include "tests/testfilterelementeditor.h"
#include "tests/testinterfaceelementeditor.h"
#include "tests/testmessageelementeditor.h"
#include "tests/testpopupelementeditor.h"
#include "tests/testquestionelementeditor.h"
#include "tests/testscriptelementeditor.h"
#include <QTest>
#endif
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaObject>
#include <QProgressDialog>
#include <QTemporaryFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->frame->setLayout(new QGridLayout(ui->frame));
  ui->tableView->setModel(&m_eventlist);
  ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->horizontalHeader()->setSectionResizeMode(3,
                                                          QHeaderView::Stretch);
  ui->tableView->setColumnWidth(0, 150);
  ui->tableView->setColumnWidth(1, 25);
  ui->tableView->setColumnWidth(2, 125);
  ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

  auto *layout = new QVBoxLayout(ui->timelineContainer);
  ui->timelineContainer->setMinimumHeight(90);
  ui->timelineContainer->setFixedHeight(90);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  TimelineWidget *timeline = new TimelineWidget(ui->timelineContainer);
  ui->timelineContainer->layout()->addWidget(timeline);

  timeline->setModel(&m_eventlist);

  connect(timeline, &TimelineWidget::eventSelected, this, [this](Element *el) {
    int row = m_eventlist.indexOf(el);

    if (row < 0)
      return;

    QModelIndex idx = m_eventlist.index(row, 0);

    ui->tableView->selectionModel()->select(
        idx, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

    ui->tableView->scrollTo(idx);
  });

  connect(ui->tableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged, this,
          [this, timeline](const QModelIndex &current, const QModelIndex &) {
            if (!current.isValid())
              return;
            Element *el = m_eventlist.elementAt(current.row());
            timeline->selectElement(el);
          });

  connect(ui->actionLoad_script, &QAction::triggered, this,
          &MainWindow::onOpenFile);
  connect(ui->actionSave_script, &QAction::triggered, this,
          &MainWindow::onSaveFile);
  connect(ui->actionSave_script_as, &QAction::triggered, this,
          &MainWindow::onSaveAsFile);
  connect(ui->actionNew_script, &QAction::triggered, this, &MainWindow::onNew);
  connect(ui->actionValidate_script, &QAction::triggered, this,
          &MainWindow::onValidateScript);
  connect(ui->actionScript, &QAction::triggered, this,
          &MainWindow::onAddScriptElement);
  connect(ui->actionError, &QAction::triggered, this,
          &MainWindow::onAddErrorElement);
  connect(ui->actionInterface, &QAction::triggered, this,
          &MainWindow::onAddInterfaceElement);
  connect(ui->actionAdaptive, &QAction::triggered, this,
          &MainWindow::onAddAdaptiveElement);
  connect(ui->actionCode, &QAction::triggered, this,
          &MainWindow::onAddCodeElement);
  connect(ui->actionAccess, &QAction::triggered, this,
          &MainWindow::onAddAccessElement);
  connect(ui->actionMessage, &QAction::triggered, this,
          &MainWindow::onAddMessageElement);
  connect(ui->actionDuration, &QAction::triggered, this,
          &MainWindow::onAddDurationElement);
  connect(ui->actionControl, &QAction::triggered, this,
          &MainWindow::onAddControlElement);
  connect(ui->actionQuestion, &QAction::triggered, this,
          &MainWindow::onAddQuestionElement);
  connect(ui->actionAssistance, &QAction::triggered, this,
          &MainWindow::onAddAssistanceElement);
  connect(ui->actionactionPopup, &QAction::triggered, this,
          &MainWindow::onAddPopupElement);
  connect(ui->actionFilter, &QAction::triggered, this,
          &MainWindow::onAddFilterElement);
  connect(ui->actionAbout_TeamCAMS_Script_Editor, &QAction::triggered, this,
          &MainWindow::onAbout);
  connect(ui->actionRemove_event, &QAction::triggered, this,
          &MainWindow::onRemoveEvent);
  connect(ui->tableView, &QTableView::customContextMenuRequested, this,
          &MainWindow::eventTableContextMenu);
  connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undo);
  connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redo);
  connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
  connect(ui->tableView->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          &MainWindow::onSelectionChanged);
#ifdef QT_TEST_ENABLED
  connect(ui->actionRun_tests, &QAction::triggered, this,
          &MainWindow::runTests);
#else
  ui->actionRun_tests->setEnabled(false);
  ui->actionRun_tests->setVisible(false);
#endif
  connect(ui->actionDuplicateEvent, &QAction::triggered, this,
          &MainWindow::onDuplicateEvent);
  connect(ui->actionHelp, &QAction::triggered, [=]() {
    QString link = "https://syscall.org/doku.php/teamcamseditor";
    QDesktopServices::openUrl(QUrl(link));
  });
  ui->tableView->setDragEnabled(true);
  resetSnapshots();
  updateActionsAndTitle();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onOpenFile() {
  int ret{-1};
  if (m_modified_flag) {
    QMessageBox msgBox{this};
    msgBox.setText(tr("This will discard the existing configuration"));
    msgBox.setWindowTitle(tr("Save changes?"));
    msgBox.setInformativeText(
        tr("Do you want to save changes before continuing?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    ret = msgBox.exec();
    if (ret == QMessageBox::Cancel) {
      return;
    }
    if (ret == QMessageBox::Yes) {
      onSaveFile();
    }
  }
  if (!m_modified_flag || ret == QMessageBox::Yes || ret == QMessageBox::No) {
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open script"), "", tr("*.xml"));
    if (fileName != "") {
      QFile file{fileName};
      if (!QFile::exists(fileName)) {
        QMessageBox::critical(QApplication::activeWindow(), tr("Error"),
                              tr("Cannot open %1").arg(fileName),
                              QMessageBox::Ok);
        return;
      }
      if (m_eventlist.open(file)) {
        m_filename = fileName;
        m_modified_flag = false;
        resetSnapshots();
        updateActionsAndTitle();
        if (m_eventlist.count() > 0) {
          ui->tableView->selectRow(0);
        } else {
          onSelectionChanged();
        }
      } else {
        QMessageBox::critical(
            this, tr("Cannot open file"),
            tr("Cannot read configuration from file %1").arg(fileName));
      }
    }
  }
}

void MainWindow::onSaveFile() {
  if (m_filename != "") {
    saveDataToFile();
  } else {
    onSaveAsFile();
  }
}

void MainWindow::onSaveAsFile() {
  QFileDialog dialog(this, tr("Save script"), "", tr("*.xml"));
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setDefaultSuffix("xml");
  if (dialog.exec()) {
    QString fileName{dialog.selectedFiles().at(0)};
    if (fileName != "") {
      m_filename = fileName;
      saveDataToFile();
    }
  }
}

void MainWindow::onNew() {
  if (m_modified_flag) {
    QMessageBox msgBox{this};
    msgBox.setText(tr("This will discard the existing configuration"));
    msgBox.setWindowTitle(tr("Save changes?"));
    msgBox.setInformativeText(
        tr("Do you want to save changes before continuing?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Cancel) {
      return;
    }
    if (ret == QMessageBox::Yes) {
      onSaveFile();
    }
  }

  m_new_flag = true;
  m_filename = "";
  m_eventlist.clear();
  m_modified_flag = false;
  resetSnapshots();
  updateActionsAndTitle();
  onSelectionChanged();
}

void MainWindow::onValidateScript() {
  ElementList list;
  QTemporaryFile file;
  if (file.open()) {
    QXmlStreamWriter sw{&file};
    XMLConfigWriter::write(sw, m_eventlist);
    file.close();
    if (!list.open(file, true)) {
      ui->tableView->selectRow(list.count());
    } else {
      QMessageBox::information(QApplication::activeWindow(),
                               tr("Validation successful"),
                               tr("The script is valid"), QMessageBox::Ok);
    }
  }
}

void MainWindow::onExit() {
  if (m_modified_flag) {
    QMessageBox msgBox{this};
    msgBox.setText(tr("You have unsaved changes"));
    msgBox.setInformativeText(
        tr("Do you want to save your data before exiting?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
      onSaveFile();
      QApplication::quit();
    } else if (ret == QMessageBox::No) {
      QApplication::quit();
    }
  } else {
    QApplication::quit();
  }
}

void MainWindow::onDataChanged() {
  m_new_flag = false;
  ui->actionDuration->setEnabled(m_eventlist.count(DurationElementType) < 1);
  ui->actionScript->setEnabled(m_eventlist.count(ScriptElementType) < 1);
  if (!m_in_undoredo_operation) {
    m_modified_flag = true;
    takeSnapshot();
    updateActionsAndTitle();
  }
}

void MainWindow::onSelectionChanged() {
  if (!m_in_undoredo_operation) {
    if ((ui->tableView->selectionModel()->selectedRows().count() == 1) &&
        ui->tableView->selectionModel()->selectedRows().first().isValid()) {
      int row = ui->tableView->selectionModel()->selectedRows().first().row();
      if (row >= 0) {
        Element *el{m_eventlist.elementAt(row)};
        if (el == m_current_element) {
          return;
        }
        if (m_current_widget != nullptr) {
          ui->frame->layout()->removeWidget(m_current_widget);
          delete m_current_widget;
          m_current_widget = nullptr;
        }
        m_current_element = el;
        switch (el->type()) {
        case ScriptElementType:
          m_current_widget = new ScriptElementEditor(el, this);
          break;
        case ErrorElementType:
          m_current_widget =
              new ErrorElementEditor(el, validQuestionIds(), this);
          break;
        case InterfaceElementType:
          m_current_widget = new InterfaceElementEditor(el, this);
          break;
        case AdaptiveElementType:
          m_current_widget = new AdaptiveElementEditor(el, this);
          break;
        case CodeElementType:
          m_current_widget = new CodeElementEditor(el, this);
          break;
        case DurationElementType:
          m_current_widget = new DurationElementEditor(el, this);
          break;
        case ControlElementType:
          m_current_widget = new ControlElementEditor(el, this);
          break;
        case QuestionElementType:
          m_current_widget =
              new QuestionElementEditor(el, otherQuestionIds(el), this);
          break;
        case AssistanceElementType:
          m_current_widget = new AssistanceElementEditor(el, this);
          break;
        case FilterElementType:
          m_current_widget = new FilterElementEditor(el, this);
          break;
        case MessageElementType:
          m_current_widget = new MessageElementEditor(el, this);
          break;
        case AccessElementType:
          m_current_widget = new AccessElementEditor(el, this);
          break;
        case PopupElementType:
            m_current_widget = new PopupElementEditor(el, this);
            break;
        }
        if (m_current_widget != nullptr) {
          connect(m_current_widget, &Editor::timeChanged, this,
                  &MainWindow::onTimeChanged);
          connect(m_current_widget, &Editor::dataChanged, &m_eventlist,
                  &ElementList::update);
          connect(m_current_widget, &Editor::timeChanged, this,
                  &MainWindow::onDataChanged);
          connect(m_current_widget, &Editor::dataChanged, this,
                  &MainWindow::onDataChanged);
          ui->frame->layout()->addWidget(m_current_widget);
        }
      }
    } else {
      if (m_current_widget != nullptr) {
        ui->frame->layout()->removeWidget(m_current_widget);
        delete m_current_widget;
        m_current_widget = nullptr;
        m_current_element = nullptr;
      }
    }
  }
}

void MainWindow::onAbout() {
  QMessageBox *msgBox = new QMessageBox(this);
  msgBox->setIcon(QMessageBox::NoIcon);
  msgBox->setWindowTitle(tr("About TeamCAMS"));
  msgBox->setText(
      tr("<h3>TeamCAMS Script Editor 2026.08</h3>"

         "<p>"
         "Copyright &copy; 2015-2026 "
         "<b>Amos Brocco</b> / University of Fribourg (Switzerland)."
         "</p>"

         "<p>"
         "This software is free software released under the terms of the "
         "<b>GNU General Public License version 3 (GPLv3)</b>. "
         "You are free to use, study, modify and redistribute it under the "
         "conditions of that license."
         "</p>"

         "<p>"
         "<b>Disclaimer:</b> This program is provided <i>AS IS</i>, without "
         "any express or implied warranty, including but not limited to the "
         "warranties of merchantability, fitness for a particular purpose, "
         "and non-infringement."
         "</p>"));
  msgBox->setStandardButtons(QMessageBox::Ok);
  msgBox->setAttribute(Qt::WA_DeleteOnClose);
  msgBox->open();
}

void MainWindow::onRemoveEvent() {
  if (ui->tableView->selectionModel()->selectedRows().size() == 0)
    return;
  auto k{ui->tableView->selectionModel()->selectedRows()};
  QList<int> rows;
  for (auto it{k.begin()}; it != k.end(); ++it) {
    rows.push_back(it->row());
  }
  std::sort(rows.begin(), rows.end());
  std::reverse(rows.begin(), rows.end());
  for (auto r : rows) {
    m_eventlist.remove(r);
  }
  onDataChanged();
}

void MainWindow::onDuplicateEvent() {
  if (ui->tableView->selectionModel()->selectedRows().size() == 0)
    return;
  m_eventlist.duplicate(
      ui->tableView->selectionModel()->selectedIndexes().at(0).row());
  onDataChanged();
}

void MainWindow::onTimeChanged(Element *e) {
  m_eventlist.sortElements();
  ui->tableView->selectRow(m_eventlist.indexOf(e));
}

void MainWindow::onAddFilterElement() {
  ui->tableView->selectRow(m_eventlist.addElement(FilterElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddScriptElement() {
  ui->tableView->selectRow(m_eventlist.addElement(ScriptElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddErrorElement() {
  ui->tableView->selectRow(m_eventlist.addElement(ErrorElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddInterfaceElement() {
  ui->tableView->selectRow(m_eventlist.addElement(InterfaceElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddAdaptiveElement() {
  ui->tableView->selectRow(m_eventlist.addElement(AdaptiveElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddCodeElement() {
  ui->tableView->selectRow(m_eventlist.addElement(CodeElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddDurationElement() {
  ui->tableView->selectRow(m_eventlist.addElement(DurationElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddControlElement() {
  ui->tableView->selectRow(m_eventlist.addElement(ControlElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddQuestionElement() {
  ui->tableView->selectRow(m_eventlist.addElement(QuestionElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddAssistanceElement() {
  ui->tableView->selectRow(m_eventlist.addElement(AssistanceElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddAccessElement() {
  ui->tableView->selectRow(m_eventlist.addElement(AccessElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddMessageElement() {
  ui->tableView->selectRow(m_eventlist.addElement(MessageElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::onAddPopupElement() {
  ui->tableView->selectRow(m_eventlist.addElement(PopupElementType));
  onSelectionChanged();
  onDataChanged();
}

void MainWindow::eventTableContextMenu(QPoint pos) {
  QModelIndex index = ui->tableView->indexAt(pos);
  if (index.isValid()) {
    QMenu *menu = new QMenu(this);
    menu->addAction(ui->actionRemove_event);
    if ((ui->tableView->selectionModel()->selectedRows().count() == 1) &&
        ((m_eventlist.elementAt(index.row())->type() !=
          ElementType::ScriptElementType) ||
         m_new_flag)) {
      menu->addAction(ui->actionDuplicateEvent);
    }
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  Q_UNUSED(event)
  QMessageBox::StandardButton resBtn = QMessageBox::Yes;
  if (m_modified_flag) {
    resBtn = QMessageBox::question(
        this, tr("Close application"),
        tr("You have unsaved changes. Do you really want to exit?\n"),
        QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
  }
  if (resBtn == QMessageBox::Yes) {
    event->accept();
  } else {
    event->ignore();
  }
}

QStringList MainWindow::otherQuestionIds(Element *thiselement) {
  QStringList lst;
  for (int i = 0; i < m_eventlist.count(); i++) {
    Element *e{m_eventlist.elementAt(i)};
    if (e == thiselement)
      continue;
    if (e->type() == ElementType::QuestionElementType) {
      if (e->parameters().contains("id") && !e->parameters()["id"].isNull() &&
          !e->parameters()["id"].toString().trimmed().isEmpty()) {
        lst.append(e->parameters()["id"].toString());
      }
    }
  }
  return lst;
}

void MainWindow::updateActionsAndTitle() {
    setWindowTitle(QString("%1%2")
                       .arg(m_filename == "" ? "untitled.xml" : m_filename)
                       .arg(m_modified_flag ? "*" : ""));
    ui->actionSave_script->setEnabled(m_filename != "" && m_modified_flag);
    ui->actionUndo->setEnabled(canUndo());
    ui->actionRedo->setEnabled(canRedo());
    ui->actionNew_script->setEnabled(!m_new_flag);
    ui->actionValidate_script->setEnabled(m_eventlist.count() > 0);
}

void MainWindow::saveDataToFile() {
  QFile file{m_filename};
  if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
    QMessageBox::critical(this, tr("Cannot save file"),
                          tr("Cannot write to file %1").arg(m_filename));
    return;
  }
  QXmlStreamWriter sw{&file};
  XMLConfigWriter::write(sw, m_eventlist);
  file.close();
  m_modified_flag = false;
  updateActionsAndTitle();
}

void MainWindow::takeSnapshot() {
  // If we are not at the end remove elements
  while (m_snapshot_index != (m_snapshots.size() - 1)) {
    delete m_snapshots.last();
    m_snapshots.removeLast();
  }
  Snapshot *sn{new Snapshot};
  sn->data = m_eventlist.snapshot();
  if (!(ui->tableView->selectionModel()->selectedRows().isEmpty())) {
    sn->selected_row =
        ui->tableView->selectionModel()->selectedRows().at(0).row();
  }
  sn->modified_flag = m_modified_flag;
  m_snapshots.append(sn);
  m_snapshot_index = m_snapshots.size() - 1;
}

void MainWindow::restoreSnapshot(const MainWindow::Snapshot &sn) {
  m_eventlist.restore(sn.data);
  if (sn.selected_row != -1) {
    ui->tableView->selectRow(sn.selected_row);
  }
  m_modified_flag = sn.modified_flag;
}

void MainWindow::resetSnapshots() {
    for (auto e : std::as_const(m_snapshots)) {
        delete e;
    }
  m_snapshots.clear();
  m_snapshot_index = -1;
  takeSnapshot();
}

void MainWindow::undo() {
  m_in_undoredo_operation = true;
  restoreSnapshot(*m_snapshots.at(--m_snapshot_index));
  updateActionsAndTitle();
  m_in_undoredo_operation = false;
  onSelectionChanged();
}

void MainWindow::redo() {
  m_in_undoredo_operation = true;
  restoreSnapshot(*m_snapshots.at(++m_snapshot_index));
  updateActionsAndTitle();
  m_in_undoredo_operation = false;
  onSelectionChanged();
}

bool MainWindow::canUndo() { return m_snapshot_index > 0; }

bool MainWindow::canRedo() {
  return m_snapshot_index < (m_snapshots.size() - 1);
}

QStringList MainWindow::validQuestionIds() {
  QStringList lst;
  for (int i = 0; i < m_eventlist.count(); i++) {
    Element *e{m_eventlist.elementAt(i)};
    if (e->type() == ElementType::QuestionElementType) {
      if (e->parameters().contains("id") && !e->parameters()["id"].isNull() &&
          !e->parameters()["id"].toString().trimmed().isEmpty()) {
        lst.append(e->parameters()["id"].toString());
      }
    }
  }
  return lst;
}

#ifdef QT_TEST_ENABLED

#define ADD_MY_TEST(tklass)                                                    \
  tklass instance_##tklass;                                                    \
  test_instances.push_back(static_cast<QObject *>(&instance_##tklass));        \
  {                                                                            \
    const QMetaObject *metaObject = instance_##tklass.metaObject();            \
    int tcount{0};                                                             \
    QStringList methods;                                                       \
    for (int i = metaObject->methodOffset(); i < metaObject->methodCount();    \
         ++i) {                                                                \
      if (metaObject->method(i).methodType() == QMetaMethod::Slot) {           \
        ++tcount;                                                              \
      }                                                                        \
    }                                                                          \
    test_count[&instance_##tklass] = tcount;                                   \
    total += tcount;                                                           \
  }

#define RUN_MY_TEST(it)                                                        \
  {                                                                            \
    result = QTest::qExec(it);                                                 \
    if (result)                                                                \
      QMessageBox::critical(QApplication::activeWindow(), tr("Test failed"),   \
                            QString{it->metaObject()->className()} +           \
                                tr(" test failed"),                            \
                            QMessageBox::Ok);                                  \
    testsDone += test_count[it];                                               \
    if (progress.wasCanceled())                                                \
      return;                                                                  \
    progress.setValue(testsDone);                                              \
  }

#define RUN_ALL_TEST                                                           \
  progress.setMaximum(total);                                                  \
  for (auto &k : test_instances) {                                             \
    RUN_MY_TEST(k)                                                             \
  }

#define SETUP_MY_TEST                                                          \
  int result{0};                                                               \
  int total{0};                                                                \
  int testsDone{0};                                                            \
  QProgressDialog progress("Running self tests...", "Cancel", 0, 61, this);    \
  progress.setWindowModality(Qt::WindowModal);                                 \
  progress.setWindowTitle(this->windowTitle());                                \
  QList<QObject *> test_instances;                                             \
  QMap<QObject *, int> test_count;

#define FINISH_MY_TEST                                                         \
  progress.close();                                                            \
  if (total == testsDone) {                                                    \
    QMessageBox::information(this, tr("Done"), tr("All test completed"),       \
                             QMessageBox::Ok);                                 \
  }

void MainWindow::runTests() {
  SETUP_MY_TEST

  ADD_MY_TEST(TestAdaptiveElementEditor)
  ADD_MY_TEST(TestAssistanceElementEditor)
  ADD_MY_TEST(TestCodeElementEditor)
  ADD_MY_TEST(TestControlElementEditor)
  ADD_MY_TEST(TestErrorElementEditor)
  ADD_MY_TEST(TestFilterElementEditor)
  ADD_MY_TEST(TestInterfaceElementEditor)
  ADD_MY_TEST(TestQuestionElementEditor)
  ADD_MY_TEST(TestScriptElementEditor)
  ADD_MY_TEST(TestMessageElementEditor)
  ADD_MY_TEST(TestAccessElementEditor)
  ADD_MY_TEST(TestPopupElementEditor)
  RUN_ALL_TEST
  FINISH_MY_TEST
}
#endif
