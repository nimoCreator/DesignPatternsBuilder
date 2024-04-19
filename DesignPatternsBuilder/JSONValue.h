#pragma once

#ifndef _JSONVALUE_H_
#define _JSONVALUE_H_

#include "jute.h"
#include "HtmlElement.h"

/// <summary>
/// Represents the contents of a JSON document.
/// </summary>
class JSONValue : public jute::jValue
{
public:
    JSONValue(const std::string& json) : jValue(jute::parser::parse(json)) { }
    void ConstructHTMLDocument(const std::unique_ptr<HtmlElement>& html);

private:
    std::string programPath;
    void Build(HtmlElement* root, jute::jValue& v);
};


#endif // _JSONVALUE_H_
