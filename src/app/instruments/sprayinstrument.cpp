#include "sprayinstrument.h"

#include <QPen>
#include <QPainter>
#include <math.h>
#include <QDebug>

SprayInstrument::SprayInstrument(InstrumentConfiguration *instrumentConfiguration, QObject *parent) :
    AbstractInstrument(":/instruments/images/instruments-icons/cursor_spray.png",
                       instrumentConfiguration,
                       parent)
{
    drawing = false;
}

void SprayInstrument::mousePressEvent(QMouseEvent *event, const QImage &frameData, const QPoint &point)
{
    if (event->button() == Qt::LeftButton) {
        preview = QImage(frameData.size(),
                             QImage::Format_ARGB32_Premultiplied);
        preview.fill(QColor(0, 0, 0, 0));
        drawing = true;

        paint(point);
    }
}

void SprayInstrument::mouseMoveEvent(QMouseEvent *, const QImage &frameData, const QPoint &point)
{
    if(!drawing) {
        updatePreview(frameData, point);
        return;
    }

    paint(point);
}

void SprayInstrument::mouseReleaseEvent(QMouseEvent *, FrameEditor &editor, const QImage &frameData, const QPoint &point)
{
    if (!drawing)
        return;

    editor.applyInstrument(preview);
    drawing = false;

    updatePreview(frameData, point);
}

void SprayInstrument::paint(const QPoint &newPoint)
{
    QPainter painter(&preview);

    painter.setPen(QPen(instrumentConfiguration->getToolColor(),
                        instrumentConfiguration->getPenSize(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    int x;
    int y;
    for (int i(0); i < 12; i++) {
        switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
            x = (prng.generate() % 5 - 2)
                * sqrt(instrumentConfiguration->getPenSize());
            y = (prng.generate() % 5 - 2)
                * sqrt(instrumentConfiguration->getPenSize());
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            x = (prng.generate() % 10 - 4)
                * sqrt(instrumentConfiguration->getPenSize());
            y = (prng.generate() % 10 - 4)
                * sqrt(instrumentConfiguration->getPenSize());
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            x = (prng.generate() % 15 - 7)
                * sqrt(instrumentConfiguration->getPenSize());
            y = (prng.generate() % 15 - 7)
                * sqrt(instrumentConfiguration->getPenSize());
            break;
        default:
            return;
        }
        qDebug() << x << y;
        painter.drawPoint(newPoint.x() + x, newPoint.y() + y);
    }
}
