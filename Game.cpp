#include "Game.h"
#include "InputQueue.h"
#include "logger/Log.h"
#include "MenuState.h"
#include "PlayState.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Handle gcc problem with C++11 threads standard  library on Windows.
#ifdef __MINGW32__
    #include "mingw_threads/mingw.condition_variable.h"
    #include "mingw_threads/mingw.mutex.h"
    #include "mingw_threads/mingw.thread.h"
#else
    #include <thread>
    #include <condition_variable>
    #include <mutex>
#endif

#include <chrono>

static std::mutex vector_mtx;

Game::Game()
{
    _begin = clock();
}

bool
Game::isStateStackEmpty()
{
    std::lock_guard<std::recursive_mutex> lk(_stack_mtx);
    return _stateStack.empty();
}

using namespace std::literals::chrono_literals;

void
Game::operator()()
{
    pushState(new MenuState());
    while(true)
    {
        if(isStateStackEmpty()) break;

        InputQueue::Event e;
        //InputQueue::getInstance().waitAndPop(e);
        while(InputQueue::getInstance().tryPop(e))
        {
            std::lock_guard<std::recursive_mutex> lock(_stack_mtx);

            GameState* tmp = _stateStack.back();
            GameState* s = tmp->handleEvents(e);
            if(s == nullptr || s != tmp)
            {
                changeState(s);
            }
        }

        {
            if(isStateStackEmpty()) break;

            std::lock_guard<std::recursive_mutex> lock(_stack_mtx);
            auto tmp = _stateStack.back();
            _end = clock();
            auto s = tmp->update((int)((double(_end - _begin) / CLOCKS_PER_SEC)* 1000));
            _begin = _end;
            if(s == nullptr || s != tmp)
            {
                changeState(s);
            }
        }
        std::this_thread::sleep_for(30ms);
    }
    quit();

}

void
Game::changeState(GameState* state)
{
	if(state == nullptr)
    {
        popState();
        return;
    }
    std::lock_guard<std::recursive_mutex> lk(_stack_mtx);
	//Cleanup the current state.
	if (!_stateStack.empty())
    {
        _stateStack.back()->onClose();
        delete _stateStack.back();
		_stateStack.pop_back();
	}
	//Store and enter the new state.
    _stateStack.push_back(state);
	_stateStack.back()->onEnter();
}

void
Game::pushState(GameState* state)
{
    std::lock_guard<std::recursive_mutex> lk(_stack_mtx);
	//Pause current state.
	if (!_stateStack.empty())
    {
		_stateStack.back()->pause();
	}
	//Store and enter the new state.
    _stateStack.push_back(state);
	_stateStack.back()->onEnter();
}

void
Game::popState()
{
    std::lock_guard<std::recursive_mutex> lk(_stack_mtx);
	// cleanup the current state.
	if (!_stateStack.empty())
    {
        _stateStack.back()->onClose();
        delete _stateStack.back();
		_stateStack.pop_back();
	}
	//Resume previous state.
	if (!_stateStack.empty())
	{
		_stateStack.back()->resume();
	}
}

void
Game::draw()
{
    //LOG("DRAW\n");
    static std::mutex mtx;
    std::lock_guard<std::mutex> lk(mtx);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    {
        std::lock_guard<std::recursive_mutex> lkx(_stack_mtx);
        _stateStack.back()->draw();
    }

    glFlush();
	glutSwapBuffers();
	//using namespace std::chrono_literals;
	//std::this_thread::sleep_for(100ms);

}

void
Game::quit()
{
    std::lock_guard<std::recursive_mutex> lk(_stack_mtx);
    while (!_stateStack.empty())
    {
        _stateStack.back()->onClose();
        delete _stateStack.back();
        _stateStack.pop_back();
    }
    exit(0);
}

Game&
Game::getInstance()
{
    static Game dam;
    return dam;
}

