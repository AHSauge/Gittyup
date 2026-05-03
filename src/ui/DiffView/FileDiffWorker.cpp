//
//          Copyright (c) 2026
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Alf Henrik Sauge
//

#include "FileDiffWorker.h"
#include "ui/DiffTreeModel.h"
#include "git/Patch.h"


FileDiffWorker::FileDiffWorker(git::Diff diff,  git::Diff stagedDiff,
                               QMap<QString, int> stagedPatches,
                               QList<QModelIndex> indices)
    : mDiff(diff), mStagedDiff(stagedDiff), mStagedPatches(stagedPatches),
    mIndices(indices) {
}

void FileDiffWorker::process() {
    for (const auto &idx : mIndices) {
        int pidx = idx.data(DiffTreeModel::PatchIndexRole).toInt();
        git::Patch patch = mDiff.patch(pidx);
        if (patch.isValid() == false) {
            emit invalidPatch();
            return;
        }

        int sidx;
        FileDiffData fdd;
        fdd.patch = patch;
        fdd.idx = idx;

        sidx = mStagedPatches.value(patch.name(), -1);
        if (sidx != -1)
            fdd.staged = mStagedDiff.patch(sidx);
        emit diffReady(fdd);
    }
    emit finished();
}