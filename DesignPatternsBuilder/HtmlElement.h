#pragma once
#ifndef _HTMLELEMENT_H_
#define _HTMLELEMENT_H_

#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "Builder.h"

using namespace std;

struct HtmlElement : public Builder
{
    const size_t indent_size = 2;

    explicit HtmlElement()
    {
    }

    explicit HtmlElement(const string& name, const string& text)
        : name(name), text(text)
    {
    }

    virtual HtmlElement* add_child(std::string name, std::string text)
    {
        HtmlElement* e = new HtmlElement(name, text);
        children.emplace_back(e);
        return e;
    }

    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');

        if (name.size() > 0) {
            oss << i << "<" << name << ">" << endl;
        }

        if (text.size() > 0)
            oss << string(indent_size * ((size_t)indent + 1), ' ') << text << endl;

        for (const auto& e : children)
            oss << e->str(indent + 1);

        if (name.size() > 0)
            oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    void set_text(const string& text) { this->text = text; }
    string get_text() const { return text; }

    void set_name(const string& name) { this->name = name; }
    string get_name() const { return name; }

private:
    string name;
    string text;
    vector<unique_ptr<HtmlElement>> children;

};


#endif // !_HTMLELEMENT_H_




