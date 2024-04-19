#include "JSONValue.h"


void JSONValue::ConstructHTMLDocument(const std::unique_ptr<HtmlElement>& html) {
    // add head
    html->add_child("head", "<title>Document</title>");
    // build body
    auto body = html->add_child("body", "");
    Build(body, *this);
}

void JSONValue::ConstructMarkdownDocument(const std::unique_ptr<MarkdownElement>& markdown) {
    Build(markdown, *this);
}

void JSONValue::Build(HtmlElement* root, jute::jValue& v) {
    jute::jType type = v.get_type();
    if (type == jute::JSTRING) {
        root->set_text(v.get_svalue()); // std::cout << v.get_svalue() << endl;
        return;
    }
    if (type == jute::JOBJECT) {
        for (size_t i = 0; i < v.get_properties().size(); i++) {
            auto first = v.get_properties()[i].first; //std::cout << first << " ";
            auto second = v.get_properties()[i].second;
            Build(root->add_child(first, ""), second);
        }
    }
    if (type == jute::JARRAY) {
        for (size_t i = 0; i < v.get_arr().size(); i++) {
            Build(root, v.get_arr()[i]);
        }
        return;
    }
}

void JSONValue::Build(MarkdownElement* root, jute::jValue& v) {{
        for (size_t i = 0; i < v.get_arr().size(); i++) {
            Build(root, v.get_arr()[i]);
        }
        return;
    }
}