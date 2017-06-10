#ifndef PATTERNTESTS_H
#define PATTERNTESTS_H

#include <QObject>

class PatternTests : public QObject
{
    Q_OBJECT
private slots:
    // TODO: All API tests. Only serialization tests added now.

    void readFromStreamFrameBasedTest();
    void writeToStreamFrameBasedTest();

    void readFromStreamScrollingTest();
    void writeToStreamScrollingTest();
};

#endif // PATTERNTESTS_H
