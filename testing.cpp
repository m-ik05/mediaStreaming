#include "header.h"
int main()
{
    // Checking constructors
    {
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show("show");

        // need to return name (and country for user) provided in declarations of variables
        if (netflix.getName() != "Netflix")
            cerr << "Wrong name for 'netflix' instance of streaming class!\n";
        if (a.getName() != "A")
            cerr << "Wrong name for 'a' instance of country class!\n";
        if (u1.getName() != "u1")
            cerr << "Wrong name for 'u1' instance of user class!\n";
        if (u1.getCountry() != "A")
            cerr << "Wrong country for 'u1' instance of user class!\n ";
        if (show.getName() != "show")
            cerr << "Wrong name for 'show' instance of content class!\n";
    }

    // Checking methods of streaming class
    {
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show("show");

        netflix.addContent(&show);
        //   check if 'show' was added correctly
        if (netflix.getContent(show) == nullptr || *netflix.getContent(show) != show)
            cerr << "Incorrect pointer for content in 'netflix' object after addContent\n";
        if (netflix.getContent(show)->getName() != "show")
            cerr << "Incorrect name of content in the 'netflix' object\n";
        netflix.removeContent(&show);
        // check if it was removed correctly
        if (netflix.getContent(show) != nullptr)
            cerr << "Incorrect pointer for content in 'netflix' object after removeContent\n";

        netflix.addUser(&u1);
        // check if 'u1' was added correctly
        if (netflix.getUser(u1) == nullptr || *netflix.getUser(u1) != u1)
            cerr << "Incorrect pointer for user in 'netflix' object after addUser\n";
        if (netflix.getUser(u1)->getName() != "u1")
            cerr << "Incorrect name of user in the 'netflix' object\n";
        netflix.removeUser(&u1);
        // we check if it was removed correctly
        if (netflix.getUser(u1) != nullptr)
            cerr << "Incorrect pointer for user in 'netflix' object after removeUser\n";

        netflix.addCountry(&a);
        // check if 'a' was added correctly
        if (netflix.getCountry(a) == nullptr || *netflix.getCountry(a) != a)
            cerr << "Incorrect pointer for country in 'netflix' object after addCountry\n";
        if (netflix.getCountry(a)->getName() != "A")
            cerr << "Incorrect name of country in the 'netflix' object\n";
        netflix.removeCountry(&a);
        // check if it was removed correctly
        if (netflix.getCountry(a) != nullptr)
            cerr << "Incorrect pointer for country in 'netflix' object after removeCountry\n";
    }

    // Checking methods of country class
    {
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show("show");

        a.addContent(&show);
        // check if 'show' was added correctly
        if (a.getContent(show) == nullptr || *a.getContent(show) != show)
            cerr << "Incorrect pointer for content in 'a' object after addContent\n";
        if (a.getContent(show)->getName() != "show")
            cerr << "Incorrect name of the country in the 'a' object\n";
        a.removeContent(&show);
        // check if it was removed correctly
        if (a.getContent(show) != nullptr)
            cerr << "Incorrect pointer for content in 'a' object after removeContent\n";

        // as user is added to a country just as it's instance is created, check if it was actually added correctly
        if (a.getUser(u1) == nullptr || *a.getUser(u1) != u1)
            cerr << "Incorrect pointer for user in 'a' object\n";
        if (a.getUser(u1)->getName() != "u1")
            cerr << "Incorrect name of the user in the 'a' object\n";
    }
    // Checking methods of user class
    {
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show("show");

        netflix.addUser(&u1);
        if (u1.findPlatform(netflix) == nullptr || *u1.findPlatform(netflix) != netflix)
            cerr << "Wrong pointer in 'u1' object after using addUser!\n";
        if (u1.findPlatform(netflix)->getName() != "Netflix")
            cerr << "Incorrect name of streaming in the 'u1' object\n";

        // check if adding piece of media to user's list works correctly
        a.addContent(&show);
        netflix.addContent(&show);
        netflix.addCountry(&a);
        u1.addWatchlist(&show);
        if (u1.findContent(show) == nullptr || *u1.findContent(show) != show)
            cerr << "Wrong pointer in 'u1' object after using addWatchlist!\n";
        if (u1.contentStatus(show) != 1)
            cerr << "Wrong value returned for contentStatus after adding to watchlist!\n";

        // check if you can like or dislike a piece of media even when not watched
        u1.like(&show);
        if (u1.contentStatus(show) != 1)
            cerr << "Wrong value returned for contentStatus after liking content that was not watched\n";
        u1.dislike(&show);
        if (u1.contentStatus(show) != 1)
            cerr << "Wrong value returned for contentStatus after disliking content that was not watched\n";

        // check changes to content's status after changing it's list placement
        u1.addWatched(&show);
        if (u1.contentStatus(show) != 2)
            cerr << "Wrong value returned for contentStatus after adding to watched\n";
        u1.like(&show);
        if (u1.contentStatus(show) != 3)
            cerr << "Wrong value returned for contentStatus after liking\n";
        u1.dislike(&show);
        if (u1.contentStatus(show) != 4)
            cerr << "Wrong value returned for contentStatus after disliking\n";
        u1.removeOpinion(&show);
        if (u1.contentStatus(show) != 2)
            cerr << "Wrong value returned for contentStatus after removing like/dislike\n";
        u1.removeContent(&show);
        if (u1.contentStatus(show) != 0)
            cerr << "Wrong value returned for contentStatus after removing from all lists\n";
    }

    // Checking conditions and content limit
    {
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show("show");

        // testing when unavailable in the user's country
        netflix.addUser(&u1);
        netflix.addContent(&show);
        a.addContent(&show);
        u1.addWatchlist(&show);
        if (u1.contentStatus(show) != 0 || u1.findContent(show) != nullptr)
            cerr << "Error when testing unavailability in country\n";
        netflix.addCountry(&a);
        u1.addWatchlist(&show);
        if (u1.contentStatus(show) != 1 || u1.findContent(show) == nullptr)
            cerr << "Error when testing availability in country\n";

        // testing when user doesn't subscribe to any platform with access to selected content
        netflix.removeUser(&u1);
        if (u1.contentStatus(show) != 0 || u1.findContent(show) != nullptr)
            cerr << "Error when testing unavailability on platform\n";
        netflix.addUser(&u1);
        if (u1.contentStatus(show) != 1 || u1.findContent(show) == nullptr)
            cerr << "Error when testing availability on platform\n";

        // testing content limitations
        streaming prime("Prime");
        streaming hbo("HBO");
        if (!prime.addContent(&show))
            cerr << "Error when adding 'show' object to second platform\n";
        if (hbo.addContent(&show))
            cerr << "Error when adding 'show' object to third platform\n";
        prime.removeContent(&show);
        if (!hbo.addContent(&show))
            cerr << "Error when adding 'show' object to third platform after deleting it from second one\n";
    }

    /*start of testing
    {
        // checking the printing functions
        streaming netflix("Netflix");
        country a("A");
        country b("B");
        user u1(&a, "u1");
        user u2(&b, "u2");
        content show1("1");
        content show2("2");
        content show3("3");

        netflix.addContent(&show1);
        netflix.addContent(&show2);
        netflix.addContent(&show3);
        netflix.addCountry(&a);
        netflix.addCountry(&b);
        netflix.addUser(&u1);
        netflix.addUser(&u2);

        cout << "CHECKING PRINTING FUNCTIONS FOR STREAMING CLASS\n";
        netflix.showContent();
        cout << '\n';
        netflix.showCountries();
        cout << '\n';
        netflix.showUsers();
    }

    {
        // checking printing methods for user's list
        streaming netflix("Netflix");
        country a("A");
        user u1(&a, "u1");
        content show1("1");
        content show2("2");
        content show3("3");

        netflix.addUser(&u1);
        netflix.addCountry(&a);
        netflix.addContent(&show1);
        netflix.addContent(&show2);
        netflix.addContent(&show3);
        a.addContent(&show1);
        a.addContent(&show2);
        a.addContent(&show3);

        u1.addWatchlist(&show1);
        u1.addWatched(&show2);
        u1.like(&show2);
        u1.addWatched(&show3);
        u1.dislike(&show3);

        cout << "CHECKING PRINTING FUNCTIONS FOR USER CLASS\n";
        u1.showLibrary();
        u1.showPlatforms();
    }

    end of testing */
    cerr
        << "End of tests\n";
    return 0;
}