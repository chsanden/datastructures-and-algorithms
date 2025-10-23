

#ifndef IKT203_TMOVIE_H
#define IKT203_TMOVIE_H
#include <string>
#include <utility>

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
            std::string title;
            std::string director;
            int year;
            EMovieGenreType genre;
            float score;

        public:

            TMovie(std::string T, std::string D, int Y, EMovieGenreType G, float S) :
            title(std::move(T)), director(std::move(D)), year(Y), genre(G), score(S) {}

            // Simple getters - using [[nodiscard]] to give warning if value is not used
            [[nodiscard]] std::string GetTitle() const
            {
                return title;
            }
            [[nodiscard]] std::string GetDirector() const
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
