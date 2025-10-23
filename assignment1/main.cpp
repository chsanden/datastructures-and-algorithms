#include <iostream>
#include "TMovieList.h"

// specialised versions of SearchFor() from TMovieList
bool SearchByTitle(const TMovie* m, void* c)
{
    const auto* title = static_cast<std::string*>(c);
    return m->GetTitle() == *title;
}

bool SearchByDirector(const TMovie* m, void* criteria)
{
    const auto* director = static_cast<std::string*>(criteria);
    return m->GetDirector() == *director;
}

bool SearchByGenre(const TMovie* m, void* criteria)
{
    const auto* genre = static_cast<EMovieGenreType*>(criteria);
    return m->GetGenre() == *genre;
}





int main()
{



}
