

#ifndef IKT203_TMOVIE_H
#define IKT203_TMOVIE_H


#include <wsman.h>
#include <string>
#include <utility>

// I know there's debate on the use of namespace, but honestly
// I cba to write std:: before everything...
using namespace std;

enum EMovieGenreType{
    ACTION = 1 << 0,
    COMEDY = 1<< 1,
    SCIFI = 1 << 2,
    HORROR = 1 << 3,
    DRAMA = 1 << 4
};


class TMovie
        {
        private:
            string title;
            string director;
            int year;
            EMovieGenreType genre;
            float score;

        public:

            TMovie(string T, string D, int Y, EMovieGenreType G, float S) :
            title(std::move(T)), director(std::move(D)), year(Y), genre(G), score(S) {}

            // Simple getters - using [[nodiscard]] to give warning if value is not used
            [[nodiscard]] string GetTitle() const
            {
                return title;
            }
            [[nodiscard]] string GetDirector() const
            {
                return director;
            }
            [[nodiscard]] int GetYear() const
            {
                return year;
            }
            [[nodiscard]] EMovieGenreType GetGenre() const
            {
                return genre;
            }
            [[nodiscard]] float GetScore() const
            {
                return score;
            }

            // Not declaring a destructor since the default compiler destructor is


};


#endif //IKT203_TMOVIE_H
