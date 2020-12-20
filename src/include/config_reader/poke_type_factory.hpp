// #include <iostream>
// #include <map>
// #include <string>

// #include "../pokemon/poke_type.hpp"

// using namespace poketypes;

// // namespace factories
// // {
// struct PokemonTypeFactory
// {
//     static PokemonTypeVariant getPokemonType(std::string type)
//     {
//         if (type == "ElectricPokemonType")
//         {
//             return poketypes::ElectricPokemonType();
//         }
//         else if (type == "WaterPokemonType")
//         {
//             return poketypes::WaterPokemonType();
//         }
//         else
//         {
//             return poketypes::WaterPokemonType();
//         }
//     };
// };
// // } // namespace factories

// // template <typename T>
// // poketypes::PokemonTypeVariant *createPokemonType() { return new T; }

// // struct BaseFactory
// // {
// //     typedef std::map<std::string, poketypes::PokemonTypeVariant *(*)()> map_type;

// //     static poketypes::PokemonTypeVariant *createInstance(std::string const &s)
// //     {
// //         map_type::iterator it = getMap()->find(s);
// //         if (it == getMap()->end())
// //             return 0;
// //         return it->second();
// //     }

// // protected:
// //     static map_type *getMap()
// //     {
// //         // never delete'ed. (exist until program termination)
// //         // because we can't guarantee correct destruction order
// //         if (!map)
// //         {
// //             map = new map_type;
// //         }
// //         return map;
// //     }

// // private:
// //     static map_type *map;
// // };

// // template <typename T>
// // struct DerivedRegister : BaseFactory
// // {
// //     DerivedRegister(std::string const &s)
// //     {
// //         getMap()->insert(std::make_pair(s, &createPokemonType<T>));
// //     }
// // };