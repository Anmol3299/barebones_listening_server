#pragma once

#include <fstream>
#include <string>
#include <vector>


class CQuoteDay {
public:
    // constructor
    explicit CQuoteDay(std::string const& filename);

    // get a random quote from the file
    std::remove_reference_t<std::string> const& getRandomQuote() const;

private:
    // the quotes
    std::vector<std::string> m_quotes;
};