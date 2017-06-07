#include "projectfile.h"

#include <QDebug>
#include <QSettings>

ProjectFile::ProjectFile()
{

}


bool ProjectFile::save(QString filename, QPointer<Fixture> fixture, PatternCollection *newPatternCollection)
{

    qDebug() << "Save project:" << filename;

    // Create a new file
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Project save failed!";
        return false;
    }

    QDataStream out(&file);


    // write header
    writeHeaderVersion(out, PROJECT_FORMAT_VERSION);

    // write scene configuration
    writeSceneConfiguration(out, fixture);

    // write patterns
    out << newPatternCollection;

    file.close();

    qDebug() << "Project successful saved";

    return true;
}


bool ProjectFile::open(QString filename, SceneTemplate* newSceneTemplate, PatternCollection *newPatternCollection)
{
    qDebug()<<"Open Project:" << filename;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<< "Error: Cannot read project file ";
        return false;
    }

    // read project file
    QDataStream in(&file);

    // read header
    if(readHeaderVersion(in) != PROJECT_FORMAT_VERSION){
        qDebug()<< "Error: Format version incorrectly";
        return false;
    }

    // read scene configuration
    if(!readSceneConfiguration(in, newSceneTemplate))
        return false;

    // read Patterns
    in >> *(newPatternCollection);
    if(in.status() == QDataStream::Ok) {
        qDebug() << "Project successful read";
    }
    else {
        qDebug() << "Project read failed!";
        return false;
    }

    return true;
}

void ProjectFile::writeHeaderVersion(QDataStream &stream, float version)
{
    stream.setVersion(QDataStream::Qt_5_8);

    stream << (QString)PROJECT_HEADER;
    stream << version;
//    stream << (QString)GIT_VERSION;
}

float ProjectFile::readHeaderVersion(QDataStream &stream)
{

    QString header;
//    QString patternPaintVersion;
    float formatVersion;

    stream.setVersion(QDataStream::Qt_5_8);

    stream >> header;
    if(header != PROJECT_HEADER){
        qDebug()<< "Error: Header incorrectly";
        return 0;
    }

    stream >> formatVersion;

//    stream >> patternPaintVersion;
//    qDebug() << "Project created with Pattern Paint version:" << patternPaintVersion;

    return formatVersion;
}

void ProjectFile::writeSceneConfiguration(QDataStream &stream, QPointer<Fixture> fixture)
{
    QSettings settings;

    stream << (QString)settings.value("BlinkyTape/firmwareName", BLINKYTAPE_DEFAULT_FIRMWARE_NAME).toString();
    stream << (QString)fixture->getName();
    stream << (qint32)fixture->getExtents().width();
    stream << (qint32)fixture->getExtents().height();
    stream << (qint32)fixture->getColorMode();
}

bool ProjectFile::readSceneConfiguration(QDataStream &stream, SceneTemplate *newScenetemplate)
{

    qint32 width;
    qint32 height;
    qint32 colorMode;

    stream >> newScenetemplate->firmwareName;
    stream >> newScenetemplate->fixtureType;
    stream >> width;
    stream >> height;
    stream >> colorMode;

    newScenetemplate->colorMode = (ColorMode)colorMode;
    newScenetemplate->size = QSize(width,height);

    if(stream.status() != QDataStream::Ok)
        return false;

    return true;
}
