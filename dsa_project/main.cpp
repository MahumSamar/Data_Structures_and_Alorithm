/*
 * *Project By
 * Group Members:
 * Fatima Seemab (291310)
 * Mahum Samar (290647)
 * BSCS-9B
 * CS-250 DATA STRUCTURES AND ALGORITHMS
 *
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//declaring the classes
class Movie;

class MovieNode;

class MovieList;

class Actor;

class ActorNode;

class ActorList;

class Director;

class DirectorNode;

class DirectorList;

class Genre;

class GenreNode;

class GenreList;

class MovieNodeIndexing;

class Controller;

class Movie {
    //movie class containing the data fields about the movie.
public:
    string MovieTitle;
    GenreList *Genre;   //genre list

    unsigned short int titleYear;
    float imdbScore;
    Director *director;     //director info
    unsigned short int numCriticForReviews;
    unsigned short int duration;
    ActorList *actorInMovieList;        //actor list who acted in the movie

    unsigned int gross;
    unsigned int numVotedUsers;
    unsigned int castTotalFacebookLikes;
    unsigned short int facenumberInPoster;
    string plotKeywords;

    string movieImdbLink;
    unsigned short int numUserForReviews;
    string language;
    string country;
    string contentRating;
    unsigned int budget;

    float aspectRatio;
    unsigned int movieFacebookLikes;
    string color;

};

class MovieNode {
    //class to create the movie node for the movie list
public:
    Movie *movie;
    MovieNode *next;
};

class MovieNodeIndexing {
public:
    MovieNode *data;
    MovieNodeIndexing *next;
    MovieNodeIndexing *prev;
};

class MovieList {
public:
    // class to create the movie list
    MovieNode *startMovieNode;
    MovieNode *lastMovieNode;
    MovieNodeIndexing *startindex;
    MovieNodeIndexing *lastindex;
    MovieNodeIndexing *loc;
    MovieNodeIndexing *ploc;

    bool isEmpty() {
        //method to check if the list is empty
        return startMovieNode == NULL;
    }

    MovieList() {
        //constructor
        startMovieNode = NULL;
        lastMovieNode = NULL;
        startindex = NULL;
        lastindex = NULL;
        loc = NULL;
        ploc = NULL;
    }

    void PrintMovieList(MovieList *movieList) {
        //method to print the movie list with all details of the movie
        if (isEmpty()) {
            cout << "List is empty." << endl;
        } else {
            MovieNode *temp = movieList->startMovieNode;
            while (temp != NULL) {
                movieList->PrintNode(temp);
                temp = temp->next;
            }
        }
    }

    void InsertMovie(MovieNode *movieNode) {
        //method to insert a movie node in movie list
        if (isEmpty()) {
            //if list empty
            startMovieNode = movieNode;
            lastMovieNode = movieNode;
        } else {
            //if list has existing nodes
            lastMovieNode->next = movieNode;
            lastMovieNode = movieNode;
        }

    }

    void PrintNode(MovieNode *movieNode);

    void InsertMoviesInSubList(Movie *movie) {
        //method to insert the movie list in the main actor list in which the actor acted

        MovieNode *moviesActedInNode = new MovieNode();     //movie node
        moviesActedInNode->movie = movie;
        if (startMovieNode == NULL) {
            startMovieNode = moviesActedInNode;
            lastMovieNode = moviesActedInNode;
        } else {
            lastMovieNode->next = moviesActedInNode;
            lastMovieNode = moviesActedInNode;
        }

    }

    void PrintMoviesActedIn(MovieList *moviesActedInList) {
        //method to print movies in which specific actor acted
        MovieNode *temp = moviesActedInList->startMovieNode;
        while (temp != NULL) {
            //prints until the list is empty
            cout << temp->movie->MovieTitle << " ";
            temp = temp->next;
        }
    }

    void PrintMoviesDirected(MovieList *directedMoviesList) {
        //method to print the movies directed by a director
        MovieNode *temp = directedMoviesList->startMovieNode;
        while (temp != NULL) {
            cout << temp->movie->MovieTitle << " ";
            temp = temp->next;
        }
    }

    /*************************************************** 8th Function *******************************************************************/

    void PrintMovieDetail(string movieName) {

        //method to print a movie detail of the movie searched by the user
        MovieNode *movieNode = startMovieNode;
        //loop until the list end
        while (movieNode != NULL) {
            while (movieNode != NULL && ((movieNode->movie->MovieTitle).substr(0, 5) != movieName.substr(0, 5))) {
                //loop until the searched movie is found by comparing first six letter of the movie search by user or the main movie list ends
                movieNode = movieNode->next;
            }
            if (movieNode == NULL && ((movieNode->movie->MovieTitle).substr(0, 5) != movieName.substr(0, 5))) {
                //if the movie is not found and the list end
                cout << "Movie not found" << endl;
                return;
            }

            PrintNode(movieNode);       //if the movie is found it prints its detail
            movieNode = movieNode->next;
        }


    }  //Worst Case time complexity for this function is bigO(n2)

    /*******************************************Year Based and Rating Based functions ***************************************************/

    //Method to check if the year wise sorted or rating wise sorted list is empty or not
    bool isEmptyIndex() {
        if (startindex == NULL) {
            return true;
        } else { return false; }
    }


    //Used for yearwise and rating wise sorting
    //Method to insert the node at front of list
    void InsertAtFront(MovieNodeIndexing *movie) {
        startindex->prev = movie;
        movie->next = startindex;
        startindex = movie;
    }

    //Used for yearwise and rating wise sorting
    //Method to insert the node at last of list
    void InsertAtEnd(MovieNodeIndexing *movie) {
        movie->prev = ploc;
        ploc->next = movie;
        movie->next = NULL;
        lastindex = movie;
    }

    void Index() {// A method to reset the values of set Index and LastIndex to NULL
        //Maintains two lists yearwise and ratingwise movielist
        startindex = NULL;
        lastindex = NULL;

    }

    /*********************************************** 10th Function ***********************************************************************/

    void InsertYearWise(MovieNode *movie) {//movie node indexing class object is created
        MovieNodeIndexing *movienode = new MovieNodeIndexing();
        movienode->data = movie;
        //for inserting 1st node in list
        if (isEmptyIndex()) {
            startindex = movienode;
            lastindex = movienode;
        } else {//always searches in list except for one to insert at logical position
            SearchYearWise(movie->movie->titleYear);

            //given year till has no movie in the list
            if (loc == NULL) {
                if (ploc == NULL) {   //newnode is inserted at front of list
                    InsertAtFront(movienode);
                } else {

                    if (ploc == lastindex) {
                        //newnode is inserted at end of list
                        InsertAtEnd(movienode);
                    }
                        //if value should be inserted in somewhere between front and end of list
                    else {//specified by loc and ploc of search function
                        movienode->next = ploc->next;
                        ploc->next = movienode;
                        movienode->prev = ploc;

                    }
                }

            }
                //if given year has movie in the list
            else {
                if (ploc == NULL) {   //value is found at start
                    InsertAtFront(movienode);
                }
                if (loc->next !=
                    NULL) {   //value is found somewhere in between front and last,value should be inserted before the existing one
                    movienode->next = loc->next;
                    loc->next = movienode;
                    movienode->prev = loc;
                } else {   //if value is found at last, new node should be inserted after the existing value
                    InsertAtEnd(movienode);
                }

            }

        }
        //Worst Case time complexity for this function is bigO(n)
    }

    //To print the movies list sorted yearwise
    void printMovieYearWise() {
        cout << "Movie Title" << "         " << "release year" << endl;
        MovieNodeIndexing *temp = startindex;
        while (temp != NULL) {
            cout << "**********************************************************" << endl << endl;
            cout << temp->data->movie->MovieTitle << "            ";
            cout << temp->data->movie->titleYear << endl << endl;
            temp = temp->next;
        }
    }

    //To search in list yearwise used in 10th to locate the position of new node
    void SearchYearWise(int titleYear) {
        //method to search  the logical position for the new node insertion
        if (isEmptyIndex()) {
            cout << "There is no value in list";
            return;
        }
        //Loc is initialized to start and ploc to null
        loc = startindex;
        ploc = NULL;

        //loop searches until the whole list is accessed or the value is found
        while ((loc != NULL) && (loc->data->movie->titleYear < titleYear)) {
            //ploc contains previous of loc
            ploc = loc;

            //loc is everytime pointed to its next
            loc = loc->next;
        }
        //if the whole list is accessed and the value is not found loc is assigned null
        if (loc != NULL && loc->data->movie->titleYear != titleYear) {
            loc = NULL;
        }

    }
    /***************************************************** 12th Function *******************************************************************/
    //Method to insert in a list sorted rating wise
    void InsertRatingWise(MovieNode *movie) {

        MovieNodeIndexing *MovieRating = new MovieNodeIndexing();
        //Object of movienodeindexing data partpoints to the address  of movienode
        MovieRating->data = movie;
        if (isEmptyIndex()) {

            startindex = MovieRating;
            lastindex = MovieRating;
        } else {
            //Search in the list if any movie already have this rating
            SearchRatingWise(movie->movie->imdbScore);
            if (loc == NULL) {
                if (ploc == NULL) {
                    InsertAtFront(MovieRating);
                } else {

                    if (ploc == lastindex) {
                        InsertAtEnd(MovieRating);
                    } else {
                        MovieRating->next = ploc->next;
                        ploc->next = MovieRating;
                        MovieRating->prev = ploc;

                    }
                }

            }
            if (loc != NULL) {
                if (ploc == NULL) {
                    InsertAtFront(MovieRating);
                }
                if (loc->next != NULL) {
                    MovieRating->next = loc->next;
                    loc->next = MovieRating;
                    MovieRating->prev = loc;
                } else {
                    InsertAtEnd(MovieRating);
                }

            }

        }


        //Worst Case time complexity for this function is bigO(n)
    }

    void SearchRatingWise(float score) {   //Method to search rating wise in list
        if (isEmptyIndex()) {
            cout << "There is no value in list";
            return;
        }
        loc = startindex;
        ploc = NULL;
        while ((loc != NULL) && (loc->data->movie->imdbScore < score)) {
            //ploc contains previous of loc
            ploc = loc;
            //loc is everytime pointed to its next
            loc = loc->next;
        }
        //if the whole list is accessed and the value is not found loc is assigned null
        if (loc != NULL && loc->data->movie->imdbScore != score) {
            loc = NULL;
        }


    }

    //Method to print the list mantained on basis of rating
    void printMovieRatingWise() {
        MovieNodeIndexing *temp = startindex;
        cout << "Movie Title" << "          " << "Rating" << endl;
        while (temp != NULL) {
            cout << "*************************************************************" << endl << endl;

            cout << temp->data->movie->MovieTitle << "           ";
            cout << temp->data->movie->imdbScore << endl << endl;
            temp = temp->next;
        }
    }


    /******************************************************* 9th Function *****************************************************************/
    void SearchMoviesInGivenYear(int year) {

        MovieNodeIndexing *temp;
        //a pointer of MovieNodeIndexing is created and pointed to start of index
        temp = startindex;

        //checks if the whole list is not accessed and the movie in list still has earlier released year than the given
        while (temp != lastindex && temp->data->movie->titleYear < year) {
            //temp is pointed to its next after every iteration
            temp = temp->next;
        }

        //When the movie in list released year in list equals to the given
        if (temp->data->movie->titleYear == year) {
            //wjile loop to retrieve all movies of relesed yaer
            while (temp->data->movie->titleYear == year) {
                cout << temp->data->movie->MovieTitle << endl;
                temp = temp->next;
            }
            return;
        }
        //The Worst case complexity for this function is bigO(n)
    }


};

