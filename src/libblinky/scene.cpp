#include "scene.h"

#include <QSettings>

#include "firmwarestore.h"
#include "exponentialbrightness.h"

QDataStream &operator<<(QDataStream &stream, const Scene &scene)
{
    // TODO: Serialize/deserialize the controller directly instead of touching the system settings
    QSettings settings;
    stream << (QString)settings.value("BlinkyTape/firmwareName", BLINKYTAPE_DEFAULT_FIRMWARE_NAME).toString();

    // TODO: Push these into the fixture class
    stream << scene.fixture->getName();
    stream << scene.fixture->getExtents().size();
    stream << (qint32)scene.fixture->getColorMode();

    // TODO: Brightness model?

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Scene &scene)
{
    // TODO: Serialize/deserialize the controller directly instead of touching the system settings
    QSettings settings;

    QString firmwareName;
    stream >> firmwareName;
    settings.setValue("BlinkyTape/firmwareName", firmwareName);

    // TODO: Push these into the fixture class
    QString fixtureName;
    QSize fixtureSize;
    ColorMode fixtureColorMode;

    stream >> fixtureName;
    stream >> fixtureSize;
    stream >> (qint32&)fixtureColorMode;

    scene.fixture = Fixture::makeFixture(fixtureName, fixtureSize);
    scene.fixture->setColorMode(fixtureColorMode);

    // TODO: Brightness model
    scene.fixture->setBrightnessModel(new ExponentialBrightness(1.8,1.8,2.1));

    return stream;
}
