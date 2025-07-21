
#ifndef MMAPFILEREADER_H
#define MMAPFILEREADER_H

#include <memory>
#include <QByteArray>
#include <QFile>
#include <QObject>

class MmapFileReader : public QObject
{
    private:
        QFile proxInFile;
        quint8 *data;
        const quint8 *ptr;
        const quint8 *end;

    public:
        MmapFileReader(QString filepath);
        ~MmapFileReader();
        bool open();
        void seek(quint32 pos);
        quint32 readVInt();

        template <class T>
        void read(T &value)
        {
            std::memcpy(&value, ptr, sizeof(T));
            ptr += sizeof(T);
        }
};

template <class T>
MmapFileReader & operator>>(MmapFileReader& mfr, T& obj)
{
    mfr.read(obj);
    return mfr;
}

#endif