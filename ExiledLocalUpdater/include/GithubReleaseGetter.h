#pragma once
#include <QObject>
#include <QTimer>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QSslError>

#include <QMainWindow>

class GithubReleaseGetter : public QObject
{
	Q_OBJECT

public:
	struct DownloadedArchive
	{
		QString path;
		QString tag;

		bool latestSucessfull = false;
	};

	GithubReleaseGetter(const QString& repoUrl);
	void downloadLatest();

	DownloadedArchive get() const { return latest; }

private:
	QString repo;
	DownloadedArchive latest;

	//

private slots:
	//

signals:
	void reply();
};