class Actor {
    //class containing data fields about the actor.
public:
    string name;
    unsigned short int facebook_likes_count;
    MovieList *moviesActedInList;
};

class ActorNode {
    //class to create the node for the actor list
public:
    Actor *actor;
    ActorNode *next;
};

class ActorList {
    //class to create the list for the actor
public:
    ActorNode *start_ActorList;
    ActorNode *last_ActorList;
    //MoviesActedInList *moviesActedInList;

    ActorList() {
        start_ActorList = NULL;
        last_ActorList = NULL;
    }

    bool isEmpty() {
        return start_ActorList == NULL;
    }

    ActorNode *SearchActor(string name) {
        //method to search the actor in the main actor list
        //new temp node for storing head of list
        ActorNode *tempActorNode = start_ActorList;
        if (isEmpty()) {
            //if list is empty
            tempActorNode = NULL;
        } else {
            //if list not empty.
            while (tempActorNode != NULL && tempActorNode->actor->name != name) {
                //search until the actor is found or the list end
                tempActorNode = tempActorNode->next;
            }

        }

        return tempActorNode;
    }

    ActorNode *InsertActor(Actor *actor) {
        //method to insert the actor in the actor list
        //temp node to search if the actor already exists or not
        ActorNode *tempActorNode = SearchActor(actor->name);

        if (tempActorNode == NULL) {
            // if the actor not exist before
            ActorNode *actorNode = new ActorNode();
            actor->moviesActedInList = new MovieList();

            actorNode->actor = actor;

            if (isEmpty()) {
                //if the list is empty
                start_ActorList = actorNode;
                last_ActorList = actorNode;
            } else {
                //if there are already nodes in the list
                last_ActorList->next = actorNode;
                last_ActorList = actorNode;
            }
            tempActorNode = actorNode;
        }
        return tempActorNode;
    }

