#include "AssemblyPublicizer.h"

#include "Logger.h"

AssemblyPublicizer::AssemblyPublicizer()
{
    //
}

QString AssemblyPublicizer::Publicize(const QString& filePath, const QString& file, const QString& execPath) const
{
    QProcess* myProcess = new QProcess();
    myProcess->setWorkingDirectory(filePath);
    myProcess->start(execPath + "/AssemblyPublicizer", { file });

    if (myProcess->waitForFinished(5000))
    {
        QByteArray out_data = myProcess->readAllStandardOutput();
        QString out_string(out_data);
        Logger::get()->Print(out_string.toStdString().c_str());
        Logger::get()->Success("Publicized Assembly has been put under " + filePath + "/publicized_assemblies");
    }
    else
    {
        Logger::get()->Failed("Executable couldn't start...");
        return QString();
    }

    return filePath + "/publicized_assemblies";
}

QString AssemblyPublicizer::Bring(const QString& filePath, const QString& file, const QString& targetPath) const
{
    Logger::get()->Print("Trying to move & delete '" + filePath + "/" + file + "' to '" + targetPath + "/" + file + "'...");

    QFile f(filePath + "/" + file);
    if (!f.exists())
    {
        Logger::get()->Failed("'" + filePath + "/" + file + "' file couldn't be found !");
        return filePath + "/" + file;
    }

    QDir dir(targetPath);
    if (!dir.exists())
    {
        Logger::get()->Failed("'" + targetPath + "' directory couldn't be found !");
        return filePath + "/" + file;
    }

    f.rename(targetPath + "/" + file);
    QDir old(filePath);
    old.rmdir(filePath);

    Logger::get()->Success("Publicized Assembly has successfully been moved to '" + targetPath + "/" + file + "'.");
    return targetPath + "/" + file;
}
