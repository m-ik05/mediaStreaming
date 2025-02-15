# mediaStreaming
A simple project for the second semester of Computer Science course on Warsaw's University of Technology  
The purpose of it was to create a simple barebones database for streaming services:
1. The Story:
   
When words in bold are used it means that we’re referring to one of the classes.  
• Streaming (from the keyword, „media streaming”, shortened for ease of use)  
	  o The main class, that represents a media streaming platform. It possesses 
	  different shows or movies (described by the class “content”) that it provides 
	  towards its users (described by the class “user”). They do not provide their 
	  service everywhere however, only in select countries (described by the class 
	  “country”).  
	 
• User  
o A person that uses the media streaming platforms (described by the class 
“streaming”). They choose the shows and movies (content) that they add to 
watchlists, are watching, have watched, liked or disliked. They also live in a 
select country.  
o Restrictions: A user can only live in one country at any given moment.

• Content  
o Media that is available at a streaming platform for the user. Their availability 
differs from country to country. They can be:  
▪ On a watchlist  
▪ Watched  
▪ Liked  
▪ Disliked  
The last two points are mutually exclusive with each other. The first condition 
excludes all the rest (i.e. if the show is on a watchlist, it cannot be liked or be 
watched already).  
o Limits: Content can be available on up to two streaming platforms.  

• Country  
o The place where the user resides. It can have different streaming platforms 
and also different content. It mainly acts as a limiting factor, that decides 
what different instances of streaming and content classes a specific user
has access to.  

2. Memory

We have two Countries A and B, three streaming platforms 1, 2 and 3, two Users A and B and finally 4 Content classes – 1, 2, 3, 4.  
Country A has access to:  
Platform 1, 2  
Content 1, 2, 3  

Country B:  
Platform 1,3  
Content 1, 4  

Platform 1 has access to:  
Content 1, 2, 3  

Platform 2:  
Content 2, 3, 4

Platform 3:  
Content 1, 3, 4

User A is from Country A and is subscribed to platforms 1, 2, 3  
By looking at the memory map, we can see that he has access to Content 1, 2, 3.  
User B is from Country B and is subscribed to platforms 2 and 3.  
He can only access Content 1, 4. due to limited amount available in Country B, even 
though technically he should be able to access both B and D