    void PrintNode(ActorNode *actorNode) {
        //prints the actor details
        cout << "Actor Name : " << actorNode->actor->name << "\t";
        cout << "Actor FB Likes : " << actorNode->actor->facebook_likes_count << "\t";
        actorNode->actor->moviesActedInList->PrintMoviesActedIn(actorNode->actor->moviesActedInList);
        cout << endl;
    }

    void PrintActorList(ActorList *actorList) {
        //method to print the actor list
        if (isEmpty()) {
            cout << "List is Empty." << endl;
        } else {
            ActorNode *temp = actorList->start_ActorList;
            while (temp != NULL) {
                actorList->PrintNode(temp);
                temp = temp->next;
            }
        }
    }

    void InsertActorInMovieList(Actor *actor) {
        //method to insert actor in the movie list who acted in that specific movie
        ActorNode *actorInMovieNode = new ActorNode();
        actorInMovieNode->actor = actor;

        if (start_ActorList == NULL) {
            start_ActorList = actorInMovieNode;
            last_ActorList = actorInMovieNode;
        } else {
            last_ActorList->next = actorInMovieNode;
            last_ActorList = actorInMovieNode;
        }
    }

    void PrintActorsInMovieList(ActorList *actorInMovieList) {
        //method to print the actors who acted in that movie
        ActorNode *temp = actorInMovieList->start_ActorList;
        while (temp != NULL) {
            cout << "Actor Name : " << temp->actor->name << "\t";
            cout << "Actor FB Likes :" << temp->actor->facebook_likes_count << "  ";
            temp = temp->next;
        }
    }

