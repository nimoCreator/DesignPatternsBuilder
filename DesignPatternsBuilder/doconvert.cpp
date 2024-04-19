#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <algorithm>

#include "ArgumentsParser.h"
#include "HtmlElement.h"
#include "JSONValue.h"

#include "vs_stream.h"


int main(int argc, char* argv[])
{

    sbuf_char* old_buf = std::cout.rdbuf();
    // hook - switch std::cout to vs debug window --------------------------------------------------
    /* for debugging purposes only ;-) !
    vs_stream vs;
    std::cout.rdbuf((sbuf_char*)&vs);
    //*/

    ArgumentsParser args(argc, argv, true);

    auto input_file = args.getParamArg("-i");  //input_file = ".\\in\\document3.json";
    auto output_file = args.getParamArg("-o");   //output_file = ".\\out\\document3.html";
    auto output_format = args.getParamArg("-f");   //output_format = "h";

    if (input_file != "")
    {
        ifstream in(input_file);
        if (in.good())
        {
            string str((std::istreambuf_iterator<char>(in)),
                (std::istreambuf_iterator<char>()));
            in.close();

            std::unique_ptr<HtmlElement> document;

            if (output_format == "h") // html
            {
                document = std::unique_ptr<HtmlElement>{ new HtmlElement("html", "") };
            }
            // . . .
            else // html default
            {
                document = std::unique_ptr<HtmlElement>{ new HtmlElement("html", "") };
            }

            JSONValue jsonParser(str);
            jsonParser.ConstructHTMLDocument(document);

            // add header
            std::stringstream ss;
            // add header
            ss << "<!DOCTYPE html>\n";
            // add body
            ss << document->str();
            // add footer
            ss << "<!-- HTML document created using IOConverter -->";

            ofstream out(output_file);
            if (out.good())
            {
                out << ss.str();
            }
            else
            {
                std::cout << ss.str();
            }
        }
    }
    else
    {
        std::cout << "Usage:\n\ndoconvert -i input_file [-o output_file] [-f format]\n\nformat:\th - HTML\n";
    }

    // unhook --------------------------------------------------------------------------------------
    std::cout.rdbuf(old_buf);


    return 0;
}