#ifndef PATTERNCOLLECTIONTESTS_H
#define PATTERNCOLLECTIONTESTS_H

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

#endif // PATTERNCOLLECTIONTESTS_H