    /********************************************** 1st function ********************************************************************/
    void SearchActorDetails(string name) {
        //1st function
        //method to search the actor details which user enter if it exist in list
        MovieList *reference = new MovieList();
        ActorNode *actorNode = SearchActor(name);
        if (actorNode != NULL) {
            //if the actor exist
            int count = 0;      //variable to count the number of movie in which the actor acted
            MovieNode *temp = actorNode->actor->moviesActedInList->startMovieNode;
            while (temp != NULL) {
                reference->InsertYearWise(temp);
                count++;
                temp = temp->next;
            }
            reference->printMovieYearWise();        //prints the movies yearwise
            cout << "Number of movies acted in:\t" << count << endl;
        }
    }
    //Worst Case time complexity is bigO(n)

    /****************************************************** 2nd function ****************************************************************/
    void SearchCoActorOfActor(string name) {

        //actor node for searching the actor
        ActorNode *actorSearched = SearchActor(name);
        if (actorSearched == NULL) {
            cout << "Actor not found" << endl;
        } else {
            //if the actor is found
            MovieNode *tempMovieNode = actorSearched->actor->moviesActedInList->startMovieNode;
            while (tempMovieNode != NULL) {
                //prints the movie name and his co_actors
                cout << "Movie: " << tempMovieNode->movie->MovieTitle << "\n";
                cout << "Co-Actors are:\n";
                tempMovieNode->movie->actorInMovieList->PrintActorsInMovieList(tempMovieNode->movie->actorInMovieList);
                cout << "\n*************************************************************\n";
                tempMovieNode = tempMovieNode->next;
            }
        }
    }
    //Worst case Time Complexity of this function is bigO(n)
    /**************************************************** 3rd Function ********************************************************************/
    void SearchUniqueCoActorOfActor(ActorList *actorList, string name) {

        //prints the unique co_actors of the actor and the movies in which they acted together
        ActorList *uniqueCoActorList = new ActorList();     //list to store the actors
        MovieNode *tempMovieNode;       //node to store the movie
        ActorNode *tempActorNode;

        ActorNode *actorFound = actorList->SearchActor(name);
        if (actorFound != NULL) {
            //if the actor is found, points to the first movie in he acted
            tempMovieNode = actorFound->actor->moviesActedInList->startMovieNode;
            while (tempMovieNode != NULL) {
                //loop until his movie ends
                //temprary actor node to point the actor node of co_actors who acted in the movie of the searched actor
                tempActorNode = tempMovieNode->movie->actorInMovieList->start_ActorList;
                while (tempActorNode != NULL) {
                    //loop until his co-actor list end
                    if (tempActorNode->actor->name != name) {
                        // if the actor name is not same as the searched actor
                        ActorNode *insertedActor;
                        Actor *coActor = new Actor();       // new actor point object to store the actor so that the original actor list is not modified
                        coActor->name = tempActorNode->actor->name;
                        coActor->facebook_likes_count = tempActorNode->actor->facebook_likes_count;
                        insertedActor = uniqueCoActorList->InsertActor(
                                coActor);          //insert the actor in the new actor list
                        insertedActor->actor->moviesActedInList->InsertMoviesInSubList(tempMovieNode->movie);
                    }
                    tempActorNode = tempActorNode->next;
                }
                tempMovieNode = tempMovieNode->next;
            }
        }

        //prints co-actors
        uniqueCoActorList->PrintActorList(uniqueCoActorList);
        cout
                << "\n************************************************************************************************************************\n";
        delete uniqueCoActorList;        //deletes the list from the heep to free memory
        //  Time Complexity for this function is big(O) of n2;
    }

    /********************************************************* 5th function ***************************************************************/
    void ActorsWorkTogether(string name1, string name2) {

        ActorNode *actor1 = SearchActor(name1);
        ActorNode *actor2 = SearchActor(name2);
        MovieNode *temp1 = actor1->actor->moviesActedInList->startMovieNode;
        MovieNode *temp2 = actor2->actor->moviesActedInList->startMovieNode;
        while (temp1 != NULL) {
            while (temp2 != NULL) {
                if (temp1->movie != temp2->movie) {
                    temp2 = temp2->next;
                } else {
                    cout << "They have acted together in following movies" << endl;
                    cout << temp2->movie->MovieTitle << endl;
                    temp2 = temp2->next;
                }
            }
            temp2 = actor2->actor->moviesActedInList->startMovieNode;
            temp1 = temp1->next;
        }
        if (temp1 != NULL) {
            cout << "They have acted together in following movies" << endl;
            cout << temp1->movie->MovieTitle << endl;
            temp1 = temp1->next;
        }
        //Worst Case Complexity of above function is big (O) of n2
    }

