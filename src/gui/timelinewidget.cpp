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

#include "timelinewidget.h"
#include "models/element.h"
#include <QAbstractItemModel>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

static constexpr int LeftMargin = 20;
static constexpr int RightMargin = 30;
static constexpr int ScriptAreaWidth = 50;
static constexpr int MarkerSize = 16;
static constexpr int MultiMarkerRadius = 7;
static constexpr int MinSpacing = 18;

TimelineWidget::TimelineWidget(QWidget *parent) : QWidget(parent) {
  setMouseTracking(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  setMinimumHeight(80);
}

QSize TimelineWidget::sizeHint() const { return QSize(400, 80); }

void TimelineWidget::setModel(ElementList *model) {
  if (m_model == model)
    return;
  if (m_model)
    disconnect(m_model, nullptr, this, nullptr);
  m_model = model;

  if (!m_model)
    return;
  connect(m_model, &QAbstractItemModel::dataChanged, this,
          QOverload<>::of(&TimelineWidget::update));
  connect(m_model, &QAbstractItemModel::modelReset, this,
          QOverload<>::of(&TimelineWidget::update));
  connect(m_model, &QAbstractItemModel::rowsInserted, this,
          QOverload<>::of(&TimelineWidget::update));
  connect(m_model, &QAbstractItemModel::rowsRemoved, this,
          QOverload<>::of(&TimelineWidget::update));
  update();
}

int TimelineWidget::chooseTickStep(int maxTime) const {
  static const QVector<int> steps{30, 60, 120, 300, 900, 1800, 3600};

  for (int step : steps) {
    int count = (maxTime + step - 1) / step;

    if (count <= 10)
      return step;
  }

  return 3600;
}

QVector<TimelineWidget::Marker> TimelineWidget::buildLayout() const {
  QVector<Marker> markers;

  if (!m_model)
    return markers;

  QMap<int, QVector<Element *>> grouped;
  for (int row = 0; row < m_model->rowCount(); ++row) {
    Element *el = m_model->elementAt(row);
    if (!el)
      continue;
    if (el->time() < 0)
      continue;
    grouped[el->time()].append(el);
  }

  if (grouped.isEmpty())
    return markers;

  int lastEventTime = grouped.lastKey();

  int maxTime = qMax(1, lastEventTime);

  for (int row = 0; row < m_model->rowCount(); ++row) {
    Element *el = m_model->elementAt(row);

    if (!el)
      continue;

    if (el->type() == DurationElementType) {
      int duration = el->parameters().value("seconds").toInt(-1);

      if (duration > 0) {
        maxTime = qMax(maxTime, duration);
      }

      break;
    }
  }
  const int timelineStartX = LeftMargin + ScriptAreaWidth;
  const int usableWidth = qMax(0, width() - timelineStartX - RightMargin);
  for (auto it = grouped.begin(); it != grouped.end(); ++it) {
    Marker m;
    m.time = it.key();
    m.elements = it.value();
    double ratio = static_cast<double>(m.time) / static_cast<double>(maxTime);
    m.x = timelineStartX + qRound(ratio * usableWidth);
    if (!m.elements.isEmpty()) {
      Element *first = m.elements.first();
      QModelIndex idx = m_model->index(m_model->indexOf(first), 1);
      QVariant icon = m_model->data(idx, Qt::DecorationRole);
      if (icon.canConvert<QPixmap>()) {
        m.icon = qvariant_cast<QPixmap>(icon);
      }
    }
    markers.push_back(m);
  }
  for (int i = 1; i < markers.size(); ++i) {
    if (markers[i].x - markers[i - 1].x < MinSpacing) {
      markers[i].x = markers[i - 1].x + MinSpacing;
    }
  }
  const int rightLimit = width() - RightMargin;
  if (!markers.isEmpty()) {
    int overflow = markers.last().x - rightLimit;
    if (overflow > 0) {
      for (auto &m : markers)
        m.x -= overflow;
    }
  }
  const int centerY = 25;
  for (auto &m : markers) {
    m.rect = QRect(m.x - 10, centerY - 10, 20, 20);
  }
  return markers;
}

void TimelineWidget::mousePressEvent(QMouseEvent *event) {
  const auto markers = buildLayout();

  if (m_scriptElement && m_scriptRect.contains(event->pos())) {
    m_selected = m_scriptElement;
    emit eventSelected(m_selected);
    update();
    return;
  }

  if (m_durationElement && m_durationRect.contains(event->pos())) {
    m_selected = m_durationElement;
    emit eventSelected(m_selected);
    update();
    return;
  }

  for (const auto &m : markers) {
    if (m.rect.contains(event->pos())) {
      if (!m.elements.isEmpty()) {
        m_selected = m.elements.first();
        emit eventSelected(m_selected);
        update();
      }
      return;
    }
  }

  QWidget::mousePressEvent(event);
}

bool TimelineWidget::isMarkerSelected(const Marker &marker) const {
  return m_selected && marker.elements.contains(m_selected);
}

static QColor colorForType(ElementType type) {
  switch (type) {
  case ErrorElementType:
    return QColor("#D55E00");
  case ScriptElementType:
    return QColor("#0072B2");
  case InterfaceElementType:
    return QColor("#56B4E9");
  case AdaptiveElementType:
    return QColor("#009E73");
  case CodeElementType:
    return QColor("#3B6FB6");
  case DurationElementType:
    return QColor("#E69F00");
  case ControlElementType:
    return QColor("#CC79A7");
  case QuestionElementType:
    return QColor("#F0E442");
  case AssistanceElementType:
    return QColor("#009E73");
  case FilterElementType:
    return QColor("#666666");
  case AccessElementType:
    return QColor("#4E79A7");
  case MessageElementType:
    return QColor("#59A14F");
  case PopupElementType:
    return QColor("#AF7AA1");
  default:
    return QColor("#808080");
  }
}

void TimelineWidget::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  const auto markers = buildLayout();
  const int centerY = 25;
  const int timelineStartX = LeftMargin + ScriptAreaWidth;
  const int usableWidth = qMax(0, width() - timelineStartX - RightMargin);

  int experimentDuration = -1;

  m_durationElement = nullptr;
  m_scriptElement = nullptr;

  for (int row = 0; row < m_model->rowCount(); ++row) {
    Element *el = m_model->elementAt(row);
    if (!el)
      continue;
    if (el->type() == DurationElementType) {
      experimentDuration = el->parameters().value("seconds").toInt(-1);
      m_durationElement = el;
    }
    if (el->type() == ScriptElementType) {
      m_scriptElement = el;
    }
  }

  int lastEventTime = 0;

  if (!markers.isEmpty()) {
    lastEventTime = markers.last().time;
  }

  int maxTime = qMax(1, lastEventTime);

  if (experimentDuration >= 0) {
    maxTime = qMax(maxTime, experimentDuration);
  }
  p.setPen(QPen(QColor(120, 120, 120), 2));
  p.drawLine(timelineStartX, centerY, width() - RightMargin, centerY);
  p.setPen(QPen(QColor(180, 180, 180), 1));
  p.drawLine(timelineStartX - 8, centerY - 12, timelineStartX - 8,
             centerY + 12);
  const int step = chooseTickStep(maxTime);
  for (int t = 0; t <= maxTime; t += step) {
    double ratio =
        static_cast<double>(t) / static_cast<double>(qMax(1, maxTime));
    int x = timelineStartX + qRound(ratio * usableWidth);
    p.setPen(QPen(QColor(180, 180, 180), 1));
    p.drawLine(x, centerY - 8, x, centerY + 8);
    QString label = (step < 3600) ? QTime(0, 0).addSecs(t).toString("mm:ss")
                                  : QTime(0, 0).addSecs(t).toString("hh:mm");
    p.setPen(Qt::darkGray);
    p.drawText(QRect(x - 30, centerY + 22, 60, 16), Qt::AlignCenter, label);
  }

  if (m_scriptElement) {
    QRect scriptRect(LeftMargin + (ScriptAreaWidth - 16) / 2, centerY - 8, 16,
                     16);
    m_scriptRect = scriptRect;
    const bool selected = (m_selected == m_scriptElement);
    p.setPen(selected ? QPen(Qt::red, 2) : QPen(QColor("#0072B2"), 2));
    p.setBrush(QColor("#56B4E9"));
    p.drawRoundedRect(scriptRect, 3, 3);
    p.setPen(Qt::white);
    p.drawText(scriptRect, Qt::AlignCenter, "S");
  }

  if (experimentDuration >= 0) {
    double ratio = static_cast<double>(experimentDuration) /
                   static_cast<double>(qMax(1, maxTime));
    int durationX = timelineStartX + qRound(ratio * usableWidth);
    durationX = qBound(LeftMargin, durationX, width() - RightMargin);
    p.setPen(QPen(QColor("#D55E00"), 3, Qt::DashLine));
    p.drawLine(durationX, 4, durationX, height() - 4);
    QRect endRect(durationX - 8, centerY - 8, 16, 16);
    m_durationRect = endRect;
    bool selected = (m_selected == m_durationElement);
    p.setPen(selected ? QPen(Qt::black, 2) : Qt::NoPen);
    p.setBrush(QColor("#D55E00"));
    p.drawEllipse(endRect);
    p.setPen(Qt::white);
    p.drawText(endRect, Qt::AlignCenter, "E");
    p.setPen(QColor("#D55E00"));
    p.drawText(QRect(durationX + 4, 0, 80, 16), Qt::AlignLeft, tr("End"));
  }

  for (const auto &m : markers) {
    if (m.elements.isEmpty())
      continue;
    Element *el = m.elements.first();
    const bool selected = (m_selected && m.elements.contains(m_selected));
    const bool afterEnd =
        (experimentDuration >= 0) && (m.time > experimentDuration);
    if (m.elements.size() > 1) {
      p.setPen(afterEnd ? QPen(Qt::red, 2) : Qt::NoPen);
      p.setBrush(QColor("#F0E442"));
      p.drawEllipse(QPoint(m.x, centerY), 8, 8);
      if (selected) {
        p.setPen(QPen(Qt::black, 2));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(QPoint(m.x, centerY), 11, 11);
      }
      continue;
    }

    QColor color = colorForType(el->type());
    QRect iconRect(m.x - 8, centerY - 8, 16, 16);
    p.setPen(afterEnd ? QPen(Qt::red, 2) : QPen(color, 2));
    p.setBrush(color.lighter(170));
    p.drawEllipse(QPoint(m.x, centerY), 11, 11);
    if (!m.icon.isNull()) {
      p.drawPixmap(iconRect, m.icon);
    }
    if (selected) {
      p.setPen(QPen(Qt::black, 2));
      p.setBrush(Qt::NoBrush);
      p.drawEllipse(QPoint(m.x, centerY), 15, 15);
    }
  }
}

void TimelineWidget::selectElement(Element *element) {
  m_selected = element;
  update();
}

void TimelineWidget::mouseMoveEvent(QMouseEvent *event) {
  const auto markers = buildLayout();

  for (const auto &m : markers) {
    if (m.rect.contains(event->pos())) {
      QString tip =
          QString(tr("<b>%1</b>"))
              .arg(QTime(0, 0).addSecs(m.time).toString(tr("hh:mm:ss")));
      if (m.elements.size() > 1) {
        tip += QString(tr("<br>%1 events")).arg(m.elements.size());
      }
      setToolTip(tip);
      return;
    }
  }

  setToolTip(QString());
}
