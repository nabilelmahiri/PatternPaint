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
    newProjectFile.writeHeaderVersion(stream, PROJECT_FORMAT_VERSION);

    // reset
    buffer.reset();

    // read header
    QCOMPARE(newProjectFile.readHeaderVersion(stream), PROJECT_FORMAT_VERSION);
}

void ProjectFileTests::sceneConfigurationTest()
{
    ProjectFile newProjectFile;
    SceneTemplate newScenetemplate;

    // Pack the data into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    // write scene configuration
    fixture = Fixture::makeFixture("Linear", QSize(1,1));

    fixture->setColorMode((ColorMode)RGB);

    newProjectFile.writeSceneConfiguration(stream, fixture);

    // reset
    buffer.reset();

    // read scene configuration
    QVERIFY(newProjectFile.readSceneConfiguration(stream, &newScenetemplate) == true);

    QCOMPARE(newScenetemplate.size, QSize(1,1));
    QCOMPARE(newScenetemplate.fixtureType, QString("Linear"));
    QCOMPARE(newScenetemplate.colorMode, ColorMode::RGB);
    QCOMPARE(newScenetemplate.firmwareName, QString("default"));
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