    /***************************************************** 4th Function *******************************************************************/
    void SearchCoCoActorOfActor(ActorList *actorList, string name) {

        //method to search the co-actors of co-actors of search actor
        ActorList *uniqueCoCoActorList = new ActorList();
        MovieNode *tempMovieNode;
        ActorNode *tempActorNode;

        ActorNode *actorFound = actorList->SearchActor(name);
        if (actorFound != NULL) {
            tempMovieNode = actorFound->actor->moviesActedInList->startMovieNode;
            while (tempMovieNode != NULL) {
                tempActorNode = tempMovieNode->movie->actorInMovieList->start_ActorList;
                while (tempActorNode != NULL) {
                    if (tempActorNode->actor->name != name) {
                        ActorNode *insertedActor;
                        Actor *coActor = new Actor();
                        coActor->name = tempActorNode->actor->name;
                        coActor->facebook_likes_count = tempActorNode->actor->facebook_likes_count;
                        insertedActor = uniqueCoCoActorList->InsertActor(coActor);
                        insertedActor->actor->moviesActedInList->InsertMoviesInSubList(tempMovieNode->movie);
                    }
                    tempActorNode = tempActorNode->next;
                }
                tempMovieNode = tempMovieNode->next;
            }
        }


        //uniqueCoCoActorList -> PrintActorList(uniqueCoCoActorList);

        ActorNode *temp = uniqueCoCoActorList->start_ActorList;
        while (temp != NULL) {
            cout << "Co-Actor : " << temp->actor->name << endl;
            cout << "************************************\n";
            cout << "Co-Actors of Co-Actor:\n";
            uniqueCoCoActorList->SearchUniqueCoActorOfActor(actorList, temp->actor->name);
            temp = temp->next;

        }

    }//Worst Case Complexity is bigO(n2)

};

class Director {
    //director class containing data fields about director.
public:
    string name;
    unsigned short int directorFacebookLikes;
    MovieList *directedMoviesList;
};

class DirectorNode {
    //class to create the node for the director list
public:
    Director *director;
    DirectorNode *next;
};

class DirectorList {
    //class to create the director list.
public:
    DirectorNode *startDirectorList;
    DirectorNode *lastDirectorList;

    bool isEmpty() {
        return startDirectorList == NULL;
    }

    DirectorNode *SearchDirector(string name) {
        //method to search the director if it already exists.
        //creating temporary directornode
        DirectorNode *tempDirectorNode = new DirectorNode();
        if (isEmpty()) {
            //if the list is empty
            tempDirectorNode = NULL;
        } else {
            //if list already have some nodes.
            tempDirectorNode = startDirectorList;
            while (tempDirectorNode != NULL && tempDirectorNode->director->name != name) {
                //transverse the list until the name is found.
                tempDirectorNode = tempDirectorNode->next;
            }

        }
        //returns the result.
        return tempDirectorNode;
    }

    DirectorNode *InsertDirector(Director *director) {
        //method to insert the director in director list
        DirectorNode *tempDirectorNode = SearchDirector(director->name);

        if (tempDirectorNode == NULL) {
            DirectorNode *directorNode = new DirectorNode();
            director->directedMoviesList = new MovieList();

            directorNode->director = director;

            if (isEmpty()) {
                startDirectorList = directorNode;
                lastDirectorList = directorNode;
            } else {
                lastDirectorList->next = directorNode;
                lastDirectorList = directorNode;
            }
            tempDirectorNode = directorNode;
        }

        return tempDirectorNode;
    }

    void PrintNode(DirectorNode *directorNode) {
        //method to print the director information
        cout << "Director Name : " << directorNode->director->name << "\t";
        cout << "Director FB Likes : " << directorNode->director->directorFacebookLikes << "\t";
        directorNode->director->directedMoviesList->PrintMoviesDirected(directorNode->director->directedMoviesList);
        cout << endl;
    }

    void PrintDirectorList(DirectorList *directorList) {
        //method to print director list
        if (isEmpty()) {
            cout << "The list is empty." << endl;
        } else {
            DirectorNode *temp = directorList->startDirectorList;
            while (temp != NULL) {
                directorList->PrintNode(temp);
                temp = temp->next;
            }
        }
    }

    /************************************************************ 6th Function ************************************************************/
    void SearchDirectorByName(string name) {

        // creating temporary directornode
        DirectorNode *tempDirectorNode = new DirectorNode();
        tempDirectorNode = SearchDirector(name);
        MovieList *moviesbydirector = new MovieList();
        moviesbydirector = tempDirectorNode->director->directedMoviesList;
        moviesbydirector->PrintMoviesDirected(moviesbydirector);
    }
    //Worst Case Complexity of Function 6 is n
};

//Genre Class
class Genre {
public:
    string genre;
};

//Genre Node class
class GenreNode {
public:
    Genre *data;
    GenreNode *next;
};

//GenreList class
class GenreList {
public:
    //To point to the genre list start and last
    GenreNode *start;
    GenreNode *last;

    //to check if list is empty or not
    bool isEmpty() {
        if (start == NULL) {
            return true;
        } else {
            return false;
        }
    }

