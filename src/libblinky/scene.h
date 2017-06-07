#ifndef SCENE_H
#define SCENE_H

#include "libblinkyglobal.h"

#include <QObject>
#include <QPointer>
#include <QDataStream>

#include "fixture.h"

class LIBBLINKY_EXPORT Scene
{
public:
    // TODO: Eventually this nees to be a list
    QPointer<Fixture> fixture;

    friend LIBBLINKY_EXPORT QDataStream &operator<<(QDataStream &stream, const Scene &scene);
    friend LIBBLINKY_EXPORT QDataStream &operator>>(QDataStream &stream, Scene &scene);
};

#endif // SCENE_H
