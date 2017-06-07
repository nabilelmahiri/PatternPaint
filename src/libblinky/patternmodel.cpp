#include "patternmodel.h"

QDataStream &operator<<(QDataStream &stream, const PatternModel &model)
{
    model.toStream(stream);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, PatternModel &model)
{
    model.fromStream(stream);
    return stream;
}
