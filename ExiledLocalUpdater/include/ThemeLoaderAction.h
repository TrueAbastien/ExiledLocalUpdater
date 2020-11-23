#pragma once
#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include "ThemeCache.h"

class ThemeLoaderAction : public QAction
{
	Q_OBJECT

public:
	ThemeLoaderAction(QMenu* parent, QWidget* app, const QString& file, ThemeCache* cache);

private:
	QString fileName;
	ThemeCache* themeCache;
	QWidget* wnd;

private slots:
	void LoadTheme();
};