    //Insert genrenode in genre list
    GenreNode *InsertGenreNode(GenreNode *pointer) {

        GenreNode *node = new GenreNode();
        //Searches genre if exist already in list,address is returned
        node = SearchGenre(pointer->data->genre);

        if (node == NULL) {//if not in list,node is created
            GenreNode *genres = new GenreNode();
            genres->data = pointer->data;

            //if is empty inserted at front
            if (isEmpty()) {
                start = genres;
                last = genres;
            }
                //otherwise inserted at last
            else {
                last->next = genres;
                last = genres;
            }
            //to return node is pointed to genre
            node = genres;
        }

        return node;
    }

    GenreNode *SearchGenre(string genre) {
        //To search a genre in list and to returns the address

        GenreNode *temp = new GenreNode();
        if (isEmpty()) {
            temp = NULL;
        } else {
            //if list already have some nodes.
            temp = start;
            while (temp != NULL && temp->data->genre != genre) {
                //transverse the list until the name is found.
                temp = temp->next;
            }
            if (temp != NULL && temp->data->genre != genre) {
                //if the node is not found.
                temp = NULL;
            }
        }
        //returns the result.
        return temp;
    }

    //For inserting in movies particular genre list
    void InsertGenreInMovie(Genre *genre) {
        GenreNode *Genrenode = new GenreNode();
        Genrenode->data = genre;

        if (start == NULL) {
            start = Genrenode;
            last = Genrenode;
        } else {
            last->next = Genrenode;
            last = Genrenode;
        }
    }

    //For printing genre of a particular movie
    void PrintGenreInMovie(GenreList *genrelist) {
        GenreNode *temp = genrelist->start;
        while (temp != NULL) {
            cout << temp->data->genre << "  ";
            temp = temp->next;
        }

    }

    /*************************************************** Function No 11 ***********************************************************/
    void PrintMoviesofCertainGenre(string genrename, MovieList *movielist) {
        //Genre Node and MovieNodes are created to point to the start of list

        GenreNode *genre = new GenreNode;
        MovieNode *temp = new MovieNode();
        temp = movielist->startMovieNode;
        genre = temp->movie->Genre->start;

        MovieList *reference = new MovieList();

        while (temp != NULL) {//loop iterates over the whole movielist
            while (genre != NULL) {
                //loop iterates for all genre nodes of movie

                if (genre->data->genre == genrename) {
                    //movies has particular genre insert in list ratingwise
                    reference->InsertRatingWise(temp);
                }
                genre = genre->next;
            }

            temp = temp->next;
            if (temp != NULL) {//for next movie genre is pointed to start
                genre = temp->movie->Genre->start;
            }
        }

        //prints rating wise list of movies
        reference->printMovieRatingWise();
        //Worst Case Complexity of above function is bigO of n2
    }

    /****************************************************** Function 7 ************************************************************/
    void PrintDirectorforGenre(string genrename, MovieList *movieList) {
        //Print director of a certain genre
        //Genre Node and MovieNodes are created to point to the start of list

        GenreNode *genre = new GenreNode;
        MovieNode *temp = new MovieNode();
        temp = movieList->startMovieNode;
        genre = temp->movie->Genre->start;
        while (temp != NULL) {//iterates for whole list of movies
            while (genre != NULL) {
                //iterates for whole list of genre of particular movie
                if (genre->data->genre ==
                    genrename) {   //if movie is of that particular genre, prints its director name
                    cout << "****************************************************" << endl << endl;
                    cout << temp->movie->director->name << endl << endl;
                }
                genre = genre->next;
            }

            temp = temp->next;
            if (temp != NULL) {
                //prints rating wise list of movies
                genre = temp->movie->Genre->start;
            }
        }

    }

    //Worst Case Complexity of above function is bigO of n2
};

class Controller {
public:

    //variables to store the director info
    string nameDirector;
    unsigned int facebookLikesDirector;
    // array to store actor info
    string nameActor[3];
    unsigned int facebookLikesActor[3];
    //array to store genre
    string genre[10];
    string line;
    string array[28];

    void stringSplit(string s) {
        //method to split the genre string and store in array
        stringstream ss(s);
        for (int i = 0; i < 10; i++) {
            getline(ss, genre[i], '|');
        }

    }

