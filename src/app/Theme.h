//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Shane Gramlich
//

#ifndef THEME_H
#define THEME_H

#include <QDir>
#include <QPalette>
#include <QString>
#include <QMap>

class QStyle;
class QStyleOption;

class Theme {
public:
  enum class BadgeRole { Foreground, Background };

  enum class BadgeState {
    Normal,
    Selected,
    Conflicted,
    Head,
    Notification,
    Modified,
    Added,
    Deleted,
    Untracked,
    Renamed
  };

  enum class CommitEditor { SpellError, SpellIgnore, LengthWarning };

  enum class Diff {
    Ours,
    Theirs,
    Addition,
    Deletion,

    WordAddition,
    WordDeletion,
    Plus,
    Minus,

    Note,
    Warning,
    Error
  };

  enum class HeatMap { Hot, Cold };

  enum class Comment { Background, Body, Author, Timestamp };

  Theme();
  virtual ~Theme() = default;

  QString diffButtonStyle(Diff role);

  virtual QDir dir() const;
  virtual QString name() const;
  virtual QStyle *style() const;
  virtual QString styleSheet() const;
  virtual void polish(QPalette &palette) const;

  virtual QColor badge(BadgeRole role, BadgeState state);
  virtual QList<QColor> branchTopologyEdges();
  virtual QColor buttonChecked();
  virtual QPalette commitList();
  virtual QColor commitEditor(CommitEditor color);
  virtual QColor diff(Diff color);
  virtual QColor heatMap(HeatMap color);
  virtual QColor remoteComment(Comment color);
  virtual QColor star();

  static Theme *create(const QString &name = QString());

private:
  /// @brief Check if GNOME prefers dark mode
  /// @return True if color-scheme is prefer-dark
  static bool gnomePrefersDark();

  /// @brief Check if the Linux desktop environment is GNOME
  /// @return True if GNOME is the desktop environment
  static bool isGNOME();

  /// @brief Check whether dark mode is preferred
  /// @return True if dark mode should be used
  static bool isDarkMode();

private:
  bool mDark;
  QString mName;
  QDir mDir;
  QVariantMap mMap;
};

#endif
