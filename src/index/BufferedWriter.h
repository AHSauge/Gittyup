
#ifndef BUFFEREDWRITER_H
#define BUFFEREDWRITER_H

#include <memory>
#include <QByteArray>
#include <QSaveFile>
#include <QObject>
#include <QtEndian>

class BufferedWriter : public QObject {
private:
  QSaveFile mFile;
  QByteArray mBuffer;
  char *mPtr;
  const char *mEnd;
  quint64 mNumBytesFlushed;
  const bool mUseBigEndian;

public:
  BufferedWriter(QString filepath, bool useBigEndian = false);
  ~BufferedWriter();
  bool open();
  bool commit();
  quint64 pos();
  void writeVInt(quint32 value);
  void flush();

  void write(const void *ptr, quint64 size) {
    if ((mPtr + size) > mEnd) {
      flush();
    }
    std::memcpy(mPtr, ptr, size);
    mPtr += size;
  }

  BufferedWriter &operator<<(const quint8 &obj) {
    write(&obj, sizeof(obj));
    return *this;
  }

  BufferedWriter &operator<<(const QByteArray &obj) {
    // Mimicing quite some unique QDataStream behaviour
    // It writes the size first, but only as 32bit if less than 0xfffffffe
    // Then it writes the data
    // This is only complicated due to the endianness handling in QDataStream
    qint64 size = obj.size();
    if (size < 0xfffffffe)
      *this << quint32(size);
    else
      *this << 0xfffffffe << size;
    write(obj.constData(), obj.size());
    return *this;
  }

  BufferedWriter &operator<<(const quint32 &obj) {
    const quint32 swapped = mUseBigEndian ? qToBigEndian(obj) : obj;
    write(&swapped, sizeof(swapped));
    return *this;
  }

  BufferedWriter &operator<<(const qint64 &obj) {
    const quint64 swapped = mUseBigEndian ? qToBigEndian(obj) : obj;
    write(&swapped, sizeof(swapped));
    return *this;
  }
};

#endif