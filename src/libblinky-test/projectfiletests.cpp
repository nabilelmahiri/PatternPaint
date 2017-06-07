#include <QBuffer>
#include <QTest>
#include <QDebug>

#include "projectfiletests.h"


void ProjectFileTests::headerVersionTest()
{

    ProjectFile newProjectFile;

    // Pack the data into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    // write header
    newProjectFile.writeHeader(stream, PROJECT_FORMAT_VERSION);

    // reset
    buffer.reset();

    // read header
    QCOMPARE(newProjectFile.readHeader(stream), PROJECT_FORMAT_VERSION);
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

void ProjectFileTests::patternsTest()
{
    PatternCollection writePatternCollection;
    PatternCollection readPatternCollection;

    // Pack the data into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    // write patterns
    Pattern::PatternType type = Pattern::Scrolling;
    QSize size = QSize(3,7);
    float frameSpeed = 15.5;

    Pattern *newPattern = new Pattern(type, size, 1);
    newPattern->setFrameSpeed(frameSpeed);
    writePatternCollection.add(newPattern,0);

    stream << writePatternCollection;

    // reset
    buffer.reset();

    // read patterns
    stream >> readPatternCollection;
    QCOMPARE(stream.status(), QDataStream::Ok);
    QCOMPARE(readPatternCollection.count(), 1);
    QCOMPARE(readPatternCollection.at(0)->getType(), type);
    QCOMPARE(readPatternCollection.at(0)->getFrameSize(), size);
    QCOMPARE(readPatternCollection.at(0)->getFrameSpeed(), frameSpeed);
}
