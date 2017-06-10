#include <QTest>
#include <QBuffer>

#include "patterntests.h"

#include "pattern.h"
#include "patternframemodel.h"
#include "patternscrollmodel.h"


void PatternTests::readFromStreamFrameBasedTest()
{
    // Write a pattern model to the stream
    QSize frameSize(10,11);
    QString fileName("filename");
    int frameCount = 12;

    // Load it into the model
    PatternFrameModel model(frameSize*10);
    model.insertRows(0,frameCount);
    model.setData(model.index(0), frameSize, PatternFrameModel::FrameSize);
    model.setData(model.index(0), fileName, PatternFrameModel::FileName);

    // Pack the model into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << model.getType();
    stream << model;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a Pattern object
    Pattern pattern;
    stream >> pattern;

    QCOMPARE(pattern.getType(), Pattern::FrameBased);
    QCOMPARE(pattern.getFrameCount(), frameCount);
    QCOMPARE(pattern.getFrameSize(), frameSize);
    QCOMPARE(pattern.getName(), fileName);

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}

void PatternTests::writeToStreamFrameBasedTest()
{
    QSize frameSize(10,11);
    int frameCount = 12;

    // Write a pattern to the stream
    Pattern pattern(Pattern::FrameBased, frameSize, frameCount);

    // Pack the model into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << pattern;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a patternModel
    Pattern::PatternType type;
    PatternFrameModel model(QSize(1,1));

    stream >> (qint32&)type;
    stream >> model;

    QCOMPARE(type, Pattern::FrameBased);
    QCOMPARE(model.data(model.index(0), PatternFrameModel::FrameSize).toSize(), frameSize);
    QCOMPARE(model.rowCount(model.index(0)), frameCount);

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}

void PatternTests::readFromStreamScrollingTest()
{
    // Write a pattern model to the stream
    QSize frameSize(10,11);
    QString fileName("filename");
    int frameCount = 12;

    // Load it into the model
    PatternScrollModel model(frameSize*10);
    model.insertRows(0,frameCount);
    model.setData(model.index(0), frameSize, PatternFrameModel::FrameSize);
    model.setData(model.index(0), fileName, PatternFrameModel::FileName);

    // Pack the model into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << model.getType();
    stream << model;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a Pattern object
    Pattern pattern;
    stream >> pattern;

    QCOMPARE(pattern.getType(), Pattern::Scrolling);
    QCOMPARE(pattern.getFrameCount(), frameCount);
    QCOMPARE(pattern.getFrameSize(), frameSize);
    QCOMPARE(pattern.getName(), fileName);

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}

void PatternTests::writeToStreamScrollingTest()
{
    QSize frameSize(10,11);
    int frameCount = 12;

    // Write a pattern to the stream
    Pattern pattern(Pattern::Scrolling, frameSize, frameCount);

    // Pack the model into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << pattern;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a patternModel
    Pattern::PatternType type;
    PatternScrollModel model(QSize(1,1));

    stream >> (qint32&)type;
    stream >> model;

    QCOMPARE(type, Pattern::Scrolling);
    QCOMPARE(model.data(model.index(0), PatternFrameModel::FrameSize).toSize(), frameSize);
    QCOMPARE(model.rowCount(model.index(0)), frameCount);

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}
