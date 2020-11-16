#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QTextStream>

#include "Logger.h"
#include "SettingFile.h"
#include "ThemeCache.h"
#include "BuildManager.h"


class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = Q_NULLPTR);
    void Cleanup();

private:
    Ui::ApplicationClass ui;

    SettingFile generalSettings, pathSettings;
    ThemeCache styleSheetCache;
    BuildManager* buildManager;

private slots:
    void FindGameFiles();
    void FindExiledRoot();
    void FindProjectFolder();
    void FindArchive();
};
