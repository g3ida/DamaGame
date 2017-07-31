#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <map>

//Handle gcc problem with C++11 threads standard  library on Windows.
#ifdef __MINGW32__
    #include "mingw_threads/mingw.condition_variable.h"
    #include "mingw_threads/mingw.mutex.h"
    #include "mingw_threads/mingw.thread.h"
#else
    #include <thread>
    #include <condition_variable>
    #include <mutex>

#endif // __MINGW32__

class InputQueue
{

public:

    struct Event
    {
        enum class Type{Reshape, Keyboard, KeyboardSpecial, Mouse, MouseMotion, MousePassiveMotion};
        struct KeyboardData
        {
            int x, y;
            unsigned char key;
        };
        struct KeyboardSpecialData
        {
            int key, x, y;
        };
        struct MouseData
        {
            int button, state, x, y;
        };
        struct ReshapeData
        {
            int w, h;
        };
        struct MouseMotionData
        {
            int x, y;
        };
        struct MousePassiveMotionData
        {
            int x, y;
        };
        //Use union to save space.
        union Data
        {
            KeyboardSpecialData keyboardSpecial;
            KeyboardData keyboard;
            MouseData mouse;
            ReshapeData reshape;
            MouseMotionData mouseMotion;
            MousePassiveMotionData mousePassiveMotion;
        };


        Type type;
        Data data;
    };

    inline static InputQueue& getInstance() {
        static InputQueue instance;
        return instance;
    }


    inline void push(Event new_value)
    {
        std::lock_guard<std::mutex> lk(_mut);
        _event_queue.push(new_value);
        _data_cond.notify_one();
    }

    inline void waitAndPop(Event& value)
    {
        std::unique_lock<std::mutex> lk(_mut);
        if(!_event_queue.empty())
        {
            value=_event_queue.front();
            _event_queue.pop();
        }
        else
        {
            _data_cond.wait(lk,[this]{return !_event_queue.empty();});
            value=_event_queue.front();
            _event_queue.pop();
        }
    }

    inline std::shared_ptr<Event> waitAndPop()
    {
        std::unique_lock<std::mutex> lk(_mut);
        if(!_event_queue.empty())
        {
            std::shared_ptr<Event> res(std::make_shared<Event>(_event_queue.front()));
            _event_queue.pop();
            return res;
        }
        else
        {
            _data_cond.wait(lk,[this]{return !_event_queue.empty();});
            std::shared_ptr<Event> res(std::make_shared<Event>(_event_queue.front()));
            _event_queue.pop();
            return res;

        }
    }

    inline bool tryPop(Event& value)
    {
        std::lock_guard<std::mutex> lk(_mut);
        if(_event_queue.empty())
            return false;
        value=_event_queue.front();
        _event_queue.pop();
        return true;
    }

    inline std::shared_ptr<Event> tryPop()
    {
        std::lock_guard<std::mutex> lk(_mut);
        if(_event_queue.empty())
            return std::shared_ptr<Event>();
        std::shared_ptr<Event> res(std::make_shared<Event>(_event_queue.front()));
        _event_queue.pop();
        return res;
    }

    inline bool empty() const
    {
        std::lock_guard<std::mutex> lk(_mut);
        return _event_queue.empty();
    }

    inline std::pair<int, int> getMouseCoords() const
    {
        return std::make_pair(_mouseX, _mouseY);
    }

    inline int getScreenWidth() const {return _screenW;}
    inline int getScreenHeight() const {return _screenH;}

    friend void mouseCallback(int button, int state, int x, int y);
    friend void motionCallback(int x, int y);
    friend void passiveMotionCallback(int x, int y);
    friend void reshapeCallback(int w, int h);



private:
    mutable std::mutex _mut;
    std::queue<Event> _event_queue;
    std::condition_variable _data_cond;
    InputQueue() {} //Make it singleton.
    int _mouseX, _mouseY;
    int _screenW, _screenH;
};
