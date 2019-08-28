cmake_minimum_required(VERSION 3.12)
project(IMUtest)

set(BUILD_DIR .)
message(${BUILD_DIR})

set(CMAKE_C_STANDARD 99)

include_directories(./Timer)
include_directories(./CNS_MGS_160S)
include_directories(./CAN)
include_directories(./CNS_RFID_1S)
include_directories(./FD123_CA_000)
include_directories(./HC_SuK043_C)
include_directories(./SPC_SDIO_1616)
include_directories(./UART)
include_directories(./FD123_CA_000)
include_directories(./HC_SuK043_C)




add_executable(IMUtest main.c ./HC_SuK043_C/HC_SuK043_C.c ./FD123_CA_000/FD123_CA_000.c ./CNS_MGS_160S/CNS_MGS_160S.c ./CNS_RFID_1S/CNS_RFID_1S.c ./UART/UART.c ./CAN/can.c ./FD123_CA_000/FD123_CA_000.c ./HC_SuK043_C/HC_SuK043_C.c ./SPC_SDIO_1616/SPC_SDIO_1616.c ./Timer/Timer.c)

target_link_libraries(IMUtest pthread m rt)

#add_custom_target(IMUtest COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
