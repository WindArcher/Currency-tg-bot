#include <tgbot/tgbot.h>
#include "currency_parser.h"
#include <iostream>
#include <vector>

class CurrencyTgBot
{
public:
    CurrencyTgBot();
    ~CurrencyTgBot() = default;
    void start();
private:
    CurrencyParser m_parser;
    TgBot::Bot m_bot;
    TgBot::InlineKeyboardMarkup::Ptr m_keyboard;
    std::vector<TgBot::InlineKeyboardButton::Ptr> m_buttons;
    void setUp();
    void currencyButtonsSetUp();
    void startCommandReplySetUp();
    void currencyCommandReplySetUp();
    void onQueryResponseSetUp();
    void addButton(std::string text, std::string callbackData);
};