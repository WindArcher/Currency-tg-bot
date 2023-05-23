#include "json.hpp"
#include <curl/curl.h>
#include <unordered_map>

class CurrencyParser
{
public: 
    enum class Currency{usd,eur,rub,gbp};
    CurrencyParser();
    std::string rateToUAH(Currency type);
    void requestData();
private:
    const std::unordered_map<Currency,int> m_codeTable = {{Currency::usd,840},
                                                          {Currency::eur,978},
                                                          {Currency::gbp,826}};
    nlohmann::json m_monoData;
    std::string get_request(std::string link);
};