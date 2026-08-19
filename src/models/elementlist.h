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
#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "element.h"
#include <QAbstractTableModel>
#include <QFile>

class ElementList : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit ElementList(QObject *parent = 0);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool remove(int row);
  bool duplicate(int row);
  bool open(QFile &source, bool validate = false);
  int count(ElementType type);
  int count();
  void clear();
  int addElement(ElementType type);
  Element *elementAt(int row);
  void sortElements();
  int indexOf(Element *e);
  QList<Element *>::iterator begin();
  QList<Element *>::iterator end();
  QStringList mimeTypes() const override;
  QMimeData *mimeData(const QModelIndexList &indexes) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  QList<Element *> snapshot();
  void restore(const QList<Element *> &sn);

private slots:
  void onScriptElement(QJsonObject parameters);
  void onQuestionElement(QString id, const QString &text);
  void onPopupElement(int startTime, QJsonObject parameters);
  void onDurationElement(int endTime);
  void onAssistanceElement(int startTime, QJsonObject parameters);
  void onInterfaceElement(int startTime, const QString &display,
                          const QString &modifier, const QString &value,
                          const QString &users);
  void onControlElement(int startTime, const QString &cmd);
  void onAdaptiveElement(int startTime, QJsonObject parameters);
  void onErrorElement(int startTime, const QString &errorType,
                      QJsonObject parameters);
  void onCodeElement(int startTime, const QString &code);
  void onFilterElement(int startTime, bool enabled, const QString &type,
                       const QString &key, const QString &user, bool feedback);
  void onMessageElement(int startTime, const QString &sender,
                        const QString &recipient, const QString &text);
  void onAccessElement(int startTime, const QString &user, int accessType);

public slots:
  void update(Element *e);

private:
  QList<Element *> m_schedule;
};

#endif // EVENTLIST_H
