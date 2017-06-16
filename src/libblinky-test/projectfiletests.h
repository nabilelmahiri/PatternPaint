#ifndef PROJECTFILETESTS_H
#define PROJECTFILETESTS_H

#include "multitests.h"

#include <QObject>

class ProjectFileTests : public QObject
{
    Q_OBJECT
private slots:
    void headerVersionTest();

    void sceneConfigurationTest();
};

TEST_DECLARE(ProjectFileTests)

#endif // PROJECTFILETESTS_H
