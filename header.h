#include <iostream>
#include <vector>
using namespace std;
class streaming;
class user;
class country;
class content;

class streaming
{
public:
    streaming(string);
    // constructor, with string as a parameter to name the specific class instance
    ~streaming();
    // destructor
    string getName();
    // returns the name of the platform
    int operator==(streaming);
    // overloading operator==
    int operator!=(streaming);
    // overloading operator!=

    int addContent(content *);
    // adds content to a platform (up to two platforms)
    // returns 1 upon adding content
    // returns 0 if this piece of content is already on two different platforms
    void removeContent(content *);
    // removes content from the platform
    void showContent();
    // show content available on the platform
    content *getContent(content);
    // returns a pointer to a specific piece of content available on the platform
    // returns nullptr if content is unavailable

    void addCountry(country *);
    // adds a streaming platform to the country
    void removeCountry(country *);
    // removes a streaming platform from the country
    void showCountries();
    // shows in which countries the platform is available in
    country *getCountry(country);
    // returns a pointer to a country if the platform is available in it
    // returns nullptr if platform is unavailable in the country

    void addUser(user *);
    // user subscribes to the platform, getting access to shows available on it
    void removeUser(user *);
    // user unsubscribes from a platform, losing access to content on it (so proper instances of content class should be removed from user's various lists)
    void showUsers();
    // shows all current users
    user *getUser(user);
    // returns a pointer to the user of the platform
    // returns nullptr if the user isn't subscribed to the platform

private:
    string name;                   // name of the streaming platform
    vector<content *> contentList; // list of all the content available on the platform
    vector<user *> userList;       // list of all of the users subscribed to the platform
    vector<country *> countryList; // list of all of the countries the platform is available in
    friend class user;
};
class user
{
public:
    user(country *, string);
    // constructor, with the country parameter as to specify where the user is located in and string as a parameter to name the specific class instance
    ~user();
    // destructor
    int operator==(user);
    // overloading operator==
    int operator!=(user);
    // overloading operator!=
    string getName();
    // returns the name of the user
    string getCountry();
    // returns the location of user

    void addWatchlist(content *);
    // adds content to user's watchlist
    void addWatched(content *);
    // adds content to users watched library (and removes it from the watchlist)
    void like(content *);
    // likes a show (also removes from the disliked list)
    void dislike(content *);
    // dislikes a show (also removes from the liked list)
    void removeContent(content *);
    // removes content from all lists
    void removeOpinion(content *);
    // removes like or dislike

    streaming *findPlatform(streaming);
    // returns pointer to a platform subscribed to by the user
    // return nullptr otherwise

    int isAvailable(content);
    // checks if content is available for user (whether in their country and/or their platform)
    content *findContent(content);
    // returns pointer to the piece of content if user has it on any list
    // returns nullptr otherwise
    int contentStatus(content);
    // returns one of  variables:
    // 1 - on a watchlist
    // 2 - watched
    // 3 - watched and liked
    // 4 - watched and disliked
    // 0 - not on any list
    void showWatchlist();
    // shows user's watchlist
    void showWatched();
    // shows user's watched list
    void showLiked();
    // shows user's liked list
    void showDisliked();
    // shows user's disliked list
    void showLibrary();
    // shows all of 4 previous categories
    void showPlatforms();
    // shows platforms the user is subscribed to

private:
    string name;                    // username
    string countryName;             // name of the country that the user is located in
    vector<content *> watchList;    // list of the content on the watchlist
    vector<content *> watchedList;  // list of all of the content watched
    vector<content *> liked;        // list of all of the liked shows
    vector<content *> disliked;     // list of all of the disliked shows
    vector<streaming *> subscribed; // list of all of the platforms that the user is subscribed to
    friend class streaming;         // as we add user to platform in streaming class, to change user's 'subscribed' list we need to friend class streaming
    friend class country;
};
class content
{
public:
    content(string);
    // constructor, with string as a parameter to name the specific class instance
    ~content();
    // destructor
    int operator==(content);
    // overloading operator==
    int operator!=(content);
    // overloading operator!=
    string getName();
    // returns the name of content

    void showCountries();
    // shows in which countries the content is available
    void showPlatforms();
    // shows on which platforms the content is available

private:
    string name;                      // name of the piece of content
    vector<country *> countryList;    // list of all of the countries content is available in
    vector<streaming *> platformList; // list of all of the platforms content is available in
    friend class streaming;           // as content is added to a platform through 'streaming' class, we need to friend it
    friend class country;             // as content is added to a country through 'country' class, we need to friend it
    friend class user;
};
class country
{
public:
    country(string);
    // constructor, with string as a parameter to name the specific class instance
    ~country();
    // destructor
    int operator==(country);
    // overloading operator==
    int operator!=(country);
    // overloading operator!=
    string getName();
    // returns the name of the country
    void addUser(user);
    // adds a user to userList

    void showPlatforms();
    // shows all streaming platforms available in the country

    void addContent(content *);
    // adds content to the country
    void removeContent(content *);
    // removes content from the country
    content *getContent(content);
    // returns pointer to content if available in the country
    // returns nullptr if otherwise
    void showContent();
    // shows all of the content available in the counrty

    void showUsers();
    // shows all of the users that are located in the country
    user *getUser(user);
    // returns pointer to a user if located in the country
    // returns nullptr if otherwise

private:
    string name;                      // name of the country
    vector<streaming *> platformList; // list of all of the platform available in the country
    vector<user *> userList;          // list of all of the users located in the country
    vector<content *> contentList;    // list of all of content available in the country
    friend class streaming;           // as we add country to platform in streaming class, to change country's 'platformList' we need to friend class streaming
    friend class user;                // user is added to country in 'user' class
};