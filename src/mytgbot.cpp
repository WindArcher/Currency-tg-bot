#include "mytgbot.h"
#include <vector>

const auto BOTKEY = "6054289843:AAHkZu3bFTBi8Ov1eR74SyrhqLqedhAqh1U"; 

CurrencyTgBot::CurrencyTgBot() : m_bot(BOTKEY), m_keyboard(new TgBot::InlineKeyboardMarkup)
{
    CurrencyTgBot::keyboardSetUp();
    CurrencyTgBot::setUp();
}

CurrencyTgBot::~CurrencyTgBot()
{

}

void CurrencyTgBot::keyboardSetUp()
{
    //std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    buttons.emplace_back(new TgBot::InlineKeyboardButton);
    buttons.back()->text = "USD";
    buttons.back()->callbackData = "USD";
    buttons.emplace_back(new TgBot::InlineKeyboardButton);
    buttons.back()->text = "EUR";
    buttons.back()->callbackData = "EUR";
    buttons.emplace_back(new TgBot::InlineKeyboardButton);
    buttons.back()->text = "RUB";
    buttons.back()->callbackData = "RUB";  
    m_keyboard->inlineKeyboard.push_back(buttons);
}

void CurrencyTgBot::start()
{
    try {
        printf("Bot username: %s\n", m_bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(m_bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}

void CurrencyTgBot::setUp()
{
    auto f = [&](TgBot::Message::Ptr message) {
        m_bot.getApi().sendMessage(message->chat->id, "Hi!" + message->chat->firstName); 
        m_parser.requestData();
        };
    m_bot.getEvents().onCommand("start", f);

    auto l = [&](TgBot::Message::Ptr message) {
        m_bot.getApi().sendMessage(message->chat->id, "What currency?", false, 0, m_keyboard); 
        
    };
    m_bot.getEvents().onCommand("currency", l);

    auto c = [&](TgBot::CallbackQuery::Ptr query) {
        if(query->data == "USD") 
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::usd));
        else if(query->data == "EUR") 
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::eur));
        else 
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::rub));
    };
    m_bot.getEvents().onCallbackQuery(c);
}