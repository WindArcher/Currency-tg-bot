#include "json.hpp"
#include <curl/curl.h>

class CurrencyParser
{
public: 
    enum class Currency{usd,eur,rub};
    CurrencyParser();
    std::string rateToUAH(Currency type);
    void requestData();
private:
    nlohmann::json m_monoData;
    std::string get_request(std::string link);
};