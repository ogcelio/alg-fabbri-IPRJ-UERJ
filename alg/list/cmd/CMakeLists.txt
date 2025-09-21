add_executable(linked_list-cmd linked_list-cmd.cpp)
add_executable(doubly_linked_list-cmd doubly_linked_list-cmd.cpp)
add_executable(circular_linked_list-cmd circular_linked_list-cmd.cpp)

target_link_libraries(linked_list-cmd list)
target_link_libraries(doubly_linked_list-cmd list)
target_link_libraries(circular_linked_list-cmd list)
