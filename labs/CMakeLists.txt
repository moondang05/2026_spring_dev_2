file(GLOB LAB_SUBDIRS CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "q*" "c*" "r*")

# 랩 폴더용 기본 cXX main.cpp 내용
set(AUTO_MAIN_CPP_CONTENT "#include <iostream>
using namespace std;
int main() {
    return 0;
}
")

# 랩 폴더용 기본 qXX main.cpp 내용
set(AUTO_Q_MAIN_CPP_CONTENT "#include <iostream>
#include \"module.h\"

using namespace std;

int main() {
    return 0;
}
")

set(AUTO_Q_MODULE_H_CONTENT "#ifndef MODULE_H
#define MODULE_H

void update();

#endif // MODULE_H
")

set(AUTO_Q_MODULE_CPP_CONTENT "#include \"module.h\"

void update() {
    
}
")

# 랩 폴더용 기본 rXX 파일 내용
set(AUTO_R_MAIN_CPP_CONTENT "#include <iostream>
#include \"module1.h\"
#include \"module2.h\"

using namespace std;

int main() {
    return 0;
}
")

set(AUTO_R_MODULE1_H_CONTENT "#ifndef MODULE1_H
#define MODULE1_H

void update1();

#endif // MODULE1_H
")

set(AUTO_R_MODULE1_CPP_CONTENT "#include \"module1.h\"

void update1() {
    
}
")

set(AUTO_R_MODULE2_H_CONTENT "#ifndef MODULE2_H
#define MODULE2_H

void update2();

#endif // MODULE2_H
")

set(AUTO_R_MODULE2_CPP_CONTENT "#include \"module2.h\"

void update2() {
    
}
")

# 랩 폴더용 기본 CMakeLists.txt 내용
set(AUTO_CMAKELISTS_CONTENT "# Generic lab CMakeLists.txt
get_filename_component(_LAB_DIR \"\${CMAKE_CURRENT_SOURCE_DIR}\" NAME)
set(_TARGET \"lab_\${_LAB_DIR}\")

file(GLOB _SOURCES CONFIGURE_DEPENDS
    \"\${CMAKE_CURRENT_SOURCE_DIR}/*.c\"
    \"\${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\"
)

if(NOT _SOURCES)
    message(WARNING \"[\${_TARGET}] No source files found -- skipping\")
    return()
endif()

add_executable(\${_TARGET} \${_SOURCES})
target_include_directories(\${_TARGET} PRIVATE \"\${CMAKE_CURRENT_SOURCE_DIR}\")

# Enforce C99 for C sources in this lab.
set_target_properties(\${_TARGET} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
")

foreach(lab_dir IN LISTS LAB_SUBDIRS)
    set(lab_dir_path "${CMAKE_CURRENT_SOURCE_DIR}/${lab_dir}")
    set(lab_cmake "${lab_dir_path}/CMakeLists.txt")
    
    if(IS_DIRECTORY "${lab_dir_path}")
        # 폴더 안에 CMakeLists.txt가 없다면 자동으로 생성
        if(NOT EXISTS "${lab_cmake}")
            message(STATUS "Auto-generating CMakeLists.txt for ${lab_dir}")     
            file(WRITE "${lab_cmake}" "${AUTO_CMAKELISTS_CONTENT}")
        endif()
        
        # 폴더 안에 소스 파일(*.c, *.cpp)이 없다면 파일들을 자동 생성
        file(GLOB existing_sources "${lab_dir_path}/*.c" "${lab_dir_path}/*.cpp")
        if(NOT existing_sources)
            if("${lab_dir}" MATCHES "^q")
                set(lab_main_cpp "${lab_dir_path}/main.cpp")
                set(lab_module_cpp "${lab_dir_path}/module.cpp")
                set(lab_module_h "${lab_dir_path}/module.h")
                
                message(STATUS "Auto-generating main.cpp, module.cpp, module.h for ${lab_dir}")
                file(WRITE "${lab_main_cpp}" "${AUTO_Q_MAIN_CPP_CONTENT}")
                file(WRITE "${lab_module_cpp}" "${AUTO_Q_MODULE_CPP_CONTENT}")
                file(WRITE "${lab_module_h}" "${AUTO_Q_MODULE_H_CONTENT}")
            elseif("${lab_dir}" MATCHES "^r")
                set(lab_main_cpp "${lab_dir_path}/main.cpp")
                set(lab_module1_cpp "${lab_dir_path}/module1.cpp")
                set(lab_module1_h "${lab_dir_path}/module1.h")
                set(lab_module2_cpp "${lab_dir_path}/module2.cpp")
                set(lab_module2_h "${lab_dir_path}/module2.h")
                
                message(STATUS "Auto-generating main.cpp, module1.cpp, module1.h, module2.cpp, module2.h for ${lab_dir}")
                file(WRITE "${lab_main_cpp}" "${AUTO_R_MAIN_CPP_CONTENT}")
                file(WRITE "${lab_module1_cpp}" "${AUTO_R_MODULE1_CPP_CONTENT}")
                file(WRITE "${lab_module1_h}" "${AUTO_R_MODULE1_H_CONTENT}")
                file(WRITE "${lab_module2_cpp}" "${AUTO_R_MODULE2_CPP_CONTENT}")
                file(WRITE "${lab_module2_h}" "${AUTO_R_MODULE2_H_CONTENT}")
            else()
                set(lab_main_cpp "${lab_dir_path}/main.cpp")
                message(STATUS "Auto-generating main.cpp for ${lab_dir}")
                file(WRITE "${lab_main_cpp}" "${AUTO_MAIN_CPP_CONTENT}")
            endif()
        endif()

        add_subdirectory("${lab_dir}")
    endif()
endforeach()
