#include "GithubReleaseGetter.h"
#include "Logger.h"

GithubReleaseGetter::GithubReleaseGetter(const QString& repoUrl)
	: repo(repoUrl)
{
    //
}

void GithubReleaseGetter::downloadLatest()
{
    QUrl url(repo + "/tags");
    //
}
