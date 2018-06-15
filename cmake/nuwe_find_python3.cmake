function(nuwe_find_python3)
    if(Python3_ROOT_DIR)
        find_program(Python3_EXECUTABLE 
            NAMES python3 python
            NAMES_PER_DIR
            HINTS ${Python3_ROOT_DIR}
            PATH_SUFFIXES Scripts
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
            )
        if(Python3_EXECUTABLE)
            message(STATUS "Found python3 executable in " ${Python3_EXECUTABLE})
        else()
            message(FATAL_ERROR "Please set python3 dir using Python3_ROOT_DIR.")
        endif()
    endif()
endfunction()

function(nuwe_check_python3_library)
    if(NOT Python3_EXECUTABLE)
        message(STATUS "Python3_EXECUTABLE is not found.")
        return()
    endif()
    execute_process(COMMAND "${Python3_EXECUTABLE}" "-c"
        "import paramiko; print(paramiko.__version__);"
        RESULT_VARIABLE _PARAMIKO_SERCH_SUCCESS
        OUTPUT_VARIABLE _PARAMIKO_SALUES_OUTPUT
        ERROR_VARIABLE _PARAMIKO_ERROR_VALUE
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT _PARAMIKO_SERCH_SUCCESS MATCHES 0)
        message(FATAL_ERROR "Paramiko import failure:\n${_PARAMIKO_ERROR_VALUE}")
        set(PARAMIKO_FOUND FALSE)
    else()
        set(PARAMIKO_FOUND TRUE)
    endif()
endfunction()
