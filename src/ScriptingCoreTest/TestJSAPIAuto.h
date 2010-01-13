/**********************************************************\ 
Original Author: Georg Fritzsche

Created:    November 7, 2009
License:    Dual license model; choose one of two:
            Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 Georg Fritzsche, Firebreath development team
\**********************************************************/

#include <string>
#include <sstream>
#include <algorithm>
#include "JSAPIAuto.h"

class TestObjectJSAPIAuto : public FB::JSAPIAuto
{
public:
    virtual ~TestObjectJSAPIAuto() {}

    TestObjectJSAPIAuto()
      : m_readOnlyMessage("read only message")
    {
        registerMethod("returnString",  make_method(this, &TestObjectJSAPIAuto::returnString));
        registerMethod("intToString",   make_method(this, &TestObjectJSAPIAuto::intToString));
        registerMethod("sumOf",         make_method(this, &TestObjectJSAPIAuto::sumOf));
        registerMethod("concatenate",   make_method(this, &TestObjectJSAPIAuto::concatenate));
        registerMethod("concatMany",    make_method(this, &TestObjectJSAPIAuto::concatMany));
        registerMethod("concatMany2",   make_method(this, &TestObjectJSAPIAuto::concatMany2));
        registerMethod("getType",       make_method(this, &TestObjectJSAPIAuto::getType));
        registerMethod("accumulate",    make_method(this, &TestObjectJSAPIAuto::accumulate));

        registerProperty("message",
                         make_property(this, 
                            &TestObjectJSAPIAuto::get_Message,
                            &TestObjectJSAPIAuto::set_Message));
        registerProperty("readOnlyMessage", 
                         make_property(this,
                            &TestObjectJSAPIAuto::get_ReadOnlyMessage));
    }

    std::string returnString(const std::string& s)
    {
        return s;
    }

    std::string intToString(long i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }

    int sumOf(long a, long b)
    {
        return a+b;
    }

    std::string concatenate(const std::string& a, const std::string& b, const std::string& c)
    {
        return a+b+c;
    }

    // catch >= 1 arguments as strings and concatenate
    std::string concatMany(const std::string& a, const FB::CatchAll& rest)
    {
        FB::VariantList::const_iterator it(rest.value.begin());
        std::string s(a);

        for( ; it != rest.value.end(); ++it)
            s += it->convert_cast<std::string>();

        return s;
    }

    // catch 2 arguments: 1 string, 1 script array
    std::string concatMany2(const std::string& a, const FB::VariantList& arr)
    {
        FB::VariantList::const_iterator it(arr.begin());
        std::string s(a);

        for( ; it != arr.end(); ++it)
            s += it->convert_cast<std::string>();

        return s;
    }

    void set_Message(const std::string& s)
    {
        m_message = s;
    }

    std::string get_Message() const
    {
        return m_message;
    }

    std::string get_ReadOnlyMessage()
    {
        return m_readOnlyMessage;
    }

    std::string getType(const FB::variant a)
    {
        return a.get_type().name();
    }

    long int accumulate(const std::vector<int>& values)
    {
        return std::accumulate(values.begin(), values.end(), 0);
    }

private:
    std::string m_message;
    const std::string m_readOnlyMessage;
};
