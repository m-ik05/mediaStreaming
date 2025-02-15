#include "header.h"
user::user(country *c, string name)
{
    this->name = name;
    this->countryName = c->getName();
    c->userList.push_back(this);
}
user::~user()
{
}
string user::getName()
{
    return this->name;
}
string user::getCountry()
{
    return this->countryName;
}
int user::operator==(user u)
{
    if (this->name == u.name)
        return 1;
    return 0;
}
int user::operator!=(user u)
{
    if (this->name != u.name)
        return 1;
    return 0;
}
streaming *user::findPlatform(streaming s)
{
    if (subscribed.empty())
        return nullptr;
    for (int i = 0; i < subscribed.size(); i++)
    {
        if (s == *subscribed[i])
            return subscribed[i];
    }
    return nullptr;
}

int user::isAvailable(content con)
{
    // flags for content availability.
    int a = 0; // a is equal to 1 if the platform itself is available in user's country
    int b = 0; // b is equal to 1 if content is available in user's country.
    int c = 0; // c is equal to 1 if content is on user's platforms
               // All three need to be positive for the content to be available

    int i;
    for (i = 0; i < subscribed.size(); i++)
    {
        for (int j = 0; j < subscribed[i]->countryList.size(); j++)
        {
            if (subscribed[i]->countryList[j]->name == countryName)
                a++;
        }
    }
    for (i = 0; i < subscribed.size(); i++)
    {
        for (int j = 0; j < con.platformList.size(); j++)
        {
            if (*subscribed[i] == *con.platformList[j])
                b++;
        }
    }
    for (i = 0; i < con.countryList.size(); i++)
    {
        if (countryName == con.countryList[i]->name)
            c++;
    }
    if (a && b && c)
        return 1;
    return 0;
}
void user::addWatchlist(content *c)
{
    int s = contentStatus(*c);
    if (!isAvailable(*c))
    {
        cout << "Content is unavailable for user!\n";
        return;
    }
    if (s == 0)
        watchList.push_back(c);
    else if (s == 1)
        cout << "Content is on a watchlist already!\n";
    else
        cout << "Content is already watched, remove it from there first\n";
}
void user::addWatched(content *c)
{
    int s = contentStatus(*c);
    if (!isAvailable(*c))
    {
        cout << "Content is unavailable for user!\n";
        return;
    }
    if (s == 0)
    {
        watchedList.push_back(c);
    }
    else if (s == 1)
    {
        removeContent(c);
        watchedList.push_back(c);
    }
    else
        cout << "Content is watched already!\n";
}
void user::like(content *c)
{
    int s = contentStatus(*c);
    if (s == 0 || s == 1)
        cout << "Content was never seen yet!\n";
    else if (s == 2)
        liked.push_back(c);
    else if (s == 3)
        cout << "Content is liked already!\n";
    else if (s == 4)
    {
        removeOpinion(c);
        liked.push_back(c);
    }
}
void user::dislike(content *c)
{
    int s = contentStatus(*c);
    if (s == 0 || s == 1)
        cout << "Content was never seen yet!\n";
    else if (s == 2)
        disliked.push_back(c);
    else if (s == 3)
    {
        removeOpinion(c);
        disliked.push_back(c);
    }
    else if (s == 4)
        cout << "Content is disliked already!\n";
}
void user::removeContent(content *c)
{
    int s = contentStatus(*c);
    if (s == 0)
        return;
    else if (s == 1)
    {
        for (int i = 0; i < watchList.size(); i++)
        {
            if (*c == *watchList[i])
                watchList.erase(watchList.begin() + i);
        }
    }
    else if (s == 2 || s == 3 || s == 4)
    {
        for (int i = 0; i < watchedList.size(); i++)
        {
            if (*c == *watchedList[i])
                watchedList.erase(watchedList.begin() + i);
        }
        if (s == 3)
        {
            for (int i = 0; i < liked.size(); i++)
            {
                if (*c == *liked[i])
                    liked.erase(liked.begin() + i);
            }
        }
        else if (s == 4)
        {
            for (int i = 0; i < disliked.size(); i++)
            {
                if (*c == *disliked[i])
                    disliked.erase(disliked.begin() + i);
            }
        }
    }
}
void user::removeOpinion(content *c)
{
    int s = contentStatus(*c);
    if (s == 3)
    {
        for (int i = 0; i < liked.size(); i++)
        {
            if (*c == *liked[i])
                liked.erase(liked.begin() + i);
        }
    }
    else if (s == 4)
    {
        for (int i = 0; i < disliked.size(); i++)
        {
            if (*c == *disliked[i])
                disliked.erase(disliked.begin() + i);
        }
    }
    else
        cout << "Content wasn't rated yet!\n";
}
content *user::findContent(content c)
{
    int i;
    if (!isAvailable(c))
        return nullptr;
    for (i = 0; i < watchList.size(); i++)
    {
        if (c == *watchList[i])
            return watchList[i];
    }
    for (i = 0; i < watchedList.size(); i++)
        if (c == *watchedList[i])
            return watchedList[i];
    return nullptr;
}
int user::contentStatus(content c)
{
    int i;
    if (!isAvailable(c))
        return 0;
    for (i = 0; i < watchList.size(); i++)
    {
        if (c == *watchList[i])
            return 1;
    }
    for (i = 0; i < watchedList.size(); i++)
    {
        if (c == *watchedList[i])
        {
            int j;
            for (j = 0; i < liked.size(); j++)
            {
                if (c == *liked[j])
                    return 3;
            }
            for (j = 0; i < disliked.size(); j++)
            {
                if (c == *disliked[j])
                    return 4;
            }
            return 2;
        }
    }
    return 0;
}
void user::showWatchlist()
{
    cout << "Watchlist of " << this->name << ":\n";
    for (int i = 0; i < watchList.size(); i++)
    {
        if (isAvailable(*watchList[i]))
            cout << watchList[i]->getName() << '\n';
    }
    cout << '\n';
}
void user::showWatched()
{
    cout << "Watched list of " << this->name << ":\n";
    for (int i = 0; i < watchedList.size(); i++)
    {
        if (isAvailable(*watchedList[i]))
            cout << watchedList[i]->getName() << '\n';
    }
    cout << '\n';
}
void user::showLiked()
{
    cout << "Liked list of " << this->name << ":\n";
    for (int i = 0; i < liked.size(); i++)
    {
        if (isAvailable(*liked[i]))
            cout << liked[i]->getName() << '\n';
    }
    cout << '\n';
}
void user::showDisliked()
{
    cout << "Disliked list of " << this->name << ":\n";
    for (int i = 0; i < disliked.size(); i++)
    {
        if (isAvailable(*disliked[i]))
            cout << disliked[i]->getName() << '\n';
    }
    cout << '\n';
}
void user::showLibrary()
{
    showWatchlist();
    showWatched();
    showLiked();
    showDisliked();
}
void user::showPlatforms()
{
    cout << "List of platforms subcribed to by " << this->name << ":\n";
    for (int i = 0; i < subscribed.size(); i++)
        cout << subscribed[i]->getName() << '\n';
    cout << '\n';
}