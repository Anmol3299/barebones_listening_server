#include "../include/CQuoteDay.hpp"

#include <random>


size_t getRandom(size_t start, size_t end) {
    std::random_device rd{};

    std::mt19937 randEngine{ rd() };

    std::uniform_int_distribution<size_t> gen{ start, end };

    return gen(randEngine);
}

// constructor
CQuoteDay::CQuoteDay(std::string const& filename) {
    std::ifstream file;
    file.open(filename);
    if (file.is_open()) {
        std::string line;

        m_quotes.emplace_back("");
        while (std::getline(file, line)) {
            if (line == "%") {
                m_quotes.emplace_back("");
            } else {
                m_quotes.back() += line;
                m_quotes.back() += '\n';
            }
        }
        while (m_quotes.back().size() == 0) {
            m_quotes.pop_back();
        }
    }
}

// Get random quotes from file
std::string const& CQuoteDay::getRandomQuote() const {
    size_t r = getRandom(0, m_quotes.size() - 1);
    return m_quotes.at(r);
}