    void FileRead(MovieList *movieList, ActorList *actorList, DirectorList *directorList, GenreList *genreList) {
        //method to read file

        ifstream file;
        file.open("IMDB_Top5000-SEECS.csv");

        getline(file, line);
        stringstream ss(line);
        for (int i = 0; i <= 27; i++) {
            //loop to read first row containing column name
            getline(ss, array[i], ',');
        }
        cout << endl;

        while (getline(file, line)) {
            //loop to read each row and split it into the fields in which data is to be stored
            MovieNode *movieNode = new MovieNode();
            Movie *movie = new Movie();

            stringstream ss(line);
            string var;

            //to read the movie title until the special charactor (A Hat)
            getline(ss, array[0], char(194));
            getline(ss, var, ',');

            //to split read row into 27 columns
            for (int i = 1; i <= 27; i++) {
                getline(ss, array[i], ',');
            }

            try {
                //try catch for stoi,stof function exception handling
                movie->MovieTitle = array[0];
                movie->Genre = new GenreList();

                //splitting genre field and splitting into individual type
                // storing in genre list
                stringSplit(array[1]);

                GenreNode *node = new GenreNode();
                for (int i = 0; i < 10; i++) {
                    Genre *genres = new Genre();
                    if (genre[i] == "") {
                        continue;
                    }

                    genres->genre = genre[i];
                    node->data = genres;

                    node = genreList->InsertGenreNode(node);
                    movie->Genre->InsertGenreInMovie(genres);

                }

                //to clear the genre list
                for (int i = 0; i < 10; i++) {
                    genre[i].clear();
                }

                if (array[2] != "") {
                    movie->titleYear = (unsigned short int) stoi(array[2]);
                } else {
                    movie->titleYear = 0;
                }

                if (array[3] != "") {
                    movie->imdbScore = stof(array[3]);
                } else {
                    movie->imdbScore = 0.0;
                }

                //director info
                nameDirector = array[4];
                if (array[5] != "") {
                    facebookLikesDirector = (unsigned int) stoi(array[5]);
                } else {
                    facebookLikesDirector = 0;
                }
                Director *director = new Director();

                if (nameDirector != "") {
                    director->name = nameDirector;
                    director->directorFacebookLikes = facebookLikesDirector;

                    DirectorNode *directorNode = directorList->InsertDirector(director);
                    directorNode->director->directedMoviesList->InsertMoviesInSubList(movie);
                    movie->director = director;
                } else {
                    director->name = "";
                    director->directorFacebookLikes = 0;

                    DirectorNode *directorNode = directorList->InsertDirector(director);
                    directorNode->director->directedMoviesList->InsertMoviesInSubList(movie);
                    movie->director = director;
                }

                if (array[6] != "") {
                    movie->numCriticForReviews = (unsigned short int) stoi(array[6]);
                } else {
                    movie->numCriticForReviews = 0;
                }

                if (array[7] != "") {
                    movie->duration = (unsigned short int) stoi(array[7]);
                } else {
                    movie->duration = 0;
                }

                //actors
                ActorNode *actorNode;
                movie->actorInMovieList = new ActorList();

                nameActor[0] = array[8];
                if (array[9] != "") {
                    facebookLikesActor[0] = (unsigned int) stoi(array[9]);
                } else {
                    facebookLikesActor[0] = 0;
                }

                if (nameActor[0] != "") {
                    //new actor object for each actor.
                    Actor *actor1 = new Actor();
                    //storing names and facebook likes.
                    actor1->name = nameActor[0];
                    actor1->facebook_likes_count = facebookLikesActor[0];

                    //calling insert method for inserting main actor list
                    actorNode = actorList->InsertActor(actor1);
                    actorNode->actor->moviesActedInList->InsertMoviesInSubList(movie);
                    movie->actorInMovieList->InsertActorInMovieList(actorNode->actor);
                }

                nameActor[1] = array[10];
                if (array[11] != "") {
                    facebookLikesActor[1] = (unsigned int) stoi(array[11]);
                } else {
                    facebookLikesActor[1] = 0;
                }

                if (nameActor[1] != "") {
                    //new actor object for each actor.
                    Actor *actor1 = new Actor();
                    //storing names and facebook likes.
                    actor1->name = nameActor[1];
                    actor1->facebook_likes_count = facebookLikesActor[1];
                    //calling insert method for inserting main actor list
                    actorNode = actorList->InsertActor(actor1);
                    actorNode->actor->moviesActedInList->InsertMoviesInSubList(movie);
                    movie->actorInMovieList->InsertActorInMovieList(actorNode->actor);

                }

                nameActor[2] = array[12];
                if (array[13] != "") {
                    facebookLikesActor[2] = (unsigned int) stoi(array[13]);
                } else {
                    facebookLikesActor[2] = 0;
                }

                if (nameActor[2] != "") {
                    //new actor object for each actor.
                    Actor *actor1 = new Actor();
                    //storing names and facebook likes.
                    actor1->name = nameActor[2];
                    actor1->facebook_likes_count = facebookLikesActor[2];

                    //calling insert method for inserting main actor list
                    actorNode = actorList->InsertActor(actor1);
                    actorNode->actor->moviesActedInList->InsertMoviesInSubList(movie);
                    movie->actorInMovieList->InsertActorInMovieList(actorNode->actor);
                }

                if (array[14] != "") {
                    movie->gross = (unsigned int) stoi(array[14]);
                } else {
                    movie->gross = 0;
                }

                if (array[15] != "") {
                    movie->numVotedUsers = (unsigned int) stoi(array[15]);
                } else {
                    movie->numVotedUsers = 0;
                }

                if (array[16] != "") {
                    movie->castTotalFacebookLikes = (unsigned int) stoi(array[16]);
                } else {
                    movie->castTotalFacebookLikes = 0;
                }

                if (array[17] != "") {
                    movie->facenumberInPoster = (unsigned short int) stoi(array[17]);
                } else {
                    movie->facenumberInPoster = 0;
                }

                movie->plotKeywords = array[18];

                movie->movieImdbLink = array[19];

                if (array[20] != "") {
                    movie->numUserForReviews = (unsigned short int) stoi(array[20]);
                } else {
                    movie->numUserForReviews = 0;
                }

                movie->language = array[21];

                movie->country = array[22];
                movie->contentRating = array[23];

                if (array[24] != "") {
                    movie->budget = (unsigned int) stoi(array[24]);
                } else {
                    movie->budget = 0;

                }

                if (array[25] != "") {
                    movie->aspectRatio = stof(array[25]);
                } else {
                    movie->aspectRatio = 0.0;
                }

                if (array[26] != "") {
                    movie->movieFacebookLikes = (unsigned int) stoi(array[26]);
                } else {
                    movie->movieFacebookLikes = 0;
                }

                movie->color = array[27];
            }
            catch (exception) {

            }

            movieNode->movie = movie;
            movieList->InsertMovie(movieNode);
        }

    }

};

