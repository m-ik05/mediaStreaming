#include "header.h"
content::content(string name)
{
    this->name = name;
}
content::~content()
{
}
string content::getName()
{
    return this->name;
}
int content::operator==(content c)
{
    if (this->name == c.name)
        return 1;
    return 0;
}
int content::operator!=(content c)
{
    if (this->name != c.name)
        return 1;
    return 0;
}
void content::showCountries()
{
    cout << "Content " << this->name << "is available in this countries:\n";
    for (int i = 0; i < countryList.size(); i++)
        cout << countryList[i]->getName() << '\n';
}
void content::showPlatforms()
{
    cout << "Content " << this->name << "is available on this platforms:\n";
    for (int i = 0; i < platformList.size(); i++)
        cout << platformList[i]->getName() << '\n';
}

country::country(string name)
{
    this->name = name;
}
country::~country()
{
}
int country::operator==(country c)
{
    if (this->name == c.name)
        return 1;
    return 0;
}
int country::operator!=(country c)
{
    if (this->name != c.name)
        return 1;
    return 0;
}
string country::getName()
{
    return this->name;
}
void country::showPlatforms()
{
    cout << "List of platforms available in " << this->name << ":\n";
    for (int i = 0; i < platformList.size(); i++)
        cout << platformList[i]->getName() << '\n';
    cout << '\n';
}
void country::addUser(user u)
{
    userList.push_back(&u);
}
void country::addContent(content *c)
{
    contentList.push_back(c);
    c->countryList.push_back(this);
}
void country::removeContent(content *c)
{
    if (contentList.empty())
        return;
    for (int i = 0; i < contentList.size(); i++)
    {
        if (*c == *contentList[i])
            contentList.erase(contentList.begin() + i);
    }
    for (int i = 0; i < c->countryList.size(); i++)
    {
        if (*this == *c->countryList[i])
            c->countryList.erase(c->countryList.begin() + i);
    }
}
content *country::getContent(content c)
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
void country::showContent()
{
    cout << "Content available in " << this->name << ":\n";
    for (int i = 0; i < contentList.size(); i++)
        cout << contentList[i]->getName() << '\n';
}
user *country::getUser(user u)
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
void country::showUsers()
{
    cout << "Users living in " << this->name << ":\n";
    for (int i = 0; i < userList.size(); i++)
        cout << userList[i]->getName() << '\n';
}