#ifndef PATTERNCOLLECTIONTESTS_H
#define PATTERNCOLLECTIONTESTS_H

#include "multitests.h"

#include <QObject>

class PatternCollectionTests : public QObject
{
    Q_OBJECT
private slots:
    // TODO: All API tests. Only serialization tests added now.

    void readFromStreamTest();
    void writeToStreamTest();
    void streamLoopbackTest();
};

TEST_DECLARE(PatternCollectionTests)

#endif // PATTERNCOLLECTIONTESTS_H
