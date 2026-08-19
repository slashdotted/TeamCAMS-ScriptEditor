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

#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include "models/elementlist.h"
#include <QRect>
#include <QVector>
#include <QWidget>

class Element;
class ElementList;

class TimelineWidget : public QWidget {
  Q_OBJECT

public:
  explicit TimelineWidget(QWidget *parent = nullptr);
  void setModel(ElementList *model);
  QSize sizeHint() const override;
  void selectElement(Element *element);

signals:
  void eventSelected(Element *element);

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  struct Marker {
    int time{0};
    QVector<Element *> elements;
    int x{0};
    QRect rect;
    QPixmap icon;
  };

  QVector<Marker> buildLayout() const;

  int chooseTickStep(int maxTime) const;

private:
  bool isMarkerSelected(const Marker &marker) const;
  ElementList *m_model = nullptr;
  Element *m_selected = nullptr;
  QRect m_durationRect;
  Element *m_durationElement = nullptr;
  QRect m_scriptRect;
  Element *m_scriptElement = nullptr;
};

#endif // TIMELINEWIDGET_H
