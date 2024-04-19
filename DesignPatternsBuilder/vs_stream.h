#pragma once

#ifndef _VSSTREAM_H_
#define _VSSTREAM_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
/// <summary>
/// Visual Studio Stream
/// do przekierowania strumienia do okna "Output->Debug" Visual Studio.
/// </summary>
class vs_stream : std::basic_streambuf<char, std::char_traits<char>>
{
protected:
    std::streamsize xsputn(const std::char_traits<char>::char_type* s, std::streamsize n)
    {
        OutputDebugStringA(s);
        return n;
    }

    std::char_traits<char>::int_type overflow(std::char_traits<char>::int_type c)
    {
        char str[2]; str[0] = c; str[1] = 0;
        OutputDebugStringA(str);
        return std::char_traits<char>::int_type(c);
    }
};
typedef std::basic_streambuf<char, std::char_traits<char>> sbuf_char;

#endif // !_VSSTREAM_H_
