#pragma once

class Settings
{
public:
    static void resetDefaults()
    {
        _boardSize = 10;
        _soundVolume = 1.f;
    }
    static int getBoardSize()
    {
        return _boardSize;
    }
    static void setBoardSize(int sz) //May only be 8 or 10.
    {
        if(sz !=10 && sz !=8 && sz !=12)
            return;
        _boardSize = sz;
    }
    static float getSoundVolume()
    {
        return _soundVolume;
    }
    static void setSoundVolume(float v)
    {
        if(v > 1.f || v < 0.f)
            return;
        _soundVolume = v;
    }

    enum class Rule
    {
        International, Canadian, Chekers, Custom
    };

    static Rule getRule()
    {
        return _GameRules;
    }

    static void setRule(Rule r)
    {
         _GameRules = r;
        switch(r)
        {
        case Rule::International:
            _boardSize = 10;
            _flyingKing = true;
            _backwardEat = true;
            _eatMaxPieces = true;
            break;
        case Rule::Canadian:
            _boardSize = 12;
            _flyingKing = true;
            _backwardEat = true;
            _eatMaxPieces = true;
            break;
        case Rule::Chekers:
            _boardSize = 8;
            _flyingKing = false;
            _backwardEat = false;
            _eatMaxPieces = false;
            break;
        case Rule::Custom:
            break;
        }
    }
    static void setFlyingKings(bool b) {_flyingKing = b;}
    static bool canKingsFly() {return _flyingKing;}
    static void setBackwardEat(bool b) {_backwardEat = b;}
    static bool canBackwardEat() {return _backwardEat;}
    static void setEatMaxPieces(bool b) {_eatMaxPieces = b;}
    static bool mustEatMaxPieces() {return _eatMaxPieces;}

    enum class Player{Human, Computer};
    static Player player1;
    static Player player2;

    static void save();

    static void load();
private:
    static int _boardSize;
    static Rule _GameRules;
    static bool _flyingKing;
    static bool _backwardEat;
    static bool _eatMaxPieces;
    static float _soundVolume;
};
