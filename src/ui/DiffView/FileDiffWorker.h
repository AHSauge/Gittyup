//
//          Copyright (c) 2026
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Alf Henrik Sauge
//

#ifndef FILE_DIFF_WORKER_H
#define FILE_DIFF_WORKER_H

#include "git/Diff.h"
#include "git/Patch.h"
#include "git/Repository.h"
#include <QModelIndex>

struct FileDiffData {
    git::Patch patch;
    git::Patch staged;
    QModelIndex idx;
};

class FileDiffWorker : public QObject {
    Q_OBJECT

    public:
        FileDiffWorker(git::Diff diff,  git::Diff stagedDiff,
                       QMap<QString, int> stagedPatches,
                       QList<QModelIndex> indices);

    signals:
        void diffReady(FileDiffData fdd);
        void finished();
        void invalidPatch();

    public slots:
        void process();

    private:
        git::Diff mDiff;
        git::Diff mStagedDiff;
        QMap<QString, int> mStagedPatches;
        QList<QModelIndex> mIndices;
};

#endif