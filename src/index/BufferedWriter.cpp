#include "BufferedWriter.h"
#include <QIODevice>
#include <QTextStream>

static const quint64 kBufferSize = 64 * 1024;

BufferedWriter::BufferedWriter(QString filepath)
: file(filepath),
numBytesFlushed(0)
{
    buffer.resize(kBufferSize);
    ptr = buffer.data();
    end = ptr + kBufferSize;
}

BufferedWriter::~BufferedWriter()
{
}

bool BufferedWriter::open()
{
    return file.open(QIODevice::WriteOnly);
}

bool BufferedWriter::commit()
{
    flush();
    return file.commit();
}

quint64 BufferedWriter::pos()
{
    return numBytesFlushed + ptr - buffer.data();
}

void BufferedWriter::writeVInt(quint32 value)
{
    if ( (ptr + 5) > end)
    {
        flush();
    }

    // Write less significant bytes first.
    // Most significant bit is set.
    while (value & ~0x7F)
    {
        *ptr++ = static_cast<quint8>((value & 0x7F) | 0x80);
        value >>= 7;
    }

    // Write most significant byte last.
    // Most significant bit is unset.
    *ptr++ = static_cast<quint8>(value);
}

void BufferedWriter::flush()
{
    if (ptr != buffer.data())
    {
        quint64 bytesToWrite = ptr - buffer.data();
        file.write(buffer.constData(), bytesToWrite);
        ptr = buffer.data();
        numBytesFlushed += bytesToWrite;
    }
}
