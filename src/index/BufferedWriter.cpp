#include "BufferedWriter.h"
#include <QIODevice>
#include <QTextStream>

static const quint64 kBufferSize = 64 * 1024;

BufferedWriter::BufferedWriter(QString filepath, bool useBigEndian)
    : mFile(filepath), mNumBytesFlushed(0), mUseBigEndian(useBigEndian) {
  mBuffer.resize(kBufferSize);
  mPtr = mBuffer.data();
  mEnd = mPtr + kBufferSize;
}

BufferedWriter::~BufferedWriter() {}

bool BufferedWriter::open() { return mFile.open(QIODevice::WriteOnly); }

bool BufferedWriter::commit() {
  flush();
  return mFile.commit();
}

quint64 BufferedWriter::pos() {
  return mNumBytesFlushed + mPtr - mBuffer.data();
}

void BufferedWriter::writeVInt(quint32 value) {
  if ((mPtr + 5) > mEnd) {
    flush();
  }

  // Write less significant bytes first.
  // Most significant bit is set.
  while (value & ~0x7F) {
    *mPtr++ = static_cast<quint8>((value & 0x7F) | 0x80);
    value >>= 7;
  }

  // Write most significant byte last.
  // Most significant bit is unset.
  *mPtr++ = static_cast<quint8>(value);
}

void BufferedWriter::flush() {
  if (mPtr != mBuffer.data()) {
    quint64 bytesToWrite = mPtr - mBuffer.data();
    mFile.write(mBuffer.constData(), bytesToWrite);
    mPtr = mBuffer.data();
    mNumBytesFlushed += bytesToWrite;
  }
}
