cmake_minimum_required(VERSION 3.10)
project(MyProject)

option(IsThatDin "Build shared libraries" 1)

# Название исполняемого файла
set(TARGET main)

# Директории с исходниками и заголовками
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Сборка библиотеки


# Создаем исполняемый файл
add_executable(${TARGET} 
    ${SOURCE_DIR}/main.c
)


# Указываем директорию с заголовками для исполняемого файла
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)

# Для разделяемой библиотеки на некоторых системах нужно добавить RPATH
if(IsThatDin)
    # Настраиваем RPATH чтобы исполняемый файл мог найти библиотеку
    set_target_properties(${TARGET} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
    
    # Дополнительно выводим информацию о типе сборки
    message(STATUS "Building shared library (libFUNC.so/dylib/dll)")
    add_library(FUNC SHARED ${SOURCE_DIR}/func.c)
else()
    message(STATUS "Building static library (libFUNC.a/lib)")
    add_library(FUNC STATIC ${SOURCE_DIR}/func.c)
endif()

# Добавляем цель для запуска программы
add_custom_target(run
    COMMAND ${TARGET}
    DEPENDS ${TARGET}
)

# Указываем директорию с заголовками для библиотеки
target_include_directories(FUNC PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}
)


# Линкуем библиотеку к исполняемому файлу
target_link_libraries(${TARGET} 
    FUNC
)

