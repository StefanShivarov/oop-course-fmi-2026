#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::swap;

namespace Books {

    namespace Constants {
        const int MAX_LENGTH = 51;
        const char DELIMITER = ';';

        // за демонстрация на филтри
        const char TARGET_AUTHOR[] = "Jane Austen";
        const int YEAR_FROM = 1990;
        const int YEAR_TO = 2010;
    }

    enum class Genre {
        CLASSIC, SCIFI, FANTASY, ROMANCE, CRIME, NONFICTION, EDUCATIONAL, OTHER
    };

    using namespace Constants;

    struct Book {
        char title[MAX_LENGTH];
        char author[MAX_LENGTH];
        int year;
        Genre genre;
    };

    namespace Utils {

        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        // Парсва неотрицателно число (година). Връща -1 при невалиден стринг.
        int parseNonNegativeInt(const char* str) {
            if (str == nullptr || str[0] == '\0') {
                return -1;
            }

            int value = 0;
            for (int i = 0; str[i] != '\0'; i++) {
                if (!isDigit(str[i])) {
                    return -1;
                }
                value = value * 10 + (str[i] - '0');
            }

            return value;
        }

        Genre parseGenreFromString(const char* str) {
            using enum Genre;
            if (strcmp(str, "Classic") == 0) return CLASSIC;
            if (strcmp(str, "Sci-fi") == 0) return SCIFI;
            if (strcmp(str, "Fantasy") == 0) return FANTASY;
            if (strcmp(str, "Romance") == 0) return ROMANCE;
            if (strcmp(str, "Crime") == 0) return CRIME;
            if (strcmp(str, "NonFiction") == 0) return NONFICTION;
            if (strcmp(str, "Educational") == 0) return EDUCATIONAL;
            return OTHER;
        }

        const char* getGenreName(Genre genre) {
            using enum Genre;
            switch (genre) {
                case CLASSIC: return "Classic";
                case SCIFI: return "Sci-fi";
                case FANTASY: return "Fantasy";
                case ROMANCE: return "Romance";
                case CRIME: return "Crime";
                case NONFICTION: return "NonFiction";
                case EDUCATIONAL: return "Educational";
                default: return "Other";
            }
        }

        // int genreToIndex(Genre g) {
        //     switch (g) {
        //     case Genre::CLASSIC:      return 0;
        //     case Genre::SCIFI:        return 1;
        //     case Genre::FANTASY:      return 2;
        //     case Genre::ROMANCE:      return 3;
        //     case Genre::CRIME:        return 4;
        //     case Genre::NONFICTION:   return 5;
        //     case Genre::EDUCATIONAL:  return 6;
        //     default:                  return 7; // OTHER
        //     }
        // }

        bool compareByYear(const Book& lhs, const Book& rhs) {
            if (lhs.year != rhs.year) {
                return lhs.year < rhs.year;
            }
            // tie-breaker
            return strcmp(lhs.title, rhs.title) < 0;
        }

        bool compareByTitle(const Book& lhs, const Book& rhs) {
            return strcmp(lhs.title, rhs.title) < 0;
        }

        const int GENRE_COUNT = 8;
        int genreIndex(Genre g) {
            return static_cast<int>(g);
        }
    }

    void readBook(Book& book, std::istream& is) {
        is.getline(book.title, MAX_LENGTH, DELIMITER);
        is.getline(book.author, MAX_LENGTH, DELIMITER);

        char buff[32];

        // year (до DELIMITER)
        is.getline(buff, 32, DELIMITER);
        book.year = Utils::parseNonNegativeInt(buff);

        // genre (до край на реда)
        is.getline(buff, 32);
        book.genre = Utils::parseGenreFromString(buff);
    }

    void writeBook(const Book& book, std::ostream& os) {
        os << book.title << " | "
           << book.author << " | "
           << book.year << " | "
           << Utils::getGenreName(book.genre) << '\n';
    }

    void writeAllBooks(const Book* books, size_t booksCount, std::ostream& os) {
        for (int i = 0; i < booksCount; i++) {
            writeBook(books[i], os);
        }
    }

    void sortBooks(Book* books, size_t booksCount, bool (*comparator)(const Book&, const Book&)) {
        for (int i = 0; i < booksCount; i++) {
            int minIndex = i;
            for (int j = i + 1; j < booksCount; j++) {
                if (comparator(books[j], books[minIndex])) {
                    minIndex = j;
                }
            }

            if (i != minIndex) {
                swap(books[i], books[minIndex]);
            }
        }
    }

    void filterBooksByCriteria(const Book* books, size_t booksCount, bool (*shouldKeep)(const Book&)) {
        for (int i = 0; i < booksCount; i++) {
            if (shouldKeep(books[i])) {
                writeBook(books[i], std::cout);
            }
        }
    }

    // ---- Конкретни критерии за демонстрация (без capture) ----

    bool isByTargetAuthor(const Book& b) {
        return strcmp(b.author, TARGET_AUTHOR) == 0;
    }

    bool isFantasy(const Book& b) {
        return b.genre == Genre::FANTASY;
    }

    bool isInYearInterval(const Book& b) {
        return b.year >= YEAR_FROM && b.year <= YEAR_TO;
    }

    // ---- Статистика по жанрове ----

    void printGenreStats(const Book* books, size_t booksCount) {
        int counts[Utils::GENRE_COUNT] = { 0 };

        for (int i = 0; i < booksCount; i++) {
            int idx = Utils::genreIndex(books[i].genre);
            if (idx >= 0 && idx < Utils::GENRE_COUNT) {
                counts[idx]++;
            }
        }

        for (int i = 0; i < Utils::GENRE_COUNT; i++) {
            Genre g = static_cast<Genre>(i);
            cout << Utils::getGenreName(g) << ": " << counts[i] << '\n';
        }
    }
}

int main() {
    using namespace Books;

    int n;
    cin >> n;
    cin.ignore();

    Book* library = new Book[n];

    for (int i = 0; i < n; i++) {
        readBook(library[i], cin);
    }

    cout << "Sort by year:\n";
    sortBooks(library, n, Utils::compareByYear);
    writeAllBooks(library, n, cout);
    cout << '\n';

    cout << "Sort by title:\n";
    sortBooks(library, n, Utils::compareByTitle);
    writeAllBooks(library, n, cout);
    cout << '\n';

    cout << "Search by author:\n";
    filterBooksByCriteria(library, n, isByTargetAuthor);
    cout << '\n';

    cout << "Filter by genre:\n";
    filterBooksByCriteria(library, n, isFantasy);
    cout << '\n';

    cout << "Filter by year interval:\n";
    filterBooksByCriteria(library, n, isInYearInterval);
    cout << '\n';

    cout << "Genre stats:\n";
    printGenreStats(library, n);

    delete[] library;
}
