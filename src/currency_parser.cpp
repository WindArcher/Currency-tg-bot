#include "currency_parser.h"

CurrencyParser::CurrencyParser()
{
    requestData();
}

void CurrencyParser::requestData()
{
    m_monoData = nlohmann::json::parse(get_request("https://api.monobank.ua/bank/currency"));
}

size_t Writer(char *buffer, size_t size, size_t nmenb, std::string *html)
{
    int result = 0;
    if(buffer != NULL)
    {
        html->append(buffer, size * nmenb);
        result = size * nmenb;
    }
    return result;
}

std::string CurrencyParser::get_request(std::string link)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return readBuffer;
    }
    return nullptr;
}

std::string CurrencyParser::rateToUAH(Currency type)
{
    for (auto& element : m_monoData) 
    {
        if (element["currencyCodeA"]== m_codeTable.at(type))
        {
            return "RateBuy : " + std::to_string(element["rateBuy"].get<float>()) + "\nRateSell : " 
            + std::to_string(element["rateSell"].get<float>());
        }
    }
    return "Bad request";
}
