#include "planet.hpp"

#include <tuple>
#include <string_view>
#include <algorithm>



namespace hse
{

    planet::pool_t::iterator planet::getEmptyPortalPostion()
    {
        planet::pool_t::iterator position;
        position = std::find(__portals.begin(), __portals.end(), -1);
        return position;
    }

    void planet::makePortal(std::int32_t idx)
    {
        auto position = getEmptyPortalPostion();
        *position = idx;
        --__empty_portals_count;
    }

    bool bindWithPortal(planet& first, std::int32_t firts_idx, planet& second, std::int32_t second_idx)
    {
        bool success = (first!=second);
        auto success_first = first.hasEmptyPortal();
        auto success_second = second.hasEmptyPortal();
        success &= success_first && success_second;
        if(success)
        {
            first.makePortal(second_idx);
            second.makePortal(firts_idx);
        }
        return success;
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
		case TYPE::ASTEROID:
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
        case TYPE::MOON:
            return

        R"(                        .--------------.                        )""\n"
        R"(                   .---'  o        .    `---.                   )""\n"
        R"(                .-'    .    O  .         .   `-.                )""\n"
        R"(             .-'     @@@@@@       .             `-.             )""\n"
        R"(           .'@@   @@@@@@@@@@@       @@@@@@@   .    `.           )""\n"
        R"(         .'@@@  @@@@@@@@@@@@@@     @@@@@@@@@         `.         )""\n"
        R"(        /@@@  o @@@@@@@@@@@@@@     @@@@@@@@@     O     \        )""\n"
        R"(       /        @@@@@@@@@@@@@@  @   @@@@@@@@@ @@     .  \       )""\n"
        R"(      /@  o      @@@@@@@@@@@   .  @@  @@@@@@@@@@@     @@ \      )""\n"
        R"(     /@@@      .   @@@@@@ o       @  @@@@@@@@@@@@@ o @@@@ \     )""\n"
        R"(    /@@@@@                  @ .      @@@@@@@@@@@@@@  @@@@@ \    )""\n"
        R"(    |@@@@@    O    `.-./  .        .  @@@@@@@@@@@@@   @@@  |    )""\n"
        R"(   / @@@@@        --`-'       o        @@@@@@@@@@@ @@@    . \   )""\n"
        R"(   |@ @@@@ .  @  @    `    @            @@      . @@@@@@    |   )""\n"
        R"(   |   @@                         o    @@   .     @@@@@@    |   )""\n"
        R"(   |  .     @   @ @       o              @@   o   @@@@@@.   |   )""\n"
        R"(   \     @    @       @       .-.       @@@@       @@@      /   )""\n"
        R"(    |  @    @  @              `-'     . @@@@     .    .    |    )""\n"
        R"(    \ .  o       @  @@@@  .              @@  .           . /    )""\n"
        R"(     \      @@@    @@@@@@       .                   o     /     )""\n"
        R"(      \    @@@@@   @@\@@    /        O          .        /      )""\n"
        R"(       \ o  @@@       \ \  /  __        .   .     .--.  /       )""\n"
        R"(        \      .     . \.-.---                   `--'  /        )""\n"
        R"(         `.             `-'      .                   .'         )""\n"
        R"(           `.    o     / | `           O     .     .'           )""\n"
        R"(             `-.      /  |        o             .-'             )""\n"
        R"(                `-.          .         .     .-'                )""\n"
        R"(                   `---.        .       .---'                   )""\n"
        R"(                        `--------------'                        )""\n";

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
            return    
        R"(                              88OOOOOCCCCCCCCOO8                              )""\n"
		R"(                        8OOOCCooooCooCoCooCoCoCooCoCO8                        )""\n"
		R"(                    8OOOCoCoCooCoCoCoCoCoCoooCCoCoooCoCCC8                    )""\n"
		R"(                 8OOCoCooCooCCoCooCoCoCoCooCoCooooCoCoCoCoCo8	             )""\n"
		R"(               OOCoCooCooCooCoCoooCoCoCooCoCoCooooCoooCoooooooC               )""\n"
		R"(             OOCoCooo.       .  .CoCoCoCoCoCooCoooCoCoCoooooooooC             )""\n"
		R"(           OOCCooo          .     :CoooCoCooCoCoCoCoCCoocooccoo:ooC           )""\n"
		R"(         OOOooCo   .        .      :CCoooCoCoCooCoCoCoCCooooCooooooC8         )""\n"
		R"(        OOCoCoc          oOOo      cCoCoCCooCoCooocoocooccccco:cccoo:o        )""\n"
		R"(       OOCoCCo         .OOOOO      CoCooCoCoCoCooCooCoCoooccoccoc:cc:oc       )""\n"
		R"(     8OOoCoCo:.   .  . .:cc       coCoCoCoCCooooooooooCcooococcocco:co::      )""\n"
		R"(     OOooCooCc.   .       .     :oCoCoCooCooooCocooccocccc:cc:ccccc:cc:oc     )""\n"
		R"(    OOoooCoCoC:  . . .    .   .oCoCoCoCooCooooooooooooCoooooccoc:oc:cc.o:c    )""\n"
		R"(   OOCoCoCoooCoC:. .     . :CoCoCoCooCcoooooocoocccccccoccccccc:cc:cc.:c.:8   )""\n"
		R"(   OO:coCoooCCoCoCooCoCooCoCooCoCoooCooooooCoCooooccoccoc:oc:co:cc:cc:cc:cc   )""\n"
		R"(  8OCooCc::cCoCooCoCooCoCooCoCooCooCooccCcoCcooccCccCcco:co::c::c..::.:..c:8  )""\n"
		R"(  OOooCooCoooc::cooCooCoCooCooCCCoooocooococcoc:oc:oc:occcc:coccc:cc.:c.:c.C  )""\n"
		R"(  OCCooCoCoCoCoooocc:ccCoCoCoCoCoCCooooCoooCoCococco:.o:.o:.c::c:.c:.c:.c..C  )""\n"
		R"(  OCCoCoooCoooCoCoCoooCocc::ccoooococcoocooccccoc:ccccc:co.:c.:c..c:.:.::..C  )""\n"
		R"(  OCoCoooCoooCoCoooCooCooooooCoocc:::cccoCccoc:oc:cc:cc:cc:oc.cc.cc.c: :: .C  )""\n"
		R"(  OoooCoooCoooCooCoCoCoCoooccoccCcooccoccoc:c:::::::c:.:::.c:.::.c..:.:::.:C  )""\n"
		R"(  8ooCoooCoooCooCCoCoCooCooooooCccoccoc:cc:cc:oc:cc:cc:cc:cc.:c:.c:........8  )""\n"
		R"(   oooCoooCoCoCoCoCoooooooooooooooCooCccoccC::o:.c:.c..:..c..:.:::.:.... ..   )""\n"
		R"(   OooCoCoCoCooooooooCococcoc:oc:cc:oc:oc:co:cc:cc::c.:c..:..c..c..:..:.::C   )""\n"
		R"(    CoCooCooCooCoooCoCooooooCoCococcoc:oc.oc:cc.c::c:.c:.:: :. .         :    )""\n"
		R"(    OoCoCoooCooocoocooccocoo:oocco:ccccc:cc.:c..c..c.:c:.c.:::.::.:. :. :     )""\n"
		R"(     OoCoooCoooCooCoCoooccCccocccc:cc:oc:oc:oc:cc.cc :: .: .. .. .. .  .      )""\n"
		R"(      OooocoooCoooocCccCccCcoCccC::o::c:.c..::.::.:..:..:..:. :. ..           )""\n"
		R"(       8ooooooccoccoo:ccccc:cc:cc:cc:oc:cc:cc..c..c..:.::..: :: .: ...        )""\n"
		R"(         CCCooCooCoCoooococ:oc.oc.o:.c:.c:.:..c:.:. :. ..           o         )""\n"
		R"(          8:oo:oo:co:cc:cc:cccco.cc.:c::c..:..c:.::.:..:..:. :. ...           )""\n"
		R"(            Oococcoccoc:coccc:oc:cc:o:.c: c: :. .. .     .      .O            )""\n"
		R"(              8occocco:co.cc.:c..::.c..c..:..c.::..:. ..  .  .:8              )""\n"
		R"(                 Cc:ccccc:cc:cc:co.:c.::..:..:..: :. .. .. .C                 )""\n"
		R"(                    C:.c:.c::c:.c.::..c..:.... ..        o                    )""\n"
		R"(                        8occ::c:.::.:::::.:.::.::..:. C                       )""\n"
		R"(                            CCc:.:..... . .. :oO                              )""\n";
        }
        return "[[WE ARE IN TROUBLE COMMANDOR]]";
    }

}
