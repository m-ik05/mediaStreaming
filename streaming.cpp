#include "header.h"
streaming::streaming(string name)
{
    this->name = name;
}
streaming::~streaming()
{
}
string streaming::getName()
{
    return this->name;
}
int streaming::operator==(streaming s)
{
    if (this->name == s.name)
        return 1;
    else
        return 0;
}
int streaming::operator!=(streaming s)
{
    if (this->name != s.name)
        return 1;
    else
        return 0;
}
int streaming::addContent(content *c)
{
    if (c->platformList.size() < 2)
    {
        contentList.push_back(c);
        c->platformList.push_back(this);
        return 1;
    }
    return 0;
}
content *streaming::getContent(content c)
{
    if (contentList.empty())
        return nullptr;
    for (int i = 0; i < contentList.size(); i++)
    {
        if (c == *contentList[i])
            return contentList[i];
    }
    return nullptr;
}
void streaming::removeContent(content *c)
{
    if (contentList.empty())
        return;
    for (int i = 0; i < contentList.size(); i++)
    {
        if (*c == *contentList[i])
            contentList.erase(contentList.begin() + i);
    }
    for (int i = 0; i < c->platformList.size(); i++)
    {
        if (*this == *c->platformList[i])
            c->platformList.erase(c->platformList.begin() + i);
    }
}
void streaming::addUser(user *u)
{
    userList.push_back(u);
    u->subscribed.push_back(this);
}
user *streaming::getUser(user u)
{
    if (userList.empty())
        return nullptr;
    for (int i = 0; i < userList.size(); i++)
    {
        if (u == *userList[i])
            return userList[i];
    }
    return nullptr;
}
void streaming::removeUser(user *u)
{
    if (userList.empty())
        return;
    for (int i = 0; i < userList.size(); i++)
    {
        if (*u == *userList[i])
            userList.erase(userList.begin() + i);
    }
    for (int i = 0; i < u->subscribed.size(); i++)
    {
        if (*this == *u->subscribed[i])
            u->subscribed.erase(u->subscribed.begin() + i);
    }
}
void streaming::addCountry(country *c)
{
    countryList.push_back(c);
    c->platformList.push_back(this);
}
country *streaming::getCountry(country c)
{
    if (countryList.empty())
        return nullptr;
    for (int i = 0; i < countryList.size(); i++)
    {
        if (c == *countryList[i])
            return countryList[i];
    }
    return nullptr;
}
void streaming::removeCountry(country *c)
{
    if (countryList.empty())
        return;
    for (int i = 0; i < countryList.size(); i++)
    {
        if (*c == *countryList[i])
            countryList.erase(countryList.begin() + i);
    }
    for (int i = 0; i < c->platformList.size(); i++)
    {
        if (*this == *c->platformList[i])
            c->platformList.erase(c->platformList.begin() + i);
    }
}
void streaming::showContent()
{
    cout << "Content available on " << this->name << ":\n";
    for (int i = 0; i < contentList.size(); i++)
        cout << contentList[i]->getName() << '\n';
}
void streaming::showCountries()
{
    cout << this->name << " is available in these countries:\n";
    for (int i = 0; i < countryList.size(); i++)
        cout << countryList[i]->getName() << '\n';
}
void streaming::showUsers()
{
    cout << "Users subscribed to " << this->name << ":\n";
    for (int i = 0; i < userList.size(); i++)
        cout << userList[i]->getName() << '\n';
}