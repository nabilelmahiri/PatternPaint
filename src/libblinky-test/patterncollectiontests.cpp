#include <QTest>
#include <QBuffer>
#include <QPointer>

#include "patterncollectiontests.h"
#include "pattern.h"
#include "patterncollection.h"

void PatternCollectionTests::readFromStreamTest()
{
    // TODO: These are probably more accurately described as patternCollectionModel tests?
    // The patternCollection should not actually know the details of how they are stored.

    // Create a list of sample patterns
    QList<QPointer<Pattern> > patterns;

    patterns.append(new Pattern(Pattern::Scrolling, QSize(1,2),10));
    patterns.append(new Pattern(Pattern::Scrolling, QSize(3,4),11));
    patterns.append(new Pattern(Pattern::FrameBased, QSize(5,6),12));
    patterns.append(new Pattern(Pattern::FrameBased, QSize(7,8),13));

    // Pack the list into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << patterns;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a Pattern object
    PatternCollection patternCollection;
    stream >> patternCollection;

    QCOMPARE(patternCollection.count(), patterns.count());

    for(int i = 0; i < patternCollection.count(); i++) {
        Pattern* expected = patterns.at(i);
        Pattern* test = patternCollection.at(i);

        // TODO: Add pattern comparison operator, drop these
        QCOMPARE(test->getType(), expected->getType());
        QCOMPARE(test->getFrameCount(), expected->getFrameCount());
        QCOMPARE(test->getFrameSize(), expected->getFrameSize());
        QCOMPARE(test->getName(), expected->getName());
    }

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}

void PatternCollectionTests::writeToStreamTest()
{
    // TODO: These are probably more accurately described as patternCollectionModel tests?
    // The patternCollection should not actually know the details of how they are stored.

    // Create a sample patternCollection
    PatternCollection patternCollection;

    patternCollection.add(new Pattern(Pattern::Scrolling, QSize(1,2),10), 0);
    patternCollection.add(new Pattern(Pattern::Scrolling, QSize(3,4),11), 1);
    patternCollection.add(new Pattern(Pattern::FrameBased, QSize(5,6),12), 2);
    patternCollection.add(new Pattern(Pattern::FrameBased, QSize(7,8),13), 3);

    // Pack the list into a stream
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    QDataStream stream;
    stream.setDevice(&buffer);

    stream << patternCollection;
    stream << QString("endOfStream");
    buffer.reset();

    // and read it back as a lsit of patterns
    QList<QPointer<Pattern> > patterns;
    stream >> patterns;

    QCOMPARE(patterns.count(), patternCollection.count());

    QCOMPARE(patternCollection.count(), patterns.count());

    for(int i = 0; i < patternCollection.count(); i++) {
        Pattern* expected = patternCollection.at(i);
        Pattern* test = patterns.at(i);

        // TODO: Add pattern comparison operator, drop these
        QCOMPARE(test->getType(), expected->getType());
        QCOMPARE(test->getFrameCount(), expected->getFrameCount());
        QCOMPARE(test->getFrameSize(), expected->getFrameSize());
        QCOMPARE(test->getName(), expected->getName());
    }

    QString endOfStreamMarker;
    stream >> endOfStreamMarker;
    QCOMPARE(endOfStreamMarker, QString("endOfStream"));
}
