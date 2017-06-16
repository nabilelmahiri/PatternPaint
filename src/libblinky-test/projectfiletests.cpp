#include <QBuffer>
#include <QTest>
#include <QDebug>

#include "projectfiletests.h"

#include "projectfile.h"
#include "exponentialbrightness.h"

void ProjectFileTests::headerVersionTest()
{
    // Pack the data into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    // write header
    ProjectFile::writeHeader(stream, PROJECT_FORMAT_VERSION);

    // reset
    buffer.reset();

    // read header
    QCOMPARE(ProjectFile::readHeader(stream), PROJECT_FORMAT_VERSION);
}

void ProjectFileTests::sceneConfigurationTest()
{
    Scene writeScene;
    Scene readScene;

    QString fixtureName("Linear");
    QSize fixtureSize(1,2);
    ColorMode fixtureColorMode(ColorMode::RGB);

    // Pack the data into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    // Make a test scene
    writeScene.fixture = Fixture::makeFixture(fixtureName, fixtureSize);
    writeScene.fixture->setColorMode(fixtureColorMode);
    writeScene.fixture->setBrightnessModel(new ExponentialBrightness(1.8,1.8,2.1));

    stream << writeScene;

    // reset
    buffer.reset();

    // read scene configuration
    stream >> readScene;
    QCOMPARE(stream.status(), QDataStream::Ok);
    // TODO: check that the controller firmware name was set

    QCOMPARE(readScene.fixture->getName(), fixtureName);
    QCOMPARE(readScene.fixture->getExtents().size(), fixtureSize);
    QCOMPARE(readScene.fixture->getColorMode(), fixtureColorMode);
}
