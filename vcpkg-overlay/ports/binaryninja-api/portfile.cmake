vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO ekilmer/binaryninja-api
    # cmake-refactor branch
    REF 0f1a7583fc7c63ee00b3741f4bc6a3bb177aea68
    SHA512 fa45615892b92eefe2ccc76411fc192ca8f3aae58e6e3ba4bdd4e9e8c6198fd0ecd66c790e62f0012a2fec11eae8b8dffd46ab9944ece242af3ae4cf4594607b
    HEAD_REF dev
)

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    INVERTED_FEATURES
        ui BinaryNinjaAPI_HEADLESS
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        ${FEATURE_OPTIONS}
        -DBinaryNinjaAPI_INSTALL_CMAKEDIR=share/BinaryNinjaAPI
        -DBinaryNinjaAPI_BUILD_EXAMPLES=OFF
        -DBinaryNinjaAPI_EXTERNAL_DEPENDENCIES=ON
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME BinaryNinjaAPI)
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE.txt")
