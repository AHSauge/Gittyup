
#ifndef BUFFEREDWRITER_H
#define BUFFEREDWRITER_H

#include <memory>
#include <QByteArray>
#include <QSaveFile>
#include <QObject>

class BufferedWriter : public QObject
{
    private:
        QSaveFile file;
        QByteArray buffer;
        char *ptr;
        const char *end;
        quint64 numBytesFlushed;

    public:
        BufferedWriter(QString filepath);
        ~BufferedWriter();
        bool open();
        bool commit();
        quint64 pos();
        //void seek(quint32 pos);
        void writeVInt(quint32 value);
        void flush();

        template <class T>
        void write(T &value)
        {
            if ( (ptr + sizeof(T)) > end)
            {
                flush();
            }
            std::memcpy(ptr, &value, sizeof(T));
            ptr += sizeof(T);
        }
};

template <class T>
BufferedWriter & operator<<(BufferedWriter& bw, const T& obj)
{
    bw.write(obj);
    return bw;
}

#endif