void MovieList::PrintNode(MovieNode *movieNode) {
    cout << "Movie Title : " << movieNode->movie->MovieTitle << "\t";
    movieNode->movie->Genre->PrintGenreInMovie(movieNode->movie->Genre);
    cout << "Year : " << movieNode->movie->titleYear << "\t";
    cout << "IMDB Score : " << movieNode->movie->imdbScore << "\t";
    cout << "Director Name : " << movieNode->movie->director->name << "\t";
    cout << "Director FB Likes : " << movieNode->movie->director->directorFacebookLikes << "\t";
    cout << "NumCriticForReviews : " << movieNode->movie->numCriticForReviews << "\t";
    cout << "Duration : " << movieNode->movie->duration << "\t";
    //actors
    movieNode->movie->actorInMovieList->PrintActorsInMovieList(movieNode->movie->actorInMovieList);
    cout << "Gross : " << movieNode->movie->gross << "\t";
    cout << "NumVotedUsers : " << movieNode->movie->numVotedUsers << "\t";
    cout << "castTotalFacebookLikes : " << movieNode->movie->castTotalFacebookLikes << "\t";
    cout << "facenumberInPoster : " << movieNode->movie->facenumberInPoster << "\t";
    cout << "plotKeywords : " << movieNode->movie->plotKeywords << "\t";
    cout << "Movie ImdbLink : " << movieNode->movie->movieImdbLink << "\t";
    cout << "numUserForReviews : " << movieNode->movie->numUserForReviews << "\t";
    cout << "language : " << movieNode->movie->language << "\t";
    cout << "country : " << movieNode->movie->country << "\t";
    cout << "contentRating : " << movieNode->movie->contentRating << "\t";
    cout << "budget : " << movieNode->movie->budget << "\t";
    cout << "aspectRatio : " << movieNode->movie->aspectRatio << "\t";
    cout << "movieFacebookLikes : " << movieNode->movie->movieFacebookLikes << "\t";
    cout << "color : " << movieNode->movie->color << endl;
    cout
            << "\n************************************************************************************************************************\n";

}

int main() {

    MovieList *movieList = new MovieList();
    ActorList *actorList = new ActorList();
    DirectorList *directorList = new DirectorList();
    GenreList *genrelist = new GenreList();

    Controller *controller = new Controller();

    controller->FileRead(movieList, actorList, directorList, genrelist);

    movieList->PrintMovieList(movieList);

    //actorList -> PrintActorList(actorList);

    //directorList -> PrintDirectorList(directorList);

    //1st function
    //actorList ->  SearchActorDetails("CCH Pounder");

    //2nd function
    //actorList -> SearchCoActorOfActor("CCH Pounder");

    //3rd function
    //actorList -> SearchUniqueCoActorOfActor("CCH Pounder");

    //4th function
    //actorList -> SearchUniqueCoActorOfCoActorOfActor("CCH Pounder");

    //8th function
    //movieList -> PrintMovieDetail("Shanghai");

    //movies functions

    /*
     * MovieNode* temp = movieList->startMovieNode;
    while (temp != NULL)
    {
        movieList->InsertYearWise(temp);
        temp = temp->next;
    }
    movieList->printMovieYearWise();
    movieList->SearchMoviesInGivenYear(2008);

    MovieNode* temp2 = movieList->startMovieNode;
    movieList->Index();

    while (temp2 != NULL)
    {

        movieList->InsertRatingWise(temp2);
        temp2 = temp2->next;
    }
    movieList->printMovieRatingWise();
    actorList->SearchActorDetails("Henry Cavill");
    //actorList -> PrintActorList(actorList);
    //actorList->ActorsWorkTogether("Jack Davenport", "Orlando Bloom");

    //directorList->PrintDirectorList(directorList);
     *
     *
     *
     */

    // actorList -> SearchCoCoActorOfActor(actorList, "CCH Pounder");

    //genrelist->PrintMoviesofCertainGenre("Documentary", movieList);
    //genrelist->PrintDirectorforGenre("Documentary", movieList);

    return 0;
}

