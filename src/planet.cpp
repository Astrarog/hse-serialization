#include "planet.hpp"

#include <tuple>


namespace hse
{

    std::pair<bool, planet::pool_t::iterator> planet::getEmptyPortalPostion()
    {
        planet::pool_t::iterator position;
        bool success = hasEmptyPortal();

        if(success)
        {
            position = __portals.end() - __empty_portals_count;
        }

        return std::make_pair(success, position);
    }

    bool bindWithPortal(planet& first, planet& second)
    {
        bool success = (first!=second);
        auto [success_first, position_first] = first.getEmptyPortalPostion();
        auto [success_second, position_second] = second.getEmptyPortalPostion();
        success &= success_first && success_second;
        if(success)
        {
            --first.__empty_portals_count;
            --second.__empty_portals_count;
            *position_first  = &second;
            *position_second = &first;
        }
        return success;
    }

    planet::planet(const std::string& name, const class color& _color, std::size_t count, TYPE type, planet* parent)
        : planet(name, _color, count+1, type)
    {
        assert(count+1 != 0);
        bool hasEmptyPortal = parent->hasEmptyPortal();
        if(!hasEmptyPortal)
        {
            throw std::logic_error("Can't create child planet. Parent has aleady occupied all they portals");
        }
        this->bindWithPortal(*parent);
    }

    std::string_view planet::getPlanetImage() const
    {
        switch (__type)
        {
        case TYPE::EARTH:
            return
     R"(                _-o#&&*''''?d:>b\_                   )""\n"
     R"(            _o/"`''  '',, dMF9MMMMMHo_               )""\n"
     R"(         .o&#'        `"MbHMMMMMMMMMMMHo.            )""\n"
     R"(       .o"" '         vodM*$&&HMMMMMMMMMM?.          )""\n"
     R"(      ,'              $M&ood,~'`(&##MMMMMMH\         )""\n"
     R"(     /               ,MMMMMMM#b?#bobMMMMHMMML        )""\n"
     R"(    &              ?MMMMMMMMMMMMMMMMM7MMM$R*Hk       )""\n"
     R"(   ?$.            :MMMMMMMMMMMMMMMMMMM/HMMM|`*L      )""\n"
     R"(  |               |MMMMMMMMMMMMMMMMMMMMbMH'   T,     )""\n"
     R"(  $H#:            `*MMMMMMMMMMMMMMMMMMMMb#}'  `?     )""\n"
     R"(  ]MMH#             ""*""""*#MMMMMMMMMMMMM'    -     )""\n"
     R"(  MMMMMb_                   |MMMMMMMMMMMP'     :     )""\n"
     R"(  HMMMMMMMHo                 `MMMMMMMMMT       .     )""\n"
     R"(  ?MMMMMMMMP                  9MMMMMMMM}       -     )""\n"
     R"(  -?MMMMMMM                  |MMMMMMMMM?,d-    '     )""\n"
     R"(   :|MMMMMM-                 `MMMMMMMT .M|.   :      )""\n"
     R"(    .9MMM[                    &MMMMM*' `'    .       )""\n"
     R"(     :9MMk                    `MMM#"        -        )""\n"
     R"(       &M}                     `          .-         )""\n"
     R"(        `&.                             .            )""\n"
     R"(          `~,   .                     ./             )""\n"
     R"(              . _                  .-                )""\n"
     R"(                '`--._,dd###pp=""'                   )""\n";
        case TYPE::MOON:
            return
         R"(           ___---___           )""\n"
         R"(        .--         --.        )""\n"
         R"(      ./   ()      .-. \.      )""\n"
         R"(     /   o    .   (   )  \     )""\n"
         R"(    / .            '-'    \    )""\n"
         R"(   | ()    .  O         .  |   )""\n"
         R"(  |                         |  )""\n"
         R"(  |    o           ()       |  )""\n"
         R"(  |       .--.          O   |  )""\n"
         R"(   | .   |    |            |   )""\n"
         R"(    \    `.__.'    o   .  /    )""\n"
         R"(     \                   /     )""\n"
         R"(      `\  o    ()      /'      )""\n"
         R"(        `--___   ___--'        )""\n"
         R"(              ---              )""\n";

        case TYPE::SATURN:
            return
        R"(                                             ___   )""\n"
        R"(                                          ,o88888  )""\n"
        R"(                                       ,o8888888'  )""\n"
        R"(                 ,:o:o:oooo.        ,8O88Pd8888"   )""\n"
        R"(             ,.::.::o:ooooOoOoO. ,oO8O8Pd888'"     )""\n"
        R"(           ,.:.::o:ooOoOoOO8O8OOo.8OOPd8O8O"       )""\n"
        R"(          , ..:.::o:ooOoOOOO8OOOOo.FdO8O8"         )""\n"
        R"(         , ..:.::o:ooOoOO8O888O8O,COCOO"           )""\n"
        R"(        , . ..:.::o:ooOoOOOO8OOOOCOCO"             )""\n"
        R"(         . ..:.::o:ooOoOoOO8O8OCCCC"o              )""\n"
        R"(            . ..:.::o:ooooOoCoCCC"o:o              )""\n"
        R"(            . ..:.::o:o:,cooooCo"oo:o:             )""\n"
        R"(         `   . . ..:.:cocoooo"'o:o:::'             )""\n"
        R"(         .`   . ..::ccccoc"'o:o:o:::'              )""\n"
        R"(        :.:.    ,c:cccc"':.:.:.:.:.'               )""\n"
        R"(      ..:.:"'`::::c:"'..:.:.:.:.:.'                )""\n"
        R"(    ...:.'.:.::::"'    . . . . .'                  )""\n"
        R"(   .. . ....:."' `   .  . . ''                     )""\n"
        R"( . . . ...."'                                      )""\n"
        R"( .. . ."'                                          )""\n"
        R"(.                                                  )""\n";

        case TYPE::MYSTERY:
            return
        R"(            +             +                  +   @          )""\n"
        R"(   |                *           o     +                .    )""\n"
        R"(  -O-    o               .               .          +       )""\n"
        R"(   |                    _,.-----.,_         o    |          )""\n"
        R"(           +    *    .-'.         .'-.          -O-         )""\n"
        R"(      *            .'.-'   .---.   `'.'.         |     *    )""\n"
        R"( .                /_.-'   /     \   .'-.\                   )""\n"
        R"(         ' -=*<  |-._.-  |   @   |   '-._|  >*=-    .     + )""\n"
        R"( -- )--           \`-.    \     /    .-'/                   )""\n"
        R"(       *     +     `.'.    '---'    .'.'    +       o       )""\n"
        R"(                  .  '-._         _.-'  .                   )""\n"
        R"(         |               `~~~~~~~`       - --===D       @   )""\n"
        R"(   o    -O-      *   .                  *        +          )""\n"
        R"(         |                      +         .            +    )""\n"
        R"(              .     @      o                        *       )""\n"
        R"(       o                          *          o           .  )""\n";
        case TYPE::DEATH:
            return "[[THERE SHOULD BE DEATH STAR HERE]]";
        }
        return "[[WE ARE IN TROUBLE COMMANDOR]]";
    }

}
