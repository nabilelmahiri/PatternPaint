#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include "libblinkyglobal.h"

#include "patterncollectionmodel.h"
#include "patterncollection.h"
#include "fixture.h"
#include "firmwarestore.h"
#include "scenetemplate.h"


#define PROJECT_HEADER     "PatternPaint Project"   /// Header of PatternPaint Project
#define PROJECT_FORMAT_VERSION     1.0              /// Version of PatternPaint Project format


class LIBBLINKY_EXPORT ProjectFile
{
public:
    ProjectFile();

    bool save(QString filename, QPointer<Fixture> fixture, PatternCollection* newPatternCollection);

    bool open(QString filename, SceneTemplate* newSceneTemplate, PatternCollection* newPatternCollection);

    void writeHeaderVersion(QDataStream& stream, float version);

    float readHeaderVersion(QDataStream& stream);

    void writeSceneConfiguration(QDataStream &stream, QPointer<Fixture> fixture);

    bool readSceneConfiguration(QDataStream &stream, SceneTemplate* newScenetemplate);

};

#endif // PROJECTFILE_H
