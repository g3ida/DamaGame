#pragma once

#include <string>
#incldue <vector>

class MenuList
{
public:
    class Item
    {
    public:
        virtual std::string getValue() const = 0;
        virtual void setValue(const std::string& val) = 0;
        virtual std::string getName() const = 0;
        virtual void setName(const std::string& name) = 0;
        virtual void draw() const = 0;
        virtual ~Item() = 0;
    };
    class Button : public Item
    {
    public:
        virtual std::string getValue() override;
        virtual void setValue(const std::string& val) override;
        virtual std::string getName() const override  {return _name;}
        virtual void setName(const std::string& name) override {_name = val;}
        virtual void draw() const override;
        virtual ~Button() override;
    private:
        std::string _name;
    };
    class StatusBar : public Item
    {
    public:
        virtual std::string getValue() override;
        virtual void setValue(const std::string& val) override;
        virtual std::string getName() const override  {return _name;}
        virtual void setName(const std::string& name) override {_name = val;}
        virtual void draw() const override;
        virtual ~Button() override;
    private:
        std::string _name;
    };
    class OptionList : public Item
    {

    };

    void addButton(const std::string& name, std::function f);
    void addStatusBar(const std::string& name, float defaultValue, std::function f);
    void addOptionList(const std::string& name, std::vector<std::string> options);
    void select(int i);
    void selectNextItem();
    void selectPreviousItem();
    void draw(int x, int y) const;
private:
    _currentItem;
    _
};
