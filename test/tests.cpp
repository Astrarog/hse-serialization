#include "test_runner.hpp"

#include "world.hpp"
#include "color.hpp"

#include <string>
#include <sstream>

using namespace hse;

//testing constructors and structure fields
void TestColorBasic()
{
    ASSERT_EQUAL(color(0xF7ABCDU), color(0xF7U, 0xABU, 0xCDU));
    ASSERT_EQUAL(color(0x001122U).r, 0x00U);
    ASSERT_EQUAL(color(0x001122U).g, 0x11U);
    ASSERT_EQUAL(color(0x001122U).b, 0x22U);
}

//testing input stream
void TestColorInput()
{
    //ok colors
    {
        {
            std::stringstream stream("#ABCD01");
            color given;
            stream >> given;
            ASSERT_EQUAL(given, color(0xABU, 0xCDU, 0x01U));
        }
        {
            std::stringstream stream("      #ABCD01");
            color given;
            stream >> given;
            ASSERT_EQUAL(given, color(0xABU, 0xCDU, 0x01U));
        }
        {
            std::stringstream stream("#ABCD01           \n  123912 faasd asdjn a");
            color given;
            stream >> given;
            ASSERT_EQUAL(given, color(0xABU, 0xCDU, 0x01U));
        }
        {
            std::stringstream stream("\n#ABCD01 faasd asdjn a");
            color given;
            stream >> given;
            ASSERT_EQUAL(given, color(0xABU, 0xCDU, 0x01U));
        }
    }
    //wrong formats
    {
        auto exception_handler = [](const std::string& input)
            {
                std::stringstream stream(input);
                std::string result = "";
                std::string expected = "Wrong color format: " + input;
                try
                {
                    color given;
                    stream >> given;
                }
                catch (std::exception& e) {
                    result = e.what();
                }
                return expected==result;
            };

        //too small color format
        ASSERT(exception_handler("#ABCDE"));

        //junk before
        ASSERT(exception_handler("1203j19unf1ufnda#ABCDEF"));

        //junk after
        ASSERT(exception_handler("#ABCDEFmgig130gm1-9032"));

        //junk inside
        ASSERT(exception_handler("#ABCkm1g2029me12DEF"));

        //inaceesible letter
        ASSERT(exception_handler("#0011FG"));

    }
}

//testing comparison of colors
void TestColorComparison()
{
    color lhs(0x000000), rhs(0x000001);
    ASSERT(lhs<rhs);
    ASSERT(lhs<=rhs);
    ASSERT(lhs!=rhs);
    ASSERT(!(lhs==rhs));
    ASSERT(!(lhs>rhs));
    ASSERT(!(lhs>=rhs));

    ASSERT(lhs==lhs);
    ASSERT(rhs==rhs);
}

//construction hasEmptyPortal
void TestPlanetBasic()
{
    //with simple planet
    {
        planet data("SomeString", 0x110022, 4, planet::TYPE::EARTH);
        ASSERT_EQUAL(data.name(), "SomeString");
        ASSERT_EQUAL(data.Color(), color(0x11, 0x00, 0x22));
        ASSERT_EQUAL(data.empty_portals_count(), 4U);

        std::vector<std::int32_t> expected = {-1, -1, -1, -1};
        ASSERT_EQUAL(data.portals(), expected);
        ASSERT(data.hasEmptyPortal());
    }

    //with zero portals
    {
        planet data("AAA-1234", {123}, 0, planet::TYPE::MOON);
        ASSERT_EQUAL(data.name(), "AAA-1234");
        ASSERT_EQUAL(data.Color(), color(123));
        ASSERT_EQUAL(data.empty_portals_count(), 0U);
        ASSERT_EQUAL(data.empty_portals_count(), data.portals().size());
        ASSERT(!(data.hasEmptyPortal()));
    }

}


int main()
{
    TestRunner tr;

    // Testing Color
    RUN_TEST(tr, TestColorBasic);
    RUN_TEST(tr, TestColorInput);
    RUN_TEST(tr, TestColorComparison);

    // Testing Planets
    RUN_TEST(tr, TestPlanetBasic);
}
