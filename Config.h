
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef NORECOIL_CONFIG_H
#define NORECOIL_CONFIG_H

namespace bpt = boost::property_tree;

typedef struct {
    std::string name;
    int shotCount;
    int shotInterval;
    bool isAutomatic;
    std::vector<std::pair<int, int>> recoilCoords;
} Weapon;

class Config {
private:
    const std::string MOVE_SMOOTHNESS_SERIALIZED_NAME = "moveSmoothness";
    const std::string WEAPONS_SERIALIZED_NAME = "weapons";
    const std::string WEAPON_NAME_SERIALIZED_NAME = "name";
    const std::string WEAPON_SHOT_COUNT_SERIALIZED_NAME = "shotCount";
    const std::string WEAPON_SHOT_INTERVAL_SERIALIZED_NAME = "shotInterval";
    const std::string WEAPON_IS_AUTOMATIC_SERIALIZED_NAME = "isAutomatic";
    const std::string WEAPON_RECOIL_COORDS_SERIALIZED_NAME = "recoilCoords";
    const std::string WEAPON_RECOIL_COORDS_X_SERIALIZED_NAME = "x";
    const std::string WEAPON_RECOIL_COORDS_Y_SERIALIZED_NAME = "y";
    const int DEFAULT_MOVE_SMOOTHNESS = 1;

    void initializeMoveSmoothness(bpt::ptree& root) {
        moveSmoothness = root.get<int>(MOVE_SMOOTHNESS_SERIALIZED_NAME, DEFAULT_MOVE_SMOOTHNESS);
    }

    void initializeWeapons(bpt::ptree& root) {
        for (bpt::ptree::value_type& weaponValueType : root.get_child(WEAPONS_SERIALIZED_NAME)) {
            std::cout << "New weapon start serialize" << std::endl;
            weapons.push_back(serializeWeapon(weaponValueType));
        }
    }

    Weapon serializeWeapon(bpt::ptree::value_type& valueType) {
        Weapon newWeapon;
        newWeapon.name = valueType.second.get<std::string>(WEAPON_NAME_SERIALIZED_NAME);
        std::cout << "New weapon " << newWeapon.name << std::endl;
        newWeapon.shotCount = valueType.second.get<int>(WEAPON_SHOT_COUNT_SERIALIZED_NAME);
        std::cout << "New weapon " << newWeapon.shotCount << std::endl;
        newWeapon.shotInterval = valueType.second.get<int>(WEAPON_SHOT_INTERVAL_SERIALIZED_NAME);
        std::cout << "New weapon " << newWeapon.shotInterval << std::endl;
        newWeapon.isAutomatic = valueType.second.get<bool>(WEAPON_IS_AUTOMATIC_SERIALIZED_NAME);
        std::cout << "New weapon " << newWeapon.isAutomatic << std::endl;
        newWeapon.recoilCoords = serializeWeaponRecoilCoords(valueType.second);
        return newWeapon;
    }

    std::vector<std::pair<int, int>> serializeWeaponRecoilCoords(bpt::ptree& root) {
        std::vector<std::pair<int, int>> newRecoilCoords;
        for (bpt::ptree::value_type& recoilCoordsValueType : root.get_child(WEAPON_RECOIL_COORDS_SERIALIZED_NAME)) {
            std::pair<int, int> singleCoords;
            singleCoords.first = recoilCoordsValueType.second.get<int>(WEAPON_RECOIL_COORDS_X_SERIALIZED_NAME);
            singleCoords.second = recoilCoordsValueType.second.get<int>(WEAPON_RECOIL_COORDS_Y_SERIALIZED_NAME);
            newRecoilCoords.push_back(singleCoords);
        }
        return newRecoilCoords;
    }

public:
    int moveSmoothness;
    std::vector<Weapon> weapons;

    explicit Config(const std::string& filename) {
        bpt::ptree root;
        bpt::read_json(filename, root);
        initializeMoveSmoothness(root);
        initializeWeapons(root);
    }
};

#endif //NORECOIL_CONFIG_H
